/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:11:25 by esellier          #+#    #+#             */
/*   Updated: 2025/09/19 14:54:56 by esellier         ###   ########.fr       */
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
	
	PmergeMe	merge;

	try
	{
		merge.checkArgs(av);
		merge.setVectorTiming();
		merge.doVector(2);
		printMessage(merge, av, ac - 1, merge.getVector(), "std::vector<int>", merge.getVectorTiming());
		merge.setDequeTiming();
		//merge.doDeque(2)
		printMessage(merge, av, ac - 1, merge.getDeque(), "std::deque<int>", merge.getDequeTiming());
	}
	catch(const std::exception& e)
	{
		std::cerr << PINK << ERROR << e.what() << RESET << '\n';
		return (1);
	}
	return (0);
}
