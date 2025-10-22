/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 09:57:30 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/22 17:15:03 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong usage: ./btc <database>" << std::endl;
        exit(1);
    }
    
    std::string databaseFile = argv[1];
    validate(databaseFile);
}