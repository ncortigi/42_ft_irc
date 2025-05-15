/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:20:12 by everonel          #+#    #+#             */
/*   Updated: 2024/03/26 17:25:45 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Server.hpp"

User::User()
{
}

User::User(int socket, std::string nickname)
{
	_socket = socket;
	_nickname = nickname;
	_registeredNick = false;
	_registeredUser = false;
	_password = false;
	_error = 0;
}

User::~User()
{
}

//Serve a comparare due oggetti User, ma uno const e l'altro no (Senza esplode tutto)
bool User::operator==(const User &other) const
{
	return (toLowerButBetter(_nickname) == toLowerButBetter(other._nickname));
}

bool User::operator!=(const User &other) const
{
	return (toLowerButBetter(_nickname) != toLowerButBetter(other._nickname));
}

bool User::operator<(const User &other) const
{
	return (toLowerButBetter(_nickname) < toLowerButBetter(other._nickname));
}

bool User::operator>(const User &other) const
{
	return (toLowerButBetter(_nickname) > toLowerButBetter(other._nickname));
}

std::string User::getNickname()
{
	return (_nickname);
}

std::string User::getUsername()
{
	return (_username);
}

std::string User::getRealname()
{
	return (_realname);
}

std::string User::getPingMssg()
{
	return (_pingMssg);
}

int User::getNbChannels()
{
	return (_channels.size());
}

int User::getSocket()
{
	return (_socket);
}

int User::getError()
{
	return (_error);
}

bool User::getPassword()
{
	return (_password);
}

bool User::getRegisteredNick()
{
	return (_registeredNick);
}

bool User::getRegisteredUser()
{
	return (_registeredUser);
}

bool User::isUserRegistered()
{
	return (_registeredNick && _registeredUser && _password);
}

std::vector<std::string> User::getChannels()
{
	return (_channels);
}

void User::setNickname(std::string nickname)
{
	_nickname = nickname;
}

void User::setUsername(std::string username)
{
	_username = username;
}

void User::setRealname(std::string realname)
{
	_realname = realname;
}

void User::setPingMssg(std::string pingMssg)
{
	_pingMssg = pingMssg;
}

void User::setSocket(int socket)
{
	_socket = socket;
}

void User::setError(int error)
{
	_error = error;
}

void User::setPassword(bool password)
{
	_password = password;
}

void User::setRegisteredNick(bool registeredNick)
{
	_registeredNick = registeredNick;
}

void User::setRegisteredUser(bool registeredUser)
{
	_registeredUser = registeredUser;
}

void User::addChannel(std::string channel)
{
	_channels.push_back(channel);
}

void User::removeChannel(std::string channel)
{
	_channels.erase(std::remove(_channels.begin(), _channels.end(), channel), _channels.end());
}