/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:48:44 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/18 12:21:29 by cwolf            ###   ########.fr       */
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


static void splitMainPend(const std::vector<int> &numbers, size_t unitSize, std::vector<int> &main, std::vector<int> &pend, std::vector<int> &leftover)
{
    main.clear();
    pend.clear();
    leftover.clear();
    
    if (unitSize == 0 || numbers.empty())
        return;

    size_t totalUnits = numbers.size() / unitSize;

    size_t usedElements = totalUnits * unitSize;

    if (totalUnits == 0)
    {
        leftover = numbers;
        return;
    }

    std::cout << "Vollstaendige Einheiten: " << totalUnits << std::endl;
    std::cout << "Benutzte Zahlen (ausser leftover): " << usedElements << std::endl;

    for (size_t u = 0; u < totalUnits/2; ++u)
    {
        size_t bStart = u * unitSize * 2; //0, 8, 16, 24 
        size_t aStart = bStart + unitSize; //4, 12, 20, 28


        if (u == 0)
        {
            main.insert(main.end(), numbers.begin() + bStart, numbers.begin() + bStart + unitSize);
            main.insert(main.end(), numbers.begin() + aStart, numbers.begin() + aStart + unitSize);
        }
        else
        {
            pend.insert(pend.end(), numbers.begin() + bStart, numbers.begin() + bStart + unitSize);
            main.insert(main.end(), numbers.begin() + aStart, numbers.begin() + aStart + unitSize); //warum wird bei u = 1 nicht in main inserted
        }
    }
    // if ungerade totalUnits die letze sache in pend 
    if (totalUnits % 2 != 0)
    {
        size_t lastStart = (totalUnits - 1) * unitSize;
        pend.insert(pend.end(), numbers.begin() + lastStart, numbers.begin() + lastStart + unitSize);
    }
    if (usedElements < numbers.size())
    {
        leftover.insert(leftover.end(), numbers.begin() + usedElements, numbers.end());
    }
}


static std::vector<size_t> generateJacobsthalUpTo(size_t n)
{
    std::vector<size_t> jac = {0, 1};
    while (jac.back() < n)
    {
        jac.push_back(jac[jac.size() - 1] + 2 * jac[jac.size() - 2]);
    }
    return jac;
}

std::vector<size_t> getJacobInsertionOrder(size_t pendSize)
{
    std::vector<size_t> jac = generateJacobsthalUpTo(pendSize + 1);
    std::vector<size_t> order;

    for (size_t i = 3; i < jac.size(); ++i)
    {
        size_t current = jac[i];
        size_t previous = jac[i - 1];

        if (current > pendSize)
            current = pendSize;

        // rückwärts vom current bis previous+1
        for (size_t j = current; j > previous; --j)
            order.push_back(j);

        if (current == pendSize)
            break;
    }

    // Wenn Jacobsthal-Zahlen nicht alles abdecken (z.B. kleine pend-Größe)
    // dann füge restliche Elemente normal hinzu
    for (size_t i = 1; i <= pendSize; ++i)
    {
        if (std::find(order.begin(), order.end(), i) == order.end())
            order.push_back(i);
    }

    return order;
}

static void rebuildNumbersFromMainAndLeftover(const std::vector<int> &main, const std::vector<int> &leftover, std::vector<int> &numbers)
{
    numbers.clear();
    numbers.reserve(main.size() + leftover.size()); //?

    numbers.insert(numbers.end(), main.begin(), main.end());
    numbers.insert(numbers.end(), leftover.begin(), leftover.end());
}

std::vector<int> FordJohnson(std::vector<std::pair<int,int>> pairs, size_t unitSize)
{
    std::cout << "First Unit Size: " << unitSize << std::endl;
    std::vector<int> numbers = flattenPairs(pairs);
    printVector(numbers);
    
    std::vector<int> main, pend, leftover;
    while (unitSize > 1)
    {
        std::cout << "Processing unitSize = " << unitSize << std::endl;
        splitMainPend(numbers, unitSize, main, pend, leftover); 
        std::cout << "Main: " << std::endl;
        printVector(main);
        std::cout << "Pend: " << std::endl;
        printVector(pend);
        std::cout << "Leftover: " << std::endl;
        printVector(leftover);
        //if something in pend
            //insert process: 
            //define jacobsthal number
            //this defines which unit in pend gets inserted first into main (per binary insertion)
            //which b in pend continues? ... until pend empty 
            //vector main -> vector numbers;
        
        if (!pend.empty())
        {
            std::vector<size_t> insertionOrder = getJacobInsertionOrder(pend.size());
            std::cout << "Jacobsthal Insertion Order: ";
            for (auto i : insertionOrder) std::cout << i << " ";
            std::cout << std::endl;
            
            // for (size_t idx : insertionOrder)
            // {
            //     // int val = pend[idx - 1];
            //     //binaryinsert (main, val)
            //     //test print 
            // }
        }
        
        rebuildNumbersFromMainAndLeftover(main, leftover, numbers);
        std::cout << "Ende der Sequence (numbers): " << std::endl;
        printVector(numbers);
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


