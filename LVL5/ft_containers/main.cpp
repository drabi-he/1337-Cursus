/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:58:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/28 18:04:58 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <iterator>
#include "./vector/vector.hpp"


// tests
# include <limits>

int main(){
    // try
    // {
    //     std::vector<int> v;
    //     v.push_back(1);
    //     v.push_back(4);
    //     v.push_back(5);
    //     v.push_back(7);
    //     v.push_back(9);
        
    //     std::cout << *(v.begin()) << std::endl;
    //     std::cout << *(v.begin() + 2) << std::endl;
    //     std::cout << "capacity = " << v.capacity() << std::endl;
    //     std::cout << "size = " << v.size() << std::endl;
    //     v.resize(3, 0);
    //     v.resize(1);
    //     v.resize(3, 0);
    //     v.resize(15);
    //     std::cout << "capacity = " << v.capacity() << std::endl;
    //     std::cout << "size = " << v.size() << std::endl;
    //     std::cout << *(v.begin()) << std::endl;
    //     std::cout << *(v.begin() + 2) << std::endl;
    //     std::cout << *(v.end()) << std::endl;
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
        
    // }
    std::cout << "****************** test 1 ******************" << std::endl;
    {
        // try
        // {
        //     std::vector<int> v(10);
            
        //     // * max capacity
        //     std::cout << v.max_size() << std::endl;

        //     // * resize
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.resize(1);
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.resize(11);
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v(10);
            
        //     // * max capacity
        //     std::cout << v.max_size() << std::endl;

        //     // * resize
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        //     v.resize(1 );
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        //     v.resize(11);
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
    }
    
    std::cout << "****************** test 2 ******************" << std::endl;
    {
        // try
        // {
        //     std::vector<int> v;
            
        //     // * push back
        //     for (int i = 0; i < 10 ; i++)
        //         v.push_back(i);
            
        //     for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
        //         std::cout << "\t" << *i << std::endl;
                
        //     v.resize(5);
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.resize(10);
        //     for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
        //         std::cout << "\t" << *i << std::endl;
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v;
            
        //     // * push_back
        //     for (int i = 0; i < 10 ; i++)
        //         v.push_back(i);
                
        //     for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
        //         std::cout << "\t" << *i << std::endl;
                
        //     v.resize(5);
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.resize(10);
        //     for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
        //         std::cout << "\t" << *i << std::endl;
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
    }
    
    std::cout << "****************** test 3 ******************" << std::endl;
    {
        // int values = 10;
        // try
        // {
        //     std::vector<int> v;

        //     std::cout << "empty = " << v.empty() << std::endl;

        //     for (int i = 0; i < values ; i++){
        //         std::cout << "size = " << v.size() << std::endl;
        //         std::cout << "capacity = " << v.capacity() << std::endl;
        //         v.push_back(i);
        //     }
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v;

        //     for (int i = 0; i < values ; i++){
        //         std::cout << "size = " << v.size() << std::endl;
        //         std::cout << "capacity = " << v.capacity() << std::endl;
        //         v.push_back(i);
        //     }
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
    }
    
    std::cout << "****************** test 4 ******************" << std::endl;
    {
        // int values = 10;
        // try
        // {
        //     std::vector<int> v;

        //     for (int i = 0; i < values ; i++)
        //         v.push_back(i);
                
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        //     v.resize (0);
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.resize (17);
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        //     v.resize (70);
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v;

        //     for (int i = 0; i < values ; i++)
        //         v.push_back(i);

        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.resize (0);
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.resize (17);
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        //     v.resize (70);
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
    }
    
    std::cout << "****************** test 5 ******************" << std::endl;
    {
        // int values = 10;
        // try
        // {
        //     std::vector<int> v(5);

        //     std::cout << "if initialised the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;
            
        //     v.resize(0);
        //     std::cout << "after resize the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;
            
        //     for (int i = 0; i < values ; i++){
        //         v.push_back(i);
        //     }
        //     for (std::vector<int>::iterator i = v.begin() ; i < v.end() ; i++){
        //         std::cout << "\t" << *i << std::endl;
        //     }
        //     std::cout << "after pushing the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;

        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v(5);

        //     std::cout << "if initialised the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;
            
        //     v.resize(0);
        //     std::cout << "after resize the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;
            
        //     for (int i = 0; i < values ; i++){
        //         v.push_back(i);
        //     }
        //     for (ft::vector<int>::iterator i = v.begin() ; i < v.end() ; i++){
        //         std::cout << "\t" << *i << std::endl;
        //     }
        //     std::cout << "after pushing the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
    }

    std::cout << "****************** test 6 ******************" << std::endl;
    {
        // int value = 5;
        // try
        // {
        //     std::vector<int> v(value);
            
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        //     for (int i = 0; i < value ; i++){
        //         v.push_back(i);
        //     }
        //     for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++){
        //        std::cout << "\t" << *i << std::endl;
        //     }
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.reserve(value * 3);
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        //     v.reserve(value);
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        //     for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++){
        //         std::cout << "\t" << *i << std::endl;
        //     }
            
        //     v.reserve(value * 4);
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v(value);
            
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        //     for (int i = 0; i < value ; i++){
        //         v.push_back(i);
        //     }
        //     for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++){
        //        std::cout << "\t" << *i << std::endl;
        //     }
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.reserve(value * 3);
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        //     v.reserve(value);
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        //     for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++){
        //         std::cout << "\t" << *i << std::endl;
        //     }
        //     v.reserve(value * 4);
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
    }    
    
    std::cout << "****************** test 7 ******************" << std::endl;
    {
        // int value = 10;
        // try
        // {
        //     std::vector<int> v(value);
            
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        //     v.shrink_to_fit();
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.resize(5);
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        //     v.shrink_to_fit();
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v(value);
            
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        //     v.shrink_to_fit();
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.resize(5);
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        //     v.shrink_to_fit();
        //     std::cout << "capacity = " << v.capacity() << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
    }

    std::cout << "****************** test 8 ******************" << std::endl;
    {
        // try
        // {
        //     std::vector<int> v(10);

        //     v[100] = 15;
        //     std::cout << v[100] << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v(10);

        //     v[100] = 15;
        //     std::cout << v[100] << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        
    }

    std::cout << "****************** test 9 ******************" << std::endl;
    {
        // try
        // {
        //     std::vector<int> v(10);

        //     v.at(8) = 15;
        //     std::cout << v.at(8) << std::endl;
        //     std::cout << v.at(9) << std::endl;
        //     std::cout << v.at(10) << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v(10);

        //     v.at(8) = 15;
        //     std::cout << v.at(8) << std::endl;
        //     std::cout << v.at(9) << std::endl;
        //     std::cout << v.at(10) << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
    }

    std::cout << "****************** test 10 ******************" << std::endl;
    {
        // try
        // {
        //     std::vector<int> v;

        //     v.push_back(11);
        //     std::cout << "front = " << v.front() << std::endl;
        //     std::cout << "back = " << v.back() << std::endl;

        //     v.push_back(5);
        //     std::cout << "front = " << v.front() << std::endl;
        //     std::cout << "back = " << v.back() << std::endl;

        //     v.front() = 1;
        //     v.back() = 15;
        //     std::cout << "front = " << v.front() << std::endl;
        //     std::cout << "back = " << v.back() << std::endl;

        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v;

        //     v.push_back(11);
        //     std::cout << "front = " << v.front() << std::endl;
        //     std::cout << "back = " << v.back() << std::endl;

        //     v.push_back(5);
        //     std::cout << "front = " << v.front() << std::endl;
        //     std::cout << "back = " << v.back() << std::endl;

        //     v.front() = 1;
        //     v.back() = 15;
        //     std::cout << "front = " << v.front() << std::endl;
        //     std::cout << "back = " << v.back() << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
    }

    std::cout << "****************** test 11 ******************" << std::endl;
    {
        // try
        // {
        //     std::vector<int> v(5);

        //     int* p = v.data();

        //     *p = 10;
        //     ++p;
        //     *p = 20;
        //     p[2] = 100;

        //     std::cout << "my vector contains : " << std::endl;
        //     for (unsigned i = 0; i < v.size() ; ++i)
        //         std::cout << '\t' << v[i] << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v(5);

        //     int* p = v.data();

        //     *p = 10;
        //     ++p;
        //     *p = 20;
        //     p[2] = 100;

        //     std::cout << "my vector contains : " << std::endl;
        //     for (unsigned i = 0; i < v.size() ; ++i)
        //         std::cout << '\t' << v[i] << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
    }
    
    std::cout << "****************** test 12 ******************" << std::endl;
    {
        // try
        // {
        //     std::vector<int> v(10);
        //     std::vector<int> v2;

        //     v.push_back(5);
        //     for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
        //         std::cout << "\t" << *i ;
        //     std::cout << std::endl ;
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.assign(15, 10);
        //     for (std::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
        //         std::cout << "\t" << *i ;
        //     std::cout << std::endl ;
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "size = " << v[8] << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        //     std::cout << "size 2 = " << v2.size() << std::endl;
        //     std::cout << "capacity 2 = " << v2.capacity() << std::endl;
        //     v2.push_back(5);
        //     v2.assign(v.begin() + 1, v.end() - 1);
        //     for (std::vector<int>::iterator i = v2.begin(); i < v2.end() ; i++)
        //         std::cout << "\t" << *i ;
        //     std::cout << std::endl ;
        //     std::cout << "size 2 = " << v2.size() << std::endl;
        //     std::cout << "capacity 2 = " << v2.capacity() << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }
        // std::cout << "----------------------------------------" << std::endl;
        // try
        // {
        //     ft::vector<int> v(10);
        //     ft::vector<int> v2;

        //     v.push_back(5);
        //     for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
        //         std::cout << "\t" << *i ;
        //     std::cout << std::endl ;
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;
            
        //     v.assign(15, 10);
        //     for (ft::vector<int>::iterator i = v.begin(); i < v.end() ; i++)
        //         std::cout << "\t" << *i ;
        //     std::cout << std::endl ;
        //     std::cout << "size = " << v.size() << std::endl;
        //     std::cout << "size = " << v[8] << std::endl;
        //     std::cout << "capacity = " << v.capacity() << std::endl;

        //     std::cout << "size 2 = " << v2.size() << std::endl;
        //     std::cout << "capacity 2 = " << v2.capacity() << std::endl;
        //     v2.push_back(5);
        //     v2.assign(v.begin() + 1, v.end() - 1);
        //     for (ft::vector<int>::iterator i = v2.begin(); i < v2.end() ; i++)
        //         std::cout << "\t" << *i ;
        //     std::cout << std::endl ;
        //     std::cout << "size 2 = " << v2.size() << std::endl;
        //     std::cout << "capacity 2 = " << v2.capacity() << std::endl;
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // } 
    }

    std::cout << "****************** test 13 ******************" << std::endl;
    {
        int value = 5;
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
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "----------------------------------------" << std::endl;
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
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        } 
    }


    
}