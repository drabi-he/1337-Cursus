/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:29:44 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/28 16:51:33 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"

// * an introduction to classes 

void	add_to_phonebook(PhoneBook *phonebook, int *i)
{
	std::string fn;
	std::string ln;
	std::string nn;
	std::string pn;
	std::string ds;
	
	std::cout << "First Name : ";
	std::cin >> fn ;
	std::cout << "Last Name : ";
	std::cin >> ln ;
	std::cout << "NickName : ";
	std::cin >> nn ;
	std::cout << "Phone Number : ";
	std::cin >> pn ;
	std::cout << "Dark Secret : ";
	std::cin >> ds ;
	Contact contact =  Contact(*i, fn, ln, nn, pn, ds);
	phonebook->addContact(*i, contact);
	(*i)++;
	if ((*i) == 8)
		(*i) = 0;
}

void	search_contact(PhoneBook phoneBook)
{
	int index;
	
	phoneBook.showAll();
	std::cout << "\033[1m\033[33mContact Index :\033[0m" ;
	std::cin >> index ;
	phoneBook.search(index - 1);
}

int main()
{
	PhoneBook	phoneBook;
	std::string	op;
	int	i;

	i = 0;
	while (1)
	{
		std::cout << "**********************" << std::endl;
		std::cout << "	OPTIONS		" << std::endl;
		std::cout << "**********************" << std::endl;
		std::cout << "	ADD		" << std::endl;
		std::cout << "	SEARCH		" << std::endl;
		std::cout << "	EXIT		" << std::endl;
		std::cout << "**********************" << std::endl;
		std::cout << "\033[1m\033[33mchoice: \033[0m" ;
		std::cin >> op ;
		if (!op.compare("EXIT"))
			break ;
		else if (!op.compare("ADD"))
			add_to_phonebook(&phoneBook, &i);
		else if (!op.compare("SEARCH"))
			search_contact(phoneBook);
		else
			std::cout << "\033[1m\033[31mInvalid Choice !!\033[0m" << std::endl;
		std::cout << "------------------------------------------------" << std::endl;
	}
	std::cout << "\033[1m\033[36mThank You !!\033[0m" << std::endl;
}