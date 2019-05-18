//This source code is under the MIT License, see LICENSE.txt.
#pragma once
#include<iostream>
#include<vector>
#include<array>
#include<tuple>
#include<utility>
#include<set>
#include<type_traits>
#include<fstream>
#include<boost/optional/optional_io.hpp>
#include<boost/multi_array.hpp>
#include"grobal_object.hpp"
#include"type_traits.hpp"

namespace debug::print
{
	namespace detail
	{
		void write(std::ostream&);

		template<class T>auto ostream_check_i(T const& v)
			->true_t<decltype(std::declval<std::ostream>() << v)>;
		std::false_type ostream_check_i(...);
		template<class T>constexpr bool ostream_check_v = decltype(ostream_check_i(std::declval<T>()))::value;

		template<class T>auto iterator_check_i(T const& v)
			->true_t<decltype((std::begin(v) != std::end(v)), *std::begin(v), ++std::begin(v))>;
		std::false_type iterator_check_i(...);
		template<class T>constexpr bool iterator_check_v = decltype(iterator_check_i(std::declval<T>()))::value;

		template<class T>auto tuple_check_i(T const&)
			->true_t<decltype(std::tuple_size<T>::value)>;
		std::false_type tuple_check_i(...);
		template<class T>constexpr bool tuple_check_v = decltype(tuple_check_i(std::declval<T>()))::value;

		template<class>struct is_dual_array :std::false_type
		{

		};
		template<class T>struct is_dual_array<boost::multi_array<T, 2>> :std::true_type
		{

		};
		template<class T>constexpr bool is_dual_array_v = is_dual_array<T>::value;
		
		template<class T, std::size_t... Is>void write_tuple(std::ostream&, T const&, std::index_sequence<Is...>);
		template<class T>void write_dual_array(std::ostream& os, boost::multi_array<T, 2>const& ar);

		template<class T, class... Ts>void write(std::ostream& os, T const& v, Ts const& ... vs)
		{
			if constexpr (sizeof...(Ts) != 0)
			{
				write(os, v);
				os << " ";
				write(os, vs...);
			}
			else if constexpr (tuple_check_v<T>)
			{
				write_tuple(os, v, std::make_index_sequence<std::tuple_size<T>::value>());
			}
			else if constexpr (is_dual_array_v<T>)
			{
				write_dual_array(os, v);
			}
			else if constexpr (ostream_check_v<T>)
			{
				os << v;
			}
			else if constexpr (iterator_check_v<T>)
			{
				auto ite = std::begin(v);
				auto end = std::end(v);
				if (ite != end)
				{
					write(os, *ite);
					for (++ite; ite != end; ++ite)
					{
						os << " ";
						write(os, *ite);
					}
				}
			}
			else
			{
				static_assert(false_t<T>::value, "this type is not support by debug print functions");
			}
		}
		template<class T, std::size_t... Is>void write_tuple(std::ostream& os, T const& v, std::index_sequence<Is...>)
		{
			write(os, std::get<Is>(v)...);
		}
		template<class T>void write_dual_array(std::ostream& os, boost::multi_array<T, 2>const& ar)
		{
			auto ite = std::begin(ar);
			auto end = std::end(ar);
			if (ite != end)
			{
				write(os, *ite);
				for (++ite; ite != end; ++ite)
				{
					os << std::endl;
					write(os, *ite);
				}
			}
		}
	}
	template<class... Ts>void write(Ts const& ... vs)
	{
		detail::write(debug::detail::obj.ofs, vs...);
	}
	template<class... Ts>void write_line(Ts const& ... vs)
	{
		write(vs...);
		debug::detail::obj.ofs << std::endl;
	}
	template<class... Ts>void message(Ts const& ... vs)
	{
		detail::write(std::cerr, vs...);
		std::cerr << std::endl;
	}
}