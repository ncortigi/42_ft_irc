/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:39:47 by everonel          #+#    #+#             */
/*   Updated: 2024/04/12 13:38:54 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"

std::string	buildInfoMsg(int info_code, std::string arg1);
std::string	buildInfoMsg2(int info_code, std::string arg1, std::string arg2);
std::string	buildInfoMsg3(int info_code, std::string arg1, std::string arg2, std::string arg3);
std::string	buildErrorMsg(int error_code, std::string arg1);
std::string	buildErrorMsg2(int error_code, std::string arg1, std::string arg2);
std::string	buildErrorMsg3(int error_code, std::string arg1, std::string arg2, std::string arg3);

std::string	toLowerButBetter(std::string str);
int			split(std::string str, const std::string delimiter, std::vector<std::string> &splitted);
int			modesplit(std::string str, std::vector<std::string> &splitted);