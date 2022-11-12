/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:32:38 by hdrabi            #+#    #+#             */
/*   Updated: 2022/11/12 12:55:32 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include <iostream>
#include <algorithm>
# include <string>

namespace ft {

    template <class T1, class T2>
    class pair
    {
		public :
			typedef T1 first_type;
			typedef T2 second_type;

        public:
            // Constructors
            pair() : first() , second() {
                // std::cout << "\e[0;33mDefault Constructor called of pair\e[0m" << std::endl;
            }

            pair(const first_type &a, const second_type &b) : first(a) , second(b) {
                // std::cout << "\e[0;33mField Constructor called of pair\e[0m" << std::endl;
            }

            template <class U, class V>
            pair(const pair< U , V > &copy): first(copy.first), second(copy.second){
                // std::cout << "\e[0;33mField Constructor called of pair\e[0m" << std::endl;
            }

            // Destructor
            ~pair(){
                // std::cout << "\e[0;31mDestructor called of pair\e[0m" << std::endl;
            }

            // Operators
            pair & operator=(const pair &assign) {
                if (this !=  &assign){
                    first = assign.first;
                    second = assign.second;
                }
                return *this;
            }

        public:
            first_type first;
            second_type second;
    };

    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &p1, const pair<T1, T2> &p2){
        return (p1.first == p2.first && p1.second == p2.second);
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &p1, const pair<T1, T2> &p2){
        return !(p1 == p2);
    }

    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &p1, const pair<T1, T2> &p2){
        return (p1.first < p2.first || (p1.first == p2.first &&  p1.second < p2.second));
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &p1, const pair<T1, T2> &p2){
        return (p1.first <= p2.first);
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &p1, const pair<T1, T2> &p2){
        return !(p1 <= p2);
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &p1, const pair<T1, T2> &p2){
        return !(p1 < p2);
    }

    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y){
        return ( pair<T1,T2>(x,y) );
    }
}


#endif