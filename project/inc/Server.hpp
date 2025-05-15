/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:25:29 by everonel          #+#    #+#             */
/*   Updated: 2024/04/12 12:55:10 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <list>
# include <algorithm>
# include <sstream>
# include <fstream>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <cmath>
# include <ctime>

# include "Utils.hpp"
# include "User.hpp"
# include "Channel.hpp"
# include "Command.hpp"

class User;
class Channel;
class Command;

class Server
{
	public:
		Server();
		Server(int port, std::string password);
		~Server();
		int			getPort();
		std::string getPassword();
		std::vector<User> getUsers();
		std::vector<User> getPending();
		std::vector<Channel> getChannels();
		User *getUser(std::string nickname);
		Channel *getChannel(std::string name);
		std::string getName();
		void setPort(int port);
		void setPassword(std::string password);
		void setUsers(std::vector<User> users);
		void setPartialCommand(int sock, std::string command);
		void addUser(User &user);
		void removeUser(User &user);
		void addPending(User &user);
		void removePending(User &user);
		bool isNickAlreadyUsed(std::string nickname);
		void addChannel(Channel &channel);
		void removeChannel(Channel &channel);
		bool isChannelRegistered(std::string channel);
		void handleCommand(std::string command, std::vector<std::string> message, User &user);
		bool isCommandSupported(const std::string& command);
		bool isCommandRegistered(const std::string& command);
		void handleMessage(std::string input, User &user);
		void sendToAll(std::string message, User &user);
		void sendWelcomeMessage(User &user);
		bool CheckNickCollision(User &user);
		void start();
		void stop(std::string message);

	private:
		std::vector<User> _users;
		std::vector<User> _pending;
		std::vector<Channel> _channels;
		std::map<int, std::string> _partialCommands;
		User _bot;
		std::string _password;
		std::string _name;
		int _port;
		int _sock;
		int	_addr_len;
		struct sockaddr_in	_addr;
};

#endif