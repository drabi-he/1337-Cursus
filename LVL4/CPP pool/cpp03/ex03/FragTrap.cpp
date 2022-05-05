/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:07:24 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/03 18:43:28 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(){
	std::cout << "\033[1m\033[32m" << "Default evolution to FragTrap" << "\033[0m" << std::endl;
    this->setHP(100);
    this->setEP(100);
    this->setAD(30);
}

FragTrap::FragTrap(std::string name) {
	std::cout << "\033[1m\033[32m" << "Initiate evolution to FragTrap" << "\033[0m" << std::endl;
    this->setName(name);
    this->setHP(100);
    this->setEP(100);
    this->setAD(30);
}

FragTrap::FragTrap(const FragTrap &ST){
	std::cout << "\033[1m\033[32m" << "Copy evolution to FragTrap" << "\033[0m" << std::endl;
    *this = ST;
}

FragTrap &FragTrap::operator= (const FragTrap &ST){
	std::cout << "\033[1m\033[32m" << "Copy assignment evolution to FragTrap" << "\033[0m" << std::endl;
    if (this != &ST)
    {
        this->setName(ST.getName());
        this->setHP(ST.getHP());
        this->setEP(ST.getEP());
        this->setAD(ST.getAD());
    }
    return *this;
}

FragTrap::~FragTrap(){
    std::cout << "\033[1m\033[31m" << "Regression from FragTrap to ClapTrap" << "\033[1m" <<std::endl;
}

void FragTrap::highFivesGuys(){
    if (this->getEP() > 0 && this->getHP() > 0)
        std::cout << "FragTrap " << this->getName() << " is demanding a high five 😡" << std::endl;
    else
        std::cout << "\033[1m\033[31m" << "FragTrap " << this->getName() << " hit points / energy points has reached 0!!" 
                << "\033[0m" << std::endl;
}
