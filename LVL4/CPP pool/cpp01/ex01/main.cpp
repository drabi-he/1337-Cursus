/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:03:09 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/30 00:15:41 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// * dynamic allocation and free of class array

int main()
{
    Zombie *z;
    int cp = -10;

    z = zombieHorde(cp, "momayaz");
    if (z == NULL)
        return (0);
    for (int i = 0; i < cp ; i++)
        z[i].announce();
    delete[] z;
}