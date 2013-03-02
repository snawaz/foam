

#pragma once

namespace foam
{
	namespace pipeline
	{
		template< template <typename,typename> class PipeClassTemplate, typename UnaryFunctor>
		struct pipe_builder
		{
			UnaryFunctor _functor;
			
			template<typename Pipe>
			auto operator()(Pipe pipe) -> PipeClassTemplate<Pipe, UnaryFunctor>
			{
				return {pipe, _functor};
			}
		};
	}
}
