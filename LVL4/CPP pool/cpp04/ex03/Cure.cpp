/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:35:42 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 11:17:13 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() : AMateria("cure"){
    // std::cout << "Default Constructor for CURE" << std::endl;
}

Cure::Cure(const Cure &C){
    // std::cout << "Copy Constructor for CURE" << std::endl;
    *this = C;
}

Cure &Cure::operator=(const Cure &C){
    // std::cout << "Copy Assignment Constructor for CURE" << std::endl;
    if (this != &C)
    {
        this->type = C.type;
    }
    return *this;
}

Cure::~Cure(){
    // std::cout << "Destructor for CURE" << std::endl;
}

AMateria * Cure::clone() const{
    return (new Cure());
}

void Cure::use(ICharacter& target){
    std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}