/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:35:32 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/05 13:28:20 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CURE_
#define _CURE_

#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <iostream>

class Cure : public AMateria
{
    private:
        
    public:
        Cure();
        Cure(const Cure &C);
        Cure &operator=(const Cure &C);
        ~Cure();
        AMateria* clone() const;
        void use(ICharacter& target);
};

#endif /* _CURE_ */
