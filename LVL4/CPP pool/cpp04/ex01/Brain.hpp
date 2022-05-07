/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:43:02 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/04 16:37:06 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BRAIN_
#define _BRAIN_

#include <iostream>

class Brain
{
    public:
        std::string ideas[100];
    public:
        Brain();
        Brain(const Brain &B);
        Brain &operator=(const Brain &B);
        ~Brain();
};




#endif /* _BRAIN_ */
