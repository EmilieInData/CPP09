/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:25:59 by esellier          #+#    #+#             */
/*   Updated: 2025/09/16 01:23:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include "Common.hpp"

class RPN
{
	public:
		RPN();
		~RPN();
		RPN(const RPN& other);
		RPN	operator=(const RPN& other);

		int		doCalcul(char sign);
		void	fillStack(std::string const& str);
		int		checkInt(char c);
		char	checkOperator(char c);

	private:
		std::stack<int, std::vector<int> >	_data;
};

#endif
