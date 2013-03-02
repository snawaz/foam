

#pragma once

#include <stdexcept>
#include <type_traits>
#include <utility>

#include "alias.h"


namespace foam
{

	template<typename T>
	class optional
	{
		public:
			typedef T value_type;
			typedef alias::aligned_storage<T> storage_type;

			optional() : _valid(false) {}

			explicit optional(T value) :  _valid(true) 
			{
				new (&_storage) T(std::move(value));
			}

			~optional()
			{
				if ( has_value() )  value().~T();
			}

			optional(optional const & other) : _valid(other._valid) 
			{
				if ( _valid )
				{
					copy(*this, other);
				}
			}

			optional(optional && other) : _valid(other._valid) 
			{
				if ( _valid )
				{
					move(*this, other);
				}
			}

			optional& operator=(optional const & other) 
			{
				if ( has_value() )
				{
					value().~T();
				}
				_valid = other._valid;
				if ( _valid )
				{
					copy(*this, other);
				}
				return *this;
			}

			optional& operator=(optional && other)
			{
				if ( has_value() )
				{
					value().~T();
				}
				_valid = other._valid;
				if ( _valid )
				{
					move(*this, other);
				}
				return *this;
			}

			bool has_value() const { return _valid; }

			T & value()
			{ 
				return const_cast<T&>(static_cast<optional<T> const &>(*this).value());
			}

			T const & value() const 
			{ 
				if ( !has_value() )
				{
					throw std::logic_error("optional<T> doesn't have value.");
				}
				return *reinterpret_cast<T const*>(&_storage);
			}
			
			bool operator==(optional const & other) const
			{
				if ( has_value() && other.has_value() )
				       return value() == other.value();
				return !has_value() && !other.has_value();
			}

			bool operator!=(optional const & other) const
			{
				return !(*this == other);
			}

		private:

			void copy(optional<T> & dst, optional<T> const & src) const
			{
				new (&dst._storage) T(src.value());
			}

			void move(optional<T> & dst, optional<T> const & src) const
			{
				new (&dst._storage) T(std::move(const_cast<T&>(src.value())));
			}

		private:

			bool _valid;

			storage_type _storage;
	};
}
