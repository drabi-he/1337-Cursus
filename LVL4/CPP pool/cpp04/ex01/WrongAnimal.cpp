/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:50:57 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/04 13:37:54 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("cow"){
    std::cout << "Default constructor for WrongAnimal" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &WA){
    std::cout << "Copy constructor for WrongAnimal" << std::endl;
    *this = WA;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &WA){
    std::cout << "Copy Assignment constructor for WrongAnimal" << std::endl;
    if (this != &WA)
    {
        this->type = WA.type;
    }
    return *this;
}

WrongAnimal::~WrongAnimal(){
    std::cout << "Destructor for WrongAnimal" << std::endl;
}

void WrongAnimal::makeSound() const {
    std::cout << "🐮 : Moooooooooooo" << std::endl;
}

std::string WrongAnimal::getType() const {
    return this->type;
}