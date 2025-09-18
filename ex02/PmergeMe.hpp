/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:25:59 by esellier          #+#    #+#             */
/*   Updated: 2025/09/18 19:17:54 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include "Common.hpp"

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe	operator=(const PmergeMe& other);

		void	checkArgs(char** av);
		void	printVector();

	private:
		std::vector<int>			_vData;
		std::vector<int>::iterator	_vIt;
		std::clock_t				_vTiming;
				
		std::deque<int>				_dData;
		std::vector<int>::iterator	_dIt;
		std::clock_t				_dTiming;
};

#endif
