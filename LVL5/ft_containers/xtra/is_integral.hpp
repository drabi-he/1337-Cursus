/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:12:13 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/30 16:05:28 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include <iostream>
# include <string>

namespace ft{
	
    template <class T>
    struct is_integral{
        typedef bool value_type;
        static const value_type value = false;
    };

    template <>
    struct is_integral<bool>{
        typedef bool value_type;
        static const value_type value = true;
    };
    
    template <>
    struct is_integral<char>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<char16_t>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<char32_t>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<wchar_t>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<signed char>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<unsigned char>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<short int>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<unsigned short int>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<int>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<unsigned int>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<long int>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<unsigned long int>{
        typedef bool value_type;
        static const value_type value = true;
    };

    template <>
    struct is_integral<long long int>{
        typedef bool value_type;
        static const value_type value = true;
    };
    
    template <>
    struct is_integral<unsigned long long int>{
        typedef bool value_type;
        static const value_type value = true;
    };
	
}

#endif