/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:58:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/05 11:23:08 by hdrabi           ###   ########.fr       */
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
    
    try
    {
        ft::RedBlackTree<int , int> RBT;

        RBT.add(10, 10);
        RBT.add(18, 18);
        RBT.add(7, 7);
        RBT.add(15, 15);
        RBT.add(16, 16);
        RBT.add(30, 30);
        // RBT.add(25, 25);
        // RBT.add(40, 40);
        // RBT.add(60, 60);
        // RBT.add(2, 2);
        // RBT.add(1, 1);
        // RBT.add(70, 70);

        // std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
        RBT.deleteNode(10);
        RBT.deleteNode(18);
        RBT.printTree(3);
        /* code */
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}