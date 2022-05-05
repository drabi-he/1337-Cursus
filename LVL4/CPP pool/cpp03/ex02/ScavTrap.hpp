/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:39:35 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/03 15:33:14 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SCAVTRAP_
#define _SCAVTRAP_

#include "ClapTrap.hpp"
#include <iostream>

class ScavTrap : public ClapTrap
{
    private:
        /* data */
    public:
        ScavTrap(/* args */);
        ScavTrap(std::string name);
        ScavTrap(const ScavTrap &ST);
        ScavTrap &operator=(const ScavTrap &ST);
        ~ScavTrap();
        void    guardGate();
        void attack(const std::string& target);
};


#endif 
