
#include <fstream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <initializer_list>

#include "../strlib/strlib.h"

namespace foam
{
	namespace streams
	{
		namespace details
		{
			template<typename T>
			struct iterator_traits
			{
				typedef std::istream_iterator<T> iterator;
				typedef const std::istream_iterator<T> const_iterator;
			};

			template<>
			struct iterator_traits<char>
			{
				typedef std::istreambuf_iterator<char> iterator;
				typedef const std::istreambuf_iterator<char> const_iterator;
			};

			template<>
			struct iterator_traits<wchar_t>
			{
				typedef std::istreambuf_iterator<wchar_t> iterator;
				typedef const std::istreambuf_iterator<wchar_t> const_iterator;
			};
		}

		template<typename T>
		class istream_reader
		{
			public:
		
				typedef T value_type;
				typedef typename details::iterator_traits<T>::iterator iterator;
				typedef typename details::iterator_traits<T>::const_iterator const_iterator;

				istream_reader(std::string const & file) 
					: m_openedStream(new std::ifstream(file)), m_refStream(*m_openedStream)
				{
					if ( !m_refStream ) 
					{
						auto msg = "snl::streams::istream_reader(std::string const &)";
					       	throw std::runtime_error(msg + foam::strlib::format(" could not open file \"{0}\".", file));
					}
				}
				istream_reader(std::istream & instream) :  m_refStream(instream)
				{
					if ( !m_refStream )
					{
						throw std::runtime_error("bad input stream is passed to snl::streams::istream_reader(std::istream &).");
					}
				}

				const_iterator begin() const
				{
					if ( !m_reset )
					{
						throw std::logic_error("cannot begin() without reset().");
					}
					auto & s = const_cast<std::istream&>(m_refStream);
					s.clear();
					s.seekg(0, std::istream::beg);
					m_begin = iterator(s);
					m_reset  = false;
					return m_begin;
				}
				const_iterator end() const { return m_end; }
		
				void reset() { m_reset = true; }

				class taker
				{
					friend class istream_reader;
					iterator & m_begin;
					size_t m_n;					
					taker(iterator & begin, size_t n) : m_begin(begin), m_n(n){}
				public:
					template<typename C>
					operator C() {
						C c;
						c.reserve(m_n);
						iterator end;
						size_t i = m_n;
						while ( i && m_begin != end )
						{
							std::cout << "reading " << *m_begin << std::endl;
							c.push_back(*m_begin);
							++m_begin;
							--i;
						}
						if ( i )
						{
							throw std::runtime_error("failure reading data from stream.");
						}
						return c;
					}
				};

				taker take(size_t n)
				{
					if ( m_reset ) 
						begin();
					return {m_begin, n};
				}
	
			private:
				std::unique_ptr<std::istream> m_openedStream;
				std::istream & m_refStream;
				mutable iterator m_begin;
				iterator m_end;	
				mutable bool m_reset = true;
		};

	}
}

