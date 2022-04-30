/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:59:36 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/30 00:15:35 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"


Zombie* zombieHorde( int N, std::string name )
{
    Zombie *zombieHorde;

    if (N <= 0)
    {
        std::cout << "\033[1m\033[31m" << "there must be at least one zombie" << "\033[0m" << std::endl ;
        return (NULL);
    }
    try {  
        zombieHorde = new Zombie[N];
    } catch (const std::exception &e) {
        std::cout << "\033[1m\033[31m" << "allocation failed" << "\033[0m" << std::endl ;
        return (NULL);
    }
    for (int i = 0; i < N; i++)
        zombieHorde[i].setName(name);
    return (zombieHorde);
}