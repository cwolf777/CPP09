/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:41:25 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/21 17:41:41 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <utility>
#include <iostream>

int lastElement(const std::vector<std::pair<int,int>> &units, size_t start, size_t size);
// void printPairs(const std::vector<std::pair<int,int>> &pairs);