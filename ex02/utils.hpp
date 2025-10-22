/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:41:25 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/22 16:47:18 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <utility>
#include <iostream>

template<template<typename...> class Container>
int lastElement(const Container<std::pair<int,int>> &units, size_t start, size_t size)
{
    size_t idx = start + size - 1;
    if (idx >= units.size())
        idx = units.size() - 1;
    return units[idx].second;
}

template<typename Container>
void printContainer(const Container &v)
{
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

template<typename Container>
void printPairs(const Container &pairs)
{
    for (size_t i = 0; i < pairs.size(); ++i)
        std::cout << "(" << pairs[i].first << "," << pairs[i].second << ") ";
    std::cout << std::endl;
}

template<typename Container>
void insertPendUnits(Container &main, Container &pend, const std::vector<size_t> &insertionOrder, size_t unitSize)
{
    if (pend.empty() || unitSize == 0)
        return;
    
    size_t pendUnits = pend.size() / unitSize;
    
    for (size_t idx : insertionOrder)
    {
        if (idx < 2) // b1 nie in pend
            continue;
        
        size_t unitIdxInPend = idx - 2; // b2 → 0, b3 → 1, usw.
        if (unitIdxInPend >= pendUnits)
            break;
        
        size_t start = unitIdxInPend * unitSize;
        size_t end = start + unitSize;
        if (end > pend.size())
            break;
        
        // Komplette Einheit extrahieren
        Container unit(pend.begin() + start, pend.begin() + end);
        int key = unit.back(); // Letztes Element = Sortierschlüssel
        
        // 🔸 Binäre Suche auf Einheitenebene in main:
        // Suche Position, an der der neue Key größer als der letzte Wert der vorherigen Einheit ist
        size_t left = 0;
        size_t right = main.size() / unitSize; // Anzahl der Einheiten in main
        
        while (left < right)
        {
            size_t mid = (left + right) / 2;
            int midKey = main[(mid + 1) * unitSize - 1]; // letzter Wert der mittleren Einheit
            if (midKey < key)
                left = mid + 1;
            else
                right = mid;
        }
        
        // 🔸 Jetzt liegt left an der Einheit, VOR der eingefügt werden muss.
        size_t insertPos = left * unitSize;
        
        // Einheit an der richtigen Stelle (blockweise) einfügen
        main.insert(main.begin() + insertPos, unit.begin(), unit.end());
        
        // std::cout << "Main nach Insert b" << idx << ": ";
        // printVector(main);
    }
    
    // Pend am Ende vollständig leeren
    pend.clear();
}

template<typename Container>
void splitMainPend(const Container &numbers, size_t unitSize, Container &main, Container &pend, Container &leftover)
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
    
    // std::cout << "Vollstaendige Einheiten: " << totalUnits << std::endl;
    // std::cout << "Benutzte Zahlen (ausser leftover): " << usedElements << std::endl;
    
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
            main.insert(main.end(), numbers.begin() + aStart, numbers.begin() + aStart + unitSize);
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

template<typename Container>
void rebuildNumbersFromMainAndLeftover(const Container &main, const Container &leftover, Container &numbers)
{
    numbers.clear();
    numbers.insert(numbers.end(), main.begin(), main.end());
    numbers.insert(numbers.end(), leftover.begin(), leftover.end());
}

// void splitMainPend(const std::vector<int> &numbers, size_t unitSize, std::vector<int> &main, std::vector<int> &pend, std::vector<int> &leftover);
std::vector<size_t> generateJacobInsertionOrder(size_t pendCount);
// void insertPendUnits(std::vector<int> &main, std::vector<int> &pend, const std::vector<size_t> &insertionOrder, size_t unitSize);
// void rebuildNumbersFromMainAndLeftover(const std::vector<int> &main, const std::vector<int> &leftover, std::vector<int> &numbers);
std::vector<int> flattenPairs(const std::vector<std::pair<int,int>> &pairs);


//deque
// void printPairsDeq(const std::deque<std::pair<int,int>> &pairs);
std::deque<int> flattenPairsDeq(const std::deque<std::pair<int,int>> &pairs);