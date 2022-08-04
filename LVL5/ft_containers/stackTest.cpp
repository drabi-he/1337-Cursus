/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackTest.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:05:52 by hdrabi            #+#    #+#             */
/*   Updated: 2022/08/04 11:33:07 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <vector>
#include <iterator>

#include "vector/vector.hpp"
#include "stack/stack.hpp"

int main() {
    std::cout << std::endl << "\033[36m" << "************************************ test 1 < empty > ************************************ " << "\033[0m" << std::endl;
    {
        
        
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v1 ;          
            std::vector<int> v2;
            ft::vector<int> v3 (3, 100);          
            std::vector<int> v4 (3, 100);        

            std::stack<int,ft::vector<int> > s1 (v1);  
            std::stack<int,std::vector<int> > s2 (v2);
            std::stack<int,ft::vector<int> > s3 (v3);  
            std::stack<int,std::vector<int> > s4 (v4);

            std::cout << std::boolalpha;
            std:: cout << "s1 is empty ? " << s1.empty() << std::endl;
            std:: cout << "s2 is empty ? " << s2.empty() << std::endl;
            std:: cout << "s3 is empty ? " << s3.empty() << std::endl;
            std:: cout << "s4 is empty ? " << s4.empty() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v1 ;          
            std::vector<int> v2;
            ft::vector<int> v3 (3, 100);          
            std::vector<int> v4 (3, 100);        

            ft::stack<int,ft::vector<int> > s1 (v1);  
            ft::stack<int,std::vector<int> > s2 (v2);
            ft::stack<int,ft::vector<int> > s3 (v3);  
            ft::stack<int,std::vector<int> > s4 (v4);

            std::cout << std::boolalpha;
            std:: cout << "s1 is empty ? " << s1.empty() << std::endl;
            std:: cout << "s2 is empty ? " << s2.empty() << std::endl;
            std:: cout << "s3 is empty ? " << s3.empty() << std::endl;
            std:: cout << "s4 is empty ? " << s4.empty() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 2 < size > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v1 ;          
            std::vector<int> v2 (10);
            ft::vector<int> v3 (3, 100);          
            std::vector<int> v4 (5, 100);        

            std::stack<int,ft::vector<int> > s1 (v1);  
            std::stack<int,std::vector<int> > s2 (v2);
            std::stack<int,ft::vector<int> > s3 (v3);  
            std::stack<int,std::vector<int> > s4 (v4);

            std:: cout << "s1 size = " << s1.size() << std::endl;
            std:: cout << "s2 size = " << s2.size() << std::endl;
            std:: cout << "s3 size = " << s3.size() << std::endl;
            std:: cout << "s4 size = " << s4.size() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v1 ;          
            std::vector<int> v2 (10);
            ft::vector<int> v3 (3, 100);          
            std::vector<int> v4 (5, 100);        

            ft::stack<int,ft::vector<int> > s1 (v1);  
            ft::stack<int,std::vector<int> > s2 (v2);
            ft::stack<int,ft::vector<int> > s3 (v3);  
            ft::stack<int,std::vector<int> > s4 (v4);

            std:: cout << "s1 size = " << s1.size() << std::endl;
            std:: cout << "s2 size = " << s2.size() << std::endl;
            std:: cout << "s3 size = " << s3.size() << std::endl;
            std:: cout << "s4 size = " << s4.size() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 3 < top > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v1 ;          
            std::vector<int> v2 (10);
            ft::vector<int> v3 (3, 100);          
            std::vector<int> v4 (5, 200);        

            std::stack<int,ft::vector<int> > s1 (v1);  
            std::stack<int,std::vector<int> > s2 (v2);
            std::stack<int,ft::vector<int> > s3 (v3);  
            std::stack<int,std::vector<int> > s4 (v4);

            // ? if you uncomment this it will segfault since the stack is empty
            // std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;
            std:: cout << "s3 top = " << s3.top() << std::endl;
            std:: cout << "s4 top = " << s4.top() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v1 ;          
            std::vector<int> v2 (10);
            ft::vector<int> v3 (3, 100);          
            std::vector<int> v4 (5, 200);        

            ft::stack<int,ft::vector<int> > s1 (v1);  
            ft::stack<int,std::vector<int> > s2 (v2);
            ft::stack<int,ft::vector<int> > s3 (v3);  
            ft::stack<int,std::vector<int> > s4 (v4);

            // ? if you uncomment this it will segfault since the stack is empty
            // std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;
            std:: cout << "s3 top = " << s3.top() << std::endl;
            std:: cout << "s4 top = " << s4.top() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 4 < push > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v1 ;          
            std::vector<int> v2 (10);
        
            std::stack<int,ft::vector<int> > s1 (v1);  
            std::stack<int,std::vector<int> > s2 (v2);

            std:: cout << "s2 top = " << s2.top() << std::endl;

            s1.push(1);
            s2.push(2);
            std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v1 ;          
            std::vector<int> v2 (10);
        
            ft::stack<int,ft::vector<int> > s1 (v1);  
            ft::stack<int,std::vector<int> > s2 (v2);

            std:: cout << "s2 top = " << s2.top() << std::endl;

            s1.push(1);
            s2.push(2);
            std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 5 < pop > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v1 ;          
            std::vector<int> v2 (10);
        
            std::stack<int,ft::vector<int> > s1 (v1);  
            std::stack<int,std::vector<int> > s2 (v2);

            // ? if you uncomment this it will segfault since the stack is empty
            // std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;

            s1.push(1);
            s2.push(2);
            std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;

            s1.push(10);
            s2.push(20);
            std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;
            
            s1.pop();
            s2.pop();
            std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> v1 ;          
            std::vector<int> v2 (10);
        
            ft::stack<int,ft::vector<int> > s1 (v1);  
            ft::stack<int,std::vector<int> > s2 (v2);

            // ? if you uncomment this it should segfault since the stack is empty
            // std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;

            s1.push(1);
            s2.push(2);
            std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;

            s1.push(10);
            s2.push(20);
            std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;
            
            s1.pop();
            s2.pop();
            std:: cout << "s1 top = " << s1.top() << std::endl;
            std:: cout << "s2 top = " << s2.top() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << std::endl << "\033[36m" << "************************************ test 6 < non-member functions > ************************************ " << "\033[0m" << std::endl;
    {
        std::cout << "\033[32m" << "----------------------- ORIGINAL -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> foo1 (2,200); 
            ft::vector<int> bar1 (2,200);

            std::vector<int> foo2 (3,100); 
            std::vector<int> bar2 (2,200); 

            std::stack<int,ft::vector<int> > s1 (foo1);  
            std::stack<int,ft::vector<int> > s2 (bar1);

            std::stack<int,std::vector<int> > s3 (foo2);  
            std::stack<int,std::vector<int> > s4 (bar2);

            if (s1 == s2) std::cout << "s1 and s2 are equal\n";
            if (s1 != s2) std::cout << "s1 and s2 are not equal\n";
            if (s1 < s2) std::cout << "s1 is less than s2\n";
            if (s1 > s2) std::cout << "s1 is greater than s2\n";
            if (s1 <= s2) std::cout << "s1 is less than or equal to s2\n";
            if (s1 >= s2) std::cout << "s1 is greater than or equal to s2\n";

            if (s3 == s4) std::cout << "s3 and s4 are equal\n";
            if (s3 != s4) std::cout << "s3 and s4 are not equal\n";
            if (s3 < s4) std::cout << "s3 is less than s4\n";
            if (s3 > s4) std::cout << "s3 is greater than s4\n";
            if (s3 <= s4) std::cout << "s3 is less than or equal to s4\n";
            if (s3 >= s4) std::cout << "s3 is greater than or equal to s4\n";
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << "\033[33m" << "----------------------- RECREATED -----------------------" << "\033[0m" << std::endl;
        try
        {
            ft::vector<int> foo1 (2,200); 
            ft::vector<int> bar1 (2,200);

            std::vector<int> foo2 (3,100); 
            std::vector<int> bar2 (2,200); 

            ft::stack<int,ft::vector<int> > s1 (foo1);  
            ft::stack<int,ft::vector<int> > s2 (bar1);

            ft::stack<int,std::vector<int> > s3 (foo2);  
            ft::stack<int,std::vector<int> > s4 (bar2);

            if (s1 == s2) std::cout << "s1 and s2 are equal\n";
            if (s1 != s2) std::cout << "s1 and s2 are not equal\n";
            if (s1 < s2) std::cout << "s1 is less than s2\n";
            if (s1 > s2) std::cout << "s1 is greater than s2\n";
            if (s1 <= s2) std::cout << "s1 is less than or equal to s2\n";
            if (s1 >= s2) std::cout << "s1 is greater than or equal to s2\n";

            if (s3 == s4) std::cout << "s3 and s4 are equal\n";
            if (s3 != s4) std::cout << "s3 and s4 are not equal\n";
            if (s3 < s4) std::cout << "s3 is less than s4\n";
            if (s3 > s4) std::cout << "s3 is greater than s4\n";
            if (s3 <= s4) std::cout << "s3 is less than or equal to s4\n";
            if (s3 >= s4) std::cout << "s3 is greater than or equal to s4\n";
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

}