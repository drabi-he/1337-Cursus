/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:03:15 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/28 22:23:19 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name): weapon(nullptr){
    this->name = name;
}

HumanB::~HumanB(){}

void    HumanB::attack(){
    if (this->weapon != NULL)
        std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
    else
        std::cout << this->name << " can't attack without a weapon " << std::endl;
}

void    HumanB::setWeapon(Weapon &weapon){
    this->weapon = &weapon;
}