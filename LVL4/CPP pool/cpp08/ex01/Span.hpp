/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:03:09 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/12 16:25:17 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SPAN_
# define _SPAN_

# include <iostream>
# include <string>
# include <vector>
# include <stdexcept>
# include <algorithm>
# include <iterator>

class Span
{
	public:
		// Constructors
		Span();
		Span(const Span &copy);
		Span(unsigned int nb);
		
		// Destructor
		~Span();
		
		// Operators
		Span & operator=(const Span &assign);
		
		// Getters / Setters
		unsigned int getNb() const;
		void setNb(unsigned int nb);
		void addNumber(int n);
		void UIaddNumber(std::vector<int>::iterator f, std::vector<int>::iterator l);
		int shortestSpan();
		int longestSpan();
		
	private:
		unsigned int _nb;
		std::vector<int> array;
		
};

#endif