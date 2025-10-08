/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:54:57 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/08 15:30:22 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main (int argc, char* argv[])
{
    //numbers passed in will always be less than 10 (int)
    //output result on standart output
    //if error while execution -> error message (standard error)
    // operations : + - * /
    
    //parse 
    // 7 7 * 7 -
    //load stack container:
    //left to right:
    //if number push it onto stack 
    //if operator pop first two numbers
    //if not 2 numbers before operator -> Error 
    //if not operator at end -> error 
    
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