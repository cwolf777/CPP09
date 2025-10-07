/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:16:45 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/07 11:13:58 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

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
        else
            applyOperator(token);
    }
    
    if (_st.size() != 1)
        std::cerr << "Error: Invalid expression" << std::endl;
    
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

void RPN::applyOperator(const std::string& op)
{
    if (_st.size() < 2)
        std::cerr << "Error: Not enough numbers in stack for operation!" << std::endl;

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