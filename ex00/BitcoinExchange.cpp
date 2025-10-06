/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:36:01 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/06 14:10:23 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    _exchangeRate = load_map();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _exchangeRate(other._exchangeRate) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        _exchangeRate = other._exchangeRate;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange(){}

std::map<std::string, double> BitcoinExchange::load_map(void)
{
    std::map<std::string, double> exchangeRates; //name: exhcangeRate, key = string, value = double

    std::ifstream file("data.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Data file cannot be opened!" << std::endl;
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