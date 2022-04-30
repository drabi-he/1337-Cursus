/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 22:28:39 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/30 00:40:40 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"

int main(int ac, char *av[])
{
    if (ac != 4)
    {
        std::cout << "\033[1m\033[31m" << "Wrong number of arguments" << "\033[0m" << std::endl;
        return 0;
    }
    Replace R(av[1], av[2], av[3]);
    R.replaceAll();
}