/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:49:17 by esellier          #+#    #+#             */
/*   Updated: 2025/09/18 19:22:10 by esellier         ###   ########.fr       */
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

//gerer les doublons de la maniere qui prend moin de temps au systeme possible (les gardes je crois)

// _vTiming = std::clock();
// _dTiming = std::clock();
//lancer les compteurs de temps dans chaque exe separe (vector/deque)

//commencer la recursivite ou on divise les paires et on les echanges 

//creer deux nouveaux vector et deque main et le reste ou on garde les grands nombres et les petits a trier 
//faire la fonction jacobsthal et l'appliquer a l'ordre de rangement

//fonction pour checker si c'est trie
//fonction qui renvoie si c'est trie, les trucs a imprimer, les compteurs de temps etc

void	PmergeMe::printVector()
{
	for (_vIt = _vData.begin(); _vIt != _vData.end(); _vIt++)
		std::cout << BLUE << *_vIt << std::endl;
}
