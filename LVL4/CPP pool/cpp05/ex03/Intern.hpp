/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:43:33 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 18:36:33 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _INTERN_
#define _INTERN_

#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

class Intern
{
    private:
        /* data */
    public:
        Intern();
        Intern(const Intern &I);
        Intern &operator=(const Intern &I);
        ~Intern();
        Form    *makeForm(const std::string &name, const std::string &target);
};

#endif /* _INTERN_ */
