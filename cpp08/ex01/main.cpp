#include "Span.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	std::cout << "=== Test from subject ===" << std::endl;
	{
		Span sp = Span(5);
		
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

	std::cout << "\n=== Test with exception (full span) ===" << std::endl;
	{
		Span sp = Span(3);
		
		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(3);
		
		try
		{
			sp.addNumber(4);
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	std::cout << "\n=== Test with exception (no span) ===" << std::endl;
	{
		Span sp = Span(5);
		
		try
		{
			std::cout << sp.shortestSpan() << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}

		sp.addNumber(42);
		
		try
		{
			std::cout << sp.longestSpan() << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	std::cout << "\n=== Test with 10,000 numbers ===" << std::endl;
	{
		Span sp = Span(10000);
		
		// Fill with range of iterators
		std::vector<int> numbers;
		for (int i = 0; i < 10000; ++i)
			numbers.push_back(i);
		
		sp.addRange(numbers.begin(), numbers.end());
		
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	}

	std::cout << "\n=== Test with 20,000 random numbers ===" << std::endl;
	{
		srand(time(NULL));
		
		Span sp = Span(20000);
		
		std::vector<int> numbers;
		for (int i = 0; i < 20000; ++i)
			numbers.push_back(rand());
		
		sp.addRange(numbers.begin(), numbers.end());
		
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	}

	std::cout << "\n=== Test with negative numbers ===" << std::endl;
	{
		Span sp = Span(5);
		
		sp.addNumber(-10);
		sp.addNumber(-5);
		sp.addNumber(0);
		sp.addNumber(5);
		sp.addNumber(10);
		
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	}

	return 0;
}
