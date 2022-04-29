/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:27:10 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/27 22:39:44 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONTACT_
# define _CONTACT_

#include <iostream>
#include <iomanip>

class Contact
{
	private:
		int index;
		std::string firstName;
		std::string lastName;
		std::string nickName;
		std::string phoneNumber;
		std::string darkSecret;

	public:
		Contact();
		Contact(int index, std::string firstName, std::string lastName, \
		std::string nickName, std::string phoneNumber, std::string darkSecret);
		void	display();
		void	displayAll();
};



#endif