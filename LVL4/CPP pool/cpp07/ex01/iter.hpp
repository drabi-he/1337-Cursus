/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:52:36 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/10 11:24:17 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ITER_
# define _ITER_

#include <iostream>

template <typename T>
void iter(T *a, int b, void (*function)(T const &)){
    for (int i = 0; i < b; i++)
        function(a[i]);
}

#endif