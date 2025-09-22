/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:49:17 by esellier          #+#    #+#             */
/*   Updated: 2025/09/23 01:17:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "Common.hpp"

PmergeMe::PmergeMe()
{
	std::cout << BLUE << "Default constructor called\n" << RESET;
}

PmergeMe::~PmergeMe()
{
	std::cout << BLUE << "Default destructor called\n" << RESET;
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
	std::cout << BLUE << "Copy constructor called\n" << RESET;
}

PmergeMe  PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->_vData = other._vData;
		this->_vIt = other._vIt;
		this->_vTiming = other._vTiming;

		this->_dData = other._dData;
		this->_dIt = other._dIt;
		this->_dTiming = other._dTiming;
	}
	else
		std::cout << ERROR << PINK << " Error: you're trying to assign a class to itself\n" << RESET;
	return (*this);
}

std::vector<int> const&	PmergeMe::getVector() const
{
	return _vData;
}

std::deque<int> const&	PmergeMe::getDeque() const
{
	return _dData;
}

std::clock_t const&	PmergeMe::getVectorTiming() const
{
	return _vTiming;
}

std::clock_t const&	PmergeMe::getDequeTiming() const
{
	return _dTiming;
}

void	PmergeMe::setVectorTiming()
{
	_vTiming = std::clock();
}

void	PmergeMe::setDequeTiming()
{
	_dTiming = std::clock();
}

void	PmergeMe::checkArgs(char** av)
{
	int		num;
	char	c;
	
	for (int i = 1; av[i]; i++)
	{
		std::istringstream ss(av[i]);
		if (!(ss >> num) || ss >> c || num < 1)
			throw std::runtime_error("Error: only positive integers allowed");
		_vData.push_back(num);
		_dData.push_back(num);
	}
	// printVector();
}

void PmergeMe::doVector(size_t pair_size)
{
	bool isOdd = false;
	if (_vData.size() % 2 != 0)
		isOdd = true;
	if(pair_size + isOdd > _vData.size())
		return;
	for (size_t i = pair_size - 1; i < _vData.size(); i += pair_size)
	{
		std::cout << PINK << "COMPARE " << _vData[i] << " to " << _vData[i - (pair_size/2)] << std::endl;
		if (_vData[i] < _vData[i - (pair_size/2)])
		{
			for (size_t j = 0; j < pair_size/2; j++)
				// std::cout << PINK << "SWAP " << _vData[i - j] << " to " << _vData[i - (size/2) - j] << std::endl;
				std::swap(_vData[i - j], _vData[i - pair_size/2 - j]);
		}
	}
	std::cout << PURPLE << "Middle: ";
	for (size_t i = 0; i < _vData.size(); i++)
		std::cout << BLUE << _vData[i] << " ";
	std::cout << std::endl;
	doVector(pair_size * 2);
	
	std::vector<Arg>	sorted;
	std::vector<Arg>	pending;
	std::vector<int>	remain;

	//fill with the two first pairs
	for(size_t i = 0; i < pair_size/2 ; i++)
	{
		std::ostringstream	tmp;
		tmp << "s1";
		sorted.push_back(Arg(_vData[i], tmp.str()));
	}
	for(size_t i = pair_size/2; i < pair_size ; i++)
	{
		std::ostringstream	tmp;
		tmp << "b1";
		sorted.push_back(Arg(_vData[i], tmp.str()));
	}
		
	//fill sorted and pending with the rest
	size_t maxSize = _vData.size() - (_vData.size() % pair_size);
	int j = 1;
	for (size_t i = pair_size; i < _vData.size(); i++)
	{
		if (i % pair_size == 0)
			j++;
		std::ostringstream	tmpSmall;
		std::ostringstream	tmpBig;
		tmpSmall << "s" << j;
		tmpBig << "b" << j;
		
		if (i >= maxSize)
			remain.push_back(_vData[i]);
		else if (i % pair_size < pair_size/2)
			pending.push_back(Arg(_vData[i], tmpSmall.str()));
		else
			sorted.push_back(Arg(_vData[i], tmpBig.str()));
	}
	
	if (!sorted.empty())
	{
		std::cout << GREEN << "SORTED: ";
		for (size_t i = 0; i < sorted.size(); i++)
			std::cout << sorted[i].num << "-" << sorted[i].tag << "   ";
		std::cout << std::endl;
	}
	if (!pending.empty())
	{
		std::cout << BLUE << "PENDING: ";
		for (size_t i = 0; i < pending.size(); i++)
			std::cout << pending[i].num << "-" << pending[i].tag << "   ";
		std::cout << std::endl;
	}
	if (!remain.empty())
	{
		std::cout << BLUE << "REMAIN: ";
		for (size_t i = 0; i < remain.size(); i++)
			std::cout << remain[i] << "   ";
		std::cout << std::endl;
	}
	
	int n1 = 1;
	int n = 1;
	while (!pending.empty())
	{
		int tmp = n;
		n = doJacobsthal(n1, n);
		n1 = tmp;
		erasePendingArgs(n, pair_size, pending, sorted);
		break;
	}
}

std::vector<Arg>::iterator	PmergeMe::doBinarySearch(int n, size_t pair_size, std::vector<Arg>::iterator it, std::vector<Arg>& sorted)
{
	std::vector<Arg>::iterator	begin = sorted.begin();
	std::vector<Arg>::iterator	end = sorted.begin();
	std::ostringstream			tmp;

	pair_size = pair_size / 2; // a mettre qund je pass l'arg ds l'appel de la fonction
	tmp << "b" << n;
	while (end != sorted.end())
	{
		if (end->tag == tmp.str()) //checker ici qu'il trouve bien TO DOOOO
		// {
			// while (end != sorted.end() && end->tag == tmp.str())
			// 	end++;
			// if (end != sorted.begin())
			// 	--end;
			break;
		// }
		end++;
	}
	// if (end == sorted.end())
	if (end != sorted.begin())
		--end;
	while(1)
	{
		size_t	d = end - begin;
		size_t	pair_nb = d / pair_size;
		size_t half_pair = pair_nb/2;
		std::cout << "Pair_size: " << pair_size << ", Dist: " << d << ", Nb de pairs: " << pair_nb << std::endl
		<< "Begin: " << begin->num << ", End: " << end->num << std::endl;
		
		std::vector<Arg>::iterator	middle = begin + ((half_pair * pair_size) - 1);
		std::cout << "MIDDLE: " << middle->num << std::endl;
		// if (it->num >= end->num) // not ok car peut etre sorted.end() et donc sans value
		if (it->num > middle->num)
		{
			if (it->num < (middle + pair_size)->num)
				return middle;
			begin = middle + 1;
		}
		else if (it->num == middle->num)
			return middle;
		else if (it->num < middle->num)
			end = middle;
		if (middle == begin || middle == end || middle < begin || middle > end)
			return middle;
	}
}

// std::vector<Arg>::iterator upper_bound_block(std::vector<Arg>::iterator first,
//                   std::vector<Arg>::iterator last, int value, size_t pair_size)
// {
//     while (blocks > 0)
//     {
//         // size_t half = blocks / 2;
//         // std::vector<Arg>::iterator mid = first + half * pair_size;

//         // dernier élément du bloc courant (ou le seul s’il est incomplet)
//         std::vector<Arg>::iterator midLast = mid + (pair_size - 1);
//         if (midLast >= last)
//             midLast = last - 1;

//         if (midLast->num <= value)
//         {
//             // aller après ce bloc
//             first = mid + pair_size;
//             blocks -= half + 1;
//         }
//         else
//         {
//             // rester avant
//             blocks = half;
//         }
//     }
//     return first;
// }

void	PmergeMe::erasePendingArgs(int n, size_t pair_size, std::vector<Arg>& pending, std::vector<Arg>& sorted)
{
	(void)pair_size;
	(void)sorted;
	if (pending.empty()) // add sorted? // TO BORROW
		return;
	std::vector<Arg>::iterator it = searchPendingArg(n, pending);
	std::cout << "num: " << it->num << ", tag: " << it->tag << std::endl;
	std::vector<Arg>::iterator it_add = doBinarySearch(n, pair_size, it, sorted);
	std::cout << "Here we add: " << it_add->num << std::endl;
	//ajouter les/le numero dans sorted et supprimer de pending
	// descendre jusqu'qu debut de la liste avant de passer au jacosthal suivant
	
}

std::vector<Arg>::iterator	PmergeMe::searchPendingArg(int n, std::vector<Arg>& pending)
{
	std::vector<Arg>::iterator	it;
	std::ostringstream			tmp;

	tmp << "s" << n;
	// std::cout << "N: " << n << "\nTMP: " << tmp.str() << std::endl; // TO BORROW
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


void	PmergeMe::printVector()
{
	for (_vIt = _vData.begin(); _vIt != _vData.end(); _vIt++)
		std::cout << BLUE << *_vIt << std::endl;
}

double	PmergeMe::calculTime(std::clock_t timer)
{
	std::clock_t	end = timer - clock();
	return (static_cast<double>(end) * 1000.0 / CLOCKS_PER_SEC);
}

int	PmergeMe::doJacobsthal(int n1, int n)
{
	n = n + (2 * n1);
	return n; 
}
//jacobsthal n = (n - 1) + 2 * (n - 2)
// 1 - 3 - 5 - 11 - 21 - 43 - 85 - 171..
// Jacobsthal numbers used: 3, 5, 11
// The order of insertion will be: b3, b2, b5, b4, b11, b10, b9, b8, b7, b6
// we insert the remainig elements in reverse order if the last remaining is smaller
//  than the next jacobstahl number
// for 7:  b3, b2, b5, b4, b7, b6 (3, 5, et pas de 11)

// 17 12 42 21 24 8 11 4 (9) (8 2)