/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:21:05 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/06 13:51:24 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


void validate(std::string filename)
{
    //try
    ////check header date | value
    ////line per line: (2012-03-15 | 54)
    ////cut until "|" if not throw error
    ////check if date is correct (regex) throw error 
    ////check after |
    ////check value, float unsigned int 0 - 1000 throw error 
    //catch
    //if line correct -> void printOutput(xyz);
}