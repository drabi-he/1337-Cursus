/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:04:49 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/28 21:27:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WEAPON_
#define _WEAPON_

#include "iostream"

class Weapon
{
    private:
        std::string type;
    public:
        Weapon();
        Weapon(std::string type);
        ~Weapon();
        std::string    getType();
        void    setType(std::string type);
};

#endif