/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:03:02 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/14 11:41:58 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Span.hpp"

int main(){
    {
        int count = 10000;
        Span S(count);
        try
        {
            srand(time(NULL));
            for (int i = 0; i < count ; i++)
            {
                if (rand() % 2)
                    S.addNumber(-1 * (rand() % (count * 10)));
                else
                    S.addNumber(rand() % (count * 10));
            }
            std::cout << S.shortestSpan() << std::endl;
            std::cout << S.longestSpan() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    {
        int count = 10;
        Span S(count);
        try
        {
            srand(time(NULL));
            for (int i = 0; i < count ; i++)
            {
                if (rand() % 2)
                    S.addNumber(-1 * (rand() % (count * 10)));
                else
                    S.addNumber(rand() % (count * 10));
            }
            std::cout << S.shortestSpan() << std::endl;
            std::cout << S.longestSpan() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    {
        try
        {
            Span S(6);
            std::vector<int> numbers;

            // S.addNumber(6);
            numbers.push_back(1);
            numbers.push_back(2);
            numbers.push_back(3);
            numbers.push_back(4);
            numbers.push_back(5);
            numbers.push_back(6);
            S.UIaddNumber(numbers.begin(), numbers.end());
            // S.addNumber(6);
            std::cout << S.shortestSpan() << std::endl;
            std::cout << S.longestSpan() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}