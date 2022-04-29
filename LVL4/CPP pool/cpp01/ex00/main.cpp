/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:03:09 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/28 16:52:43 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// * difference between dynamic a static declaration

int main()
{
    std::string name;
    Zombie z;
    
    std::cout << "Creating zombie in the stack" << std::endl;
    std::cout << "Zombie Name : " ;
    std::cin >> name;
    z = Zombie(name);
    
    std::cout << "Creating zombie in the heap" << std::endl;
    std::cout << "Zombie Name : " ;
    std::cin >> name;
    randomChump(name);
}