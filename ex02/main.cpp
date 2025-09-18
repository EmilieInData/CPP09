/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:11:25 by esellier          #+#    #+#             */
/*   Updated: 2025/09/18 17:57:23 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Common.hpp"
#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 3)
	{
		std::cout << ERROR << PINK " Error: minimum two arguments required\n" << RESET;
		return (1);
	}
	
	PmergeMe					merge;
		
	try
	{
		merge.checkArgs(av);
	}
	catch(const std::exception& e)
	{
		std::cerr << PINK << ERROR << e.what() << RESET << '\n';
		return (1);
	}
	return (0);
}
