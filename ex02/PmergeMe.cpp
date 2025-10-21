/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:54:57 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/21 18:28:41 by cwolf            ###   ########.fr       */
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

    for (int i = 1; i < argc; ++i) // Start bei 1, weil argv[0] = Programmname
    {
        std::string arg(argv[i]);

        // --- Eingabevalidierung ---
        for (size_t j = 0; j < arg.size(); ++j)
        {
            if (!std::isdigit(arg[j]))
                throw std::invalid_argument("Error: Invalid input '" + arg + "'");
        }

        long num = std::strtol(arg.c_str(), NULL, 10);
        if (num < 0 || num > INT_MAX)
            throw std::out_of_range("Error: Number out of range '" + arg + "'");

        // --- In beide Container einfügen ---
        _vec.push_back(static_cast<int>(num));
        _deq.push_back(static_cast<int>(num));
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
    std::cout << "Sorted List (Vec): " << std::endl;
    printVector(_vec);
}

std::vector<std::pair<int, int>> PmergeMe::makeAndSortPairs(const std::vector<int> &numbers, int &leftover)
{
    leftover = -1; //default
    std::vector<std::pair<int, int>> pairs;
    size_t n = numbers.size(); //n = number of numbers

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
    // if (i < n) leftover = numbers[i];
    
    if (numbers.size() % 2 != 0)
        leftover = numbers.back();

    return pairs; //return container of pairs
}

void PmergeMe::firstUnitSort(std::vector<std::pair<int,int>> &units, size_t &unitSize)
{
    size_t n = units.size();  //wie viele paare
    if (n <= 1)
        return;

    // size_t unitSize = 1; // Starting unit size = 1 paar, vergleicht ein paar mit dem anderen danach 2 paare mit 2 naechsten 

    while (unitSize < n) //while unit size is smaller than number of pairs
    {
        // Paarweise vergleichen
        for (size_t i = 0; i + 2*unitSize - 1 < n; i += 2*unitSize) //einheiten werden paarweise durchlaufen 
        {
            size_t leftStart = i;
            size_t rightStart = i + unitSize;
            // Vergleiche letzte Elemente der beiden Einheiten
            int lastLeft = lastElement(units, leftStart, unitSize);
            int lastRight = lastElement(units, rightStart, unitSize);
            if (lastLeft > lastRight)
            {
                // swap units
                for (size_t j = 0; j < unitSize; ++j)
                    std::swap(units[leftStart + j], units[rightStart + j]);
            }
        }
        // printPairs(units);
        unitSize *= 2; // nächste Stufe: Einheiten verdoppeln
    }
    unitSize /= 2;
}

//Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque Deque

void PmergeMe::sortDeque()
{
    int leftover;
    std::deque<std::pair<int,int>> pairs = makeAndSortPairsDeq(_deq, leftover);

    size_t unitSize = 1;
    firstUnitSort(pairs, unitSize);
    
    _vec = FordJohnson(pairs, unitSize, leftover);
    std::cout << "Sorted List (Vec): " << std::endl;
    printVector(_vec);
}

std::deque<std::pair<int, int>> PmergeMe::makeAndSortPairsDeq(const std::deque<int> &numbers, int &leftover)
{
    leftover = -1; //default
    std::deque<std::pair<int, int>> pairs;
    size_t n = numbers.size(); //n = number of numbers

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
    // if (i < n) leftover = numbers[i];
    
    if (numbers.size() % 2 != 0)
        leftover = numbers.back();

    return pairs; //return container of pairs
}

void PmergeMe::firstUnitSortDeq(std::deque<std::pair<int,int>> &units, size_t &unitSize)
{
    size_t n = units.size();  //wie viele paare
    if (n <= 1)
        return;

    // size_t unitSize = 1; // Starting unit size = 1 paar, vergleicht ein paar mit dem anderen danach 2 paare mit 2 naechsten 

    while (unitSize < n) //while unit size is smaller than number of pairs
    {
        // Paarweise vergleichen
        for (size_t i = 0; i + 2*unitSize - 1 < n; i += 2*unitSize) //einheiten werden paarweise durchlaufen 
        {
            size_t leftStart = i;
            size_t rightStart = i + unitSize;
            // Vergleiche letzte Elemente der beiden Einheiten
            int lastLeft = lastElement(units, leftStart, unitSize);
            int lastRight = lastElement(units, rightStart, unitSize);
            if (lastLeft > lastRight)
            {
                // swap units
                for (size_t j = 0; j < unitSize; ++j)
                    std::swap(units[leftStart + j], units[rightStart + j]);
            }
        }
        // printPairs(units);
        unitSize *= 2; // nächste Stufe: Einheiten verdoppeln
    }
    unitSize /= 2;
}