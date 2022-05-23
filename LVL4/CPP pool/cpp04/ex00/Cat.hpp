/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:51:10 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/17 14:33:00 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CAT_
# define _CAT_

#include "Animal.hpp"
#include <iostream>

class Cat : public Animal
{
    private:
        /* data */
    public:
        Cat();
        Cat(const Cat &C);
        Cat &operator=(const Cat &C);
        ~Cat();
        virtual void makeSound() const;
};

#endif