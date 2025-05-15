/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:19:08 by everonel          #+#    #+#             */
/*   Updated: 2024/03/05 15:18:33 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	for (size_t i = 0; av[1][i]; i++)
	{
		if (!isdigit(av[1][i]))
		{
			std::cerr << "Invalid port. Port must be a numeric value" << std::endl;
			return (1);
		}
	}
	if (std::atoi(av[1]) < 1024 || std::atoi(av[1]) > 49151)
	{
		std::cerr << "Invalid port. Port must be between 1024 and 49151" << std::endl;
		return (1);
	}
	Server irc(std::atoi(av[1]), av[2]);
	try 
	{
		irc.start();
	}
	catch (std::exception &e)
	{
		irc.stop(e.what());
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
  