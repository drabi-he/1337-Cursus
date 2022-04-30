/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:02:50 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 23:30:35 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(){}

Zombie::Zombie(std::string name){
    this->name = name;
}

Zombie::~Zombie()
{
    std::cout << "\033[1m\033[31m" << "Zombie " + this->name + " has been destroyed!!" << "\033[0m" << std::endl;
}

void Zombie::announce(){
    std::cout << "\033[1m\033[33m" << this->name << ":  BraiiiiiiinnnzzzZ..." << "\033[0m" << std::endl;
}

void Zombie::setName(std::string name){
    this->name = name;
}