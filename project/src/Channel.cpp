/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:04:14 by ncortigi          #+#    #+#             */
/*   Updated: 2024/03/28 17:27:31 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

Channel::Channel()
{
}

Channel::Channel(const Channel &other)
{
	_name = other._name;
	_users = other._users;
	_topic = other._topic;
	_inviteOnly = other._inviteOnly;
	_LockedTopic = other._LockedTopic;
	_hasPassword = other._hasPassword;
	_limit = other._limit;
	_password = other._password;
	_invited = other._invited;
}

Channel::Channel(std::string name, User *user)
{
	_name = toLowerButBetter(name);
	_users.insert(std::pair<std::string, bool>(user->getNickname(), true));
	_topic = "";
	_inviteOnly = false;
	_LockedTopic = true;
	_hasPassword = false;
	_limit = -1;
}

Channel::~Channel()
{
}

bool Channel::operator==(const Channel &other) const
{
	return (toLowerButBetter(_name) == toLowerButBetter(other._name));
}

bool Channel::isEmpty()
{
	return (_users.size() == 0);
}

std::string Channel::getName()
{
	return _name;
}

std::string Channel::getTopic()
{
	return _topic;
}

std::string Channel::getPassword()
{
	return _password;
}

bool Channel::getInviteOnly()
{
	return _inviteOnly;
}

bool Channel::getLockedTopic()
{
	return _LockedTopic;
}

bool Channel::hasPassword()
{
	return _hasPassword;
}

int Channel::getLimit()
{
	return _limit;
}

int Channel::getNbUsers()
{
	return _users.size();
}

int Channel::getNbOperators()
{
	int nb = 0;
	for (std::map<std::string, bool>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second == true)
			nb++;
	}
	return nb;
}

void Channel::setName(std::string name)
{
	_name = name;
}

void Channel::setPassword(std::string password)
{
	_password = password;
}

void Channel::setTopic(std::string topic)
{
	_topic = topic;
}

void Channel::setInviteOnly(bool inviteOnly)
{
	_inviteOnly = inviteOnly;
}

void Channel::setLockedTopic(bool lockedTopic)
{
	_LockedTopic = lockedTopic;
}

void Channel::setHasPassword(bool hasPassword)
{
	_hasPassword = hasPassword;
}

void Channel::setLimit(int limit)
{
	_limit = limit;
}

bool Channel::isOperator(std::string nick)
{
	for (std::map<std::string, bool>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->first == nick)
			return it->second;
	}
	return false;
}

void Channel::giveOperator(std::string nick)
{
	for (std::map<std::string, bool>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->first == nick)
			it->second = true;
	}
}

void Channel::removeOperator(std::string nick)
{
	for (std::map<std::string, bool>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->first == nick)
			it->second = false;
	}
}

void Channel::setNewOperator(std::string nick, Server &server)
{
	std::string username = server.getUser(nick)->getUsername();
	std::map<std::string, bool>::iterator it = _users.begin();
	int i = rand() % _users.size();
	for (int j = 0; j < i; j++)
		it++;
	if (it->first == nick)
	{
		it++;
		if (it == _users.end())
			it = _users.begin();
	}
	it->second = true;
	std::string response = ":" + nick + "!" + username + "@localhost MODE " + _name + " +o :" + it->first + "\r\n";
	sendToChannel(response, nick, true, server);
}

void Channel::invite(std::string nick)
{
	_invited.push_back(nick);
}

void Channel::uninvite(std::string nick)
{
	_invited.erase(std::find(_invited.begin(), _invited.end(), nick));   
}

bool Channel::isInvited(std::string nick)
{
	return (std::find(_invited.begin(), _invited.end(), nick) != _invited.end());
}

void Channel::UserList(User *user, Server &server)
{
	std::string list = "353 " + user->getNickname() + " = " + _name + " :" + getUsersList() + "\r\n";
	this->sendToChannel(list, user->getNickname(), true, server);
}

std::string Channel::getUsersList()
{
	std::string list = "";
	for (std::map<std::string, bool>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second == true)
			list += "@" + it->first + " ";
		else
			list += it->first + " ";
	}
	list = list.substr(0, list.size() - 1);
	return list;
}

void Channel::addUser(std::string nick)
{
	_users.insert(std::pair<std::string, bool>(nick, false));
}

void Channel::removeUser(std::string nick)
{
	for (std::map<std::string, bool>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->first == nick)
		{
			_users.erase(it);
			return;
		}
	}
}

void Channel::updateNick(std::string oldNick, std::string newNick)
{
	bool isOp = isOperator(oldNick);
	removeUser(oldNick);
	addUser(newNick);
	if (isOp)
		giveOperator(newNick);
	for (std::vector<std::string>::iterator it2 = _invited.begin(); it2 != _invited.end(); it2++)
	{
		if (*it2 == oldNick)
		{
			*it2 = newNick;
			return;
		}
	}
}

bool Channel::isUserInChannel(std::string nick)
{
	return (_users.find(nick) != _users.end());
}

std::map<std::string, bool> Channel::getUsers()
{
	return _users;
}

void Channel::sendToChannel(std::string message, std::string nick, bool sendToUser, Server &server)
{
	for (std::map<std::string, bool>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->first != nick || sendToUser)
		{
			int socket = server.getUser(it->first)->getSocket();
			send(socket, message.c_str(), message.size(), 0);
		}
	}
}
