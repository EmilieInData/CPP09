/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Common.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:57:26 by esellier          #+#    #+#             */
/*   Updated: 2025/09/22 16:18:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_HPP
# define COMMON_HPP

#define ERROR	"📍"
#define RESET   "\033[0m"
#define BLUE	"\033[38;5;147m"
#define PINK    "\033[38;5;207m"
#define GREEN  	"\033[38;5;194m"
#define PURPLE  "\033[38;5;62m"

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <exception>
#include <cstdlib>
#include <sstream>
#include <ctime>

struct Arg {
	int 		num;
	std::string	tag;

    Arg(int n, const std::string& t) : num(n), tag(t) {} //definir dans une classe a part ?
};

#endif
