/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:30:29 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/05 13:29:09 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ICE_
#define _ICE_

#include "AMateria.hpp"
#include <iostream>

class Ice : public AMateria
{
    private:
        /* data */
    public:
        Ice();
        Ice(const Ice &I);
        Ice &operator=(const Ice &I);
        ~Ice();
        AMateria* clone() const;
        void use(ICharacter& target);
};

#endif /* _ICE_ */
