/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:02:58 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/05 15:02:55 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CHARACTER
#define _CHARACTER

#include "ICharacter.hpp"
#include "AMateria.hpp"
#include <iostream>

class Character : public ICharacter
{
    private:
        std::string name;
        AMateria *inventory[4];
        AMateria *storage[4];
    public:
        Character();
        Character(const std::string &name);
        Character(const Character &C);
        Character &operator=(const Character &C);
        ~Character();
        std::string const & getName() const;
        virtual void equip(AMateria* m);
        virtual void unequip(int idx);
        virtual void use(int idx, ICharacter& target);
};

#endif /* _CHARACTER */
