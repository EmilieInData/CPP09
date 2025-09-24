/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:49:17 by esellier          #+#    #+#             */
/*   Updated: 2025/09/24 19:48:33 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "Common.hpp"

PmergeMe::PmergeMe()
{
	std::cout << PURPLE << "Default constructor called\n" << RESET;
}

PmergeMe::~PmergeMe()
{
	std::cout << PURPLE << "Default destructor called\n" << RESET;
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
	std::cout << PURPLE << "Copy constructor called\n" << RESET;
}

PmergeMe  PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->_vData = other._vData;
		this->_vTiming = other._vTiming;
		this->_dData = other._dData;
		this->_dTiming = other._dTiming;
	}
	else
		std::cerr << ERROR << PINK << " Error: you're trying to assign a class to itself\n" << RESET;
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
}

double	PmergeMe::calculTime(std::clock_t timer)
{
	std::clock_t	end = clock() - timer;
	return (static_cast<double>(end) * 1000.0 / CLOCKS_PER_SEC);
}

int	PmergeMe::doJacobsthal(int n1, int n)
{
	n = n + (2 * n1);
	return n; 
}


// --> VECTOR FUNCTIONS

void PmergeMe::doVector(size_t pair_size)
{
	bool isOdd = false;
	if (_vData.size() % 2 != 0)
		isOdd = true;
	if(pair_size + isOdd > _vData.size())
		return;
	for (size_t i = pair_size - 1; i < _vData.size(); i += pair_size)
	{
		if (_vData[i] < _vData[i - (pair_size/2)])
		{
			for (size_t j = 0; j < pair_size/2; j++)
				std::swap(_vData[i - j], _vData[i - pair_size/2 - j]);
		}
	}
	doVector(pair_size * 2);
	
	std::vector<Arg>	sorted;
	std::vector<Arg>	pending;
	std::vector<int>	remain;
	// --> fill with the two first pairs
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
	// --> fill sorted and pending with the rest
	size_t maxSize = _vData.size() - (_vData.size() % (pair_size / 2));
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
	// --> debug 01
	int n1 = 1;
	int n = 1;
	while (!pending.empty())
	{
		int tmp = n;
		n = doJacobsthal(n1, n);
		n1 = tmp;
		movePendingArgsVector(n, pair_size / 2, pending, sorted);
	}
	fillDataVector(sorted, remain);
	return;
}

void	PmergeMe::fillDataVector(std::vector<Arg> &sorted, std::vector<int>& remain)
{
	_vData.clear();
	for (std::vector<Arg>::iterator it = sorted.begin(); it != sorted.end(); it++)
		_vData.push_back(it->num);
	for (std::vector<int>::iterator it = remain.begin(); it != remain.end(); it++)
		_vData.push_back(*it);
}

std::vector<Arg>::iterator	PmergeMe::doBinarySearchVector(int n, size_t pair_size, std::vector<Arg>::iterator it, std::vector<Arg>& sorted)
{
	std::vector<Arg>::iterator	begin = sorted.begin() + pair_size - 1;
	std::vector<Arg>::iterator	end = sorted.begin();
	std::ostringstream			tmp;

	tmp << "b" << n;
	while (end != sorted.end())
	{
		if (end->tag == tmp.str())
			break;
		end++;
	}
	if (end != sorted.begin())
		--end;
	while(1)
	{
		size_t	d = end - begin;
		// --> debug 02
		std::vector<Arg>::iterator	middle = begin + d/2;
		while (middle != sorted.begin())
		{
			if (middle + 1 != sorted.end() && middle->tag != (middle + 1)->tag)
				break;
			middle -= 1;
			if (middle->tag != (middle + 1)->tag)
				break;
		}	
		if (begin == end)
			middle = begin;
		// --> debug 03
		if (middle < begin || middle > end || middle == end)//to check if ok
			return middle + 1;
		else if (it->num > middle->num)
		{
			if (((size_t)std::distance(middle, sorted.end()) > pair_size) && ((middle + pair_size) != sorted.end()))
			{
				if (it->num <= (middle + pair_size)->num)
					return middle +1;
				if (it->num > (middle + pair_size)->num && (middle + pair_size) == end)
					return end + 1;
			}
			begin = middle;
		}
		else if (it->num == middle->num)
			return middle + 1;
		else if (it->num < middle->num)
		{
			if (middle == begin || (((size_t)std::distance(sorted.begin(), middle) >= pair_size)
				&& it->num > (middle - pair_size)->num))
				return middle - pair_size + 1;
			end = middle;
		}
	}
}

void	PmergeMe::movePendingArgsVector(int n, size_t pair_size, std::vector<Arg>& pending, std::vector<Arg>& sorted)
{
	while(n > 1)
	{
		if (pending.empty())
			return;
		std::vector<Arg>::iterator it = searchPendingArg(n, pending);
		std::istringstream iss(it->tag.substr(1));
		iss >> n;
		// --> debug 04	
		std::vector<Arg>::iterator it_add = doBinarySearchVector(n, pair_size, it, sorted);
		// --> debug 05
		std::vector<Arg>::iterator	first = it - pair_size + 1;
		std::vector<Arg>::iterator 	end = it + 1; //element after the last to copy
		sorted.insert(it_add, first, end);
		pending.erase(first,end);
		n -= 1;
		// --> debug 06
	}
}


// --> DEQUE FONCTIONS

void PmergeMe::doDeque(size_t pair_size)
{
	bool isOdd = false;
	if (_dData.size() % 2 != 0)
		isOdd = true;
	if(pair_size + isOdd > _dData.size())
		return;
	for (size_t i = pair_size - 1; i < _dData.size(); i += pair_size)
	{
		if (_dData[i] < _dData[i - (pair_size/2)])
		{
			for (size_t j = 0; j < pair_size/2; j++)
				std::swap(_dData[i - j], _dData[i - pair_size/2 - j]);
		}
	}
	doDeque(pair_size * 2);
	
	std::deque<Arg>	sorted;
	std::deque<Arg>	pending;
	std::deque<int>	remain;
	// --> fill with the two first pairs
	for(size_t i = 0; i < pair_size/2 ; i++)
	{
		std::ostringstream	tmp;
		tmp << "s1";
		sorted.push_back(Arg(_dData[i], tmp.str()));
	}
	for(size_t i = pair_size/2; i < pair_size ; i++)
	{
		std::ostringstream	tmp;
		tmp << "b1";
		sorted.push_back(Arg(_dData[i], tmp.str()));
	}
	// --> fill sorted and pending with the rest
	size_t maxSize = _dData.size() - (_dData.size() % (pair_size / 2));
	int j = 1;
	for (size_t i = pair_size; i < _dData.size(); i++)
	{
		if (i % pair_size == 0)
			j++;
		std::ostringstream	tmpSmall;
		std::ostringstream	tmpBig;
		tmpSmall << "s" << j;
		tmpBig << "b" << j;
		
		if (i >= maxSize)
			remain.push_back(_dData[i]);
		else if (i % pair_size < pair_size/2)
			pending.push_back(Arg(_dData[i], tmpSmall.str()));
		else
			sorted.push_back(Arg(_dData[i], tmpBig.str()));
	}
	// --> debug 01
	int n1 = 1;
	int n = 1;
	while (!pending.empty())
	{
		int tmp = n;
		n = doJacobsthal(n1, n);
		n1 = tmp;
		movePendingArgsDeque(n, pair_size / 2, pending, sorted);
	}
	fillDataDeque(sorted, remain);
	return;
}

void	PmergeMe::fillDataDeque(std::deque<Arg> &sorted, std::deque<int>& remain)
{
	_dData.clear();
	for (std::deque<Arg>::iterator it = sorted.begin(); it != sorted.end(); it++)
		_dData.push_back(it->num);
	for (std::deque<int>::iterator it = remain.begin(); it != remain.end(); it++)
		_dData.push_back(*it);
}

std::deque<Arg>::iterator	PmergeMe::doBinarySearchDeque(int n, size_t pair_size, std::deque<Arg>::iterator it, std::deque<Arg>& sorted)
{
	std::deque<Arg>::iterator	begin = sorted.begin() + pair_size - 1;
	std::deque<Arg>::iterator	end = sorted.begin();
	std::ostringstream			tmp;

	tmp << "b" << n;
	while (end != sorted.end())
	{
		if (end->tag == tmp.str())
			break;
		end++;
	}
	if (end != sorted.begin())
		--end;
	while(1)
	{
		size_t	d = end - begin;
		// --> debug 02
		std::deque<Arg>::iterator	middle = begin + d/2;
		while (middle != sorted.begin())
		{
			if (middle + 1 != sorted.end() && middle->tag != (middle + 1)->tag)
				break;
			middle -= 1;
			if (middle->tag != (middle + 1)->tag)
				break;
		}	
		if (begin == end)
			middle = begin;
		// --> debug 03
		if (middle < begin || middle > end || middle == end)//to check if ok
			return middle + 1;
		else if (it->num > middle->num)
		{
			if (((size_t)std::distance(middle, sorted.end()) > pair_size) && ((middle + pair_size) != sorted.end()))
			{
				if (it->num <= (middle + pair_size)->num)
					return middle +1;
				if (it->num > (middle + pair_size)->num && (middle + pair_size) == end)
					return end + 1;
			}
			begin = middle;
		}
		else if (it->num == middle->num)
			return middle + 1;
		else if (it->num < middle->num)
		{
			if (middle == begin || (((size_t)std::distance(sorted.begin(), middle) >= pair_size)
				&& it->num > (middle - pair_size)->num))
				return middle - pair_size + 1;
			end = middle;
		}
	}
}

void	PmergeMe::movePendingArgsDeque(int n, size_t pair_size, std::deque<Arg>& pending, std::deque<Arg>& sorted)
{
	while(n > 1)
	{
		if (pending.empty())
			return;
		std::deque<Arg>::iterator it = searchPendingArg(n, pending);
		std::istringstream iss(it->tag.substr(1));
		iss >> n;
		// --> debug 04	
		std::deque<Arg>::iterator it_add = doBinarySearchDeque(n, pair_size, it, sorted);
		// --> debug 05
		std::deque<Arg>::iterator	first = it - pair_size + 1;
		std::deque<Arg>::iterator 	end = it + 1; //element after the last to copy
		sorted.insert(it_add, first, end);
		pending.erase(first,end);
		n -= 1;
		// --> debug 06
	}
}


// --> debug 01

		// if (!sorted.empty())
		// {
		// 	std::cout << PINK << "SORTED: ";
		// 	for (size_t i = 0; i < sorted.size(); i++)
		// 		std::cout << sorted[i].num << "-" << sorted[i].tag << "   ";
		// 	std::cout << std::endl;
		// }
		// if (!pending.empty())
		// {
		// 	std::cout << PINK  << "PENDING: ";
		// 	for (size_t i = 0; i < pending.size(); i++)
		// 		std::cout << pending[i].num << "-" << pending[i].tag << "   ";
		// 	std::cout << std::endl;
		// }
		// if (!remain.empty())
		// {
		// 	std::cout << PINK  << "REMAIN: ";
		// 	for (size_t i = 0; i < remain.size(); i++)
		// 		std::cout << remain[i] << "   ";
		// 	std::cout << std::endl;
		// }


// --> debug 02

		// size_t	pair_nb = d / pair_size + 1;
		// size_t half_pair = pair_nb/2;
		// std::cout << "Pair_size: " << pair_size << ", Dist: " << d << ", Nb de pairs: " << pair_nb << std::endl
		// << "Begin: " << begin->num  << "-" << begin->tag << ", End: " << end->num  << "-" << end->tag << std::endl;


// -->debug 03
		// std::cout << "MIDDLE: " << middle->num << "-" << middle->tag << std::endl;


// --> debug 04

		// if (!sorted.empty())
		// {
		// 	std::cout << GREEN << "SORTED BEFORE: ";
		// 	for (size_t i = 0; i < sorted.size(); i++)
		// 		std::cout << sorted[i].num << "-" << sorted[i].tag << "   ";
		// 	std::cout << std::endl;
		// }
		// if (!pending.empty())
		// {
		// 	std::cout << GREEN  << "PENDING BEFORE: ";
		// 	for (size_t i = 0; i < pending.size(); i++)
		// 		std::cout << pending[i].num << "-" << pending[i].tag << "   ";
		// 	std::cout << std::endl;
		// }
		// std::cout << BLUE << "num: " << it->num << ", tag: " << it->tag << std::endl;


//  --> debug 05

		// if (it_add != sorted.end())
		// 	std::cout << "Position where we had the number before: " << it_add->num << std::endl;


// --> debug 06

		// if (!sorted.empty())
		// {
		// 	std::cout << GREEN << "SORTED AFTER: ";
		// 	for (size_t i = 0; i < sorted.size(); i++)
		// 		std::cout << sorted[i].num << "   ";
		// 	std::cout << RESET << std::endl;
		// }
		// if (!pending.empty())
		// {
		// 	std::cout << GREEN << "PENDING AFTER: ";
		// 	for (size_t i = 0; i < pending.size(); i++)
		// 		std::cout << pending[i].num << "   ";
		// 	std::cout << RESET << std::endl;
		// }
