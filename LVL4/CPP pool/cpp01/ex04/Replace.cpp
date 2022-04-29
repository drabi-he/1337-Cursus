/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 22:51:25 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/28 23:56:22 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"

Replace::Replace(std::string oldString, std::string newString, std::string inFile){
    this->oldString = oldString;
    this->newString = newString;
    this->inFile = inFile;
    this->outFile = inFile + ".replace";
}

Replace::~Replace(){}

void    Replace::replaceAll(){
    std::ifstream infile;
    std::ofstream outfile;
    std::string line;
    int len;
    int i;

    if (!this->oldString.compare("") || !this->inFile.compare(""))
        return ;
    infile.open(this->inFile);
    outfile.open(this->outFile);
    len = this->oldString.length();
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            while((i = line.find(this->oldString)) != -1)
            {
                line.erase(i, len);
                line.insert(i, this->newString);
            }
            outfile << line << std::endl;
        }
    }
    infile.close();
    outfile.close();
}
