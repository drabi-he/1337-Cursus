/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:01:39 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 11:17:24 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria("ice"){
    // std::cout << "Default Constructor for ICE" << std::endl;
}

Ice::Ice(const Ice &I){
    // std::cout << "Copy Constructor for ICE" << std::endl;
    *this = I;
}
Ice &Ice::operator=(const Ice &I){
    // std::cout << "Copy Assignment Constructor for ICE" << std::endl;
    if (this != &I)
    {
        this->type = I.type;
    }
    return *this;
}
        
Ice::~Ice(){
    // std::cout << "Destructor for ICE" << std::endl;
}

AMateria * Ice::clone() const{
    return (new Ice());
}

void Ice::use(ICharacter& target){
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}