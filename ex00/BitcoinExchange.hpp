/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:25:59 by esellier          #+#    #+#             */
/*   Updated: 2025/09/04 19:56:04 by esellier         ###   ########.fr       */
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

		void			saveData(std::ifstream& file);
		void			removeSpaces(std::string& line);
		bool			checkLetters(std::string& line);
		void			saveInput(std::ifstream& file);
		bool			checkDates(std::string& date);

	private:
		std::map<std::string, double>					_data;
		std::map<std::string, double>::iterator			_itData;
		std::map<std::string, std::string>				_file;
		std::map<std::string, std::string>::iterator	_it;
};

#endif
