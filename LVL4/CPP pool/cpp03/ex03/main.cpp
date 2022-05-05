/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:07:25 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/03 18:39:30 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "DiamondTrap.hpp"
#include "DiamondTrap.hpp"
#include <iomanip>
#include <iostream>

int const count = 5;

void gameplay(DiamondTrap C[count])
{
    int clap;
    int action;
    int target;
    std::string name;

    while (1)
    {
        target  = -1;
        std::cout << "\033[1m" << std::setw(10) << "ID" << " | " 
                    << "\033[33m" <<  std::setw(10) << "Name" << " | " 
                    << "\033[32m" <<  std::setw(10) << "Hit Points" << " | " 
                    << "\033[36m" <<  std::setw(13) << "Energy Points" << " | " 
                    << "\033[34m" <<  std::setw(13) << "Attack Damage" << "\033[0m" <<std::endl;
        for (int i = 0 ; i < count ; i++)
            std::cout << "\033[1m" << std::setw(10) << (i + 1) << " | " 
                    << "\033[33m" <<  std::setw(10) << C[i].getName() << " | " 
                    << "\033[32m" <<  std::setw(10) << C[i].getHP() << " | " 
                    << "\033[36m" <<  std::setw(13) << (C[i].getEP() == -1 ? 0 : C[i].getEP()) << " | " 
                    << "\033[34m" <<  std::setw(13) << C[i].getAD() << "\033[0m" <<std::endl;
        std::cout << "choose your DiamondTrap (-1 to exit): ";
        std::cin >> clap;
        if (clap == -1)
        {
            std::cout << "Goodbye !!" << std::endl;
            break ;
        }
        if ( clap < 1 || clap > count)
        {
            std::cout << "\033[1m\033[31m" << "invalid clap !!" << "\033[1m" << std::endl;
            continue ;
        }
        std::cout << "1 - ATTACK : " << std::endl;
        std::cout << "2 - REPAIR : " << std::endl;
        std::cout << "3 - Who Am I : " << std::endl;
        std::cout << "choose your action : ";
        std::cin >> action;
        if ( action < 1 || action > 3)
        {
            std::cout << "\033[1m\033[31m" << "invalid choice !!" << "\033[1m" << std::endl;
            continue ;
        }
        if (action == 1)
        {
            std::cout << "choose your target : ";
            std::cin >> name;
            for (int i = 0; i < count ; i++)
                if (C[i].getName() == name)
                    target = i;
            C[clap - 1].attack(name);
            if (clap - 1 == target)
                std::cout << "\033[1m\033[31m" << "attack missed (can't attack itself)" << "\033[1m" << std::endl;
            else if (target == -1)
                std::cout << "\033[1m\033[31m" << "attack missed (target " + name + " not found) (T_T)" << "\033[1m" << std::endl;
            else
                if (C[clap - 1].getEP() + 1 != 0 && C[clap - 1].getHP() > 0)
                    C[target].takeDamage(C[1].getAD());
        }
        if (action == 2)
        {
            std::cout << "choose your repair amount : ";
            std::cin >> target;
            C[clap - 1].beRepaired(target);
        }
        if (action == 3)
        {
            C[clap - 1].whoAmI();
        }  
    }
}

int main()
{
    DiamondTrap C[count];
    std::string name;
    int value;

    std::cout << "Creating 5 DiamondTraps" << std::endl;
    for (int i = 0; i < count ; i++)
    {
        std::cout << "give DiamondTrap " << (i + 1) << " a name : ";
        std::cin >> name;
        C[i] = DiamondTrap(name);
    }
    std::cout << "Editting DiamondTraps" << std::endl;
    for (int i = 0; i < count ; i++)
    {
        std::cout << "\033[1m\033[33m" << "modify DiamondTrap " << (i + 1) << " HP (-1 to keep default) : [" << C[i].getHP() << "] " << "\033[0m";
        std::cin >> value;
        if (value >= 0)
            C[i].setHP(value);
        std::cout << "\033[1m\033[33m" << "modify DiamondTrap " << (i + 1) << " EP (-1 to keep default) : [" << C[i].getEP() << "] " << "\033[0m";
        std::cin >> value;
        if (value >= 0)
            C[i].setEP(value);
        std::cout << "\033[1m\033[33m" << "modify DiamondTrap " << (i + 1) << " AP (-1 to keep default) : [" << C[i].getAD() << "] " << "\033[0m";
        std::cin >> value;
        if (value >= 0)
            C[i].setAD(value);
    }
    gameplay (C);
}