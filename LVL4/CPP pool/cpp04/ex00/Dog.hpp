/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:51:15 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/17 14:33:08 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DOG_
# define _DOG_

#include "Animal.hpp"
#include <iostream>

class Dog : public Animal
{
    private:
        /* data */
    public:
        Dog();
        Dog(const Dog &D);
        Dog &operator=(const Dog &D);
        ~Dog();
        virtual void makeSound() const;
};

#endif