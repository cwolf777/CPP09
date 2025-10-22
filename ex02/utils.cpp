/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:48:44 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/21 18:21:01 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"
#include "utils.hpp"

// Letztes Element einer Einheit holen
// int lastElement(const std::vector<std::pair<int,int>> &units, size_t start, size_t size)
// {
//     size_t idx = start + size - 1;
//     if (idx >= units.size())
//         idx = units.size() - 1;
//     return units[idx].second;
// }




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

// std::vector<std::pair<int,int>> makeAndSortPairs(const std::vector<int> &numbers, int &leftover) //Paare gebildet und intern gesortet
// {
//     leftover = -1; //default
//     std::vector<std::pair<int,int>> pairs;
//     size_t n = numbers.size(); //n = number of numbers

//     size_t i = 0;
//     while (i + 1 < n)
//     {
//         int a = numbers[i];
//         int b = numbers[i+1];
//         if (a > b)
//             std::swap(a,b);
//         pairs.push_back(std::make_pair(a,b));
//         i += 2;
//     }
//     // if (i < n) leftover = numbers[i];
    
//     if (numbers.size() % 2 != 0)
//         leftover = numbers.back();

//     return pairs; //return container of pairs
// }

void printPairs(const std::vector<std::pair<int,int>> &pairs) {
    for (size_t i = 0; i < pairs.size(); ++i)
        std::cout << "(" << pairs[i].first << "," << pairs[i].second << ") ";
    std::cout << std::endl;
}

void printPairsDeq(const std::deque<std::pair<int,int>> &pairs) {
    for (size_t i = 0; i < pairs.size(); ++i)
        std::cout << "(" << pairs[i].first << "," << pairs[i].second << ") ";
    std::cout << std::endl;
}



// void splitMainPend(const std::vector<int> &numbers, size_t unitSize, std::vector<int> &main, std::vector<int> &pend, std::vector<int> &leftover)
// {
//     main.clear();
//     pend.clear();
//     leftover.clear();
    
//     if (unitSize == 0 || numbers.empty())
//         return;

//     size_t totalUnits = numbers.size() / unitSize;

//     size_t usedElements = totalUnits * unitSize;

//     if (totalUnits == 0)
//     {
//         leftover = numbers;
//         return;
//     }

//     // std::cout << "Vollstaendige Einheiten: " << totalUnits << std::endl;
//     // std::cout << "Benutzte Zahlen (ausser leftover): " << usedElements << std::endl;

//     for (size_t u = 0; u < totalUnits/2; ++u)
//     {
//         size_t bStart = u * unitSize * 2; //0, 8, 16, 24 
//         size_t aStart = bStart + unitSize; //4, 12, 20, 28


//         if (u == 0)
//         {
//             main.insert(main.end(), numbers.begin() + bStart, numbers.begin() + bStart + unitSize);
//             main.insert(main.end(), numbers.begin() + aStart, numbers.begin() + aStart + unitSize);
//         }
//         else
//         {
//             pend.insert(pend.end(), numbers.begin() + bStart, numbers.begin() + bStart + unitSize);
//             main.insert(main.end(), numbers.begin() + aStart, numbers.begin() + aStart + unitSize); //warum wird bei u = 1 nicht in main inserted
//         }
//     }
//     // if ungerade totalUnits die letze sache in pend 
//     if (totalUnits % 2 != 0)
//     {
//         size_t lastStart = (totalUnits - 1) * unitSize;
//         pend.insert(pend.end(), numbers.begin() + lastStart, numbers.begin() + lastStart + unitSize);
//     }
//     if (usedElements < numbers.size())
//     {
//         leftover.insert(leftover.end(), numbers.begin() + usedElements, numbers.end());
//     }
// }

static std::vector<size_t> generateJacobsthalUpTo(size_t limit)
{
    std::vector<size_t> j = {0, 1};
    while (j.back() < limit) {
        size_t next = j[j.size()-1] + 2 * j[j.size()-2];
        j.push_back(next);
    }
    return j;
}

std::vector<size_t> generateJacobInsertionOrder(size_t pendCount)
{
    std::vector<size_t> order;
    if (pendCount == 0)
        return order;

    // maximaler b-Index, der in pend existiert (b2..bMax)
    size_t bMax = pendCount + 1; // b2..b(bMax)

    // Erzeuge Jacobsthal-Zahlen bis >= bMax
    std::vector<size_t> jac = generateJacobsthalUpTo(bMax);

    // Wir interessieren uns ab J(3).
    // Für jedes J(i) fügen wir rückwärts j = min(J(i), bMax) .. (J(i-1)+1) ein.
    for (size_t i = 3; i < jac.size(); ++i)
    {
        size_t current = jac[i];
        size_t previous = jac[i-1];

        // begrenze current auf bMax
        if (current > bMax) current = bMax;

        // berechne begin/end als signed, um sicheren Abwärtszählzyklus zu haben
        long long begin = static_cast<long long>(current);
        long long end   = static_cast<long long>(previous) + 1; // inklusiv

        // Falls begin < end, nichts zu tun für diesen Schritt
        if (begin < end) {
            // nichts
        } else {
            for (long long j = begin; j >= end; --j) {
                if (j >= 2 && static_cast<size_t>(j) <= bMax) {
                    order.push_back(static_cast<size_t>(j));
                }
            }
        }

        if (current == bMax)
            break; // wir haben die maximale verfügbare b-Index erreicht
    }

    // Ergänze fehlende Indizes (2..bMax) falls nötig — in aufsteigender Reihenfolge
    for (size_t x = 2; x <= bMax; ++x) {
        if (std::find(order.begin(), order.end(), x) == order.end())
            order.push_back(x);
    }

    return order;
}


// void rebuildNumbersFromMainAndLeftover(const std::vector<int> &main, const std::vector<int> &leftover, std::vector<int> &numbers)
// {
//     numbers.clear();
//     numbers.reserve(main.size() + leftover.size()); //?

//     numbers.insert(numbers.end(), main.begin(), main.end());
//     numbers.insert(numbers.end(), leftover.begin(), leftover.end());
// }

// static size_t findInsertPos(const std::vector<int> &main, int key)
// {
//     size_t left = 0;
//     size_t right = main.size();

//     while (left < right)
//     {
//         size_t mid = left + (right - left) / 2;
//         if (main[mid] < key)
//             left = mid + 1;
//         else
//             right = mid;
//     }
//     return left; // Position, an der eingefügt werden soll
// }

// void insertPendUnits(std::vector<int> &main, std::vector<int> &pend, const std::vector<size_t> &insertionOrder, size_t unitSize)
// {
//     if (pend.empty() || unitSize == 0)
//         return;

//     size_t pendUnits = pend.size() / unitSize;

//     for (size_t idx : insertionOrder)
//     {
//         if (idx < 2) // b1 nie in pend
//             continue;

//         size_t unitIdxInPend = idx - 2; // b2 → 0, b3 → 1, usw.
//         if (unitIdxInPend >= pendUnits)
//             break;

//         size_t start = unitIdxInPend * unitSize;
//         size_t end = start + unitSize;

//         if (end > pend.size())
//             break;

//         // Komplette Einheit extrahieren
//         std::vector<int> unit(pend.begin() + start, pend.begin() + end);
//         int key = unit.back(); // Letztes Element = Sortierschlüssel

//         // 🔸 Binäre Suche auf Einheitenebene in main:
//         // Suche Position, an der der neue Key größer als der letzte Wert der vorherigen Einheit ist
//         size_t left = 0;
//         size_t right = main.size() / unitSize; // Anzahl der Einheiten in main
//         while (left < right)
//         {
//             size_t mid = (left + right) / 2;
//             int midKey = main[(mid + 1) * unitSize - 1]; // letzter Wert der mittleren Einheit

//             if (midKey < key)
//                 left = mid + 1;
//             else
//                 right = mid;
//         }

//         // 🔸 Jetzt liegt left an der Einheit, VOR der eingefügt werden muss.
//         size_t insertPos = left * unitSize;

//         // Einheit an der richtigen Stelle (blockweise) einfügen
//         main.insert(main.begin() + insertPos, unit.begin(), unit.end());

//         // std::cout << "Main nach Insert b" << idx << ": ";
//         // printVector(main);
//     }

//     // Pend am Ende vollständig leeren
//     pend.clear();
// }

// std::vector<int> FordJohnson(std::vector<std::pair<int,int>> pairs, size_t unitSize, int oddNum)
// {
    
//     // std::cout << "First Unit Size: " << unitSize << std::endl;
//     std::vector<int> numbers = flattenPairs(pairs);
//     printVector(numbers);
    
//     if (oddNum != -1)
//     {
//         numbers.push_back(oddNum);
//     }
    
//     printVector(numbers);
    
//     std::vector<int> main, pend, leftover;
//     while (unitSize >= 1)
//     {
//         std::cout << "Processing unitSize = " << unitSize << std::endl;
//         splitMainPend(numbers, unitSize, main, pend, leftover); 
//         std::cout << "Main: " << std::endl;
//         printVector(main);
//         std::cout << "Pend: " << std::endl;
//         printVector(pend);
//         std::cout << "Leftover: " << std::endl;
//         printVector(leftover);
        
//         if (!pend.empty())
//         {
//             std::vector<size_t> insertionOrder = generateJacobInsertionOrder(pend.size() / unitSize);
//             // std::cout << "Jacobsthal Insertion Order: ";
//             // for (auto i : insertionOrder) std::cout << i << " ";
//             // std::cout << std::endl;
            
//             insertPendUnits(main, pend, insertionOrder, unitSize);
//         }
//         // std::cout << "Main after Insertion: " << std::endl;
//         // printVector(main);
//         // std::cout << "Leftover after Insertion: " << std::endl;
//         // printVector(leftover);
//         rebuildNumbersFromMainAndLeftover(main, leftover, numbers);
//         // std::cout << "Ende der Sequence (numbers): " << std::endl;
//         // printVector(numbers);
//         unitSize /= 2;
//     }
//     return main;
// }


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

std::deque<int> flattenPairsDeq(const std::deque<std::pair<int,int>> &pairs)
{
    std::deque<int> result;
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        result.push_back(pairs[i].first);
        result.push_back(pairs[i].second);
    }
    return result;
}





