/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:25:59 by esellier          #+#    #+#             */
/*   Updated: 2025/09/01 20:25:35 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include "Common.hpp"

class BitcoinExchange
{
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange  operator=(const BitcoinExchange& other);

        void        saveData(std::ifstream& file);

    private:
        std::map<std::string, int>              _data;
        std::map<std::string, int>::iterator    _it;
};

#endif
