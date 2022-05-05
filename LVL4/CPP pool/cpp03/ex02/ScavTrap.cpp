/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:39:54 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/03 18:17:15 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(){
	std::cout << "\033[1m\033[32m" << "Default evolution to ScavTrap" << "\033[0m" << std::endl;
    this->setHP(100);
    this->setEP(50);
    this->setAD(20);
}

ScavTrap::ScavTrap(std::string name) {
	std::cout << "\033[1m\033[32m" << "Initiate evolution to ScavTrap" << "\033[0m" << std::endl;
    this->setName(name);
    this->setHP(100);
    this->setEP(50);
    this->setAD(20);
}

ScavTrap::ScavTrap(const ScavTrap &ST){
	std::cout << "\033[1m\033[32m" << "Copy evolution to ScavTrap" << "\033[0m" << std::endl;
    *this = ST;
}

ScavTrap &ScavTrap::operator= (const ScavTrap &ST){
	std::cout << "\033[1m\033[32m" << "Copy assignment evolution to ScavTrap" << "\033[0m" << std::endl;
    if (this != &ST)
    {
        this->setName(ST.getName());
        this->setHP(ST.getHP());
        this->setEP(ST.getEP());
        this->setAD(ST.getAD());
    }
    return *this;
}

ScavTrap::~ScavTrap(){
    std::cout << "\033[1m\033[31m" << "Regression from ScavTrap to scavTrap" << "\033[1m" <<std::endl;
}

void ScavTrap::guardGate(){
    if (this->getEP() > 0 && this->getHP() > 0)
        std::cout << "ScavTrap " << this->getName() << " switched to Guard mode" << std::endl;
    else
        std::cout << "\033[1m\033[31m" << "ScavTrap " << this->getName() << " hit points / energy points has reached 0!!" 
                << "\033[0m" << std::endl;
}

void ScavTrap::attack(const std::string& target){
    if (this->getHP() <= 0){
        std::cout << "\033[1m\033[31m" << "scavTrap " << this->getName() << " can't attack because he has no more hit points" 
                << "\033[0m" << std::endl;;
        return ;
    }
    if (this->getEP() <= 0){
        this->setEP(this->getEP() - 1);
        std::cout << "\033[1m\033[31m" << "scavTrap " << this->getName() << " can't attack because he has no more energy points" 
                << "\033[0m" << std::endl;
        return ;
    }
    if (this->getHP() > 0 && this->getEP() > 0)
    {
        this->setEP(this->getEP() - 1);
        std::cout << "\033[1m\033[32m" << "ScavTrap " << this->getName() << " attacks " << target << ", causing "
                    << this->getAD() << " points of damage!" << "\033[0m" << std::endl;
    }
}