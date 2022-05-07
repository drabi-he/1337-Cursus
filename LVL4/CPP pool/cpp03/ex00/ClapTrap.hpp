/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:07:23 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/05 16:22:04 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CLAPTRAP_
#define _CLAPTRAP_

#include <iostream>
#include <iomanip>

class ClapTrap
{
    private:
        std::string name;
        unsigned int hitPoints;
        unsigned int energyPoints;
        unsigned int attackDamage;
        
    public:
        ClapTrap();
        ClapTrap(std::string name);
        ClapTrap(const ClapTrap &CT);
        ClapTrap &operator = (const ClapTrap &CT);
        ~ClapTrap();

        std::string getName() const;
        int getHP() const ;
        int getEP() const ;
        int getAD() const ;

        void setName(std::string name);
        void setHP(int HP);
        void setEP(int EP);
        void setAD(int AD);
        
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
};




#endif