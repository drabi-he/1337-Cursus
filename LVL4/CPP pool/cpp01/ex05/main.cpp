/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 00:42:14 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 01:00:21 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(){
    Harl H;

    H.complain("DEBUG");
    H.complain("INFO");
    H.complain("WARNING");
    H.complain("ERROR");
}