

#pragma once

#include <vector>
#include <iterator>


namespace snl
{
	template<typename T>
	class range 
	{
		public:
			class iterator : public std::iterator<std::input_iterator_tag, T, std::ptrdiff_t, T const*, T const&>
			{
				friend class range<T>;
				
				public:
				
					T operator *() const 
				      	{ 
						return i_; 
				      	}
					const iterator & operator++() 	
				      	{ 
						++i_; 
						return *this; 
					}
					iterator operator++(int) 
					{ 
						iterator copy(*this); 
						++i_; 
						return copy; 
					}
					bool operator ==(const iterator &other) const 
					{
						return i_ == other.i_; 
					}
					bool operator !=(const iterator &other) const 
					{
						return i_ != other.i_; 
					}
					
				protected:
			      	
					iterator(T start) : i_ (start) { }
				
				private:
			      		T i_;
			};

			iterator begin() const { return begin_; }
			iterator end() const { return end_; }
			range(T  begin, T end) : begin_(begin), end_(end) {}
		private:
			iterator begin_;
			iterator end_;
	};

	template<typename T>
	range<T> make_range(T start, size_t count)
	{
		return range<T>(start, start + count);
	}

	template<typename T>
	std::vector<T> to_vector(range<T> const & r)
	{
		return std::vector<T>(r.begin(), r.end());
	}
}
