/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:49:17 by esellier          #+#    #+#             */
/*   Updated: 2025/09/19 18:29:01 by esellier         ###   ########.fr       */
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
	
	std::vector<int>	sorted;
	std::vector<int>	pending;

	//fill with the two first pairs
	for(size_t i = 0; i < pair_size ; i++)
		sorted.push_back(_vData[i]);
		
	// for(size_t i = pair_size + pair_size/2; i < _vData.size(); i += pair_size/2) //checker si ok avec 11 num par exemple
	// {
	// 	for(size_t j = 0; j < pair_size/2; j++)
	// 	{
	// 		sorted.push_back(_vData[i]);
	// 		i++;
	// 	}
	// }
	
	//fill sorted and pending with the rest
	size_t maxSize = _vData.size() - (_vData.size() % pair_size);
	for (size_t i = pair_size; i < maxSize; i++)
	{
		if (i % pair_size < pair_size/2)
			pending.push_back(_vData[i]);
		else
			sorted.push_back(_vData[i]);	 
	}
	
	std::cout << GREEN << "SORTED: ";
	for (size_t i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;
	std::cout << BLUE << "PENDING: ";
	for (size_t i = 0; i < pending.size(); i++)
		std::cout << pending[i] << " ";
	std::cout << std::endl;

}
//faire la fonction jacobsthal et l'appliquer a l'ordre de rangement


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

//jacobsthal n = (n - 1) + 2 * (n - 2)
// 1 - 3 - 5 - 11 - 21 - 43 - 85 - 171..
