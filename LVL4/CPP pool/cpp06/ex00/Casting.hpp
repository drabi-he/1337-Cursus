/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Casting.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:37:56 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/09 17:25:56 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CASTING_
# define _CASTING_

#define NOTYPE -1
#define CHAR 1
#define INT 2
#define FLOAT 3
#define DOUBLE 4

# include <iostream>
#include <exception>
#include <limits>

class Casting
{
	private:
		int		type;
		char	charValue;
		int		intValue;
		float	floatValue;
		double	doubleValue;

	public:

		Casting();
		Casting( Casting const & src );
		~Casting();

		Casting &		operator=( Casting const & rhs );


		void detectType(char *str);
		void convertResult(char *str);
		void printResult(char *str);
		void charToOther();
		void intToOther();
		void floatToOther();
		void doubleToOther();
		
		class EmptyException : public std::exception {
			public :
			virtual const char* what() const throw() {
                    return "Please insert a value to analyse" ;
                }
		};

		class WrongInput : public std::exception {
			public :
			virtual const char* what() const throw() {
                    return "Input doesn't match any type" ;
                }
		};
};

int detectPseudo(char *str);
int detectFD(char *str);
int detectI(char *str);

#endif /* ********************************************************* */