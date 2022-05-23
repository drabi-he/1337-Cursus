/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:51:08 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/04 13:38:55 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(){
    std::cout << "Default evolution for WrongCat" << std::endl;
    this->type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat &WC){
    std::cout << "Copy evolution for WrongCat" << std::endl;
    *this = WC;
}

WrongCat &WrongCat::operator=(const WrongCat &WC){
    std::cout << "Copy Assignment evolution for WrongCat" << std::endl;
    if (this != &WC)
    {
        this->type = WC.type;
    }
    return *this;
}

WrongCat::~WrongCat(){
    std::cout << "Regression from WrongCat to WrongAnimal" << std::endl;
}

void WrongCat::makeSound() const {
    std::cout << "🐱 : Meow Meow" << std::endl;
}