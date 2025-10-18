#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vectorData(other._vectorData), _dequeData(other._dequeData) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vectorData = other._vectorData;
        _dequeData = other._dequeData;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::isValidNumber(const std::string& str) const {
    if (str.empty())
        return false;

    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i]))
            return false;
    }

    return true;
}

bool PmergeMe::parseInput(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);

        if (!isValidNumber(arg)) {
            std::cerr << "Error" << std::endl;
            return false;
        }

        long num = atol(arg.c_str());
        if (num < 0 || num > 2147483647) {
            std::cerr << "Error" << std::endl;
            return false;
        }

        _vectorData.push_back(static_cast<int>(num));
        _dequeData.push_back(static_cast<int>(num));
    }

    if (_vectorData.empty()) {
        std::cerr << "Error" << std::endl;
        return false;
    }

    return true;
}

void PmergeMe::insertionSortVector(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void PmergeMe::mergeVector(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < leftArr.size()) {
        arr[k++] = leftArr[i++];
    }

    while (j < rightArr.size()) {
        arr[k++] = rightArr[j++];
    }
}

void PmergeMe::mergeInsertSortVector(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1)
        return;

    // Use insertion sort for small subarrays
    const int threshold = 16;

    // First pass: sort pairs
    for (int i = 0; i < n - 1; i += 2) {
        if (arr[i] > arr[i + 1]) {
            std::swap(arr[i], arr[i + 1]);
        }
    }

    // Iterative merge-insert sort
    for (int size = 2; size < n; size *= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min(left + 2 * size - 1, n - 1);

            if (right - left + 1 <= threshold) {
                insertionSortVector(arr, left, right);
            } else {
                mergeVector(arr, left, mid, right);
            }
        }
    }

    // Final insertion sort to ensure everything is sorted
    if (n > 1) {
        insertionSortVector(arr, 0, n - 1);
    }
}

void PmergeMe::insertionSortDeque(std::deque<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void PmergeMe::mergeDeque(std::deque<int>& arr, int left, int mid, int right) {
    std::deque<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::deque<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < leftArr.size()) {
        arr[k++] = leftArr[i++];
    }

    while (j < rightArr.size()) {
        arr[k++] = rightArr[j++];
    }
}

void PmergeMe::mergeInsertSortDeque(std::deque<int>& arr) {
    int n = arr.size();
    if (n <= 1)
        return;

    const int threshold = 16;

    // First pass: sort pairs
    for (int i = 0; i < n - 1; i += 2) {
        if (arr[i] > arr[i + 1]) {
            std::swap(arr[i], arr[i + 1]);
        }
    }

    // Iterative merge-insert sort
    for (int size = 2; size < n; size *= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min(left + 2 * size - 1, n - 1);

            if (right - left + 1 <= threshold) {
                insertionSortDeque(arr, left, right);
            } else {
                mergeDeque(arr, left, mid, right);
            }
        }
    }

    // Final insertion sort
    if (n > 1) {
        insertionSortDeque(arr, 0, n - 1);
    }
}

void PmergeMe::sort() {
    // Display before
    std::cout << "Before: ";
    for (size_t i = 0; i < _vectorData.size() && i < 5; i++) {
        std::cout << _vectorData[i] << " ";
    }
    if (_vectorData.size() > 5) {
        std::cout << "[...]";
    }
    std::cout << std::endl;

    // Sort with vector and measure time
    struct timeval start, end;
    gettimeofday(&start, NULL);

    std::vector<int> vectorCopy = _vectorData;
    mergeInsertSortVector(vectorCopy);

    gettimeofday(&end, NULL);
    double vectorTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    // Sort with deque and measure time
    gettimeofday(&start, NULL);

    std::deque<int> dequeCopy = _dequeData;
    mergeInsertSortDeque(dequeCopy);

    gettimeofday(&end, NULL);
    double dequeTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    // Display after
    std::cout << "After: ";
    for (size_t i = 0; i < vectorCopy.size() && i < 5; i++) {
        std::cout << vectorCopy[i] << " ";
    }
    if (vectorCopy.size() > 5) {
        std::cout << "[...]";
    }
    std::cout << std::endl;

    // Display times
    std::cout << "Time to process a range of " << _vectorData.size()
              << " elements with std::vector : " << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _dequeData.size()
              << " elements with std::deque : " << dequeTime << " us" << std::endl;
}

void PmergeMe::displayResults(double vectorTime, double dequeTime) const {
    (void)vectorTime;
    (void)dequeTime;
}
