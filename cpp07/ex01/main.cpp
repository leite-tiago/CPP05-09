/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:10:11 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/21 14:10:12 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "iter.hpp"

// Test function for integers
void printInt(int const & x)
{
	std::cout << x << " ";
}

// Test function for strings
void printString(std::string const & s)
{
	std::cout << s << " ";
}

// Test function that modifies the value (doubles it)
void doubleValue(int & x)
{
	x *= 2;
}

// Template function to demonstrate it works with templates
template <typename T>
void print(T const & x)
{
	std::cout << x << " ";
}

int main(void)
{
	std::cout << "=== Test 1: Array of integers ===" << std::endl;
	int intArray[] = {1, 2, 3, 4, 5};
	size_t intLen = 5;

	std::cout << "Original: ";
	::iter(intArray, intLen, printInt);
	std::cout << std::endl;

	std::cout << "After doubling: ";
	::iter(intArray, intLen, doubleValue);
	::iter(intArray, intLen, printInt);
	std::cout << std::endl;

	std::cout << "\n=== Test 2: Array of strings ===" << std::endl;
	std::string strArray[] = {"Hello", "World", "from", "42"};
	size_t strLen = 4;

	std::cout << "Strings: ";
	::iter(strArray, strLen, printString);
	std::cout << std::endl;

	std::cout << "\n=== Test 3: Using template function ===" << std::endl;
	double doubleArray[] = {1.1, 2.2, 3.3, 4.4, 5.5};
	size_t doubleLen = 5;

	std::cout << "Doubles: ";
	::iter(doubleArray, doubleLen, print<double>);
	std::cout << std::endl;

	std::cout << "\n=== Test 4: Using template function with ints ===" << std::endl;
	int intArray2[] = {10, 20, 30, 40, 50};
	std::cout << "Ints: ";
	::iter(intArray2, intLen, print<int>);
	std::cout << std::endl;

	return 0;
}
