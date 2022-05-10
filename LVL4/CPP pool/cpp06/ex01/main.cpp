/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:01:34 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/09 18:12:14 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int main(){
    Data test;
    uintptr_t tmp1;
    Data *tmp2;

    test.test = 10;
    std::cout << test.test << std::endl;
    tmp1 = serialize(&test);
    std::cout << tmp1 << std::endl;
    tmp2 = deserialize(tmp1);
    std::cout << tmp2->test << std::endl;
    std::cout << deserialize(serialize(tmp2))->test << std::endl;
}