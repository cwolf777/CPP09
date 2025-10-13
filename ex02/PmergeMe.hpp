/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:54:57 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/13 16:30:20 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
// #include <algorithm>
// #include <chrono>

template <typename Container>
class PmergeMe
{
    private:
        Container data;
        double timeTaken;

        Container fordJohnson(Container vec);
        {
            if (vec.size() <= 1)
            {
                return vec;
            }
    
            Container big, small;

            //sort numbers into big and small ones [7, 3, 9, 1, 4] > big[7, 9, 4], small[3, 1] 
            for (size_t i = 0; i < vec.size(); i +=2)
            {
                if (i + 1 < vec.size())
                {
                    if (vec[i] < vec[i + 1])
                    {
                        small.push_back(vec[i]);
                        big.push_back(vec[i + 1]);
                    }
                    else
                    {
                        big.push_back(vec[i]);
                        small.push_back(vec[i + 1]);
                    }
                }
                else
                {
                    big.push_back(vec[i]);
                }
            }

            //recursive execution of fordJohnson with big container > sorts big numbers into small and big > until only one element left in big 
            big = fordJohnson(big);

            for (size_t i = 0; i < small.size(); ++i)
            {
                auto pos = std::lower_bound(big.begin(), big.end(), small[i]);
                big.insert(pos, small[i]);
            }

            return big;
        }
    
    public:
        PmergeMe() : timeTaken(0), data(NULL) {}; //??? = default
        PmergeMe(const std::vector<int>& input)
        {
            timeTaken = -1;
            data.insert(data.end(), input.begin(), input.end());
        };
        PmergeMe(const PmergeMe& other) : data(other.data), timeTaken(other.timeTaken) {};
        PmergeMe& operator=(const PmergeMe& other)
        {
            if (this != &other)
            {
                data = other.data;
                timeTaken = other.timeTaken;   
            }
            return *this;
        }
        ~PmergeMe(){};

        void sort();
        {
            auto start = std::chrono::high_resolution_clock::now();
            data = fordJohnson(data);
            auto end = std::chrono::high_resolution_clock::now();
            timeTaken = std::chrono::duration<double, std::micro>(end - start).count();
        }

        void print() const
        {
            for (size_t i = 0; i < data.size(); ++i)
                std::cout << data[i] << " ";
            std::cout << std::endl;             
        }

        double getTime() const {return timeTaken;}
};

