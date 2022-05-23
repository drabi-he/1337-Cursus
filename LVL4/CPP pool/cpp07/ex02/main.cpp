/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:52:33 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/23 12:21:08 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int main( void ) {

    Array<int>			intArray;
	Array<std::string>	stringArray(10);
	Array<std::string>	otherStringArray;
	Array<int> const	test1(10);

	std::cout << test1[0] << std::endl;
	// test1[0] = 1;
	std::cout << test1[0] << std::endl;

	stringArray[0] = "Hi";
	stringArray[1] = "Hello";
	stringArray[2] = "How are you?";
	stringArray[3] = "Fine and you?";
	stringArray[4] = "Doing great thanks!";
	stringArray[5] = "You're very welcome";
	std::cout << "intArray.size() = " << intArray.size() << std::endl;
	std::cout << "stringArray.size() = " << stringArray.size() << std::endl;
	otherStringArray = stringArray;
	otherStringArray[3] = "I'm good, how about you?";

	try
	{
		std::cout << stringArray[59] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		std::cout << stringArray[-3] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
    std::cout <<"-------------------------------------" << std::endl;
    try { 
        Array<std::string>	test(5);
        test = stringArray;
        test[2] = "haha";
        std::cout << stringArray[2] << std::endl;
        std::cout << test[2] << std::endl;
    }
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
    std::cout <<"-------------------------------------" << std::endl;
    try { 
        Array<std::string>	test2(stringArray);
        test2[2] = "haha";
        std::cout << stringArray[2] << std::endl;
        std::cout << test2[2] << std::endl;
    }
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
    std::cout <<"-------------------------------------" << std::endl;


	return 0;
}

// #define MAX_VAL 750
// int main(int, char**)
// {
//     Array<int> numbers(MAX_VAL);
//     int* mirror = new int[MAX_VAL];
//     srand(time(NULL));
//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         const int value = rand();
//         numbers[i] = value;
//         mirror[i] = value;
//     }
//     //SCOPE
//     {
//         Array<int> tmp = numbers;
//         Array<int> test(tmp);
//     }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         if (mirror[i] != numbers[i])
//         {
//             std::cerr << "didn't save the same value!!" << std::endl;
//             return 1;
//         }
//     }
//     try
//     {
//         numbers[-2] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
//     try
//     {
//         numbers[MAX_VAL] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         numbers[i] = rand();
//     }
//     delete [] mirror;//
//     return 0;
// }