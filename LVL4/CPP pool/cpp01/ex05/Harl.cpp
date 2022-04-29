/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 00:07:56 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 00:53:43 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl(/* args */){}

Harl::~Harl(){}

void Harl::debug(){
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}
void Harl::info(){
    std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put "\
    "enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::cout;
}
void Harl::warning(){
    std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for "\
    "years whereas you started working here since last month." << std::endl;
}
void Harl::error(){
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}
void Harl::complain(std::string level){
    void (Harl::*choose[4])(void) = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };
    
    std::string choice[4] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR"
    };
    
    for (int i = 0; i < 4; i++)
        if(level == choice[i])
            (this->*choose[i])();
}