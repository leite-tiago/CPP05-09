#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe {
private:
    std::vector<int> _vectorData;
    std::deque<int> _dequeData;

    // Vector implementation
    void mergeInsertSortVector(std::vector<int>& arr);
    void insertionSortVector(std::vector<int>& arr, int left, int right);
    void mergeVector(std::vector<int>& arr, int left, int mid, int right);

    // Deque implementation
    void mergeInsertSortDeque(std::deque<int>& arr);
    void insertionSortDeque(std::deque<int>& arr, int left, int right);
    void mergeDeque(std::deque<int>& arr, int left, int mid, int right);

    // Ford-Johnson helpers
    template<typename Container>
    void fordJohnsonSort(Container& arr);

    bool isValidNumber(const std::string& str) const;

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    bool parseInput(int argc, char** argv);
    void sort();
    void displayResults(double vectorTime, double dequeTime) const;
};

#endif
