/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:32:57 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 17:19:39 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SHRUBBERYCREATIONFORM_
#define _SHRUBBERYCREATIONFORM_

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>
#include <fstream>

class ShrubberyCreationForm : public Form
{
    private:
        std::string target;
    public:
        ShrubberyCreationForm();
        ShrubberyCreationForm(const std::string &target);
        ShrubberyCreationForm(const ShrubberyCreationForm &SCF);
        ShrubberyCreationForm &operator=(const ShrubberyCreationForm &SCF);
        ~ShrubberyCreationForm();
        void valid(Bureaucrat const &B) const;
        void execute(Bureaucrat const &B) const;
};



#endif /* _SHRUBBERYCREATIONFORM_ */
