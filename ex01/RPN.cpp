/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:49:17 by esellier          #+#    #+#             */
/*   Updated: 2025/09/16 01:16:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "Common.hpp"

RPN::RPN()
{
	std::cout << BLUE << "Default constructor called\n" << RESET;
}

RPN::~RPN()
{
	std::cout << BLUE << "Default destructor called\n" << RESET;
}

RPN::RPN(const RPN& other)
{
	*this = other;
	std::cout << BLUE << "Copy constructor called\n" << RESET;
}

RPN  RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		this->_data = other._data;
	}
	else
		std::cout << ERROR << PINK << " Error: you're trying to assign a class to itself\n" << RESET;
	return (*this);
}

int	RPN::doCalcul(char sign)
{
	if (_data.size() < 2)
		throw std::runtime_error("Error: invalid mathematical expression");
	int	second = _data.top();
	_data.pop();
	int	first = _data.top();
	_data.pop();
	int	result;
	
	switch(sign)
	{
		case '-':
			result = first - second;
			break;
		case '+':
			result = first + second;
			break;
		case '*':
			result = first * second;
			break;
		case '/':
			if (second == 0)
				throw std::runtime_error("Error: division by 0 not allowed");
			result = first / second;
			break;
		default:
			throw std::runtime_error("Error: incorrect operator");
	}
	if (!_data.empty())
		throw std::runtime_error("Error: invalid mathematical expression");
	return result;
}

void	RPN::fillStack(std::string const& str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ' || str[i] == '	')
			continue;
		else if (checkInt(str[i]) != -1)
		{
			_data.push(checkInt(str[i]));
			if (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '	')
				throw std::runtime_error("Error, bad argument");
		}
		else if (checkOperator(str[i]) != 'x')
		{
			_data.push(doCalcul(str[i]));
			if (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '	')
				throw std::runtime_error("Error, bad argument");
		}
		else
			throw std::runtime_error("Error, bad argument");
	}
	std::cout << GREEN << _data.top() << RESET << std::endl;
}

int	RPN::checkInt(char c)
{
	if (c < '0' || c > '9')
		return -1;
	return c - '0';
}

char	RPN::checkOperator(char c)
{
	if(c != '-' && c != '+' && c != '*' && c != '/')
		return 'x';
	return c;
}
