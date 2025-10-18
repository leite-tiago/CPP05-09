#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _database = other._database;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    for (size_t i = 0; i < date.length(); i++) {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            return false;
    }

    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    // Check days in month
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28))
            return false;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return false;
    }

    return true;
}

bool BitcoinExchange::isValidValue(const std::string& value) const {
    if (value.empty())
        return false;

    size_t start = 0;
    bool hasDot = false;

    if (value[0] == '-' || value[0] == '+')
        start = 1;

    if (start >= value.length())
        return false;

    for (size_t i = start; i < value.length(); i++) {
        if (value[i] == '.') {
            if (hasDot)
                return false;
            hasDot = true;
        } else if (!isdigit(value[i]))
            return false;
    }

    return true;
}

double BitcoinExchange::stringToDouble(const std::string& str) const {
    std::stringstream ss(str);
    double value;
    ss >> value;
    return value;
}

bool BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open database file." << std::endl;
        return false;
    }

    std::string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }

        size_t pos = line.find(',');
        if (pos == std::string::npos)
            continue;

        std::string date = trim(line.substr(0, pos));
        std::string value = trim(line.substr(pos + 1));

        if (isValidDate(date) && isValidValue(value)) {
            _database[date] = stringToDouble(value);
        }
    }

    file.close();
    return true;
}

double BitcoinExchange::getExchangeRate(const std::string& date) const {
    std::map<std::string, double>::const_iterator it = _database.find(date);

    if (it != _database.end()) {
        return it->second;
    }

    // Find closest lower date
    it = _database.lower_bound(date);
    if (it == _database.begin()) {
        return 0.0;
    }

    --it;
    return it->second;
}

void BitcoinExchange::processInputFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }

        size_t pos = line.find('|');
        if (pos == std::string::npos) {
            std::cerr << "Error: bad input => " << trim(line) << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, pos));
        std::string valueStr = trim(line.substr(pos + 1));

        if (!isValidDate(date)) {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        if (!isValidValue(valueStr)) {
            std::cerr << "Error: bad input => " << valueStr << std::endl;
            continue;
        }

        double value = stringToDouble(valueStr);

        if (value < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }

        if (value > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        double rate = getExchangeRate(date);
        double result = value * rate;

        std::cout << date << " => " << value << " = " << result << std::endl;
    }

    file.close();
}
