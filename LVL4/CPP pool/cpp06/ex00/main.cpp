/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:58:33 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/09 17:36:29 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Casting.hpp"

int main(int ac, char *av[])
{
    try
    {
        if (ac == 1)
            throw Casting::EmptyException();
        Casting C;
        for (int i = 1; av[i] != nullptr ; i++)
        {
            std::cout << std::endl << "< ------------------------ " << i << " : " << av[i] <<" ------------------------ >" << std::endl;
            C.detectType(av[i]);
            C.printResult(av[i]);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}