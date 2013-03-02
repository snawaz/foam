
#pragma once

#include <vector>
#include <map>
#include <array>
#include <functional>
#include <stdexcept>

#include "../meta/typelist.hpp"
#include "../noncopyable.hpp"
#include "../strlib/strlib.hpp"
#include "../algorithms/algorithm.hpp"

namespace snl
{
	namespace functional
	{
		namespace details
		{
			
		}
		struct bad_function : std::domain_error
		{
			bad_function(std::string const & message) : std::domain_error(message) {}
		};
		
		struct bad_remover : std::domain_error
		{
			bad_remover(std::string const & message) : std::domain_error(message) {}
		};
		
		template<typename Signature>
		class multifunction;
		
		template<typename Signature>
		class remover : public noncopyable
		{
			enum object_status
			{
				moved_none,
				moved_remover,
				moved_multifunction,
				moved_both,
				function_removed
			};
			public:
				void operator()()
				{
					switch(m_status)
					{
						case function_removed:
							{
								throw bad_remover("Cannot remove function. It is already removed.");
							}
						case moved_none:
							{
								auto it = m_this->m_functors.find(m_key);
								if ( it != m_this->m_functors.end() )
								{
									m_this->m_functors.erase(it);
									m_status = function_removed;
								}
								else
								{
									throw bad_remover("Cannot remove function. The multifunction has been moved.");
								}
							}
							break;
						case moved_remover:
							{
								throw bad_remover("Cannot remove function. snl::functional::remover has been moved.");
							}
							break;
						case moved_multifunction:
							{
								throw bad_remover("Cannot remove function. snl::functional::multifunction has been moved.");
							}
							break;
						case moved_both:
							{
								snl::strlib::string_builder sb("Cannot remove function.");
								sb.write("snl::functional::multifunction and snl::functional::remover has been moved.");
								throw bad_remover(sb);
							}
							break;
					}
				}
				remover(remover && other) 
					: m_this(other.m_this), m_key(other.m_key), m_status(other.m_status)
				{
					other.m_key = -2;
					other.m_status = moved_remover;
				}
				remover const & operator=(remover && other) 
				{
					m_this  = other.m_this;
					m_key = other.m_key; 
					m_status = other.m_status;

					other.m_key = -2;
					other.m_status = moved_remover;
					return *this;
				}

			private:
				remover(multifunction<Signature> *ref, int key) 
				: m_this(ref), m_key(key), m_status(moved_none) { }

				friend class multifunction<Signature>;
				int m_key;
				object_status m_status;
				multifunction<Signature> *m_this;
		};

		template<typename R, typename ...Args>
		class multifunction<R(Args...)> : noncopyable
		{
			public:
				typedef R signature_type(Args...);
				typedef R return_type;
				typedef snl::meta::typelist<Args...> argument_types;
				typedef remover<signature_type> remover_type;
				
				multifunction() : m_next_available_key(0) {}
				multifunction(multifunction && other) = default;
				multifunction& operator = (multifunction && other) = default;


				template<typename Functor>
				remover_type add(Functor f)
				{
					if ( !has_target(f) )
					{
						throw bad_function("std::function<> cannot be added to multifunction, as it has no target associated with it.");
					}
					m_functors[m_next_available_key] = f;
					return {this, m_next_available_key++};
				}

				template<typename ...Functors>
				auto add_many(Functors ... fs) -> std::array<remover_type,sizeof...(Functors)>  
				{
					return {{ add(fs) ... }};
				}

				void operator()(Args...args) const
				{
					for(auto && f : m_functors)
					{
						f.second(args...);
					}
				}

				explicit operator bool() const
				{
					return m_functors.size() != 0;
				}
			private:
				template<typename Signature>
				bool has_target(std::function<Signature> const & f) const
				{
					return static_cast<bool>(f);
				}
				template<typename Signature>
				bool has_target(Signature const & f) const
				{
					return true;
				}
			private:
				friend class remover<signature_type>;
				int m_next_available_key;
				std::map<int,std::function<R(Args...)>> m_functors;
				
		};

	} //functional
}//snl
