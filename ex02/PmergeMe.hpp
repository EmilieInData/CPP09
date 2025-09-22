/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:25:59 by esellier          #+#    #+#             */
/*   Updated: 2025/09/23 01:06:11 by marvin           ###   ########.fr       */
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

		std::vector<int> const&		getVector() const;
		std::deque<int> const&		getDeque() const;
		std::clock_t const&			getVectorTiming() const;
		std::clock_t const&			getDequeTiming() const;
		void						setVectorTiming();
		void						setDequeTiming();

		void						checkArgs(char** av);
		void 						doVector(size_t size);
		std::vector<Arg>::iterator	doBinarySearch(int n, size_t pair_size, std::vector<Arg>::iterator it, std::vector<Arg>& sorted);
		void						erasePendingArgs(int n, size_t pair_size, std::vector<Arg>& pending, std::vector<Arg>& sorted);
		std::vector<Arg>::iterator	searchPendingArg(int n, std::vector<Arg>& pending);
		void						printVector();
		double						calculTime(std::clock_t timer);
		int							doJacobsthal(int n1, int n);

	private:
		std::vector<int>			_vData;
		std::vector<int>::iterator	_vIt;
		std::clock_t				_vTiming;
				
		std::deque<int>				_dData;
		std::deque<int>::iterator	_dIt;
		std::clock_t				_dTiming;
};

template <typename T>
bool	isSorted(const T& data)
{
	return is_sorted(data.begin(), data.end());
}

template <typename T>
void	printMessage(PmergeMe& merge, char** av, int ac, const T& data, std::string container, std::clock_t timer)
{
	std::cout << PURPLE << "\nBefore: ";
	for (int i = 1; av[i]; i++)
		std::cout << BLUE << av[i] << " ";
	std::cout << PURPLE << "\nAfter: ";
	for (size_t i = 0; i < data.size(); i++)
		std::cout << BLUE << data[i] << " ";
	std::cout << PURPLE << "\nTime to process a range of " << BLUE << ac
			  << PURPLE << " elements with " << BLUE << container << PURPLE
			  << ": " << GREEN << merge.calculTime(timer) << std::endl;
}

#endif
