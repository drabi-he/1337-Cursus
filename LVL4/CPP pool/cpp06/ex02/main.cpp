/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:21:32 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/09 19:19:42 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"


Base * generate(void){
    srand(time(NULL));
    int r = rand() % 3;
    
    if (r == 0)
    {       
        // std::cout << "A" << std::endl;
        return new A();
    }
    else if (r == 1)
    {
        // std::cout << "B" << std::endl;
        return new B();
    }
    else
    {
        // std::cout << "C" << std::endl;
        return new C();
    }
}

void identify(Base* p){
    A *a;
    B *b;
    C *c;
    
    if ((a = dynamic_cast<A*>(p)))
        std::cout << "1 - We Got Type A" << std::endl;
    else if ((b = dynamic_cast<B*>(p)))
        std::cout << "1 - We Got Type B" << std::endl;
    else if ((c = dynamic_cast<C*>(p)))
        std::cout << "1 - We Got Type C" << std::endl;
} 

void identify(Base& p){    
    try
    {
        A &a = dynamic_cast<A&>(p);
        (void)a;
        std::cout << "2 - We Got Type A" << std::endl;
    }
    catch(const std::exception& e)
    {
        (void)e;
    }
    try
    {
        B &b = dynamic_cast<B&>(p);
        (void)b;
        std::cout << "2 - We Got Type B" << std::endl;
    }
    catch(const std::exception& e)
    {
        (void)e;
    }
    try
    {
        C &c = dynamic_cast<C&>(p);
        (void)c;
        std::cout << "2 - We Got Type C" << std::endl;
    }
    catch(const std::exception& e)
    {
        (void)e;
    }

} 

int main(){

    Base *b;
    
    b = generate();
    identify(b); 
    identify(*b); 
}