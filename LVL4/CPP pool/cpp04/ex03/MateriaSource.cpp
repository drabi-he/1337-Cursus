/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:51:39 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 11:17:39 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource(){
    // std::cout << "Default Constructor for MateriaSource" << std::endl;
    this->inventory[0] = nullptr;
    this->inventory[1] = nullptr;
    this->inventory[2] = nullptr;
    this->inventory[3] = nullptr;
}

MateriaSource::MateriaSource(const MateriaSource &MS){
    // std::cout << "Copy Constructor for MateriaSource" << std::endl;
    *this = MS;
}

MateriaSource &MateriaSource::operator=(const MateriaSource &MS){
    // std::cout << "Copy Assignment Constructor for MateriaSource" << std::endl;
    if (this != &MS)
    {
        if (this->inventory[0] != nullptr)
            delete this->inventory[0];
        if (this->inventory[1] != nullptr)
            delete this->inventory[1];
        if (this->inventory[2] != nullptr)
            delete this->inventory[2];
        if (this->inventory[3] != nullptr)
            delete this->inventory[3];
        
        this->inventory[0] = MS.inventory[0] != nullptr ? MS.inventory[0]->clone() : nullptr;
        this->inventory[1] = MS.inventory[1] != nullptr ? MS.inventory[1]->clone() : nullptr;
        this->inventory[2] = MS.inventory[2] != nullptr ? MS.inventory[2]->clone() : nullptr;
        this->inventory[3] = MS.inventory[3] != nullptr ? MS.inventory[3]->clone() : nullptr;
    }
    return *this;
}

MateriaSource::~MateriaSource(){
    if (this->inventory[0] != nullptr)
        delete this->inventory[0];
    if (this->inventory[1] != nullptr)
        delete this->inventory[1];
    if (this->inventory[2] != nullptr)
        delete this->inventory[2];
    if (this->inventory[3] != nullptr)
        delete this->inventory[3];
    // std::cout << "Destructor for MateriaSource" << std::endl;
}

void MateriaSource::learnMateria(AMateria* m){
    for (int i = 0 ; i < 4 ; i++)
    {
        if (this->inventory[i] == NULL)
        {
            this->inventory[i] = m;
            break;
        }
    }
}

AMateria* MateriaSource::createMateria(std::string const & type){
    if (type != "ice" && type != "cure")
        return 0;
    for (int i = 0; i < 4; i++)
    {
        if (this->inventory[i] != nullptr && this->inventory[i]->getType() == type)
            return this->inventory[i]->clone();
    }
    return 0;
}