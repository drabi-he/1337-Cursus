/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:58:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/06/17 16:26:05 by hdrabi           ###   ########.fr       */
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

    test.add(10, 0);
    test.add(18, 0);
    test.add(7, 0);
    test.add(15, 0);
    test.add(16, 0);
    test.add(30, 0);
    test.add(25, 0);
    test.add(40, 0);
    test.add(60, 0);
    test.add(2, 0);
    test.add(1, 0);
    test.add(70, 0);
    test.printTree(test._root, 0, 3);
}