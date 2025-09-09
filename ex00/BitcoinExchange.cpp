/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:49:17 by esellier          #+#    #+#             */
/*   Updated: 2025/09/09 19:23:40 by esellier         ###   ########.fr       */
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
		this->_itData = other._itData;
		// this->_input = other._input;
		// this->_itInput = other._itInput;
	}
	else
		std::cout << ERROR << PINK << " Error: you're trying to assign a class to itself\n" << RESET;
	return (*this);
}


std::map<std::string, double> const&	BitcoinExchange::getData()const
{
	return _data;
}

// std::map<std::string, std::string> const&	BitcoinExchange::getInput()const
// {
// 	return _input;
// }

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
	// 2022-01-09,41864.44
	return ;    
}
// for (size_t i = 0; i < line.length(); i++)
// {
// 	if (!isdigit(line[i]) && line[i] != '.' && line[i] != '-' && line[i] != ',')
// 		continue;
// }

void	BitcoinExchange::removeSpaces(std::string& line)
{
	line.erase(std::remove_if(line.begin(), line.end(), (int(*)(int))std::isspace), line.end());
}
bool	BitcoinExchange::checkLetters(std::string const& line)
{
	for (size_t i = 0; i < line.length(); i++)
	{
		if (std::isalpha(line[i]))
			return true;
	}
	return false;
}

void BitcoinExchange::checkInput(std::ifstream& file)
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
		try
		{
			checkDate(date);
			checkValue(value);
			doCalcul(date, value);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			continue;
		}
		std::cout << BLUE << date << " => " << value << " = \n";
				//   << GREEN << result operation << RESET << std::endl;
	}
	return ; 
}

void	BitcoinExchange::checkDate(std::string const& date)
{
	int	day;
	int	month;
	int	year;
	int	array[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (date.length() != 10)
		throw std::runtime_error("Error: bad input => " + date);
	for (size_t i = 0; i < date.length(); i++)
	{
		if (!isdigit(date[i]))
		{
			if ((i != 4 && i != 7) || ((i == 4 || i == 7) && date[i] != '-'))
				throw std::runtime_error("Error: bad input => " + date);
		}
	}
	std::stringstream(date.substr(0, 4)) >> year;
	std::stringstream(date.substr(5, 2)) >> month;
	std::stringstream(date.substr(8, 2)) >> day;
	// std::cout << "Year: " << year << ", Month: " << month << ", Day: " << day << std::endl;
	
    if (date < _data.begin()->first|| date > today() || month < 1 || month > 12 || day < 1)
		throw std::runtime_error("Error: bad input => " + date);
	
	if (leapYear(year))
		array[1] = 29;
	if (day > array[month - 1])
		throw std::runtime_error("Error: bad input => " + date);
	return;	
}

bool	BitcoinExchange::leapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true;
	return false;
}

std::string	BitcoinExchange::today()
{
	std::stringstream	date;
    std::time_t 		t = std::time(0); // time in second since 1970/01/01
    std::tm* 			now = std::localtime(&t); // struct with year, month, day, sec..

    int year  = now->tm_year + 1900; //computer begin in 1900 , 2025 = 125
    int month = now->tm_mon + 1;	 //0 -> january, 11->december
    int day   = now->tm_mday;

    date << year << "-" << std::setw(2) << std::setfill('0')
		 << month << "-" << std::setw(2) << std::setfill('0')
		 << day;

	// std::cout << PINK << "TODAY: " << date.str() << RESET << std::endl; //TO BORROW
    return date.str();
}

void	BitcoinExchange::checkValue(std::string const& value)
{
	double	num;
	bool	flag = false;
	
	if (value.empty())
		throw std::runtime_error("Error: value is missing");
	if (value[0] == '-')
		throw std::runtime_error("Error: value is not a positive number => " + value);
	for (size_t i = 0; i < value.length(); i++)
	{
		if (value[i] < '0' || value[i] > '9')
		{
			if (value[i] == '.' && flag == false)
				flag = true;
			else
				throw std::runtime_error("Error: value is not a number => " + value);
		}
	}
	num = atof(value.c_str());
	if (num >= 1000)
		throw std::runtime_error("Error: value is too large => " + value);
	if (num <= 0)
		throw std::runtime_error("Error: value is too small => " + value);
	return;
}

double	BitcoinExchange::doCalcul(std::string const& date, std::string const& value)
{
	
	//faire une boucle pour chercher la date si pas trouver la plus petite, donc boucle on check
	//que la value sauvee n'est pas au dessus de la value cherchee

	//faire le calcul et imprimer le resultat ou le message d'erreur
}




// --> to know <--
// << std::fixed << std::setprecision(2) , pour imprimer les float/double 

// if (std::isnan(x))
