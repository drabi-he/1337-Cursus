/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:51:05 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/17 14:40:25 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ANIMAL_
# define _ANIMAL_

#include "Brain.hpp"
#include <iostream>

class Animal
{
    protected:
        std::string type;
    public:
        Animal();
        Animal(const Animal &A);        
        Animal &operator=(const Animal &A);
        virtual ~Animal();
        std::string getType() const;
        virtual void    makeSound() const;
        virtual Brain *getBrain() const;
};


#endif