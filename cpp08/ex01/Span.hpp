/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:41:58 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/21 18:22:58 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <exception>
# include <algorithm>
# include <limits>

class Span
{
	private:
		unsigned int _maxSize;
		std::vector<int> _numbers;

	public:
		Span();
		Span(unsigned int n);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();

		void addNumber(int number);
		int shortestSpan() const;
		int longestSpan() const;

		template <typename Iterator>
		void addRange(Iterator begin, Iterator end)
		{
			while (begin != end)
			{
				addNumber(*begin);
				++begin;
			}
		}

		class SpanFullException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return "Span is full, cannot add more numbers";
				}
		};

		class NoSpanException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return "Not enough numbers to calculate span";
				}
		};
};

#endif
