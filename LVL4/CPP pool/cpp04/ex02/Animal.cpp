/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:50:57 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/04 16:25:18 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("dragon"){
    std::cout << "Default constructor for Animal" << std::endl;
}

Animal::Animal(const Animal &A){
    std::cout << "Copy constructor for Animal" << std::endl;
    *this = A;
}

Animal &Animal::operator=(const Animal &A){
    std::cout << "Copy Assignment constructor for Animal" << std::endl;
    if (this != &A)
    {
        this->type = A.type;
    }
    return *this;
}

Animal::~Animal(){
    std::cout << "Destructor for Animal" << std::endl;
}

void Animal::makeSound() const {
    std::cout << "🐉 : Rawr Rawr" << std::endl;
}

std::string Animal::getType() const {
    return this->type;
}
