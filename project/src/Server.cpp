/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:26:11 by ncortigi          #+#    #+#             */
/*   Updated: 2024/04/12 13:59:06 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

Server::Server()
{
}

Server::Server(int port, std::string password)
{
	_port = port;
	_password = password;
	_name = ":IRCSERVER";
	_bot = User(0, "Solver");
}

Server::~Server()
{
}

int Server::getPort()
{
	return (_port);
}

std::string Server::getPassword()
{
	return (_password);
}

std::vector<User> Server::getUsers()
{
	return (_users);
}

std::vector<User> Server::getPending()
{
	return (_pending);
}

std::vector<Channel> Server::getChannels()
{
	return (_channels);
}

User *Server::getUser(std::string nickname)
{
	std::vector<User>::iterator it = _users.begin();
	while (it != _users.end())
	{
		if (toLowerButBetter(it->getNickname()) == toLowerButBetter(nickname))
			return &(*it);
		it++;
	}
	return (NULL);
}

Channel *Server::getChannel(std::string name)
{
	std::vector<Channel>::iterator it = _channels.begin();
	while (it != _channels.end())
	{
		if (toLowerButBetter(it->getName()) == toLowerButBetter(name))
			return &(*it);
		it++;
	}
	return (NULL);
}

std::string Server::getName()
{
	return (_name);
}

void Server::setPort(int port)
{
	_port = port;
}

void Server::setPassword(std::string password)
{
	_password = password;
}

void Server::setUsers(std::vector<User> users)
{
	_users = users;
}

void Server::setPartialCommand(int sock, std::string command)
{
	_partialCommands[sock] = command;
}

void Server::addUser(User &user)
{
	_users.push_back(user);
}


void Server::removeUser(User &user)
{
	std::vector<User>::iterator it = std::find(_users.begin(), _users.end(), user);
	if (it != _users.end())
		_users.erase(it);
}

void Server::addPending(User &user)
{
	_pending.push_back(user);
}

void Server::removePending(User &user)
{
	std::vector<User>::iterator it = std::find(_pending.begin(), _pending.end(), user);
	if (it != _pending.end())
		_pending.erase(it);
}

bool Server::isNickAlreadyUsed(std::string nickname)
{
	std::vector<User>::iterator it = _users.begin();
	while (it != _users.end())
	{
		if (toLowerButBetter(it->getNickname()) == toLowerButBetter(nickname))
			return (true);
		it++;
	}
	return (false);
}

void Server::addChannel(Channel &channel)
{
	_channels.push_back(channel);
}

void Server::removeChannel(Channel &channel)
{
	std::vector<Channel>::iterator it = std::find(_channels.begin(), _channels.end(), channel);
	if (it != _channels.end())
		_channels.erase(it);
}

bool Server::isChannelRegistered(std::string channel)
{
	if (channel[0] != '#' && channel[0] != '&')
		return (false);
	std::vector<Channel>::iterator it = _channels.begin();
	while (it != _channels.end())
	{
		if (toLowerButBetter(it->getName()) == toLowerButBetter(channel))
			return (true);
		it++;
	}
	return (false);
}

void Server::sendToAll(std::string message, User &user)
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (_users[i].getSocket() != user.getSocket())
			send(_users[i].getSocket(), message.c_str(), message.size(), 0);
	}
}

void Server::handleCommand(std::string command, std::vector<std::string> message, User &user)
{
	if (command == "USERHOST" || command == "WHO" || command == "CAP")
		return ;
	if (command == "PASS")
		Command::pass(message, user, _password);
	else if (command == "NICK")
		Command::nick(message, user, *this);
	else if (command == "USER")
		Command::user(message, user);
	else if (command == "PING")
		Command::ping(message, user);
	else if (command == "JOIN")
		Command::join(message, user, *this);
	else if (command == "INVITE")
		Command::invite(message, user, *this);
	else if (command == "PRIVMSG")
		Command::privmsg(message, user, *this);
	else if (command == "HELP")
		Command::help(user);
	else if (command == "QUIT")
		Command::quit(message, user, *this);
	else if (command == "PART")
		Command::part(message, user, *this);
	else if (command == "MODE")
		Command::mode(message, user, *this);
	else if (command == "TOPIC")
		Command::topic(message, user, *this);
	else if (command == "KICK")
		Command::kick(message, user, *this);
}

bool Server::isCommandSupported(const std::string& command)
{
	if (command == "USERHOST" || command == "WHO" || command == "CAP" || command == "PASS" || command == "NICK" || command == "USER" || command == "PING" || command == "JOIN" 
		|| command == "INVITE" || command == "PRIVMSG" || command == "HELP" || command == "QUIT" || command == "PART" 
			|| command == "MODE" || command == "TOPIC" || command == "KICK")
		return true;
	return false;
}

bool Server::isCommandRegistered(const std::string& command)
{
	if (command == "WHO" || command == "CAP" || command == "PASS" || command == "NICK" || command == "USER" || command == "PING" || command == "HELP")
		return true;
	return false;
}

void Server::handleMessage(std::string input, User &user)
{
	if (input.empty())
		return ;
	_partialCommands[user.getSocket()] += input;
	
	size_t newlinePos;
	if ((newlinePos = _partialCommands[user.getSocket()].find("\n")) != std::string::npos || 
		(newlinePos = _partialCommands[user.getSocket()].find("\r")) != std::string::npos)
	{
		std::cout << _partialCommands[user.getSocket()];
		std::string rawArgs = _partialCommands[user.getSocket()].substr(0, newlinePos);
		std::vector<std::string> args;
		split(rawArgs, " ", args);
		if (args.size() == 0)
		{
			_partialCommands[user.getSocket()] = "";
			return ;
		}
		std::string command = args[0];
		args.erase(args.begin());
		if (!isCommandSupported(command))
		{
			std::string response = buildErrorMsg2(421, user.getNickname(), command);
			send(user.getSocket(), response.c_str(), response.size(), 0);
			_partialCommands[user.getSocket()] = "";
			return ;
		}
		else if (!user.isUserRegistered() && !isCommandRegistered(command))
		{
			std::string response = buildErrorMsg(451, user.getNickname());
			send(user.getSocket(), response.c_str(), response.size(), 0);
			_partialCommands[user.getSocket()] = "";
			return ;
		}
		try 
		{
			handleCommand(command, args, user);
		}
		catch (std::runtime_error &e)
		{
			_partialCommands[user.getSocket()] = "";
			getpeername(user.getSocket(), (struct sockaddr*)&_addr, (socklen_t*)&_addr_len);
			std::cout << "Host disconnected, ip " << inet_ntoa(_addr.sin_addr) << ", port " << ntohs(_addr.sin_port) << std::endl;
			close(user.getSocket());
			user.setSocket(0);
			removePending(user);
		}
		catch (std::exception &e)
		{}
		_partialCommands[user.getSocket()] = "";
	}
}
	
static void	signalHandler(int signum)
{
	(void)signum;
	throw std::runtime_error("Server stopped");
}

void Server::sendWelcomeMessage(User &user)
{
	std::string nickSetMessage = _name + " 001 " + user.getNickname() + " :You are now registered to the Server\r\n";
	send(user.getSocket(), nickSetMessage.c_str(), nickSetMessage.length(), 0);
	std::string userSetMessage = _name + " 002 " + user.getNickname() + " :Your host is irc.example.com, running version ExampleIRCServer 1.0\r\n";
	send(user.getSocket(), userSetMessage.c_str(), userSetMessage.length(), 0);
	std::string rplCreatedMessage = _name + " 003 " + user.getNickname() + " :This server was created in 2024 by ncortigi, fracerba and everonel\r\n";
	send(user.getSocket(), rplCreatedMessage.c_str(), rplCreatedMessage.length(), 0);
	std::string rplMyInfo = _name + " 004 " + user.getNickname() + " IRCSERVER 1.0 * +ioltk\r\n";
	send(user.getSocket(), rplMyInfo.c_str(), rplMyInfo.length(), 0);
	std::string RPL_MOTD =  _name + " 372 " + user.getNickname() + " :- Welcome to the IRCSERVER -\r\n";
    send(user.getSocket(), RPL_MOTD.c_str(), RPL_MOTD.length(), 0);
    std::string RPL_ENDOFMOTD = _name + " 376 " + user.getNickname() + " :End of MOTD command\r\n";
    send(user.getSocket(), RPL_ENDOFMOTD.c_str(), RPL_ENDOFMOTD.length(), 0);
}

bool	Server::CheckNickCollision(User &user)
{
	if (isNickAlreadyUsed(user.getNickname()))
	{
		std::string response = _name + " 433 " + user.getNickname() + " :Nickname is already in use\r\n";
		send(user.getSocket(), response.c_str(), response.length(), 0);
		user.setRegisteredNick(false);
		return (false);
	}
	return (true);
}

void	Server::start()
{
	int					new_sock, sd;
	int					max_sock, activity, valread;
	int					opt = 1;
	fd_set				readfds;
	char				buffer[513];
	std::string			response;

	if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		throw std::runtime_error("Failed to create socket");
	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("Failed to set socket options");

	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(_port);

	if (bind(_sock, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
		throw std::runtime_error("Failed to bind socket");
	std::cout << "Server started on port: " << _port << std::endl;
	if (listen(_sock, 3) < 0)
		throw std::runtime_error("Failed to listen on socket");
	
	_addr_len = sizeof(_addr);
	std::cout << "Waiting for connections..." << std::endl;
	signal(SIGINT, signalHandler);
	while (1)
	{
		FD_ZERO(&readfds);
		FD_SET(_sock, &readfds);
		max_sock = _sock;
		for (size_t i = 0; i < _pending.size(); i++)
		{
			sd = _pending[i].getSocket();
			if (sd > 0)
				FD_SET(sd, &readfds);
			if (sd > max_sock)
				max_sock = sd;
		}
		for (size_t i = 0; i < _users.size(); i++)
		{
			sd = _users[i].getSocket();
			if (sd > 0)
				FD_SET(sd, &readfds);
			if (sd > max_sock)
				max_sock = sd;
		}
		activity = select(max_sock + 1, &readfds, NULL, NULL, NULL);
		if ((activity < 0) && (errno != EINTR))
			throw std::runtime_error("Select error");
		if (FD_ISSET(_sock, &readfds))
		{
			if ((new_sock = accept(_sock, (struct sockaddr *)&_addr, (socklen_t*)&_addr_len)) < 0)
				throw std::runtime_error("Failed to accept connection");
			std::cout << "New connection, socket fd is " << new_sock << ", ip is: " << inet_ntoa(_addr.sin_addr) << \
				", port: " << ntohs(_addr.sin_port) << std::endl;
			
			std::string welcomeMessage = _name + " INFO :Hello, welcome to the server\r\n";
			if (send(new_sock, welcomeMessage.c_str(), welcomeMessage.length(), 0) != 47)
				throw std::runtime_error("Failed to send welcome message");
			std::cout << "Welcome message sent successfully" << std::endl;

			User newUser(new_sock, "newUser");
			addPending(newUser);
			std::cout << "Waiting for registration..." << std::endl;
		}
		for (size_t i = 0; i < _users.size(); i++)
		{
			sd = _users[i].getSocket();
			if (FD_ISSET(sd, &readfds))
			{
				if ((valread = read(sd, buffer, 512)) == 0)
				{
					_partialCommands[_users[i].getSocket()] = "";
					Command::controlQuit(_users[i], *this);
					getpeername(sd, (struct sockaddr*)&_addr, (socklen_t*)&_addr_len);
					std::cout << "Host disconnected, ip " << inet_ntoa(_addr.sin_addr) << ", port " << ntohs(_addr.sin_port) << std::endl;
				}
				else
				{
					buffer[valread] = '\0';
					handleMessage(std::string(buffer), _users[i]);
					for (int i = 0; i < valread; i++)
						buffer[i] = '\0';
				}
			}
		}
		for (size_t i = 0; i < _pending.size(); i++)
		{
			sd = _pending[i].getSocket();
			if (FD_ISSET(sd, &readfds))
			{
				if ((valread = read(sd, buffer, 512)) == 0)
				{
					_partialCommands[_pending[i].getSocket()] = "";
					getpeername(sd, (struct sockaddr*)&_addr, (socklen_t*)&_addr_len);
					std::cout << "Host disconnected, ip " << inet_ntoa(_addr.sin_addr) << ", port " << ntohs(_addr.sin_port) << std::endl;
					close(sd);
					_pending[i].setSocket(0);
					removePending(_pending[i]);
				}
				else
				{
					buffer[valread] = '\0';
					handleMessage(std::string(buffer), _pending[i]);
					for (int i = 0; i < valread; i++)
						buffer[i] = '\0';
					if (_pending[i].isUserRegistered())
					{
						if (CheckNickCollision(_pending[i]))
						{
							sendWelcomeMessage(_pending[i]);
							addUser(_pending[i]);
							Command::startBot(_pending[i]);
							removePending(_pending[i]);
						}
					}
				}
			}
		}
	}
}

void Server::stop(std::string message)
{
	message = _name + " QUIT :" + message + "\r\n";
	for (size_t i = 0; i < _pending.size(); i++)
	{
		send(_pending[i].getSocket(), message.c_str(), message.size(), 0);
		close(_pending[i].getSocket());
		_pending[i].setSocket(0);
	}
	for (size_t i = 0; i < _users.size(); i++)
	{
		send(_users[i].getSocket(), message.c_str(), message.size(), 0);
		close(_users[i].getSocket());
		_users[i].setSocket(0);
	}
	close(_sock);
}
