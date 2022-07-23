/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorTest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:56:18 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/23 17:56:44 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <iterator>
#include "./vector/vector.hpp"
#include "./iterators/iterator.hpp"

int main (){
    std::cout << "\033[36m" << "************************************ test 0 < constructors , iterators > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v1;
            std::vector<int> v2(5, 5);
            std::vector<int> v3(v2.begin(), v2.end());
            std::vector<int> v4(v3);
            

            std::cout << "*********** v1 < normal > ************" << std::endl;
            for (std::vector<int>::iterator it = v1.begin() ; it != v1.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            
            std::cout << "*********** v1 < reverse > ************" << std::endl;
            for (std::vector<int>::reverse_iterator it = v1.rbegin() ; it != v1.rend(); it++)
                std::cout << "\t" << *it;
            std::cout << std::endl;

            std::cout << "*********** v2 < normal > ************" << std::endl;
            for (std::vector<int>::iterator it = v2.begin() ; it != v2.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            
            std::cout << "*********** v2 < reverse > ************" << std::endl;
            for (std::vector<int>::reverse_iterator it = v2.rbegin() ; it != v2.rend(); it++)
                std::cout << "\t" << *it;
            std::cout << std::endl;

            std::cout << "*********** v3 < normal > ************" << std::endl;
            for (std::vector<int>::iterator it = v3.begin() ; it != v3.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            
            std::cout << "*********** v3 < reverse > ************" << std::endl;
            for (std::vector<int>::reverse_iterator it = v3.rbegin() ; it != v3.rend(); it++)
                std::cout << "\t" << *it;
            std::cout << std::endl;

            std::cout << "*********** v4 < normal > ************" << std::endl;
            for (std::vector<int>::iterator it = v4.begin() ; it != v4.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            
            std::cout << "*********** v4 < reverse > ************" << std::endl;
            for (std::vector<int>::reverse_iterator it = v4.rbegin() ; it != v4.rend(); it++)
                std::cout << "\t" << *it;
            std::cout << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v1;
            ft::vector<int> v2(5, 5);
            ft::vector<int> v3(v2.begin(), v2.end());
            ft::vector<int> v4(v3);
            

            std::cout << "*********** v1 < normal > ************" << std::endl;
            for (ft::vector<int>::iterator it = v1.begin() ; it != v1.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            
            std::cout << "*********** v1 < reverse > ************" << std::endl;
            for (ft::vector<int>::reverse_iterator it = v1.rbegin() ; it != v1.rend(); it++)
                std::cout << "\t" << *it;
            std::cout << std::endl;

            std::cout << "*********** v2 < normal > ************" << std::endl;
            for (ft::vector<int>::iterator it = v2.begin() ; it != v2.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            
            std::cout << "*********** v2 < reverse > ************" << std::endl;
            for (ft::vector<int>::reverse_iterator it = v2.rbegin() ; it != v2.rend(); it++)
                std::cout << "\t" << *it;
            std::cout << std::endl;

            std::cout << "*********** v3 < normal > ************" << std::endl;
            for (ft::vector<int>::iterator it = v3.begin() ; it != v3.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            
            std::cout << "*********** v3 < reverse > ************" << std::endl;
            for (ft::vector<int>::reverse_iterator it = v3.rbegin() ; it != v3.rend(); it++)
                std::cout << "\t" << *it;
            std::cout << std::endl;

            std::cout << "*********** v4 < normal > ************" << std::endl;
            for (ft::vector<int>::iterator it = v4.begin() ; it != v4.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            
            std::cout << "*********** v4 < reverse > ************" << std::endl;
            for (ft::vector<int>::reverse_iterator it = v4.rbegin() ; it != v4.rend(); it++)
                std::cout << "\t" << *it;
            std::cout << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        
    }
    
    std::cout << std::endl << "\033[36m" << "************************************ test 1 < max_size > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v(10, 3);
            
            std::cout << v.max_size() << std::endl;

            for (std::vector<int>::iterator it = v.begin() ; it != v.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            
            // * resize
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            v.resize(5);
            for (std::vector<int>::iterator it = v.begin() ; it != v.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;  
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.resize(11);
            for (std::vector<int>::iterator it = v.begin() ; it != v.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v(10, 3);
            
            std::cout << v.max_size() << std::endl;

            for (ft::vector<int>::iterator it = v.begin() ; it != v.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            
            // * resize
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            v.resize(5);
            for (ft::vector<int>::iterator it = v.begin() ; it != v.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.resize(11);
            for (ft::vector<int>::iterator it = v.begin() ; it != v.end(); it++)
                std::cout << "\t" << *it ;
            std::cout << std::endl;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    
    std::cout << std::endl << "\033[36m" << "************************************ test 2 < size , capacity > ************************************ " << "\033[0m" << std::endl;
    {
        int values = 10;
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v;

            // * size & capacity
            for (int i = 0; i < values ; i++){
                std::cout << "size = " << v.size() << " | ";
                std::cout << "capacity = " << v.capacity() << std::endl;
                v.push_back(i);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v;

            // * size & capacity
            for (int i = 0; i < values ; i++){
                std::cout << "size = " << v.size() << " | ";
                std::cout << "capacity = " << v.capacity() << std::endl;
                v.push_back(i);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 3 < resize > ************************************ " << "\033[0m" << std::endl;
    {
        int values = 10;
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v;

            for (int i = 0; i < values ; i++)
                v.push_back(i);
                
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;

            v.resize (0);
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.resize (17);
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;

            v.resize (70);
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v;

            for (int i = 0; i < values ; i++)
                v.push_back(i);

            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.resize (0);
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.resize (17);
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;

            v.resize (70);
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 4 < empty > ************************************ " << "\033[0m" << std::endl;
    {
        int values = 10;
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v(5);

            std::cout << "if initialised the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;
            
            v.resize(0);
            std::cout << "after resize the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;
            
            for (int i = 0; i < values ; i++){
                v.push_back(i);
            }
            for (std::vector<int>::iterator i = v.begin() ; i < v.end() ; i++){
                std::cout << "\t" << *i << std::endl;
            }
            std::cout << "after pushing the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v(5);

            std::cout << "if initialised the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;
            
            v.resize(0);
            std::cout << "after resize the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;
            
            for (int i = 0; i < values ; i++){
                v.push_back(i);
            }
            for (ft::vector<int>::iterator i = v.begin() ; i < v.end() ; i++){
                std::cout << "\t" << *i << std::endl;
            }

            std::cout << "after pushing the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 5 < reserve > ************************************ " << "\033[0m" << std::endl;
    {
        int value = 5;
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v(value);
            
            std::cout << "capacity = " << v.capacity() << std::endl;
            for (int i = 0; i < value ; i++){
                v.push_back(i);
            }
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++){
               std::cout << "\t" << *i << std::endl;
            }
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.reserve(value * 3);
            std::cout << "capacity = " << v.capacity() << std::endl;

            v.reserve(value);
            std::cout << "capacity = " << v.capacity() << std::endl;
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++){
                std::cout << "\t" << *i << std::endl;
            }
            
            v.reserve(value * 4);
            std::cout << "capacity = " << v.capacity() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v(value);
            
            std::cout << "capacity = " << v.capacity() << std::endl;
            for (int i = 0; i < value ; i++){
                v.push_back(i);
            }
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++){
               std::cout << "\t" << *i << std::endl;
            }
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.reserve(value * 3);
            std::cout << "capacity = " << v.capacity() << std::endl;

            v.reserve(value);
            std::cout << "capacity = " << v.capacity() << std::endl;
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++){
                std::cout << "\t" << *i << std::endl;
            }
            v.reserve(value * 4);
            std::cout << "capacity = " << v.capacity() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 6 < operator [] > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v(10);

            v[100] = 15;
            std::cout << v[100] << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v(10);

            v[100] = 15;
            std::cout << v[100] << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 7 < at > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v(10);

            v.at(8) = 15;
            std::cout << v.at(8) << std::endl;
            std::cout << v.at(9) << std::endl;
            std::cout << v.at(10) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v(10);

            v.at(8) = 15;
            std::cout << v.at(8) << std::endl;
            std::cout << v.at(9) << std::endl;
            std::cout << v.at(10) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 8 < front , back > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v;

            v.push_back(11);
            std::cout << "front = " << v.front() << std::endl;
            std::cout << "back = " << v.back() << std::endl;

            v.push_back(5);
            std::cout << "front = " << v.front() << std::endl;
            std::cout << "back = " << v.back() << std::endl;

            v.front() = 1;
            v.back() = 15;
            std::cout << "front = " << v.front() << std::endl;
            std::cout << "back = " << v.back() << std::endl;

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v;

            v.push_back(11);
            std::cout << "front = " << v.front() << std::endl;
            std::cout << "back = " << v.back() << std::endl;

            v.push_back(5);
            std::cout << "front = " << v.front() << std::endl;
            std::cout << "back = " << v.back() << std::endl;

            v.front() = 1;
            v.back() = 15;
            std::cout << "front = " << v.front() << std::endl;
            std::cout << "back = " << v.back() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 9 < assign > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v(10);
            std::vector<int> v2;

            v.push_back(5);
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl ;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.assign(15, 10);
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl ;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "size = " << v[8] << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;

            std::cout << "size 2 = " << v2.size() << std::endl;
            std::cout << "capacity 2 = " << v2.capacity() << std::endl;
            v2.push_back(5);
            v2.assign(v.begin() + 1, v.end() - 1);
            for (std::vector<int>::iterator i = v2.begin(); i < v2.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl ;
            std::cout << "size 2 = " << v2.size() << std::endl;
            std::cout << "capacity 2 = " << v2.capacity() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v(10);
            ft::vector<int> v2;

            v.push_back(5);
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl ;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.assign(15, 10);
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl ;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "size = " << v[8] << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;

            std::cout << "size 2 = " << v2.size() << std::endl;
            std::cout << "capacity 2 = " << v2.capacity() << std::endl;
            v2.push_back(5);
            v2.assign(v.begin() + 1, v.end() - 1);
            for (ft::vector<int>::iterator i = v2.begin(); i < v2.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl ;
            std::cout << "size 2 = " << v2.size() << std::endl;
            std::cout << "capacity 2 = " << v2.capacity() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }  
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 10 < push_back > ************************************ " << "\033[0m" << std::endl;
    {
        int values = 10;
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v;
            
            for (int i = 0; i < values ; i++)
                v.push_back(i);
            
            for (std::vector<int>::iterator i = v.begin(); i != v.end() ; i++)
                std::cout << "\t" << *i << std::endl;
                
            v.resize(0);
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.resize(10);
            for (std::vector<int>::iterator i = v.begin(); i != v.end() ; i++)
                std::cout << "\t" << *i << std::endl;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v;
            
            for (int i = 0; i < values ; i++)
                v.push_back(i);
                
            for (ft::vector<int>::iterator i = v.begin(); i != v.end() ; i++)
                std::cout << "\t" << *i << std::endl;
                
            v.resize(0);
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.resize(10);
            for (ft::vector<int>::iterator i = v.begin(); i != v.end() ; i++)
                std::cout << "\t" << *i << std::endl;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 11 < pop_back > ************************************ " << "\033[0m" << std::endl;
    {
        int value = 5;
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v;

            for (int i = 0; i < value ; i++){
                v.push_back(i);
            }
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.pop_back();
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            std::cout << "capacity = " << *(v.end()) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v;

            for (int i = 0; i < value ; i++){
                v.push_back(i);
            }
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            
            v.pop_back();
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            std::cout << "capacity = " << *(v.end()) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        } 
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 12 < insert > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v (3,100);
            std::vector<int>::iterator it;

            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
                    
            it = v.begin();
            it = v.insert ( it , 200 );
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
            
            it = v.begin() + 2;
            v.insert ( it , 6 , 10 );
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
            
            it = v.begin();
            std::vector<int> v1 (2,400);
            v.insert (it + 2 , v1.begin() , v1.end());
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;

            int myarray [] = { 501,502,503 };
            v.insert (v.begin(), myarray, myarray+3);
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v (3,100);
            ft::vector<int>::iterator it;

            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
                    
            it = v.begin();
            it = v.insert ( it , 200 );
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
            it = v.begin() + 2;
            v.insert ( it , 6 , 10 );
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;

            it = v.begin();
            ft::vector<int> v1 (2,400);
            v.insert (it + 2 , v1.begin() , v1.end());
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;

            int myarray [] = { 501,502,503 };
            v.insert (v.begin(), myarray, myarray+3);
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 13 < erase > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v;

            for (int i=1; i<=10; i++)
                v.push_back(i);
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
            
            v.erase (v.begin()+5);
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;

            v.erase (v.begin(),v.begin() + 2);
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;

            std::cout << "\t" << *(v.end()) << std::endl;
                
            v.erase (v.begin() + 2,v.begin() + 5);
            for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;

            std::cout << "\t" << *(v.end()) << std::endl;
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v;

            for (int i=1; i<=10; i++)
                v.push_back(i);
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
            
            v.erase (v.begin()+5);
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;

            v.erase (v.begin(),v.begin() + 2);
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;
            
            std::cout << "\t" << *(v.end()) << std::endl;
                
            v.erase (v.begin() + 2,v.begin() + 5);
            for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
                std::cout << "\t" << *i ;
            std::cout << std::endl;

            std::cout << "\t" << *(v.end()) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 14 < swap > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> foo (3,100);
            std::vector<int> bar (5,200);

            std::cout << "foo size = " << foo.size() << '\n';
            std::cout << "foo capacity = " << foo.capacity() << '\n';
            std::cout << "foo addr  = " << &(*foo.begin()) << '\n';
            std::cout << "bar size = " << bar.size() << '\n';
            std::cout << "bar capacity = " << bar.capacity() << '\n';
            std::cout << "bar addr  = " << &(*bar.begin()) << '\n';
            foo.swap(bar);

            std::cout << "foo contains:";
            for (unsigned i=0; i<foo.size(); i++)
                std::cout << ' ' << foo[i];
            std::cout << '\n';
            std::cout << "foo size = " << foo.size() << '\n';
            std::cout << "foo capacity = " << foo.capacity() << '\n';
            std::cout << "foo addr  = " << &(*foo.begin()) << '\n';

            std::cout << "bar contains:";
            for (unsigned i=0; i<bar.size(); i++)
                std::cout << ' ' << bar[i];
            std::cout << '\n';
            std::cout << "bar size = " << bar.size() << '\n';
            std::cout << "bar capacity = " << bar.capacity() << '\n';
            std::cout << "bar addr  = " << &(*bar.begin()) << '\n';
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> foo (3,100);
            ft::vector<int> bar (5,200);

            std::cout << "foo size = " << foo.size() << '\n';
            std::cout << "foo capacity = " << foo.capacity() << '\n';
            std::cout << "foo addr  = " << &(*foo.begin()) << '\n';
            std::cout << "bar size = " << bar.size() << '\n';
            std::cout << "bar capacity = " << bar.capacity() << '\n';
            std::cout << "bar addr  = " << &(*bar.begin()) << '\n';
            foo.swap(bar);

            std::cout << "foo contains:";
            for (unsigned i=0; i<foo.size(); i++)
                std::cout << ' ' << foo[i];
            std::cout << '\n';
            std::cout << "foo size = " << foo.size() << '\n';
            std::cout << "foo capacity = " << foo.capacity() << '\n';
            std::cout << "foo addr  = " << &(*foo.begin()) << '\n';

            std::cout << "bar contains:";
            for (unsigned i=0; i<bar.size(); i++)
                std::cout << ' ' << bar[i];
            std::cout << '\n';
            std::cout << "bar size = " << bar.size() << '\n';
            std::cout << "bar capacity = " << bar.capacity() << '\n';
            std::cout << "bar addr  = " << &(*bar.begin()) << '\n';
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 15 < clear > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> v;
            v.push_back (100);
            v.push_back (200);
            v.push_back (300);

            std::cout << "contains:";
            for (unsigned i = 0; i < v.size() ; i++)
                std::cout << ' ' << v[i];
            std::cout << std::endl;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;

            v.clear();
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            v.push_back (1101);
            v.push_back (2202);

            std::cout << "contains:";
            for (unsigned i = 0; i < v.size() ; i++)
                std::cout << ' ' << v[i];
            std::cout << std::endl;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            std::cout << "end = " << *v.end() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v;
            v.push_back (100);
            v.push_back (200);
            v.push_back (300);

            std::cout << "contains:";
            for (unsigned i = 0; i < v.size() ; i++)
                std::cout << ' ' << v[i];
            std::cout << std::endl;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;

            v.clear();
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            v.push_back (1101);
            v.push_back (2202);

            std::cout << "contains:";
            for (unsigned i = 0; i < v.size() ; i++)
                std::cout << ' ' << v[i];
            std::cout << std::endl;
            std::cout << "size = " << v.size() << std::endl;
            std::cout << "capacity = " << v.capacity() << std::endl;
            std::cout << "end = " << *v.end() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 16 < non-member functions > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            std::vector<int> foo (3,100); 
            std::vector<int> bar (2,200); 

            if (foo == bar) std::cout << "foo and bar are equal\n";
            if (foo != bar) std::cout << "foo and bar are not equal\n";
            if (foo < bar) std::cout << "foo is less than bar\n";
            if (foo > bar) std::cout << "foo is greater than bar\n";
            if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
            if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";

            foo.swap(bar);
            if (foo == bar) std::cout << "foo and bar are equal\n";
            if (foo != bar) std::cout << "foo and bar are not equal\n";
            if (foo < bar) std::cout << "foo is less than bar\n";
            if (foo > bar) std::cout << "foo is greater than bar\n";
            if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
            if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
            
            std::cout << "foo: ";
            for (unsigned i = 0; i < foo.size() ; i++)
                std::cout << ' ' << foo[i];
            std::cout << std::endl;
            std::cout << "bar: ";
            for (unsigned i = 0; i < bar.size() ; i++)
                std::cout << ' ' << bar[i];
            std::cout << std::endl;
            std::swap(foo, bar);
            std::cout << "foo: ";
            for (unsigned i = 0; i < foo.size() ; i++)
                std::cout << ' ' << foo[i];
            std::cout << std::endl;
            std::cout << "bar: ";
            for (unsigned i = 0; i < bar.size() ; i++)
                std::cout << ' ' << bar[i];
            std::cout << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> foo (3,100); 
            ft::vector<int> bar (2,200);


            if (foo == bar) std::cout << "foo and bar are equal\n";
            if (foo != bar) std::cout << "foo and bar are not equal\n";
            if (foo < bar) std::cout << "foo is less than bar\n";
            if (foo > bar) std::cout << "foo is greater than bar\n";
            if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
            if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
            
            foo.swap(bar);
            if (foo == bar) std::cout << "foo and bar are equal\n";
            if (foo != bar) std::cout << "foo and bar are not equal\n";
            if (foo < bar) std::cout << "foo is less than bar\n";
            if (foo > bar) std::cout << "foo is greater than bar\n";
            if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
            if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";

            std::cout << "foo: ";
            for (unsigned i = 0; i < foo.size() ; i++)
                std::cout << ' ' << foo[i];
            std::cout << std::endl;
            std::cout << "bar: ";
            for (unsigned i = 0; i < bar.size() ; i++)
                std::cout << ' ' << bar[i];
            std::cout << std::endl;
            ft::swap(foo, bar);
            std::cout << "foo: ";
            for (unsigned i = 0; i < foo.size() ; i++)
                std::cout << ' ' << foo[i];
            std::cout << std::endl;
            std::cout << "bar: ";
            for (unsigned i = 0; i < bar.size() ; i++)
                std::cout << ' ' << bar[i];
            std::cout << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    
}
