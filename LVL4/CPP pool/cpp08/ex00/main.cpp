/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:23:20 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/12 14:49:53 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <vector>
#include <array>
#include <deque>

int main()
{

    {
        std::vector<int> numbers;

        numbers.push_back(1);
        numbers.push_back(2);
        numbers.push_back(3);
        numbers.push_back(4);
        numbers.push_back(5);
        numbers.push_back(6);
        try
        {
            std::cout << *easyfind(numbers, 1) << std::endl;
            std::cout << *easyfind(numbers, 5) << std::endl;
            std::cout << *easyfind(numbers, 7) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    {
        std::array<int, 5> ar1 = {3, 4, 5, 1, 2};
        
        try
        {
            std::cout << *easyfind(ar1, 1) << std::endl;
            std::cout << *easyfind(ar1, 5) << std::endl;
            std::cout << *easyfind(ar1, 7) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    {
        std::deque<int> gquiz;
        gquiz.push_back(1);
        gquiz.push_back(2);
        gquiz.push_back(3);
        gquiz.push_back(4);
        gquiz.push_back(5);
        gquiz.push_back(6);
        
        try
        {
            std::cout << *easyfind(gquiz, 1) << std::endl;
            std::cout << *easyfind(gquiz, 5) << std::endl;
            std::cout << *easyfind(gquiz, 7) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    
    
}