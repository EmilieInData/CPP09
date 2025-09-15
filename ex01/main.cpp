/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:11:25 by esellier          #+#    #+#             */
/*   Updated: 2025/09/16 01:20:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Common.hpp"
#include "RPN.hpp"

int main(int av, char **ac)
{
	if (av != 2)
	{
		std::cout << ERROR << PINK " Error: one argument required\n" << RESET;
		return (1);
	}

	RPN polish;
	
	try
	{
		polish.fillStack(ac[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << PINK << ERROR << e.what() << RESET << '\n';
		return (1);
	}
	return (0);
}
