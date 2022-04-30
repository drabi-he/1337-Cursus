/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:23:12 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 22:34:18 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int ac, char *av[])
{
	if (ac == 1)
		std::cout << "\033[1m\033[31m" << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << "\033[0m";
	else {
		for (int i = 1; i < ac ; i++) {
			int j = -1;

			while (av[i][++j])
				std::cout << (char) std::toupper(av[i][j]);
		}
	}
	std::cout << std::endl;
}