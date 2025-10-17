/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:48:44 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/17 16:03:33 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"

// Letztes Element einer Einheit holen
int lastElement(const std::vector<std::pair<int,int>> &units, size_t start, size_t size)
{
    size_t idx = start + size - 1;
    if (idx >= units.size())
        idx = units.size() - 1;
    return units[idx].second;
}


void firstUnitSort(std::vector<std::pair<int,int>> &units, size_t &unitSize)
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

std::vector<std::pair<int,int>> makeAndSortPairs(const std::vector<int> &numbers, int &leftover) //Paare gebildet und intern gesortet
{
    leftover = -1; //default
    std::vector<std::pair<int,int>> pairs;
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
    if (i < n) leftover = numbers[i];

    return pairs; //return container of pairs
}

void printPairs(const std::vector<std::pair<int,int>> &pairs) {
    for (size_t i = 0; i < pairs.size(); ++i)
        std::cout << "(" << pairs[i].first << "," << pairs[i].second << ") ";
    std::cout << std::endl;
}




static void splitMainPend(const std::vector<int> &numbers, size_t unitSize, std::vector<int> &main, std::vector<int> &pend)
{
    main.clear();
    pend.clear();
    
    size_t  totalUnits = numbers.size() / (2 * unitSize);
    if (totalUnits == 0)
        return;
        
    for (size_t u = 0; u < totalUnits; ++u)
    {
        size_t bStart = u * 2 * unitSize;       // Beginn b
        size_t aStart = bStart + unitSize;      // Beginn a

        // 1. b1/b2/... in main oder pend
        if (u == 0) // erste Einheit: b1 in main
            main.insert(main.end(), numbers.begin() + bStart, numbers.begin() + bStart + unitSize);
        else        // restliche b's in pend
            pend.insert(pend.end(), numbers.begin() + bStart, numbers.begin() + bStart + unitSize);

        // 2. a1/a2/... immer in main
        main.insert(main.end(), numbers.begin() + aStart, numbers.begin() + aStart + unitSize);
    }

}

std::vector<int> FordJohnson(std::vector<std::pair<int,int>> pairs, size_t unitSize)
{
    std::cout << "First Unit Size: " << unitSize << std::endl;
    std::vector<int> numbers = flattenPairs(pairs);
    printVector(numbers);
    
    std::vector<int> main, pend;
    while (unitSize > 1)
    {
        std::cout << "Processing unitSize = " << unitSize << std::endl;
        splitMainPend(numbers, unitSize, main, pend);
        // std::cout << "Main: " << std::endl;
        // printVector(main);
        // std::cout << "Pend: " << std::endl;
        // printVector(pend);
        
        //if something in pend
            //insert process: 
            //define jacobsthal number
            //this defines which unit in pend gets inserted first into main (per binary insertion)
            //which b in pend continues? ... until pend empty 
            //vector main -> vector numbers;
            
        
        



        unitSize /= 2;
    }
    return main;
}


std::vector<int> flattenPairs(const std::vector<std::pair<int,int>> &pairs)
{
    std::vector<int> result;
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        result.push_back(pairs[i].first);
        result.push_back(pairs[i].second);
    }
    return result;
}


void printVector(const std::vector<int> &v)
{
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}