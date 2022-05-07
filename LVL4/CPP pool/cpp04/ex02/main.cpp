/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:51:18 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 16:02:46 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Brain.hpp"

int main()
{
    int count = 3;
    Animal *animals[count];


    for (int i = 0 ; i < count; i++)
    {
        std::cout << "< ----------------- " << i + 1 <<" ----------------- >" << std::endl;
        if (i % 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();    
    }
    for (int i = 0 ; i < count; i++)
    {
        for (int j = 0; j < 5; j++)
        {            
            if (i % 2)
                animals[i]->getBrain()->ideas[j] = "Give Me A Bone " + std::to_string(j + 1);
            else
                animals[i]->getBrain()->ideas[j] = "I Love Fish " + std::to_string(j + 1);  
        }
    }
    std::cout << std::endl;
    for (int i = 0 ; i < count; i++)
    {
        std::cout << "> ----------------- " << i + 1 <<" ----------------- <" << std::endl;
        std::cout << "this is a : " << animals[i]->getType() << std::endl;
        animals[i]->makeSound();
        std::cout << "! -------- it has many ideas -------- !" << std::endl;
        for (int j = 0; j < 5; j++)            
            std::cout << "\t" << animals[i]->getBrain()->ideas[j] << std::endl;
        std::cout << std::endl;
    }
    for (int i = 0 ; i < count; i++)
    {
        std::cout << "> ----------------- " << i + 1 <<" ----------------- <" << std::endl;
        delete animals[i];
    }
}