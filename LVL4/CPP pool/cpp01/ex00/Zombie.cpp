/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:02:50 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/28 15:39:15 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(){}

Zombie::Zombie(std::string name){
    this->name = name;
}

Zombie::~Zombie()
{
    std::cout << "Zombie " + this->name + " has been destroyed!!" << std::endl;
}

void Zombie::announce(){
    std::cout << this->name << ":  BraiiiiiiinnnzzzZ..." << std::endl;
}