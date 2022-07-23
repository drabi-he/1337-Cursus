/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:58:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/23 19:16:29 by hdrabi           ###   ########.fr       */
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
#include "./map/map.hpp"

// tests
# include <limits>


int main(){
    
    try
    {
        // ft::RedBlackTree<int> RBT;

        // RBT.add(10);
        // RBT.add(18);
        // RBT.add(7);
        // RBT.add(15);
        // RBT.add(16);
        // RBT.add(30);
        // RBT.add(25);
        // RBT.add(40);
        // RBT.add(60);
        // RBT.add(2);
        // RBT.add(1);
        // RBT.add(70);

        // RBT.erase(18);
        // RBT.erase(0);
        // ft::RedBlackTree<int>::iterator it;
        // it = RBT.begin();
        // std::cout << *it << std::endl;
        // RBT.erase(1);
        // it = RBT.begin();
        // std::cout << *it << std::endl;
        // RBT.printTree(3);


    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}