/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:27:22 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/10 13:04:24 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHONEBOOK_
# define _PHONEBOOK_

#include <iostream>
#include <iomanip>
#include "Contact.hpp"

class PhoneBook
{
	private:
		Contact phoneBook[8];
		static int cp;
	public:
		PhoneBook();
		void	addContact(int index, Contact contact);
		void	showAll();
		void	search(int index);
};


#endif