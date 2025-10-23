/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:54:57 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/23 20:12:41 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main (int argc, char* argv[])
{
    // 7 7 * 7 -
    
    if (argc != 2)
    {
        std::cerr << "Wrong usage: ./btc <database>" << std::endl;
            exit(1);
    }
        
    RPN test;
    float result = test.execute(argv[1]);

    std::cout << "Result: " << result << std::endl;

    return (0);
}