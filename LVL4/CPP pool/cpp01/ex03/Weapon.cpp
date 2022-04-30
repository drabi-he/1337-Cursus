/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:02:55 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 22:31:30 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(){}

Weapon::Weapon(std::string type){
    this->type = type;
}

Weapon::~Weapon(){}

std::string Weapon::getType(){
    return this->type;
}

void    Weapon::setType(std::string type){

    this->type = type;
}