/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:23:20 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/24 11:58:00 by hdrabi           ###   ########.fr       */
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
            std::cout << *easyfind(ar1, 2) << std::endl;
            std::cout << *easyfind(ar1, 4) << std::endl;
            std::cout << *easyfind(ar1, 0) << std::endl;
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
            std::cout << *easyfind(gquiz, 3) << std::endl;
            std::cout << *easyfind(gquiz, 6) << std::endl;
            std::cout << *easyfind(gquiz, 7) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}