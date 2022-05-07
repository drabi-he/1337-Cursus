/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:51:13 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/04 16:46:25 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(){
    std::cout << "Default evolution to Dog" << std::endl;
    this->type = "Dog";
    this->brain = new Brain();
}

Dog::Dog(const Dog &D){
    std::cout << "Copy evolution to Dog" << std::endl;
    *this = D;
}

Dog &Dog::operator=(const Dog &D){
    std::cout << "Copy Assignment evolution to Dog" << std::endl;
    if (this != &D)
    {
        this->type = D.type;
    }
    return *this;
}

Dog::~Dog(){
    std::cout << "Dog Destroying its Brain" << std::endl;
    delete brain;
    std::cout << "Regression from Dog to Animal" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "🐶 : Woof Woof" << std::endl;
}

Brain *Dog::getBrain() const {
    return (this->brain);
}