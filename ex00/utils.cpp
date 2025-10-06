/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:21:05 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/06 11:39:41 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


std::map<std::string, double> load_map(void)
{
    std::map<std::string, double> exchangeRates; //name: exhcangeRate, key = string, value = double

    std::ifstream file("data.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Fail cannot be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line;
    bool firstLine = true;
    
    while(std::getline(file, line)) //if line left, saves line in line 
    {
        if (firstLine)
        {
            firstLine = false;
            continue; //skips to next line (skips iteration)
        }
        
        std::stringstream ss(line); //makes line devideable
        std::string dateStr;
        std::string rateStr;
        
        if (std::getline(ss, dateStr, ',') && std::getline(ss, rateStr)) //line wird in dateStr und rateStr aufgeteilt, beides muss erfolgreich sein
        {
            double rate = std::stod(rateStr);
            exchangeRates[dateStr] = rate; //key: dateStr, value: rate, saves in map
        }    
    }
    file.close();
    return exchangeRates;
}


// void validate(std::string filename)
// {
//     //try
//     ////check header date | value
//     ////line per line: (2012-03-15 | 54)
//     ////cut until "|" if not throw error
//     ////check if date is correct (regex) throw error 
//     ////check after |
//     ////check value, float unsigned int 0 - 1000 throw error 
//     //catch
//     //if line correct -> void printOutput(xyz);
// }