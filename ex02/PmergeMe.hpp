/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:25:59 by esellier          #+#    #+#             */
/*   Updated: 2025/09/24 19:42:29 by esellier         ###   ########.fr       */
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
		double						calculTime(std::clock_t timer);
		int							doJacobsthal(int n1, int n);
		
		void 						doVector(size_t size);
		void						fillDataVector(std::vector<Arg> &sorted, std::vector<int>& remain);
		std::vector<Arg>::iterator	doBinarySearchVector(int n, size_t pair_size, std::vector<Arg>::iterator it, std::vector<Arg>& sorted);
		void						movePendingArgsVector(int n, size_t pair_size, std::vector<Arg>& pending, std::vector<Arg>& sorted);

		void 						doDeque(size_t size);
		void						fillDataDeque(std::deque<Arg> &sorted, std::deque<int>& remain);
		std::deque<Arg>::iterator	doBinarySearchDeque(int n, size_t pair_size, std::deque<Arg>::iterator it, std::deque<Arg>& sorted);
		void						movePendingArgsDeque(int n, size_t pair_size, std::deque<Arg>& pending, std::deque<Arg>& sorted);
	
	private:
		std::vector<int>			_vData;
		std::clock_t				_vTiming;
				
		std::deque<int>				_dData;
		std::clock_t				_dTiming;
};

template <typename T>
void	isSorted(T& container, std::string name)
{
	for (typename T::const_iterator it = container.begin(); it != container.end(); it++)
	{
		if (it + 1 != container.end() && (*it > *(it + 1)))
		{
			std::cout << BLUE << ERROR << " Is NOT sorted!\n\n";
			return;
		}
	}
	std::cout << BLUE << name << " is sorted!\n\n";
}

template <typename T>
void	printMessage(PmergeMe& merge, int ac, const T& data, std::string container, std::clock_t timer)
{
	std::cout << PURPLE << "Time to process a range of " << BLUE << ac
			  << PURPLE << " elements with " << BLUE << container << PURPLE
			  << ": " << GREEN << merge.calculTime(timer) << " ms\n" << PURPLE 
			  << "Memory used: " << GREEN << sizeof(data) << " octets" << std::endl;
	isSorted(data, container);
}

template<typename T>
void	printNumber(char **av, T& container)
{
	std::cout << PURPLE << "\nBefore: ";
	for (int i = 1; av[i]; i++)
		std::cout << BLUE << av[i] << " ";
	std::cout << PURPLE << "\n\nAfter: ";
	for (size_t i = 0; i < container.size(); i++)
		std::cout << BLUE << container[i] << " ";
	std::cout << std::endl << std::endl;
}

template <typename T>
typename T::iterator	searchPendingArg(int n, T& pending)
{
	typename T::iterator	it;
	std::ostringstream		tmp;

	tmp << "s" << n;
	for (it = pending.begin(); it != pending.end(); it++)
	{
		if (it->tag == tmp.str())
		{
			while (it != pending.end() && it->tag == tmp.str())
				it++;
			return --it;
		}
	}
	return --it;
}

#endif
