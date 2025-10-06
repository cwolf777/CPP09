/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 09:57:30 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/06 13:50:43 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main (int argc, char* argv[])
{
    // (void)argv[1];
    if (argc != 1)
    {
        std::cout << "Wrong usage: ./btc <database>" << std::endl;
        exit(1);
    }
    
    BitcoinExchange btc;
    btc.load_map();
    
    int count = 0;
    for (const auto& pair : btc._exchangeRate) {
        std::cout << pair.first << " -> " 
                  << std::fixed << std::setprecision(2) 
                  << pair.second << std::endl;
        count++;
        if (count >= 10) break; // nur die ersten 10
    }
    std::string databaseFile = argv[1];
    validate(databaseFile);
}