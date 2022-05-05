/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:10:12 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/04 14:02:37 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(){
	std::cout << "\033[1m\033[32m" << "Default evolution to DiamondTrap" << "\033[0m" << std::endl;
    this->name = "";
    this->ClapTrap::setName( name + "_clap_name");
    this->setHP(this->FragTrap::getHP());
    this->setEP(this->ScavTrap::getEP());
    this->setAD(this->FragTrap::getAD());
}
DiamondTrap::DiamondTrap(std::string name){
	std::cout << "\033[1m\033[32m" << "Initiate evolution to DiamondTrap" << "\033[0m" << std::endl;
    this->name = name;
    this->ClapTrap::setName( name + "_clap_name");
    this->setHP(this->FragTrap::getHP());
    this->setEP(this->ScavTrap::getEP());
    this->setAD(this->FragTrap::getAD());
}
DiamondTrap::DiamondTrap(const DiamondTrap &DT){
	std::cout << "\033[1m\033[32m" << "Copy evolution to DiamondTrap" << "\033[0m" << std::endl;
        *this = DT;
}
DiamondTrap &DiamondTrap::operator=(const DiamondTrap &DT){
	std::cout << "\033[1m\033[32m" << "Copy assignment evolution to DiamonTrap" << "\033[0m" << std::endl;
    if (this != &DT)
    {
        this->name = DT.name;
        this->setName(DT.getName());
        this->setHP(DT.getHP());
        this->setEP(DT.getEP());
        this->setAD(DT.getAD());
    }
    return *this;
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "\033[1m\033[31m" << "Regression from DiamondTrap to ClapTrap" << "\033[1m" <<std::endl;
}

void DiamondTrap::attack(std::string target)
{
    ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
    if (this->getEP() > 0 && this->getHP() > 0)
        std::cout << "my name is : " << this->name << " My ClapTrap name is : " << this->ClapTrap::getName() << std::endl;
    else
        std::cout << "\033[1m\033[31m" << "FragTrap " << this->getName() << " hit points / energy points has reached 0!!" 
                << "\033[0m" << std::endl;
}