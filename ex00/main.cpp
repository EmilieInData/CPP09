/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:11:25 by esellier          #+#    #+#             */
/*   Updated: 2025/09/04 19:24:16 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Common.hpp"
#include "BitcoinExchange.hpp"

int main(int av, char **ac)
{
	BitcoinExchange be;

	if (av != 2)
	{
		if (av == 1)
			std::cout << ERROR << PINK " Error: database file is missing\n" << RESET;
		else
			std::cout << ERROR << PINK " Error: only one database allowed\n" << RESET;
		return (1);
	}
		
	std::ifstream fileData("data.csv");
	if (!fileData.is_open())
	{
		std::cout << ERROR << PINK " Error: data.csv file is not open\n" << RESET;
		fileData.close();
		return (1);
	}
	be.saveData(fileData);
	fileData.close();

	std::ifstream file(ac[1]);
	if (!file.is_open())
	{
		std::cout << ERROR << PINK " Error: argument file is not open\n" << RESET;
		file.close();
		return (1);
	}
	be.saveInput(file);
	file.close();
	return (0);
}
