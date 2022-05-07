/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:07:20 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/05 16:24:29 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

// ? constructors & destructor

ClapTrap::ClapTrap(){
	std::cout << "\033[1m\033[32m" << "Default constructor called" << "\033[0m" << std::endl;
    hitPoints = 10;
    energyPoints = 10;
    attackDamage = 0;
}

ClapTrap::ClapTrap(std::string name): name(name){
	std::cout << "\033[1m\033[32m" << "Initiation constructor called" << "\033[0m" << std::endl;
    hitPoints = 10;
    energyPoints = 10;
    attackDamage = 0;
}

ClapTrap::ClapTrap(const ClapTrap &CT){
	std::cout << "\033[1m\033[32m" << "Copy constructor called" << "\033[0m" << std::endl;
    *this = CT;
}

ClapTrap & ClapTrap::operator = (const ClapTrap &CT){
    if (this != &CT)
    {
        this->name = CT.getName();
        this->hitPoints = CT.getHP();
        this->energyPoints = CT.getEP();
        this->attackDamage = CT.getAD();
    }
    return *this;
}

ClapTrap::~ClapTrap(){
	std::cout << "\033[1m\033[31m" << "Destructor called" << "\033[0m" << std::endl;
}

// ? getter & setter

std::string ClapTrap::getName() const{
    return this->name;
}
int ClapTrap::getHP() const{
    return this->hitPoints;
    
}
int ClapTrap::getEP() const{
    return this->energyPoints;
    
}
int ClapTrap::getAD() const {
    return this->attackDamage;
}

void ClapTrap::setName(std::string name){
    if (name != "")
        this->name = name;
}
void ClapTrap::setHP(int HP){
    if (HP > 0)
        this->hitPoints = HP;
}
void ClapTrap::setEP(int EP){
    if (EP > 0)
        this->energyPoints = EP;
}
void ClapTrap::setAD(int AD){
    if (AD >= 0)
        this->attackDamage = AD;
}

// ? member functions

void ClapTrap::attack(const std::string& target){
        if (this->hitPoints <= 0){
        std::cout << "\033[1m\033[31m" << "ClapTrap " << this->getName() << " can't attack because he has no more hit points" 
                << "\033[0m" << std::endl;;
        return ;
    }
    if (this->energyPoints <= 0){
        this->energyPoints = -1;
        std::cout << "\033[1m\033[31m" << "ClapTrap " << this->getName() << " can't attack because he has no more energy points" 
                << "\033[0m" << std::endl;
        return ;
    }
    if (this->hitPoints > 0 && this->energyPoints > 0)
    {
        this->energyPoints--;
        std::cout << "\033[1m\033[32m" << "ClapTrap " << this->getName() << " attacks " << target << ", causing "
                    << this->getAD() << " points of damage!" << "\033[0m" << std::endl;
    }
}

void ClapTrap::takeDamage(unsigned int amount){
    std::cout << "\033[1m\033[31m" << "ClapTrap " << this->getName() ;
    if (this->hitPoints > 0)
    {
        std::cout << " has received  "
                    << amount << " points of damage!" << "\033[0m" << std::endl;
        this->hitPoints -= amount;
    }
    else
       std::cout << " has no more hit points" << "\033[0m" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount){
    if (this->hitPoints <= 0 || this->energyPoints <= 0)
    {
        std::cout << "\033[1m\033[31m" << "ClapTrap " << this->getName() << " hit points / energy points has reached 0!!" 
                << "\033[0m" << std::endl;
        return ;
    }
    std::cout << "\033[1m\033[32m" << "ClapTrap " << this->getName() << " has been repaired for "<< amount << " points of HP!" 
            << "\033[0m" << std::endl;
    this->hitPoints += amount;
    this->energyPoints--;
}