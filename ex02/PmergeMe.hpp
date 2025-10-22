/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:54:57 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/22 16:58:07 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <utility>
#include <climits>
#include <chrono>
#include <iomanip>

class PmergeMe
{
    private:
        std::vector<int> _vec;
        std::deque<int> _deq;
        std::vector<int> _unsorted;
        
        std::vector<std::pair<int, int>> makeAndSortPairs(const std::vector<int> &numbers, int &leftover);
        std::deque<std::pair<int, int>> makeAndSortPairsDeq(const std::deque<int> &numbers, int &leftover);
        
        void firstUnitSort(std::vector<std::pair<int,int>> &units, size_t &unitSize);
        void firstUnitSortDeq(std::deque<std::pair<int,int>> &units, size_t &unitSize);
        
        std::vector<int> FordJohnson(std::vector<std::pair<int,int>> pairs, size_t unitSize, int oddNum);
        std::deque<int> FordJohnsonDeq(std::deque<std::pair<int,int>> pairs, size_t unitSize, int oddNum);
        
    public:
        PmergeMe();                                  
        PmergeMe(const PmergeMe &other);             
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();
        
        void loadInput(char **argv, int count);
        void sortVector();
        void sortDeque();
        void printResults(double timeVec, double timeDeq) const;
        
};
