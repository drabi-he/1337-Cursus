/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:03:09 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/28 16:55:30 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"

// * introduction to references

int main()
{
    std::string greet = "HI THIS IS BRAIN";
    std::string *stringPTR = &greet;
    std::string &stringREF = greet;

    std::cout << "**** MEMORY ADDRESS ****" << std::endl;
    std::cout << "string    = " << &greet << std::endl;
    std::cout << "pointer   = " << &(*stringPTR) << std::endl;
    std::cout << "reference = " << &stringREF << std::endl;
    std::cout << "******** VALUE *********" << std::endl;
    std::cout << "string    = " << greet << std::endl;
    std::cout << "pointer   = " << *stringPTR << std::endl;
    std::cout << "reference = " << stringREF <<std::endl;
}