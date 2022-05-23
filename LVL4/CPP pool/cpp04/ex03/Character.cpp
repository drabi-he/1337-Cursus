/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:50:50 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/17 15:15:17 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"


Character::Character(){
    // std::cout << "Default Constructor for Character" << std::endl;
    this->name = "default";
    this->inventory[0] = nullptr;
    this->inventory[1] = nullptr;
    this->inventory[2] = nullptr;
    this->inventory[3] = nullptr;
}

Character::Character(const std::string &name){
    // std::cout << "Initialise Constructor for Character" << std::endl;
    this->name = name;
    this->inventory[0] = nullptr;
    this->inventory[1] = nullptr;
    this->inventory[2] = nullptr;
    this->inventory[3] = nullptr;
}

Character::Character(const Character &C){
    // std::cout << "Copy Constructor for Character" << std::endl;
    *this = C;
}

Character &Character::operator=(const Character &C){
    // std::cout << "Copy Assignment Constructor for Character" << std::endl;
    if (this != &C)
    {
        this->name = C.name;
        if (this->inventory[0] != nullptr)
            delete this->inventory[0];
        if (this->inventory[1] != nullptr)
            delete this->inventory[1];
        if (this->inventory[2] != nullptr)
            delete this->inventory[2];
        if (this->inventory[3] != nullptr)
            delete this->inventory[3];
        
        this->inventory[0] = C.inventory[0] != nullptr ? C.inventory[0]->clone() : nullptr;
        this->inventory[1] = C.inventory[1] != nullptr ? C.inventory[1]->clone() : nullptr;
        this->inventory[2] = C.inventory[2] != nullptr ? C.inventory[2]->clone() : nullptr;
        this->inventory[3] = C.inventory[3] != nullptr ? C.inventory[3]->clone() : nullptr;
    }
    return *this;
}

Character::~Character(){
        if (this->inventory[0] != nullptr)
            delete this->inventory[0];
        if (this->inventory[1] != nullptr)
            delete this->inventory[1];
        if (this->inventory[2] != nullptr)
            delete this->inventory[2];
        if (this->inventory[3] != nullptr)
            delete this->inventory[3];

        if (this->storage[0] != nullptr)
            delete this->storage[0];
        if (this->storage[1] != nullptr)
            delete this->storage[1];
        if (this->storage[2] != nullptr)
            delete this->storage[2];
        if (this->storage[3] != nullptr)
            delete this->storage[3];
    // std::cout << "Destructor for Character" << std::endl;
}

std::string const & Character::getName() const {
    return this->name;
}

void Character::equip(AMateria* m){
    for (int i = 0 ; i < 4 ; i++)
    {
        if (this->inventory[i] == NULL)
        {
            this->inventory[i] = m;
            break;
        }
    }
}

void Character::unequip(int idx){
    if (idx < 0 || idx > 3)
        return ;
    if (this->inventory[idx] != nullptr)
    {
        this->storage[idx] = this->inventory[idx];
        this->inventory[idx] = nullptr;
    }
}

void Character::use(int idx, ICharacter& target){
    if (idx < 0 || idx > 3 || this->inventory[idx] == nullptr)
        return ;
    this->inventory[idx]->use(target);
}