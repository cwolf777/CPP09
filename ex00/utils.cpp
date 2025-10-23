/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:21:05 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/23 20:11:42 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

static void checkHeader(const std::string& firstLine)
{
    std::string expected = "date | value";

    if (firstLine != expected)
    {
        throw std::logic_error("Error: Invalid header. Expected: 'date | value'");
    }
}

static void validateDate(const std::string& dateStr)
{
    // Entferne führende/trailing Leerzeichen
    std::string date = dateStr;
    date.erase(0, date.find_first_not_of(" \t"));
    date.erase(date.find_last_not_of(" \t") + 1);

    // Regex für YYYY-MM-DD
    std::regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");

    if (!std::regex_match(date, dateRegex))
    {
        throw std::logic_error("Error: Invalid date format -> " + date);
    }

    int year = std::stoi(date.substr(0,4));
    int month = std::stoi(date.substr(5,2));
    int day = std::stoi(date.substr(8,2));

    if (month < 1 || month > 12)
        throw std::logic_error("Error: Month out of range -> " + date);

    if (day < 1 || day > 31)
        throw std::logic_error("Error: Day out of range -> " + date);
        
    if (year < 0 || year > 2025)
        throw std::logic_error("Error: Year out of range -> " + date);

}

static void validateValue(const std::string& valueStr)
{
    std::string value = valueStr;
    value.erase(0, value.find_first_not_of(" \t"));
    value.erase(value.find_last_not_of(" \t") + 1);

    if (value.empty())
    {
        throw std::logic_error("Error: Value is empty");
    }
    
    // bool dotSeen = false;
    // for (size_t i = 0; i < value.size(); ++i)
    // {
    //     if (value[i] == '.')
    //     {
    //         if (dotSeen)
    //             throw std::logic_error("Error: Invalid number format -> " + value);
    //         dotSeen = true;
    //     } 
    //     else if (!std::isdigit(value[i]))
    //         throw std::logic_error("Error: Value contains invalid character -> " + value);
    // }
    
    size_t pos;
    float number;
    try
    {
        number = std::stof(value, &pos);
    }
    catch(const std::exception& e)
    {
        throw std::logic_error("Error: Invalid number -> " + value);
    }

    if (pos != value.length())
    {
        throw std::logic_error("Error: Value contains invalid character -> " + value);
    }

    if (number < 0.0 || number > 1000.0)
    {
        throw std::logic_error("Error: Value out of range (0-1000) -> " + value);
    }
}


static void printOutput(const std::map<std::string, double>& exchangeRates,
                 const std::string& dateStr, const std::string& valueStr)
{
    std::string value = valueStr;
    value.erase(0, value.find_first_not_of(" \t"));
    value.erase(value.find_last_not_of(" \t") + 1);

    double number = std::stod(value);
    
    auto it = exchangeRates.lower_bound(dateStr); //zeigt auf datum oder eins groesser (Lexikografischer Vergleich)
    
    if (it == exchangeRates.end()) //-> datum groesser als alle in map -> it--
    {
        --it;
    }
    else if (it->first != dateStr)  //it->first zugriff auf key
    {
        if (it == exchangeRates.begin())
        {
            throw std::logic_error("Error: no earlier date available for " + dateStr);
        }
        --it;
    }
    
    double rate = it->second;
    double result = number * rate;

    std::cout << dateStr << " => " << number 
              << " = " << std::fixed << std::setprecision(2) 
              << result << std::endl;

}
void validate(const std::string& filename)
{   
    BitcoinExchange btc;
    btc.load_map();

    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Input file cannot be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }

    try
    {
        std::string line;

        if (std::getline(inputFile, line))
            checkHeader(line);
        else
            throw std::logic_error("Error: File is empty");
        
        while (std::getline(inputFile, line))
        {
            std::stringstream ss(line); //makes line devideable
            std::string dateStr;
            std::string valueStr;   //(2012-03-15 | 54)
            
            if (std::getline(ss, dateStr, '|') && std::getline(ss, valueStr))
            {
                try
                {
                    validateDate(dateStr);
                    validateValue(valueStr);
                    printOutput(btc._exchangeRate, dateStr, valueStr);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            else
            {
                std::cerr << "Error: Invalid line format!" << std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

