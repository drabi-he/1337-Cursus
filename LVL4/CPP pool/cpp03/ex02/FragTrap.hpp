/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:06:19 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/03 16:27:14 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FRAGTRAP_
#define _FRAGTRAP_

#include "ClapTrap.hpp"
#include <iostream>

class FragTrap : public ClapTrap
{
private:
    /* data */
public:
    FragTrap(/* args */);
    FragTrap(std::string name);
    FragTrap(const FragTrap &FT);
    FragTrap &operator = (const FragTrap &FT);
    ~FragTrap();
    void highFivesGuys();
};


#endif 
