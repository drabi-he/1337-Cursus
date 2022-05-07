/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:05:28 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/04 16:37:18 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(){
    std::cout << "Default constructor for Brain" << std::endl;
}

Brain::Brain(const Brain &B){
    std::cout << "Copy constructor for Brain" << std::endl;
    *this = B;
}

Brain &Brain::operator=(const Brain &B){
    std::cout << "Copy Assignment constructor for Brain" << std::endl;
    if (this != &B)
    {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = B.ideas[i];
    }
    return (*this);
}

Brain::~Brain(){
    std::cout << "Destructor for Brain" << std::endl;
}
