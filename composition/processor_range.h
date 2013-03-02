
#pragma once

#include <iterator>
#include <utility>
#include <type_traits>

#include "container_traits.h"
#include "range_iterator.h"
#include "iterator_wrapper.h"
#include "utility.h"
#include "../alias.h"

namespace foam
{
	namespace pipeline
	{
		template<typename Range, typename Predicate>
		class filter_range
		{
				typedef filter_range<Range, Predicate>                               self_type;
				typedef iterator_wrapper<alias::iterator<Range>, Predicate>          iiterator;
			public:
				typedef range_iterator<self_type, iiterator>                         iterator;
				typedef alias::value_type<Range>                                     value_type;

				filter_range(Range pipe, Predicate predicate) 
					: _range(pipe), _predicate(predicate) 
				{
				}

				iterator begin() 
				{
				       	return { this, ibegin() }; 
				}
				iterator end()  
				{ 
					return { this, iend() };   
				}
				template<typename PiplelineBuilder>
				auto operator | (PiplelineBuilder builder) -> decltype(std::declval<PiplelineBuilder>()(std::declval<self_type>()))
				{
					return builder(*this);
				}
			private:
				friend iterator;
				iiterator ibegin()
				{
					using std::begin;
					iiterator it = { begin(_range), _predicate };
					for(auto eop = iend(); it != eop && !predicate(it) ;  ++it);
					return it;
				}
				iiterator iend()
				{
					using std::end;
					return { end(_range), _predicate };
				}
				iiterator next (iiterator & it) 
				{
					auto eop = iend();
					for(++it; it != eop && !predicate(it) ; ++it);
					return it;
			       	}
				value_type value(iiterator & it)	
				{
					return *it;
				}
				bool predicate(iiterator & it)
				{
					return it.state(*it);
				}
			private:
				Range _range;
				Predicate _predicate;

		};

		template<typename Range, typename UnaryTransformer>
		class transform_range
		{
				typedef transform_range<Range, UnaryTransformer>   self_type;
				typedef alias::iterator<Range>                     iiterator;
			public:
				typedef range_iterator<self_type, iiterator>       iterator;
				typedef alias::type<call_result<UnaryTransformer,       
	 				alias::value_type<Range>>>                 value_type;  

				transform_range(Range pipe, UnaryTransformer transformer) 
					: _range(pipe), _transformer(transformer) 
				{
				}

				iterator begin() 
				{
				       	return { this, ibegin() }; 
				}
				iterator end()  
				{ 
					return { this, iend() };   
				}
				template<typename PipelineBuilder>
				auto operator | (PipelineBuilder builder) -> decltype(std::declval<PipelineBuilder>()(std::declval<self_type>()))
				{
					return builder(*this);
				}
			private:
				friend iterator;
				iiterator ibegin()
				{
					using std::begin;
					return begin(_range);
				}
				iiterator iend()
				{
					using std::end;
					return end(_range);
				}
				iiterator next (iiterator it) 
				{
					return ++it;
			       	}
				value_type value(iiterator it)	
				{
					return _transformer(*it);
				}
			private:
				Range _range;
				UnaryTransformer _transformer;

		};

		template<typename Range, typename Predicate>
		class take_range
		{
				typedef take_range<Range, Predicate>                                self_type;
				typedef iterator_wrapper<alias::iterator<Range>, Predicate>         iiterator;
			public:
				typedef range_iterator<self_type, iiterator>                        iterator;
			        typedef alias::value_type<Range>                                    value_type;

				take_range(Range pipe, Predicate predicate) 
					: _range(pipe), _predicate(predicate) 
				{
				}

				iterator begin() 
				{
				       	return { this, ibegin() };
				}
				iterator end()  
				{ 
					return { this, iend() };   
				}
				template<typename PiplelineBuilder>
				auto operator | (PiplelineBuilder builder) -> decltype(std::declval<PiplelineBuilder>()(std::declval<self_type>()))
				{
					return builder(*this);
				}
			private:
				friend iterator;
				iiterator ibegin()
				{
					using std::begin;
					iiterator it { begin(_range), _predicate };
					if ( it != iend() && apply_predicate(it)) //_predicate(*it)) 
						return it;
					return iend();
				}
				iiterator iend()
				{
					using std::end;
					return {end(_range), _predicate};
				}
				iiterator next (iiterator & it) 
				{
					++it;
					return it == iend() ? iend() : (apply_predicate(it) ? it : iend());
			       	}
				value_type value(iiterator & it)	
				{
					return *it;
				}
				bool apply_predicate(iiterator & it)
				{
					return it.state(*it);
				}
			private:
				Range _range;
				Predicate _predicate;

		};

		template<typename Range, typename Selector, typename Comparator>
		struct order_range
		{
				typedef order_range<Range, Selector, Comparator>                    self_type;
				typedef iterator_wrapper<alias::iterator<Range>, std::size_t>       iiterator;
			public:
				typedef range_iterator<self_type, iiterator>                        iterator;
				typedef alias::value_type<Range>                                    value_type;

				order_range(Range range, Selector selector, Comparator comparator)
					: _range(range), _selector(selector), _comparator(comparator) {}

				iterator begin() 
				{
				       	return { this, ibegin() };
				}
				iterator end()  
				{ 
					return { this, iend() };   
				}

				template<typename PiplelineBuilder>
				auto operator | (PiplelineBuilder builder) -> decltype(std::declval<PiplelineBuilder>()(std::declval<self_type>()))
				{
					return builder(*this);
				}

			private:
				friend iterator;

				iiterator ibegin()
				{
					using std::begin;
					using std::end;
					auto it = begin(_range);
					auto eor = end(_range);
					if ( it == eor )
						return {it, static_cast<std::size_t>(-1) };
					std::size_t i=0;
					iiterator curr {it, i};
					++it; 
					++i;
					while ( it != eor )
					{
						if ( compare (*it, *curr) ) //true means *it should come before *curr
						{
							if ( !same(*it, *curr) ) //if same, let the first appear before the second (i.e the repetition)
							{
								curr.value = it;
								curr.state = i;
							}
						}
						++it;
						++i;
					}
					return curr;
				}
				iiterator iend()
				{
					using std::end;
					auto it = end(_range);
					return {it, 0};
				}
				iiterator next(iiterator & curr) 
				{
					using std::begin;
					using std::end;
					auto it = begin(_range);
					auto eor = end(_range);	
					size_t i = 0;
					
					iiterator p = iend(); //potential iterator
					
					while ( it != eor )
					{
						if ( i == curr.state )
						{
							++it;
							++i;
							continue;
						}
						
						if ( same(*it, *curr) )
						{
							if ( i > curr.state )
							{
 								p.value = it;
     							        p.state = i;
 								break;
							}
							++it;
							++i;
							continue;
						}
						else if ( p == iend() )
						{
							if ( !compare ( *it, *curr ) ) //false means *it should come after *curr
							{
								p.value = it;
								p.state = i;
							}
						}
						else
						{
							if ( !compare ( *it, *curr ) ) //false means *it should come after *curr
							{
								if ( compare ( *it, *p ) ) //true means *it should come before *p
								{
									p.value = it;
									p.state = i;
								}
							}
						}
						++it;
						++i;
					}
					return p;
			       	}
				value_type value(iiterator & it)	
				{
					return *it;
				}
				bool compare(value_type const & a, value_type const & b)
				{
					return _comparator ( _selector(a), _selector(b) );
				}
				bool same(value_type const & a, value_type const & b)
				{
					bool x = compare(a,b);
					bool y = compare(b,a);
					return (x && y) || (!x && !y);
				}
			private:
				Range _range;
				Selector _selector;
				Comparator _comparator;

		};

		template<typename Range>
		struct reverse_range
		{
				typedef reverse_range<Range>                                        self_type;
				//typedef alias::iterator<Range>                                      iiterator;
				typedef iterator_wrapper<alias::iterator<Range>, std::size_t>       iiterator;
			public:
				typedef range_iterator<self_type, iiterator>                        iterator;
				typedef alias::value_type<Range>                                    value_type;

				reverse_range(Range range) : _range(range) {}

				iterator begin()
				{
					return {this, ibegin() };
				}
				iterator end()
				{
					return {this, iend() };
				}
				
				template<typename PiplelineBuilder>
				auto operator | (PiplelineBuilder builder) -> decltype(std::declval<PiplelineBuilder>()(std::declval<self_type>()))
				{
					return builder(*this);
				}
			private:
				friend iterator;

				iiterator ibegin()
				{
					using std::begin;
					using std::end;

					auto it = begin(_range);
					auto eor = end(_range);

					iiterator ret = iend();
					std::size_t i = 0;

					while ( it != eor ) 
					{
						ret.value = it;
						ret.state = i;
						++it;
						++i;
					}
					return ret;

				}
				iiterator iend()
				{
					using std::end;
					return { end(_range), 0 };
				}
				iiterator next(iiterator & curr)
				{
					if ( curr.state == 0 )
						return iend();

					using std::begin;
					auto it = begin(_range);
					for(std::size_t i = 0 ; i < (curr.state -1) ; ++i )
						++it;	
					return { it, curr.state - 1 };
				}
				value_type value(iiterator & it)
				{
					return *it;
				}
			private:
				Range _range;

		};

	}
}

