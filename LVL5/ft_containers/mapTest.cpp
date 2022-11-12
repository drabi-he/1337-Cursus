/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:05:19 by hdrabi            #+#    #+#             */
/*   Updated: 2022/11/12 14:10:23 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <iterator>
#include "./map/map.hpp"


int main() {

    std::cout << "\033[36m" << "************************************ test 0 < constructors , iterators > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::map<std::string, int> m1;

            m1["c"] = 1;
            m1["a"] = 2;
            m1["b"] = 3;
            m1["d"] = 4;

            std::map<std::string, int> m2(m1.begin(), m1.end());
            std::map<std::string, int> m3(m1);

            std::cout << "*********** m1 < normal > ************" << std::endl;
            for (std::map<std::string, int>::iterator it = m1.begin() ; it != m1.end(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;

            std::cout << "*********** m1 < reverse > ************" << std::endl;
            for (std::map<std::string, int>::reverse_iterator it = m1.rbegin() ; it != m1.rend(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;

            std::cout << "*********** m2 < normal > ************" << std::endl;
            for (std::map<std::string, int>::iterator it = m2.begin() ; it != m2.end(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;

            std::cout << "*********** m2 < reverse > ************" << std::endl;
            for (std::map<std::string, int>::reverse_iterator it = m2.rbegin() ; it != m2.rend(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;

            std::cout << "*********** m3 < normal > ************" << std::endl;
            for (std::map<std::string, int>::iterator it = m3.begin() ; it != m3.end(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;

            std::cout << "*********** m3 < reverse > ************" << std::endl;
            for (std::map<std::string, int>::reverse_iterator it = m3.rbegin() ; it != m3.rend(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {

            ft::map<std::string, int> m1;

            m1["c"] = 1;
            m1["a"] = 2;
            m1["b"] = 3;
            m1["d"] = 4;

            ft::map<std::string, int> m2(m1.begin(), m1.end());
            ft::map<std::string, int> m3(m1);

            std::cout << "*********** m1 < normal > ************" << std::endl;
            for (ft::map<std::string, int>::iterator it = m1.begin() ; it != m1.end(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;

            std::cout << "*********** m1 < reverse > ************" << std::endl;
            for (ft::map<std::string, int>::reverse_iterator it = m1.rbegin() ; it != m1.rend(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;

            std::cout << "*********** m2 < normal > ************" << std::endl;
            for (ft::map<std::string, int>::iterator it = m2.begin() ; it != m2.end(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;

            std::cout << "*********** m2 < reverse > ************" << std::endl;
            for (ft::map<std::string, int>::reverse_iterator it = m2.rbegin() ; it != m2.rend(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;

            std::cout << "*********** m3 < normal > ************" << std::endl;
            for (ft::map<std::string, int>::iterator it = m3.begin() ; it != m3.end(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;

            std::cout << "*********** m3 < reverse > ************" << std::endl;
            for (ft::map<std::string, int>::reverse_iterator it = m3.rbegin() ; it != m3.rend(); it++)
                std::cout << "\n" << it->first << "\t" << it->second;
            std::cout << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

    }

    std::cout << std::endl << "\033[36m" << "************************************ test 1 < empty , size , max_size > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::map<std::string, int> m1;
            std::map<int , int> m2;
            std::map<std::string , std::string> m3;

            std::cout << "m1 empty : " << m1.empty() << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1["a"] = 1;
            std::cout << "m1 empty : " << m1.empty() << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1["b"] = 2;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1["c"] = 3;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1["d"] = 4;
            std::cout << "m1 size : " << m1.size() << std::endl;

            std::cout << "m1 max_size : " << m1.max_size() << std::endl;
            std::cout << "m2 max_size : " << m2.max_size() << std::endl;
            std::cout << "m3 max_size : " << m3.max_size() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::map<std::string, int> m1;
            ft::map<int , int> m2;
            ft::map<std::string , std::string> m3;

            std::cout << "m1 empty : " << m1.empty() << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1["a"] = 1;
            std::cout << "m1 empty : " << m1.empty() << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1["b"] = 2;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1["c"] = 3;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1["d"] = 4;
            std::cout << "m1 size : " << m1.size() << std::endl;

            std::cout << "m1 max_size : " << m1.max_size() << std::endl;
            std::cout << "m2 max_size : " << m2.max_size() << std::endl;
            std::cout << "m3 max_size : " << m3.max_size() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 2 < insert > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::map<std::string, int> m1;
            std::pair<std::map<std::string, int>::iterator, bool> p;

            p = m1.insert(std::make_pair("a", 1));
            std::cout << std::boolalpha;
            std::cout << "insert a : " << "[ " << p.first->first << " , " << p.first->second << " ] | Added : " << p.second << std::endl;
            p = m1.insert(std::make_pair("a", 1));
            std::cout << "insert a : " << "[ " << p.first->first << " , " << p.first->second << " ] | Added : " << p.second << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;

            p = m1.insert(std::make_pair("b", 2));
            std::cout << "insert b : " << "[ " << p.first->first << " , " << p.first->second << " ] | Added : " << p.second << std::endl;
            p = m1.insert(std::make_pair("b", 2));
            std::cout << "insert b : " << "[ " << p.first->first << " , " << p.first->second << " ] | Added : " << p.second << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;

            std::map<std::string, int> m2;
            std::map<std::string, int>::iterator it;
            m2["a"] = 1;
            m2["b"] = 2;
            m2["d"] = 4;
            m2["e"] = 5;
            m2["f"] = 6;
            m2["g"] = 7;
            m2["h"] = 8;
            std::cout << "*********** m2 before ************" << std::endl;
            for (std::map<std::string, int>::iterator it2 = m2.begin() ; it2 != m2.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;

            it = m2.insert(m2.begin(), std::make_pair("c", 3));
            std::cout << "*********** m2 after ************" << std::endl;
            for (std::map<std::string, int>::iterator it2 = m2.begin() ; it2 != m2.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "insert c : " << "[ " << it->first << " , " << it->second << " ]" << std::endl;
            std::cout << "m2 size : " << m2.size() << std::endl;

            std::map<std::string, int> m3;
            m3["a"] = 1;
            m3["b"] = 2;

            std::cout << "*********** m3 before ************" << std::endl;
            for (std::map<std::string, int>::iterator it2 = m3.begin() ; it2 != m3.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m3 size : " << m3.size() << std::endl;

            m3.insert(m2.begin(), m2.end());
            std::cout << "*********** m3 after ************" << std::endl;
            for (std::map<std::string, int>::iterator it2 = m3.begin() ; it2 != m3.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m3 size : " << m3.size() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::map<std::string, int> m1;
            ft::pair<ft::map<std::string, int>::iterator, bool> p;

            p = m1.insert(ft::make_pair("a", 1));
            std::cout << std::boolalpha;
            std::cout << "insert a : " << "[ " << p.first->first << " , " << p.first->second << " ] | Added : "<< p.second << std::endl;
            p = m1.insert(ft::make_pair("a", 1));
            std::cout << "insert a : " << "[ " << p.first->first << " , " << p.first->second << " ] | Added : "<< p.second << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;

            p = m1.insert(ft::make_pair("b", 2));
            std::cout << "insert b : " << "[ " << p.first->first << " , " << p.first->second << " ] | Added : " << p.second << std::endl;
            p = m1.insert(ft::make_pair("b", 2));
            std::cout << "insert b : " << "[ " << p.first->first << " , " << p.first->second << " ] | Added : " << p.second << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;

            ft::map<std::string, int> m2;
            ft::map<std::string, int>::iterator it;
            m2["a"] = 1;
            m2["b"] = 2;
            m2["d"] = 4;
            m2["e"] = 5;
            m2["f"] = 6;
            m2["g"] = 7;
            m2["h"] = 8;
            std::cout << "*********** m2 before ************" << std::endl;
            for (ft::map<std::string, int>::iterator it2 = m2.begin() ; it2 != m2.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;

            it = m2.insert(m2.begin(), ft::make_pair("c", 3));
            std::cout << "*********** m2 after ************" << std::endl;
            for (ft::map<std::string, int>::iterator it2 = m2.begin() ; it2 != m2.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "insert c : " << "[ " << it->first << " , " << it->second << " ]" << std::endl;
            std::cout << "m2 size : " << m2.size() << std::endl;

            ft::map<std::string, int> m3;
            m3["a"] = 1;
            m3["b"] = 2;

            std::cout << "*********** m3 before ************" << std::endl;
            for (ft::map<std::string, int>::iterator it2 = m3.begin() ; it2 != m3.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m3 size : " << m3.size() << std::endl;

            m3.insert(m2.begin(), m2.end());
            std::cout << "*********** m3 after ************" << std::endl;
            for (ft::map<std::string, int>::iterator it2 = m3.begin() ; it2 != m3.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m3 size : " << m3.size() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 3 < erase > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::map<std::string, int> m1;

            m1["a"] = 1;
            m1["b"] = 2;
            m1["c"] = 3;
            m1["d"] = 4;
            m1["e"] = 5;
            m1["f"] = 6;
            std::cout << "*********** m1 before ************" << std::endl;
            for (std::map<std::string, int>::iterator it2 = m1.begin() ; it2 != m1.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1.erase(m1.begin());
            std::cout << "*********** m1 after 1 ************" << std::endl;
            for (std::map<std::string, int>::iterator it2 = m1.begin() ; it2 != m1.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;
            std::cout << "elements erased : " << m1.erase("d") << std::endl;
            std::cout << "elements erased : " << m1.erase("d") << std::endl;
            std::cout << "*********** m1 after 2 ************" << std::endl;
            for (std::map<std::string, int>::iterator it2 = m1.begin() ; it2 != m1.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1.erase(m1.begin(), ++(++m1.begin()));
            std::cout << "*********** m1 after 3 ************" << std::endl;
            for (std::map<std::string, int>::iterator it2 = m1.begin() ; it2 != m1.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::map<std::string, int> m1;

            m1["a"] = 1;
            m1["b"] = 2;
            m1["c"] = 3;
            m1["d"] = 4;
            m1["e"] = 5;
            m1["f"] = 6;
            std::cout << "*********** m1 before ************" << std::endl;
            for (ft::map<std::string, int>::iterator it2 = m1.begin() ; it2 != m1.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1.erase(m1.begin());
            std::cout << "*********** m1 after 1 ************" << std::endl;
            for (ft::map<std::string, int>::iterator it2 = m1.begin() ; it2 != m1.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;
            std::cout << "elements erased : " << m1.erase("d") << std::endl;
            std::cout << "elements erased : " << m1.erase("d") << std::endl;
            std::cout << "*********** m1 after 2 ************" << std::endl;
            for (ft::map<std::string, int>::iterator it2 = m1.begin() ; it2 != m1.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;
            m1.erase(m1.begin(), ++(++m1.begin()));
            std::cout << "*********** m1 after 3 ************" << std::endl;
            for (ft::map<std::string, int>::iterator it2 = m1.begin() ; it2 != m1.end(); it2++)
                std::cout << "\n" << it2->first << "\t" << it2->second;
            std::cout << std::endl;
            std::cout << "m1 size : " << m1.size() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 4 < swap > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::map<char,int> foo,bar;

            foo['x']=100;
            foo['y']=200;

            bar['a']=11;
            bar['b']=22;
            bar['c']=33;

            std::cout << "foo contains:\n";
            for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "foo size : " << foo.size() << std::endl;

            std::cout << "bar contains:\n";
            for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "bar size : " << bar.size() << std::endl;

            foo.swap(bar);

            std::cout << "foo contains:\n";
            for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "foo size : " << foo.size() << std::endl;

            std::cout << "bar contains:\n";
            for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "bar size : " << bar.size() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::map<char,int> foo,bar;

            foo['x']=100;
            foo['y']=200;

            bar['a']=11;
            bar['b']=22;
            bar['c']=33;

            std::cout << "foo contains:\n";
            for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "foo size : " << foo.size() << std::endl;

            std::cout << "bar contains:\n";
            for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "bar size : " << bar.size() << std::endl;

            foo.swap(bar);

            std::cout << "foo contains:\n";
            for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "foo size : " << foo.size() << std::endl;

            std::cout << "bar contains:\n";
            for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "bar size : " << bar.size() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 5 < clear > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::map<char,int> m1;

            m1['x']=100;
            m1['y']=200;
            m1['z']=300;

            std::cout << "m1 contains:\n";
            for (std::map<char,int>::iterator it=m1.begin(); it!=m1.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "m1 size : " << m1.size() << std::endl;

            m1.clear();
            std::cout << "m1 contains:\n";
            for (std::map<char,int>::iterator it=m1.begin(); it!=m1.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "m1 size : " << m1.size() << std::endl;

            m1['a']=1101;
            m1['b']=2202;

            std::cout << "m1 contains:\n";
            for (std::map<char,int>::iterator it=m1.begin(); it!=m1.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "m1 size : " << m1.size() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::map<char,int> m1;

            m1['x']=100;
            m1['y']=200;
            m1['z']=300;

            std::cout << "m1 contains:\n";
            for (ft::map<char,int>::iterator it=m1.begin(); it!=m1.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "m1 size : " << m1.size() << std::endl;

            m1.clear();
            std::cout << "m1 contains:\n";
            for (ft::map<char,int>::iterator it=m1.begin(); it!=m1.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "m1 size : " << m1.size() << std::endl;

            m1['a']=1101;
            m1['b']=2202;

            std::cout << "m1 contains:\n";
            for (ft::map<char,int>::iterator it=m1.begin(); it!=m1.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';
            std::cout << "m1 size : " << m1.size() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 6 < key_comp , value_comp > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            {
                std::map<char,int> m1;

                std::map<char,int>::key_compare _comp = m1.key_comp();

                m1['a']=100;
                m1['b']=200;
                m1['c']=300;

                std::cout << "m1 contains:\n";

                char highest = m1.rbegin()->first;     // key value of last element

                std::map<char,int>::iterator it = m1.begin();
                do {
                    std::cout << it->first << " => " << it->second << '\n';
                } while ( _comp((*it++).first, highest) );

                std::cout << '\n';
            }

            {
                std::map<char,int> m2;

                m2['x']=1001;
                m2['y']=2002;
                m2['z']=3003;

                std::cout << "m2 contains:\n";

                std::pair<char,int> highest = *m2.rbegin();          // last element

                std::map<char,int>::iterator it = m2.begin();
                do {
                    std::cout << it->first << " => " << it->second << '\n';
                } while ( m2.value_comp()(*it++, highest) );
            }

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            {
                ft::map<char,int> m1;

                ft::map<char,int>::key_compare _comp = m1.key_comp();

                m1['a']=100;
                m1['b']=200;
                m1['c']=300;

                std::cout << "m1 contains:\n";

                char highest = m1.rbegin()->first;     // key value of last element

                ft::map<char,int>::iterator it = m1.begin();
                do {
                    std::cout << it->first << " => " << it->second << '\n';
                } while ( _comp((*it++).first, highest) );

                std::cout << '\n';
            }

            {
                ft::map<char,int> m2;

                m2['x']=1001;
                m2['y']=2002;
                m2['z']=3003;

                std::cout << "m2 contains:\n";

                ft::pair<char,int> highest = *m2.rbegin();          // last element

                ft::map<char,int>::iterator it = m2.begin();
                do {
                    std::cout << it->first << " => " << it->second << '\n';
                } while ( m2.value_comp()(*it++, highest) );
            }

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 7 < find > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::map<char,int> m1;
            std::map<char,int>::iterator it;

            m1['a']=50;
            m1['b']=100;
            m1['c']=150;
            m1['d']=200;

            it = m1.find('b');
            if (it != m1.end())
                m1.erase (it);

            std::cout << "elements in m1:" << '\n';
            std::cout << "a => " << m1.find('a')->second << '\n';
            std::cout << "c => " << m1.find('c')->second << '\n';
            std::cout << "d => " << m1.find('d')->second << '\n';

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::map<char,int> m1;
            ft::map<char,int>::iterator it;

            m1['a']=50;
            m1['b']=100;
            m1['c']=150;
            m1['d']=200;

            it = m1.find('b');
            if (it != m1.end())
                m1.erase (it);

            std::cout << "elements in m1:" << '\n';
            std::cout << "a => " << m1.find('a')->second << '\n';
            std::cout << "c => " << m1.find('c')->second << '\n';
            std::cout << "d => " << m1.find('d')->second << '\n';

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 8 < count > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::map<char,int> m1;
            char c;

            m1 ['a']=101;
            m1 ['c']=202;
            m1 ['f']=303;

            for (c='a'; c<'h'; c++)
            {
                std::cout << c;
                if (m1.count(c)>0)
                std::cout << " is an element of m1.\n";
                else
                std::cout << " is not an element of m1.\n";
            }

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::map<char,int> m1;
            char c;

            m1 ['a']=101;
            m1 ['c']=202;
            m1 ['f']=303;

            for (c='a'; c<'h'; c++)
            {
                std::cout << c;
                if (m1.count(c)>0)
                std::cout << " is an element of m1.\n";
                else
                std::cout << " is not an element of m1.\n";
            }

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 9 < lower_bound , upper_bound , equal_range > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::map<char,int> m1;
            std::map<char,int>::iterator low,up;

            m1['a']=20;
            m1['b']=40;
            m1['c']=60;
            m1['d']=80;
            m1['e']=100;

            low=m1.lower_bound ('b');
            up=m1.upper_bound ('d');

            std::cout << "low : " << low->first << '\n';
            std::cout << "up : " << up->first << '\n';

            m1.erase(low,up);

            for (std::map<char,int>::iterator it=m1.begin(); it!=m1.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';

            std::map<char,int> m2;

            m2['a']=10;
            m2['b']=20;
            m2['d']=30;

            std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
            ret = m2.equal_range('b');

            std::cout << "\tequal_range for existing key: " << '\n';
            std::cout << "lower bound points to: ";
            std::cout << ret.first->first << " => " << ret.first->second << '\n';

            std::cout << "upper bound points to: ";
            std::cout << ret.second->first << " => " << ret.second->second << '\n';

            ret = m2.equal_range('c');


            std::cout << "\tequal_range for non-existing key: " << '\n';
            std::cout << "lower bound points to: ";
            std::cout << ret.first->first << " => " << ret.first->second << '\n';

            std::cout << "upper bound points to: ";
            std::cout << ret.second->first << " => " << ret.second->second << '\n';

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::map<char,int> m1;
            ft::map<char,int>::iterator low,up;

            m1['a']=20;
            m1['b']=40;
            m1['c']=60;
            m1['d']=80;
            m1['e']=100;

            low=m1.lower_bound ('b');
            up=m1.upper_bound ('d');

            std::cout << "low : " << low->first << '\n';
            std::cout << "up : " << up->first << '\n';

            m1.erase(low,up);

            for (ft::map<char,int>::iterator it=m1.begin(); it!=m1.end(); ++it)
                std::cout << it->first << " => " << it->second << '\n';

            ft::map<char,int> m2;

            m2['a']=10;
            m2['b']=20;
            m2['d']=30;

            ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
            ret = m2.equal_range('b');


            std::cout << "\tequal_range for existing key: " << '\n';
            std::cout << "lower bound points to: ";
            std::cout << ret.first->first << " => " << ret.first->second << '\n';

            std::cout << "upper bound points to: ";
            std::cout << ret.second->first << " => " << ret.second->second << '\n';

            ret = m2.equal_range('c');


            std::cout << "\tequal_range for non-existing key: " << '\n';
            std::cout << "lower bound points to: ";
            std::cout << ret.first->first << " => " << ret.first->second << '\n';

            std::cout << "upper bound points to: ";
            std::cout << ret.second->first << " => " << ret.second->second << '\n';
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

}