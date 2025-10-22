/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:48:44 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/22 16:47:58 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"
#include "utils.hpp"

static std::vector<size_t> generateJacobsthalUpTo(size_t limit)
{
    std::vector<size_t> j = {0, 1};
    while (j.back() < limit)
    {
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

    size_t bMax = pendCount + 1;
    
    std::vector<size_t> jac = generateJacobsthalUpTo(bMax);

    for (size_t i = 3; i < jac.size(); ++i)
    {
        size_t current = jac[i];
        size_t previous = jac[i-1];
        if (current > bMax) current = bMax;

        long long begin = static_cast<long long>(current);
        long long end   = static_cast<long long>(previous) + 1;

        if (begin < end)
        {
            // nichts
        }
        else
        {
            for (long long j = begin; j >= end; --j)
            {
                if (j >= 2 && static_cast<size_t>(j) <= bMax)
                {
                    order.push_back(static_cast<size_t>(j));
                }
            }
        }

        if (current == bMax)
            break;
    }

    for (size_t x = 2; x <= bMax; ++x)
    {
        if (std::find(order.begin(), order.end(), x) == order.end())
            order.push_back(x);
    }

    return order;
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





