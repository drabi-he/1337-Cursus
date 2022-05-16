/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 22:51:25 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/13 16:24:14 by hdrabi           ###   ########.fr       */
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

    if (!this->oldString.compare("") || !this->inFile.compare("")){
        std::cout << "\033[1m\033[31m" << "infile \\ string to replace can't be empty" << "\033[0m" << std::endl;
        return ;
    }
    infile.open(this->inFile);
    len = this->oldString.length();
    if (infile.is_open())
    {
        outfile.open(this->outFile);
        while (getline(infile, line))
        {
            if (this->oldString != this->newString)
            while((i = line.find(this->oldString)) != -1)
            {
                line.erase(i, len);
                line.insert(i, this->newString);
            }
            if (outfile.is_open())
                outfile << line << std::endl;
            else
            std::cout << "\033[1m\033[31m" << "outfile can't be opened" << "\033[0m" << std::endl;
        }
    } else
        std::cout << "\033[1m\033[31m" << "infile can't be opened" << "\033[0m" << std::endl;
    infile.close();
    outfile.close();
}
