/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:01:37 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/09 18:05:34 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HEADER_
#define _HEADER_

#include <iostream>

typedef struct Data
{
    int test;
} Data;

Data* deserialize(uintptr_t raw);
uintptr_t serialize(Data* ptr);

#endif 