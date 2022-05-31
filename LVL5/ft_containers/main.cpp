/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:58:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/31 19:56:27 by hdrabi           ###   ########.fr       */
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
    
    ft::vector<int> v1;

    std::cout << v1.size() << std::endl;
    std::cout << v1.capacity() << std::endl;
    v1.pop_back();
    v1.pop_back();
    // v1.push_back(1);
    std::cout << v1.size() << std::endl;
    std::cout << v1.capacity() << std::endl;

}