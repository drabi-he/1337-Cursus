/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xtraTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:08:47 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/23 17:27:45 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "./xtra/enable_if.hpp"
#include "./xtra/is_integral.hpp"
#include "./xtra/equal.hpp"
#include "./xtra/lexicographical_compare.hpp"
#include "./xtra/pair.hpp"
#include "./iterators/iterator.hpp"
#include "./vector/vector.hpp"
#include "./iterators/iterator_traits.hpp"

template <class T>
typename ft::enable_if<std::is_integral<T>::value,bool>::type
    is_odd (T i) {return bool(i%2);}

template < class T>
typename ft::enable_if<std::is_integral<T>::value,bool>::type
    is_even (T i) {return !bool(i%2);}

bool mypredicate (int i, int j) {
    return (i == j);
}
bool mycomp (char c1, char c2){
    return std::tolower(c1)<std::tolower(c2);
}

int main (){
    
    std::cout << "\033[36m" << "************************************ test 1 < enable_if > ************************************ " << "\033[0m" << std::endl;
    {
        int i = 1;    

        std::cout << std::boolalpha;
        std::cout << "i is odd: " << is_odd(i) << std::endl;
        std::cout << "i is even: " << is_even(i) << std::endl;
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 2 < is_integral > ******************" << "\033[0m" << std::endl;
    {
        std::cout << std::boolalpha;
        std::cout << "is_integral:" << std::endl;
        std::cout << "char: " << ft::is_integral<char>::value << std::endl;
        std::cout << "int: " << ft::is_integral<int>::value << std::endl;
        std::cout << "float: " << ft::is_integral<float>::value << std::endl;
        
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 3 < equal > ************************************ " << "\033[0m" << std::endl;
    {
        int myints[] = {20,40,60,80,100};               
        std::vector<int>myvector (myints ,myints+5);     

        if ( ft::equal (myvector.begin(), myvector.end(), myints) )
            std::cout << "The contents of both sequences are equal.\n";
        else
            std::cout << "The contents of both sequences differ.\n";

        myvector[3]=81;                                 

        if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
            std::cout << "The contents of both sequences are equal.\n";
        else
            std::cout << "The contents of both sequences differ.\n";
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 4 < lexicographical_compare > ************************************ " << "\033[0m" << std::endl;
    {
        char foo[]="Apple";
        char bar[]="apartment";

        std::cout << std::boolalpha;

        std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

        std::cout << "Using default comparison (operator<): ";
        std::cout << std::lexicographical_compare(foo , foo + 5 , bar , bar + 9);
        std::cout << '\n';

        std::cout << "Using mycomp as comparison object: ";
        std::cout << std::lexicographical_compare(foo , foo + 5 , bar , bar + 9 , mycomp);
        std::cout << '\n';
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 5 < pair > ************************************ " << "\033[0m" << std::endl;
    {
        ft::pair <int,int> foo;
        ft::pair <int,int> bar;

        foo = ft::make_pair (10,20);
        bar = ft::make_pair (10.5,'A'); 

        std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
        std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
    }
    
    
    std::cout << std::endl << "\033[36m" << "************************************ test 5 < reverse_iterators > ************************************ " << "\033[0m" << std::endl;
    {
        {
            std::vector<int> test;
            test.push_back(1);
            test.push_back(2);
            test.push_back(3);
            test.push_back(4);
            test.push_back(5);
            test.push_back(6);
            std::reverse_iterator<std::vector<int>::iterator> rit(test.end());

            std::cout << *(rit) << std::endl;
            std::cout << *(rit.base()) << std::endl;
            std::cout << *(rit + 1) << std::endl;
            std::cout << *(++rit) << std::endl;
            std::cout << *(rit++) << std::endl;
            rit += 1;
            std::cout << *(rit) << std::endl;
            std::cout << *(rit.base()) << std::endl;
            std::cout << *(rit - 1) << std::endl;
            std::cout << *(--rit) << std::endl;
            std::cout << *(rit--) << std::endl;
            rit -= 1;
            std::cout << *(rit) << std::endl;
            std::cout << *(rit.base()) << std::endl;
            std::cout << rit[1] << std::endl;
            std::cout << rit[4] << std::endl;
        }
            std::cout << "----------------------------------------------------" << std::endl;
        {
            ft::vector<int> test;
            test.push_back(1);
            test.push_back(2);
            test.push_back(3);
            test.push_back(4);
            test.push_back(5);
            test.push_back(6);
            ft::reverse_iterator<ft::vector<int>::iterator> rit(test.end());

            std::cout << *(rit) << std::endl;
            std::cout << *(rit.base()) << std::endl;
            std::cout << *(rit + 1) << std::endl;
            std::cout << *(++rit) << std::endl;
            std::cout << *(rit++) << std::endl;
            rit += 1;
            std::cout << *(rit) << std::endl;
            std::cout << *(rit.base()) << std::endl;
            std::cout << *(rit - 1) << std::endl;
            std::cout << *(--rit) << std::endl;
            std::cout << *(rit--) << std::endl;
            rit -= 1;
            std::cout << *(rit) << std::endl;
            std::cout << *(rit.base()) << std::endl;
            std::cout << rit[1] << std::endl;
            std::cout << rit[4] << std::endl;
        }
    }

}