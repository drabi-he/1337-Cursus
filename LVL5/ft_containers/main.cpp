/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:58:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/06/15 11:06:05 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include "./vector/vector.hpp"
#include "./iterators/iterator.hpp"
#include "./xtra/is_integral.hpp"
#include "./xtra/enable_if.hpp"
#include "./redBlackTree/RedBlackTree.hpp"

// tests
# include <limits>


int main(){
    
    ft::RedBlackTree<int, int> test;

    std::cout << std::boolalpha;
    std::cout << test._null_node->value.first << std::endl;
    std::cout << test._null_node->value.second << std::endl;
    std::cout << test._null_node->isBlack << std::endl;

    std::pair<int, int> p1;
    p1.first = 10;
    p1.second = 10;

    ft::pair<int, int> p2;
    p2.first = 10;
    p2.second = 10;
}