/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:54:57 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/17 15:34:38 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <utility>

void printPairs(const std::vector<std::pair<int,int>> &pairs);
std::vector<std::pair<int, int>> makeAndSortPairs(const std::vector<int> &numbers, int &leftover);
void firstUnitSort(std::vector<std::pair<int,int>> &units, size_t &unitSize);


std::vector<int> FordJohnson(std::vector<std::pair<int,int>> pairs, size_t unitSize);
std::vector<int> flattenPairs(const std::vector<std::pair<int,int>> &pairs);
void printVector(const std::vector<int> &v);

class PmergeMe
{

};
