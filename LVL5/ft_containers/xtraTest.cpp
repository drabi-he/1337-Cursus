/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xtraTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:08:47 by hdrabi            #+#    #+#             */
/*   Updated: 2022/06/03 14:34:23 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "./xtra/enable_if.hpp"
#include "./xtra/is_integral.hpp"
#include "./xtra/equal.hpp"
#include "./xtra/lexicographical_compare.hpp"
#include "./xtra/pair.hpp"

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
    
    std::cout << "****************** test 1 < enable_if > ******************" << std::endl;
    {
        int i = 1;    

        std::cout << std::boolalpha;
        std::cout << "i is odd: " << is_odd(i) << std::endl;
        std::cout << "i is even: " << is_even(i) << std::endl;
    }

    std::cout << std::endl << "****************** test 2 < is_integral > ******************" << std::endl;
    {
        std::cout << std::boolalpha;
        std::cout << "is_integral:" << std::endl;
        std::cout << "char: " << ft::is_integral<char>::value << std::endl;
        std::cout << "int: " << ft::is_integral<int>::value << std::endl;
        std::cout << "float: " << ft::is_integral<float>::value << std::endl;
        
    }

    std::cout << std::endl << "****************** test 3 < equal > ******************" << std::endl;
    {
        int myints[] = {20,40,60,80,100};               
        std::vector<int>myvector (myints,myints+5);     

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

    std::cout << std::endl << "****************** test 4 < lexicographical_compare > ******************" << std::endl;
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

    std::cout << std::endl << "****************** test 5 < pair > ******************" << std::endl;
    {
        ft::pair <int,int> foo;
        ft::pair <int,int> bar;

        foo = ft::make_pair (10,20);
        bar = ft::make_pair (10.5,'A'); 

        std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
        std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
    }

}