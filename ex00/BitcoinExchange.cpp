/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:49:17 by esellier          #+#    #+#             */
/*   Updated: 2025/09/04 20:12:41 by esellier         ###   ########.fr       */
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
	double      rate;
	
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
		// _itData = _data.find(date);
		// std::cout << PURPLE << std::fixed << std::setprecision(2) << _itData->first << " : " << _itData->second << std::endl;
	}
	return ;    
}

void	BitcoinExchange::removeSpaces(std::string& line)
{
	line.erase(std::remove_if(line.begin(), line.end(), (int(*)(int))std::isspace), line.end());
}
bool	BitcoinExchange::checkLetters(std::string& line)
{
	for (size_t i = 0; i < line.length(); i++)
	{
		if (std::isalpha(line[i]))
			return true;
	}
	return false;
}

void BitcoinExchange::saveInput(std::ifstream& file)
{
	std::string	line;
	std::string	date;
	std::string	value;
	bool		firstLine = true;
	
	while (getline(file, line))
	{
		removeSpaces(line);
		if (firstLine)
		{
			firstLine = false;
			if (checkLetters(line))
				continue;
		}
		std::size_t found = line.find("|");
		if (found == std::string::npos)
		{
			date = line;
			value = "";
		}
		else
		{		
			date = line.substr(0, found);
			value = line.substr(found + 1);
		}
		_file[date] = value;
		// _it = _file.find(date);
		// std::cout << PURPLE << _it->first << " : " << _it->second << std::endl;
	}
	
	return ; 
}

bool	BitcoinExchange::checkDates(std::string& date)
{
	int		d;
	int		m;
	int		y;
	char	c = '-';
	int		tmp;
	
	for (size_t i = 1; i < date.length(); i++)
	{
		//checker que des chiffres
		if (date[i] == c)
		{
			y = (int)date.substr(0, c);
			tmp = i;
		}
		if (date[i] == c)
		{
			m = (int)date.substr(i, c);	
	}
		return false;

	//checker aue la date est correct, elle existe	
	return true;
	
	2011-01-03
}

// bool isLeapYear(int year) {
//     return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
// }

// bool isValidDate(const std::string& dateStr) {
//     int day, month, year;
//     char sep1, sep2;

//     std::istringstream ss(dateStr);
//     if (!(ss >> day >> sep1 >> month >> sep2 >> year)) return false;
//     if (sep1 != '/' || sep2 != '/') return false;

//     if (year < 0 || month < 1 || month > 12 || day < 1) return false;

//     int daysInMonth[] = {31, (isLeapYear(year) ? 29 : 28), 31, 30, 31, 30,
//                          31, 31, 30, 31, 30, 31};

//     return day <= daysInMonth[month - 1];
// }

// bool	BitcoinExchange::checkValues(std::string& value)
// {
// 	if (checkLetters(value))
// 		return false;
		
// 	return true;

// -1.2
// }

//faire une boucle pour chercher la date si pas trouver la plus petite, donc boucle on check
//que la value sauvee n'est pas au dessus de la value cherchee

//verifier si format date ok
//transformer la value en int ou float et verifier le format (entre 0  1000 non inclus etc)

//faire le calcul et imprimer le resultat ou le message d'erreur

//la boucle se finit quand le fichier est entierement lu

// --> to know <--
// << std::fixed << std::setprecision(2) , pour imprimer les float/double 

// if (std::isnan(x))
