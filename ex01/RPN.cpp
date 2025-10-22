/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:16:45 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/08 15:54:11 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(){}
RPN::RPN(const RPN& other) : _st(other._st){}
RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
    {
        _st = other._st;
    }
    return *this;
}
RPN::~RPN(){}

float RPN::execute(const std::string& expression)
{
    std::stringstream ss(expression);
    std::string token;
    
    while (ss >> token)
    {
        if(isNumber(token))
        {
            int num = std::stoi(token);
            _st.push(num);
        }
        else if (isOperator(token))
        {
            applyOperator(token);
        }
        else
        {
            std::cout << "Error: Invalid Input: " << token << std::endl;
            exit (EXIT_FAILURE);
        }
        
    }
    
    if (_st.size() != 1)
    {
        std::cerr << "Error: Invalid expression" << std::endl;
        exit (1);
    }
    
    return _st.top();
}

bool RPN::isNumber(const std::string& token)
{
    if (token.empty())
        return false;
    for (size_t i = 0; i < token.size(); ++i)
    {
        char c = token[i];
        if (!std::isdigit(c))
            return false;
    }
    return true;
}

bool RPN::isOperator(const std::string& token)
{
    if (token.size() != 1)
        return false;

    char c = token[0];
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    else
        return false;
        
}

void RPN::applyOperator(const std::string& op)
{
    if (_st.size() < 2)
    {
        std::cerr << "Error: Not enough numbers in stack for operation: " << op << std::endl;
        exit (EXIT_FAILURE);
    }

    float b = _st.top();
    _st.pop();
    float a = _st.top();
    _st.pop();
    
    if (op == "+")
    {
        _st.push(a + b);
    }
    else if (op == "-")
    {
        _st.push(a - b);
    }
    else if (op == "*")
    {
        _st.push(a * b);
    }
    else if (op == "/")
    {
        if (b == 0)
            std::cerr << "Error: Division by zero" << std::endl;
        _st.push(a / b);
    }
    else
    {
        std::cerr << "Error: Unknown operator -> " << op << std::endl;
    }
}

