/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:27:10 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/10 12:57:06 by hdrabi           ###   ########.fr       */
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
		
		int getIndex() const;
		std::string getFirstName() const;
		std::string getLastName() const;
		std::string getNickName() const;
		std::string getPhoneNumber() const;
		std::string getDarkSecret() const;

		void setIndex(int i) ;
		void setFirstName(std::string fn) ;
		void setLastName(std::string ln) ;
		void setNickName(std::string nn) ;
		void setPhoneNumber(std::string pn) ;
		void setDarkSecret(std::string ds) ;
};



#endif