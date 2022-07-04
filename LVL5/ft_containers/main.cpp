/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:58:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/04 13:57:13 by hdrabi           ###   ########.fr       */
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
    
    ft::RedBlackTree<int , int> RBT;

    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);
    RBT.add(1, 1);

    RBT.printTree(3);

    return 0;
}