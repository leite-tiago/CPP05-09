/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:05:00 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/17 23:07:18 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Base.hpp"
#include "../inc/A.hpp"
#include "../inc/B.hpp"
#include "../inc/C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

int main()
{
	std::srand(std::time(NULL));

	std::cout << "=== Test 1: Generate and identify by pointer ===" << std::endl;
	Base* obj1 = generate();
	std::cout << "Identify by pointer: ";
	identify(obj1);
	std::cout << "Identify by reference: ";
	identify(*obj1);
	delete obj1;
	std::cout << std::endl;

	std::cout << "=== Test 2: Generate and identify by pointer ===" << std::endl;
	Base* obj2 = generate();
	std::cout << "Identify by pointer: ";
	identify(obj2);
	std::cout << "Identify by reference: ";
	identify(*obj2);
	delete obj2;
	std::cout << std::endl;

	std::cout << "=== Test 3: Generate and identify by pointer ===" << std::endl;
	Base* obj3 = generate();
	std::cout << "Identify by pointer: ";
	identify(obj3);
	std::cout << "Identify by reference: ";
	identify(*obj3);
	delete obj3;
	std::cout << std::endl;

	std::cout << "=== Test 4: Direct instantiation ===" << std::endl;
	A a;
	B b;
	C c;

	std::cout << "A - Identify by pointer: ";
	identify(&a);
	std::cout << "A - Identify by reference: ";
	identify(a);

	std::cout << "B - Identify by pointer: ";
	identify(&b);
	std::cout << "B - Identify by reference: ";
	identify(b);

	std::cout << "C - Identify by pointer: ";
	identify(&c);
	std::cout << "C - Identify by reference: ";
	identify(c);

	return 0;
}
