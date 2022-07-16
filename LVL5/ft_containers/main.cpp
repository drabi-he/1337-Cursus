/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:58:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/16 13:16:04 by hdrabi           ###   ########.fr       */
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

        // std::cout << (RBT.find(10) != nullptr ? "true" : "false" ) << std::endl;
        // RBT.add(10);
        // std::cout << (RBT.find(10) != nullptr ? "true" : "false" ) << std::endl;
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

        // ft::RedBlackTree<int> RBT2;
        // RBT2 = RBT;

        // ft::RedBlackTree<int>::reverse_iterator it(RBT.end());
        // ft::RedBlackTree<int>::reverse_iterator it2(RBT.begin());
        
        // for ( ; it != it2 ; it++)
        // {
            // std::cout << *it << std::endl;
        // }
        // RBT.deleteNode(10);
        // RBT.deleteNode(18);
        // RBT.printTree(3);

        // std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
        // RBT2.printTree(3);
        /* code */

        ft::map<int, int> map;

        // std::cout << "size : "  << map.size() << std::endl;
        map[1] = 1;
        // std::cout << "size : "  << map.size() << std::endl;

        std::cout << "here\n"  << map[1] << std::endl;
        // std::cout << "size : "  << map.size() << std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}