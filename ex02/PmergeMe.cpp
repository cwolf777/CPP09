/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:54:57 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/22 16:59:18 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "utils.hpp"

PmergeMe::PmergeMe(){};

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq){};

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe(){};

void PmergeMe::loadInput(char **argv, int argc)
{
    if (argc <= 1)
        throw std::invalid_argument("Error: No numbers provided");

    for (int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);

        for (size_t j = 0; j < arg.size(); ++j)
        {
            if (!std::isdigit(arg[j]))
                throw std::invalid_argument("Error: Invalid input '" + arg + "'");
        }

        long num = std::strtol(arg.c_str(), NULL, 10);
        if (num < 0 || num > INT_MAX)
            throw std::out_of_range("Error: Number out of range '" + arg + "'");

        _vec.push_back(static_cast<int>(num));
        _deq.push_back(static_cast<int>(num));
        _unsorted.push_back(static_cast<int>(num));
    }

    if (_vec.empty() || _deq.empty())
        throw std::invalid_argument("Error: No valid numbers provided");
}


void PmergeMe::sortVector()
{
    int leftover;
    std::vector<std::pair<int, int>> pairs = makeAndSortPairs(_vec, leftover);

    size_t unitSize = 1;
    firstUnitSort(pairs, unitSize);
    
    _vec = FordJohnson(pairs, unitSize, leftover);
}

std::vector<std::pair<int, int>> PmergeMe::makeAndSortPairs(const std::vector<int> &numbers, int &leftover)
{
    leftover = -1;
    std::vector<std::pair<int, int>> pairs;
    size_t n = numbers.size();

    size_t i = 0;
    while (i + 1 < n)
    {
        int a = numbers[i];
        int b = numbers[i+1];
        if (a > b)
            std::swap(a,b);
        pairs.push_back(std::make_pair(a,b));
        i += 2;
    }
    
    if (numbers.size() % 2 != 0)
        leftover = numbers.back();

    return pairs;
}

void PmergeMe::firstUnitSort(std::vector<std::pair<int,int>> &units, size_t &unitSize)
{
    size_t n = units.size();
    if (n <= 1)
        return;

    while (unitSize < n)
    {
        // compare pairs
        for (size_t i = 0; i + 2*unitSize - 1 < n; i += 2*unitSize)
        {
            size_t leftStart = i;
            size_t rightStart = i + unitSize;
            //last element of unit decides which position 
            int lastLeft = lastElement(units, leftStart, unitSize);
            int lastRight = lastElement(units, rightStart, unitSize);
            if (lastLeft > lastRight)
            {
                for (size_t j = 0; j < unitSize; ++j)
                    std::swap(units[leftStart + j], units[rightStart + j]);
            }
        }
        unitSize *= 2; // nächste Stufe: Einheiten verdoppeln
    }
    unitSize /= 2;
}

std::vector<int> PmergeMe::FordJohnson(std::vector<std::pair<int,int>> pairs, size_t unitSize, int oddNum)
{
        
    // std::cout << "First Unit Size: " << unitSize << std::endl;
    std::vector<int> numbers = flattenPairs(pairs);
    if (oddNum != -1)
    {
        numbers.push_back(oddNum);
    }
    // printContainer(numbers);
    std::vector<int> main, pend, leftover;
    while (unitSize >= 1)
    {
        // std::cout << "Processing unitSize = " << unitSize << std::endl;
        splitMainPend(numbers, unitSize, main, pend, leftover); 
        if (!pend.empty())
        {
            std::vector<size_t> insertionOrder = generateJacobInsertionOrder(pend.size() / unitSize);
            insertPendUnits(main, pend, insertionOrder, unitSize);
        }
        rebuildNumbersFromMainAndLeftover(main, leftover, numbers);
        unitSize /= 2;
    }
    return main;
}


//Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque

void PmergeMe::sortDeque()
{
    int leftover;
    std::deque<std::pair<int,int>> pairs = makeAndSortPairsDeq(_deq, leftover);

    size_t unitSize = 1;
    firstUnitSortDeq(pairs, unitSize);
    
    _deq = FordJohnsonDeq(pairs, unitSize, leftover);
}

std::deque<std::pair<int, int>> PmergeMe::makeAndSortPairsDeq(const std::deque<int> &numbers, int &leftover)
{
    leftover = -1; //default
    std::deque<std::pair<int, int>> pairs;
    size_t n = numbers.size();

    size_t i = 0;
    while (i + 1 < n)
    {
        int a = numbers[i];
        int b = numbers[i+1];
        if (a > b)
            std::swap(a,b);
        pairs.push_back(std::make_pair(a,b));
        i += 2;
    }
    
    if (numbers.size() % 2 != 0)
        leftover = numbers.back();

    return pairs;
}

void PmergeMe::firstUnitSortDeq(std::deque<std::pair<int,int>> &units, size_t &unitSize)
{
    size_t n = units.size();
    if (n <= 1)
        return;

    while (unitSize < n)
    {
        // compare pairs
        for (size_t i = 0; i + 2*unitSize - 1 < n; i += 2*unitSize)
        {
            size_t leftStart = i;
            size_t rightStart = i + unitSize;
            //last element of unit decides which position 
            int lastLeft = lastElement(units, leftStart, unitSize);
            int lastRight = lastElement(units, rightStart, unitSize);
            if (lastLeft > lastRight)
            {
                for (size_t j = 0; j < unitSize; ++j)
                    std::swap(units[leftStart + j], units[rightStart + j]);
            }
        }
        unitSize *= 2;
    }
    unitSize /= 2;
}

std::deque<int> PmergeMe::FordJohnsonDeq(std::deque<std::pair<int,int>> pairs, size_t unitSize, int oddNum)
{
    // std::cout << "First Unit Size: " << unitSize << std::endl;
    std::deque<int> numbers = flattenPairsDeq(pairs);
    if (oddNum != -1)
    {
        numbers.push_back(oddNum);
    }
    // printContainer(numbers);
    std::deque<int> main, pend, leftover;
    while (unitSize >= 1)
    {
        // std::cout << "Processing unitSize = " << unitSize << std::endl;
        splitMainPend(numbers, unitSize, main, pend, leftover);
        if (!pend.empty())
        {
            std::vector<size_t> insertionOrder = generateJacobInsertionOrder(pend.size() / unitSize);
            insertPendUnits(main, pend, insertionOrder, unitSize);
        }
        rebuildNumbersFromMainAndLeftover(main, leftover, numbers);
        unitSize /= 2;
    }
    return main;
}

void PmergeMe::printResults(double timeVec, double timeDeq) const
{
    std::cout << "Before: ";
    for (size_t i = 0; i < _unsorted.size(); ++i)
        std::cout << _unsorted[i] << " ";
    std::cout << std::endl;

    std::cout << "After:  ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << _unsorted.size()
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << _unsorted.size()
              << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}