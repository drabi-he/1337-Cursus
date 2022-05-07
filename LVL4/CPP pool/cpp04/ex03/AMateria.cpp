/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:21:42 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 11:16:50 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(){
    // std::cout << "Default Constructor for AMateria" << std::endl;
}

AMateria::AMateria(std::string const & type){
    // std::cout << "Initialise Constructor for AMateria" << std::endl;
    this->type = type;
}

AMateria::AMateria(const AMateria &AM){
    // std::cout << "Copy Constructor for AMateria" << std::endl;
    *this = AM;
}

AMateria &AMateria::operator=(const AMateria &AM){
    // std::cout << "Copy Assignment Constructor for AMateria" << std::endl;
    (void)AM;
    return *this;
}

AMateria::~AMateria(){
    // std::cout << "Destructor for AMateria" << std::endl;
}

std::string const & AMateria::getType() const{
    return this->type;
}

void AMateria::use(ICharacter& target){
    (void)target;
}