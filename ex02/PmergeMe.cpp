/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:49:17 by esellier          #+#    #+#             */
/*   Updated: 2025/09/23 18:43:11 by esellier         ###   ########.fr       */
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
		// std::cout << PINK << "COMPARE " << _vData[i] << " to " << _vData[i - (pair_size/2)] << std::endl; // TO BORROW
		if (_vData[i] < _vData[i - (pair_size/2)])
		{
			for (size_t j = 0; j < pair_size/2; j++)
				// std::cout << PINK << "SWAP " << _vData[i - j] << " to " << _vData[i - (size/2) - j] << std::endl;
				std::swap(_vData[i - j], _vData[i - pair_size/2 - j]);
		}
	}
	// std::cout << PURPLE << "Middle: ";
	// for (size_t i = 0; i < _vData.size(); i++)
	// 	std::cout << BLUE << _vData[i] << " ";
	// std::cout << std::endl;
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
	
	int n1 = 1;
	int n = 1;
	while (!pending.empty())
	{
		int tmp = n;
		n = doJacobsthal(n1, n);
		n1 = tmp;
		movePendingArgs(n, pair_size / 2, pending, sorted);
	}
	fillData(sorted, remain);
	return;
}

void	PmergeMe::fillData(std::vector<Arg> &sorted, std::vector<int>& remain)
{
	_vData.clear();
	for (std::vector<Arg>::iterator it = sorted.begin(); it != sorted.end(); it++)
		_vData.push_back(it->num);
	for (std::vector<int>::iterator it = remain.begin(); it != remain.end(); it++)
		_vData.push_back(*it);
}

std::vector<Arg>::iterator	PmergeMe::doBinarySearch(int n, size_t pair_size, std::vector<Arg>::iterator it, std::vector<Arg>& sorted)
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
	// std::cout << PURPLE << "END= " << end->num << ", " << end->tag << std::endl;
	while(1)
	{
		size_t	d = end - begin;
		// size_t	pair_nb = d / pair_size + 1;
		// size_t half_pair = pair_nb/2;
		// std::cout << "Pair_size: " << pair_size << ", Dist: " << d << ", Nb de pairs: " << pair_nb << std::endl // TO BORROW
		// << "Begin: " << begin->num << ", End: " << end->num << std::endl; // TO BORROW
		std::vector<Arg>::iterator	middle = begin + d/2;
		// while (middle + 1 != sorted.end() && (middle + 1)->tag == middle->tag)
		// 	middle += 1;
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
		// std::cout << "MIDDLE: " << middle->num << std::endl;
		// if (it->num >= end->num) // not ok car peut etre sorted.end() et donc sans value
		if (middle < begin || middle > end || middle == end)//to check if ok
			return middle + 1;
		else if (it->num > middle->num)
		{
			if (((size_t)std::distance(middle, sorted.end()) > pair_size) && ((middle + pair_size) != sorted.end()))
			{
				if (it->num < (middle + pair_size)->num)
					return middle +1;
				if (it->num > (middle + pair_size)->num && (middle + pair_size) == end)
					return end + 1;
			}
			begin = middle;
		}
		else if (it->num == middle->num) // TO CHECK IF OK
			return middle;
		else if (it->num < middle->num)
		{
			// if (middle == begin || (middle != sorted.begin() && it->num > (middle - pair_size)->num))
			if (middle == begin || (((size_t)std::distance(sorted.begin(), middle) >= pair_size)
				&& it->num > (middle - pair_size)->num))
				return middle - pair_size + 1;
			end = middle;
		}
	}
}



void	PmergeMe::movePendingArgs(int n, size_t pair_size, std::vector<Arg>& pending, std::vector<Arg>& sorted)
{
	while(n > 1)
	{
		if (pending.empty()) // add sorted? // TO BORROW
			return;
		std::vector<Arg>::iterator it = searchPendingArg(n, pending);
		std::istringstream iss(it->tag.substr(1));
		iss >> n;
		// int value = 0;
		// if (!(iss >> value))
		//     return -1; //proteger la convertion mm si normalement ok
		
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
		std::vector<Arg>::iterator it_add = doBinarySearch(n, pair_size, it, sorted);
		// if (it_add != sorted.end())
		// 	it_add += 1;
		// if (it_add != sorted.end())
		// 	std::cout << "Position where we had the number before: " << it_add->num << std::endl;
	
		std::vector<Arg>::iterator	first = it - pair_size + 1;
		std::vector<Arg>::iterator 	end = it + 1; //element after the last to copy
		sorted.insert(it_add, first, end);
		pending.erase(first,end);
		n -= 1;
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
	}
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

void	PmergeMe::isSorted()
{
	for (std::vector<int>::iterator it = _vData.begin(); it != _vData.end(); it++)
	{
		if (it + 1 != _vData.end() && (*it > *(it + 1)))
		{
			std::cout << PINK << ERROR << " Is NOT sorted!\n";
			return;
		}
	}
	std::cout << PINK << " Is sorted!\n";
}
//jacobsthal n = (n - 1) + 2 * (n - 2)
// 1 - 3 - 5 - 11 - 21 - 43 - 85 - 171..
// Jacobsthal numbers used: 3, 5, 11
// The order of insertion will be: b3, b2, b5, b4, b11, b10, b9, b8, b7, b6
// we insert the remainig elements in reverse order if the last remaining is smaller
//  than the next jacobsthal number
// for 7:  b3, b2, b5, b4, b7, b6 (3, 5, et pas de 11)

// 17 12 42 21 24 8 11 4 (9) (8 2)
