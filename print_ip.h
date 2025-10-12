#ifndef _SFINAE_H_
#define _SFINAE_H_

#include <cstdint>
#include <type_traits>
#include <iostream>
#include "utils.h"

template <typename Integer,
          typename std::enable_if<std::is_integral<Integer>::value == true, bool>::type = true>
void printIp(const Integer & input)
{
    // check all 1 byte types: char, int8_t, uint8_t
    if (sizeof(input) == 1 && !std::is_same<Integer, bool>::value)
        std::cout << +(static_cast<uint8_t>(input)) << std::endl;
    else if (std::is_same<Integer, int16_t>::value)
    {
        printIntegralBytes(&input, sizeof(input));
    }
    else if (std::is_same<Integer, int32_t>::value)
    {
        printIntegralBytes(&input, sizeof(input));
    }
    else
    {
        printIntegralBytes(&input, sizeof(input));
    }
};

template<typename ...>
using to_void = void;

template<typename T, typename = void>
struct is_container : std::false_type {};

template<typename T>
struct is_container<T,
        to_void<decltype(std::declval<T>().begin()),
                decltype(std::declval<T>().end()),
                typename T::value_type
        >> : std::true_type
{};

// prints vector, list, string
template <typename Container,
          typename std::enable_if<is_container<Container>::value, bool>::type = true>
void printIp(const Container & __attribute__((unused)) input)
{
    for (auto itEl = input.begin(); itEl != input.end(); )
    {
        std::cout << *itEl;
        if (++itEl != input.end() && !std::is_same<Container, std::string>::value)
            std::cout << '.';
    }

    std::cout << std::endl;
};

template<typename T, typename... Ts>
struct all_types_are_same : std::conjunction<std::is_same<T, Ts>...> {};

template<typename Tuple,
         typename = std::enable_if_t<
                   all_types_are_same<
                        std::tuple_element_t<0, Tuple>,
                        std::tuple_element_t<1, Tuple>,
                        std::tuple_element_t<2, Tuple>
                   >::value
        >>
void printIp(const Tuple &  t)
{
    std::cout << std::get<0>(t) << "." <<
                 std::get<1>(t) << "." <<
                 std::get<2>(t) << "." <<
                 std::get<3>(t) << std::endl;
}


#endif //_SFINAE_H_
