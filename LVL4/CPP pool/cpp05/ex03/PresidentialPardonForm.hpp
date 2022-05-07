/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:33:30 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 17:13:29 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PRESIDENTIALPARDONFORM_
#define _PRESIDENTIALPARDONFORM_

#include "Form.hpp"
#include <iostream>

class PresidentialPardonForm : public Form
{
    private:
        std::string target;
    public:
        PresidentialPardonForm();
        PresidentialPardonForm(const std::string &target);
        PresidentialPardonForm(const PresidentialPardonForm &PPF);
        PresidentialPardonForm &operator=(const PresidentialPardonForm &PPF);
        ~PresidentialPardonForm();
        void execute(Bureaucrat const &B) const;
        void valid(Bureaucrat const &B) const;
};



#endif /* _PRESIDENTIALPARDONFORM_ */
