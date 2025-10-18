#include <iostream>
#include <string>
#include "Array.hpp"

#define MAX_VAL 750

int main(int, char**)
{
	// Test 1: Empty array
	std::cout << "=== Test 1: Empty array ===" << std::endl;
	Array<int> empty;
	std::cout << "Size of empty array: " << empty.size() << std::endl;

	// Test 2: Array with size
	std::cout << "\n=== Test 2: Array with size ===" << std::endl;
	Array<int> numbers(MAX_VAL);
	int* mirror = new int[MAX_VAL];

	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}
	std::cout << "Created array of size: " << numbers.size() << std::endl;

	// Test 3: Copy constructor
	std::cout << "\n=== Test 3: Copy constructor ===" << std::endl;
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
		std::cout << "Original array size: " << numbers.size() << std::endl;
		std::cout << "Copied array size: " << test.size() << std::endl;
		std::cout << "Modifying copy..." << std::endl;
		test[0] = 42;
		std::cout << "Original[0]: " << numbers[0] << std::endl;
		std::cout << "Copy[0]: " << test[0] << std::endl;
	}

	// Test 4: Check values
	std::cout << "\n=== Test 4: Checking values ===" << std::endl;
	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "didn't save the same value!!" << std::endl;
			delete[] mirror;
			return 1;
		}
	}
	std::cout << "All values match! ✓" << std::endl;

	// Test 5: Out of bounds access
	std::cout << "\n=== Test 5: Out of bounds access ===" << std::endl;
	try
	{
		numbers[-2] = 0;
		std::cerr << "Should have thrown exception!" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception caught for negative index ✓" << std::endl;
	}

	try
	{
		numbers[MAX_VAL] = 0;
		std::cerr << "Should have thrown exception!" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception caught for index >= size ✓" << std::endl;
	}

	// Test 6: Modifying values
	std::cout << "\n=== Test 6: Modifying values ===" << std::endl;
	for (int i = 0; i < MAX_VAL; i++)
	{
		numbers[i] = rand();
	}
	std::cout << "Successfully modified all values ✓" << std::endl;

	delete[] mirror;

	// Test 7: String array
	std::cout << "\n=== Test 7: String array ===" << std::endl;
	Array<std::string> strings(5);
	strings[0] = "Hello";
	strings[1] = "World";
	strings[2] = "from";
	strings[3] = "42";
	strings[4] = "School";

	std::cout << "String array contents: ";
	for (unsigned int i = 0; i < strings.size(); i++)
	{
		std::cout << strings[i];
		if (i < strings.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;

	// Test 8: Assignment operator
	std::cout << "\n=== Test 8: Assignment operator ===" << std::endl;
	Array<int> original(3);
	original[0] = 10;
	original[1] = 20;
	original[2] = 30;

	Array<int> assigned;
	assigned = original;

	std::cout << "Original size: " << original.size() << std::endl;
	std::cout << "Assigned size: " << assigned.size() << std::endl;
	std::cout << "Modifying assigned array..." << std::endl;
	assigned[0] = 999;
	std::cout << "Original[0]: " << original[0] << std::endl;
	std::cout << "Assigned[0]: " << assigned[0] << std::endl;

	std::cout << "\n=== All tests completed! ===" << std::endl;
	return 0;
}
