/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:06:16 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/24 11:54:43 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef _EASYFIND_
#define _EASYFIND_

#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename T>
typename T::iterator easyfind(T a, int b){
    typename T::iterator rst;

    rst = std::find(a.begin(), a.end(), b);
    if (rst == a.end())
        throw std::logic_error("item not found");
    return rst;
}

#endif