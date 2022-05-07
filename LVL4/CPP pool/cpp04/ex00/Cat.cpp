/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:51:08 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/04 12:39:07 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(){
    std::cout << "Default evolution for Cat" << std::endl;
    this->type = "Cat";
}

Cat::Cat(const Cat &C){
    std::cout << "Copy evolution for Cat" << std::endl;
    *this = C;
}

Cat &Cat::operator=(const Cat &C){
    std::cout << "Copy Assignment evolution for Cat" << std::endl;
    if (this != &C)
    {
        this->type = C.type;
    }
    return *this;
}

Cat::~Cat(){
    std::cout << "Regression from Cat to Animal" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "🐱 : Meow Meow" << std::endl;
}