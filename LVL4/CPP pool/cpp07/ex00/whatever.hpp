/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:52:36 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/10 11:24:17 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WHATEVER_
# define _WHATEVER_

#include <iostream>

template <typename T>
void swap(T &a, T &b){
    T tmp;

    tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
T min(T &a, T &b){
    if (a < b)
        return a;
    return b;
}

template <typename T>
T max(T &a, T &b){
        if (a > b)
        return a;
    return b;
}
#endif