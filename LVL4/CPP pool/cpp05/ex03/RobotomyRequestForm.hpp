/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:33:10 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 17:11:57 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ROBOTOMYREQUESTFORM_
#define _ROBOTOMYREQUESTFORM_

#include "Form.hpp"
#include <iostream>

class RobotomyRequestForm : public Form
{
    private:
        std::string target;
    public:
        RobotomyRequestForm();
        RobotomyRequestForm(const std::string &target);
        RobotomyRequestForm(const RobotomyRequestForm &RRF);
        RobotomyRequestForm &operator=(const RobotomyRequestForm &RRF);
        ~RobotomyRequestForm();
        void execute(Bureaucrat const &B) const;
        void valid(Bureaucrat const &B) const;
};

#endif /* _ROBOTOMYREQUESTFORM_ */