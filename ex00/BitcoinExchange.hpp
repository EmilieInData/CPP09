/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:25:59 by esellier          #+#    #+#             */
/*   Updated: 2025/09/15 23:22:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include "Common.hpp"

class BitcoinExchange
{
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange	operator=(const BitcoinExchange& other);

		std::map<std::string, double> const&		getData()const;
		// std::map<std::string, std::string> const&	getInput()const;
		
		void			saveData(std::ifstream& file);
		void			removeSpaces(std::string& line);
		bool			checkLetters(std::string const& line);
		void			checkInput(std::ifstream& file);
		void			checkDate(std::string const& date);
		double			checkValue(std::string const& value);
		bool 			leapYear(int year);
		std::string		today();
		double			doCalcul(std::string const& date, double value);


	private:
		std::map<std::string, double>					_data;
		std::map<std::string, double>::iterator			_itData;
		// std::map<std::string, std::string>				_input;
		// std::map<std::string, std::string>::iterator	_itInput;
};

#endif
