/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:58:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/06/03 12:03:36 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <iterator>
#include "./vector/vector.hpp"
#include "./iterators/iterator.hpp"
#include "./xtra/is_integral.hpp"
#include "./xtra/enable_if.hpp"


// tests
# include <limits>

int main(){
    
    ft::vector<int> v1 (3);

    v1.push_back(1);
    std::cout << &(*v1.begin()) << std::endl;
    v1.push_back(2);
    std::cout << &(*v1.begin()) << std::endl;
    std::cout << &(*(v1.begin() + 1)) << std::endl;

}