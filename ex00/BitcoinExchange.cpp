/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:49:17 by esellier          #+#    #+#             */
/*   Updated: 2025/09/01 20:17:48 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "Common.hpp"

BitcoinExchange::BitcoinExchange()
{
    std::cout << PURPLE << "Default constructor called\n" << RESET;
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << PURPLE << "Default destructor called\n" << RESET;    
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    *this = other;
    std::cout << PURPLE << "Copy constructor called\n" << RESET;    
}

   
BitcoinExchange  BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        this->_data = other._data;
        this->_it = other._it;
    }
    else
        std::cout << ERROR << PINK << " Error: you're trying to assign a class to itself\n" << RESET;
    return (*this);
}

void    BitcoinExchange::saveData(std::ifstream& file)
{
    std::string line;
    std::string date;
    int         rate;
    
    while (getline(file, line))
    {
        if (line[0] != '1' && line[0] != '2')
            continue;
        std::size_t found = line.find(",");
        if (found == std::string::npos)
            continue;
        
        date = line.substr(0, found);
        std::istringstream(line.substr(found + 1)) >> rate;
        _data[date] = rate;
        
        // _it = _data.find(date);
        // std::cout << PURPLE << _it->first << " : " << _it->second << std::endl;
    }
    return ;    
}
