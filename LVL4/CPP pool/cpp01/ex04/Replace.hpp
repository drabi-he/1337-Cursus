/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 22:35:46 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/28 23:11:30 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _REPLACE_
#define _REPLACE_

# include <fstream>

class Replace
{
    private:
        std::string oldString;
        std::string newString;
        std::string inFile;
        std::string outFile;
    public:
        Replace(std::string oldString, std::string newString, std::string inFile);
        ~Replace();
        void    replaceAll();
};


#endif