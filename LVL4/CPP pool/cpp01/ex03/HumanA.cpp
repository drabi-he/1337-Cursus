/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:03:04 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/28 22:22:25 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HUMANA_
#define _HUMANA_

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &w): weapon(w){
    this->name = name;
}

HumanA::~HumanA(){}

void    HumanA::attack(){
        std::cout << this->name << " attacks with their " << this->weapon.getType() << std::endl;
}

#endif