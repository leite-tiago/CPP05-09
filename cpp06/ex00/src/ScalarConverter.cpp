/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:58:29 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/17 23:07:18 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iomanip>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

static bool isChar(const std::string& str)
{
	return (str.length() == 3 && str[0] == '\'' && str[2] == '\'');
}

static bool isInt(const std::string& str)
{
	size_t i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (i >= str.length())
		return false;
	while (i < str.length())
	{
		if (!isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}

static bool isFloat(const std::string& str)
{
	if (str == "-inff" || str == "+inff" || str == "inff" || str == "nanf")
		return true;

	if (str[str.length() - 1] != 'f')
		return false;

	size_t i = 0;
	bool hasDot = false;

	if (str[i] == '+' || str[i] == '-')
		i++;
	if (i >= str.length() - 1)
		return false;

	while (i < str.length() - 1)
	{
		if (str[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (!isdigit(str[i]))
			return false;
		i++;
	}
	return hasDot;
}

static bool isDouble(const std::string& str)
{
	if (str == "-inf" || str == "+inf" || str == "inf" || str == "nan")
		return true;

	size_t i = 0;
	bool hasDot = false;

	if (str[i] == '+' || str[i] == '-')
		i++;
	if (i >= str.length())
		return false;

	while (i < str.length())
	{
		if (str[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (!isdigit(str[i]))
			return false;
		i++;
	}
	return hasDot;
}

static void printChar(double value, bool impossible)
{
	std::cout << "char: ";
	if (impossible || std::isnan(value) || std::isinf(value))
		std::cout << "impossible";
	else if (value < 0 || value > 127)
		std::cout << "impossible";
	else if (value < 32 || value == 127)
		std::cout << "Non displayable";
	else
		std::cout << "'" << static_cast<char>(value) << "'";
	std::cout << std::endl;
}

static void printInt(double value, bool impossible)
{
	std::cout << "int: ";
	if (impossible || std::isnan(value) || std::isinf(value))
		std::cout << "impossible";
	else if (value < INT_MIN || value > INT_MAX)
		std::cout << "impossible";
	else
		std::cout << static_cast<int>(value);
	std::cout << std::endl;
}

static void printFloat(double value)
{
	std::cout << "float: ";
	float f = static_cast<float>(value);
	if (std::isnan(value))
		std::cout << "nanf";
	else if (std::isinf(value))
		std::cout << (value > 0 ? "+inff" : "-inff");
	else
	{
		std::cout << std::fixed << std::setprecision(1) << f << "f";
	}
	std::cout << std::endl;
}

static void printDouble(double value)
{
	std::cout << "double: ";
	if (std::isnan(value))
		std::cout << "nan";
	else if (std::isinf(value))
		std::cout << (value > 0 ? "+inf" : "-inf");
	else
	{
		std::cout << std::fixed << std::setprecision(1) << value;
	}
	std::cout << std::endl;
}

static void convertFromChar(const std::string& str)
{
	char c = str[1];
	double value = static_cast<double>(c);

	printChar(value, false);
	printInt(value, false);
	printFloat(value);
	printDouble(value);
}

static void convertFromInt(const std::string& str)
{
	char* end;
	long l = std::strtol(str.c_str(), &end, 10);
	bool impossible = false;

	if (*end != '\0' || l < INT_MIN || l > INT_MAX)
		impossible = true;

	double value = static_cast<double>(l);

	printChar(value, impossible);
	printInt(value, impossible);
	printFloat(value);
	printDouble(value);
}

static void convertFromFloat(const std::string& str)
{
	char* end;
	float f = std::strtof(str.c_str(), &end);
	double value = static_cast<double>(f);

	printChar(value, false);
	printInt(value, false);
	printFloat(value);
	printDouble(value);
}

static void convertFromDouble(const std::string& str)
{
	char* end;
	double value = std::strtod(str.c_str(), &end);

	printChar(value, false);
	printInt(value, false);
	printFloat(value);
	printDouble(value);
}

void ScalarConverter::convert(const std::string& literal)
{
	if (literal.empty())
	{
		std::cout << "Error: empty literal" << std::endl;
		return;
	}

	if (isChar(literal))
		convertFromChar(literal);
	else if (isInt(literal))
		convertFromInt(literal);
	else if (isFloat(literal))
		convertFromFloat(literal);
	else if (isDouble(literal))
		convertFromDouble(literal);
	else
		std::cout << "Error: invalid literal" << std::endl;
}
