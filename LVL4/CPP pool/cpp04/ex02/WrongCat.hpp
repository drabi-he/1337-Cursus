/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:51:10 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/04 13:28:40 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WRONGCAT_
# define _WRONGCAT_

#include "WrongAnimal.hpp"
#include <iostream>

class WrongCat : public WrongAnimal
{
    private:
        /* data */
    public:
        WrongCat();
        WrongCat(const WrongCat &WC);
        WrongCat &operator=(const WrongCat &WC);
        ~WrongCat();
        void makeSound() const;
};

#endif