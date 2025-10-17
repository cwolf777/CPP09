/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:54:57 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/17 14:38:47 by cwolf            ###   ########.fr       */
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


class PmergeMe
{

};
