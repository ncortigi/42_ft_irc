#include "../inc/Command.hpp"

Command::Command()
{
}

Command::~Command()
{
}

static void	validatePermission(User &user, bool condition, std::string message)
{
	if (condition)
	{
		send(user.getSocket(), message.c_str(), message.size(), 0);
		throw std::exception();
	}
}

static void	validatePermission2(User &user, bool condition, std::string message)
{
	if (condition)
	{
		send(user.getSocket(), message.c_str(), message.size(), 0);
		throw std::runtime_error("Invalid password");
	}
}

void Command::pass(std::vector<std::string> message, User &user, std::string password)
{
	validatePermission(user, message.size() < 1, buildErrorMsg2(461, user.getNickname(), "PASS"));
	std::string passw;
	if (message[0].find(":") == 0)
		passw = message[0].substr(1, message[0].size() - 1);
	else
		passw = message[0];
	validatePermission(user, user.getPassword(), buildErrorMsg(462, user.getNickname()));
	validatePermission2(user, passw != password, buildErrorMsg(464, user.getNickname()));
	user.setPassword(true);
}

void setNickInChannels(User &user, Server &server, std::string nick)
{
	std::vector<std::string> channels = user.getChannels();
	for (size_t i = 0; i < channels.size(); i++)
	{
		Channel *tmp = server.getChannel(channels[i]);
		tmp->updateNick(user.getNickname(), nick);
	}
}

void Command::nick(std::vector<std::string> message, User &user, Server &server)
{
	validatePermission(user, message.size() < 1, buildErrorMsg(431, user.getNickname()));
	std::string nick = message[0];
	validatePermission(user, nick.length() > 9, buildErrorMsg2(432, user.getNickname(), nick));
	for (size_t i = 0; i < nick.size(); i++)
	{
		validatePermission(user, !isalnum(nick[i]) && nick[i] != '-' && nick[i] != '_' && nick[i] != '[' && nick[i] != ']' && nick[i] != '{' 
			&& nick[i] != '}' && nick[i] != '\\' && nick[i] != '|' && nick[i] != '^' && nick[i] != '`' && nick[i] != '~', 
			buildErrorMsg2(432, user.getNickname(), nick));
	}
	validatePermission(user, server.isNickAlreadyUsed(nick) || nick == "Solver", buildErrorMsg2(433, user.getNickname(), nick));
	if (user.isUserRegistered())
	{
		std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost NICK :" + nick + "\r\n";
		server.sendToAll(response, user);
		send(user.getSocket(), response.c_str(), response.size(), 0);
		setNickInChannels(user, server, nick);
	}
	user.setNickname(nick);
	user.setRegisteredNick(true);
}

void Command::user(std::vector<std::string> message, User &user)
{
	validatePermission(user, message.size() < 4, buildErrorMsg2(461, user.getNickname(), "USER"));
	validatePermission(user, user.getRegisteredUser(), buildErrorMsg(462, user.getNickname()));
	if (message[3].find(":") != 0)
		return ;
	if (message[0].length() > 9)
		return ;
	user.setRegisteredUser(true);
	user.setUsername(message[0]);
	user.setRealname(message[3].substr(1, message[3].size() - 1));
}

void sendJoin(Channel *channel, User &user, Server &server)
{
	std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost JOIN :" + channel->getName() + "\r\n";
	channel->sendToChannel(response, user.getNickname(), true, server);
	std::string response1 = buildInfoMsg3(353, user.getNickname(), channel->getName(), channel->getUsersList());
	send(user.getSocket(), response1.c_str(), response1.size(), 0);
	std::string response2 = buildInfoMsg2(366, user.getNickname(), channel->getName());
	send(user.getSocket(), response2.c_str(), response2.size(), 0);
	std::string response4;
	if (channel->getTopic().empty())
		response4 = buildInfoMsg3(331, user.getNickname(), channel->getName(), "");
	else
		response4 = buildInfoMsg3(332, user.getNickname(), channel->getName(), channel->getTopic());
	send(user.getSocket(), response4.c_str(), response4.size(), 0);
}

void Command::join(std::vector<std::string> message, User &user, Server &server)
{
	validatePermission(user, message.size() < 1, buildErrorMsg2(461, user.getNickname(), "JOIN"));
	std::vector<std::string> channel;
	split(message[0], ",", channel);
	std::vector<std::string> key;
	size_t kSize = 0;
	if (message.size() == 2)
		kSize = split(message[1], ",", key);
	for (size_t i = 0; i < channel.size(); i++)
		validatePermission(user, (channel[i].find("#") != 0 && channel[i].find("&") != 0), buildErrorMsg2(403, user.getNickname(), channel[i]));
	for (size_t i = 0; i < channel.size(); i++)
	{
		validatePermission(user, user.getNbChannels() + 1 > 10, buildErrorMsg2(405, user.getNickname(), channel[i]));
		if (!server.isChannelRegistered(channel[i]))
		{
			Channel newChannel(channel[i], &user);
			if (kSize > 0 && i < kSize && !key[i].empty())
			{
				newChannel.setPassword(key[i]);
				newChannel.setHasPassword(true);
			}
			server.addChannel(newChannel);
			user.addChannel(server.getChannels().back().getName());
			sendJoin(&newChannel, user, server);
		}
		else
		{
			Channel *tmp = server.getChannel(channel[i]);
			if (tmp->isUserInChannel(user.getNickname()))
				continue ;
			validatePermission(user, tmp->getInviteOnly() && !tmp->isInvited(user.getNickname()), buildErrorMsg2(473, user.getNickname(), channel[i]));
			if (tmp->hasPassword())
			{
				validatePermission(user, kSize == 0 || i >= kSize, buildErrorMsg2(475, user.getNickname(), channel[i]));
				validatePermission(user, kSize > 0 && i < kSize && key[i] != tmp->getPassword(), buildErrorMsg2(475, user.getNickname(), channel[i]));
			}
			validatePermission(user, tmp->getLimit() == tmp->getNbUsers(), buildErrorMsg2(471, user.getNickname(), channel[i]));
			tmp->addUser(user.getNickname());
			user.addChannel(tmp->getName());
			sendJoin(tmp, user, server);
			tmp->UserList(&user, server);
			if (tmp->isInvited(user.getNickname()))
				tmp->uninvite(user.getNickname());
		}
	}
}

void	Command::part(std::vector<std::string> message, User &user, Server &server)
{
	validatePermission(user, message.size() < 1, buildErrorMsg2(461, user.getNickname(), "PART"));
	std::vector<std::string> channel;
	split(message[0], ",", channel);
	for (size_t i = 0; i < channel.size(); i++)
	{
		validatePermission(user, !server.isChannelRegistered(channel[i]), buildErrorMsg2(403, user.getNickname(), channel[i]));
		Channel *tmp = server.getChannel(channel[i]);
		validatePermission(user, !tmp->isUserInChannel(user.getNickname()), buildErrorMsg2(442, user.getNickname(), channel[i]));
		if (tmp->getNbOperators() == 1 && tmp->isOperator(user.getNickname()) && tmp->getNbUsers() > 1)
			tmp->setNewOperator(user.getNickname(), server);
		std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost PART :" + tmp->getName() + "\r\n";
		tmp->sendToChannel(response, user.getNickname(), true, server);
		user.removeChannel(tmp->getName());
		tmp->removeUser(user.getNickname());
		tmp->UserList(&user, server);
		if (tmp->isEmpty())
			server.removeChannel(*tmp);
	}
}

void	Command::ping(std::vector<std::string> message, User &user)
{
	std::string pongMessage = "PONG :" + message[0] + "\r\n";
	send(user.getSocket(), pongMessage.c_str(), pongMessage.size(), 0);
}

void Command::privmsg(std::vector<std::string> message, User &user, Server &server)
{
	validatePermission(user, (message.size() < 1 || message[0].find(":") == 0), buildErrorMsg(411, user.getNickname()));
	validatePermission(user, (message.size() < 2 || message[1].find(":") != 0), buildErrorMsg(412, user.getNickname()));

	std::vector<std::string> target;
	split(message[0], ",", target);
	std::string m = message[1].substr(1, message[1].size() - 1);
	for (size_t i = 0; i < target.size(); i++)
	{
		if (target[i].find("#") == 0 || target[i].find("&") == 0)
		{
			validatePermission(user, !server.isChannelRegistered(target[i]), buildErrorMsg2(401, user.getNickname(), target[i]));
			Channel *tmp = server.getChannel(target[i]);
			validatePermission(user, !tmp->isUserInChannel(user.getNickname()), buildErrorMsg2(404, user.getNickname(), target[i]));
			std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost PRIVMSG " + target[i] + " :" + m + "\r\n";
			tmp->sendToChannel(response, user.getNickname(), false, server);
		}
		else
		{
			if (target[i] == "Solver")
			{
				bot(message, user, server);
				return ;
			}
			validatePermission(user, !server.isNickAlreadyUsed(target[i]), buildErrorMsg2(401, user.getNickname(), target[i]));
			User *tmp = server.getUser(target[i]);
			std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost PRIVMSG " + target[i] + " :" + m + "\r\n";
			send(tmp->getSocket(), response.c_str(), response.size(), 0);
		}
	}
}

void Command::kick(std::vector<std::string> message, User &user, Server &server)
{
	validatePermission(user, message.size() < 2, buildErrorMsg2(461, user.getNickname(), "KICK"));
	std::string channel = message[0];
	validatePermission(user, !server.isChannelRegistered(channel), buildErrorMsg2(403, user.getNickname(), channel));
	Channel *tmp = server.getChannel(channel);
	validatePermission(user, !tmp->isUserInChannel(user.getNickname()), buildErrorMsg2(442, user.getNickname(), channel));
	validatePermission(user, !tmp->isOperator(user.getNickname()), buildErrorMsg2(482, user.getNickname(), channel));
	std::string target = message[1];
	validatePermission(user, !server.isNickAlreadyUsed(target), buildErrorMsg2(401, user.getNickname(), target));
	User *tmp1 = server.getUser(target);
	validatePermission(user, !tmp->isUserInChannel(target), buildErrorMsg2(441, user.getNickname(), target));
	tmp->removeUser(tmp1->getNickname());
	tmp1->removeChannel(tmp->getName());
	std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost KICK " + channel + " " + target;
	if (message.size() > 2)
	{
		if (message[2].find(":") == 0)
			message[2] = message[2].substr(1, message[2].size() - 1);
		response += " :" + message[2];
	}
	response += "\r\n";
	send(tmp1->getSocket(), response.c_str(), response.size(), 0);
	tmp->sendToChannel(response, user.getNickname(), true, server);
	if (tmp->isEmpty())
		server.removeChannel(*tmp);
	else
		tmp->UserList(&user, server);
}

void Command::invite(std::vector<std::string> message, User &user, Server &server)
{
	validatePermission(user, message.size() < 2, buildErrorMsg2(461, user.getNickname(), "INVITE"));
	validatePermission(user, !server.isNickAlreadyUsed(message[0]) , buildErrorMsg2(401, user.getNickname(), message[0]));
	User *target = server.getUser(message[0]);
	validatePermission(user, !server.isChannelRegistered(message[1]), buildErrorMsg2(403, user.getNickname(), message[1]));
	Channel *channel = server.getChannel(message[1]);
	validatePermission(user, !channel->isUserInChannel(user.getNickname()), buildErrorMsg2(442, user.getNickname(), message[1]));
	validatePermission(user, !channel->isOperator(user.getNickname()), buildErrorMsg2(482, user.getNickname(), message[1]));
	validatePermission(user, channel->isUserInChannel(target->getNickname()), buildErrorMsg3(443, user.getNickname(), message[0], message[1]));
	
	if (channel->getInviteOnly())
		channel->invite(target->getNickname());
	std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost INVITE " + message[0] + " " + message[1] + "\r\n";
	send(target->getSocket(), response.c_str(), response.size(), 0);
	std::string response2 = "341 " + user.getNickname() + " " + message[0] + " " + message[1] + " :Invite to channel sent\r\n";
	send(user.getSocket(), response2.c_str(), response2.size(), 0);
}

void Command::topic(std::vector<std::string> message, User &user, Server &server)
{
	validatePermission(user, message.size() < 1, buildErrorMsg2(461, user.getNickname(), "TOPIC"));
	validatePermission(user, !server.isChannelRegistered(message[0]), buildErrorMsg2(403, user.getNickname(), message[0]));
	Channel *tmp = server.getChannel(message[0]);
	if (message.size() == 1)
	{
		std::string response;
		if (tmp->getTopic().empty())
			response = buildInfoMsg3(331, user.getNickname(), tmp->getName(), "");
		else
			response = buildInfoMsg3(332, user.getNickname(), tmp->getName(), tmp->getTopic());
		send(user.getSocket(), response.c_str(), response.size(), 0);
	}
	else
	{
		validatePermission(user, !tmp->isUserInChannel(user.getNickname()), buildErrorMsg2(442, user.getNickname(), message[0]));
		validatePermission(user, !tmp->isOperator(user.getNickname()) && tmp->getLockedTopic(), buildErrorMsg2(482, user.getNickname(), message[0]));
		
		std::string newTopic = message[1];
		if (message[1].find(":") == 0)
			newTopic = message[1].substr(1, message[1].size() - 1);
		if (tmp->getTopic() == newTopic)
			return ;
		tmp->setTopic(newTopic);
		std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost TOPIC " + message[0] + " :" + newTopic + "\r\n";
		tmp->sendToChannel(response, user.getNickname(), true, server);
	}
}

void modeSetOperator(Channel *tmp, User &user, Server &server, bool flag, std::string target)
{
	if (target.empty())
		target = user.getNickname();
	if (target == user.getNickname() && flag)
		return ;
	validatePermission(user, !server.isNickAlreadyUsed(target), buildErrorMsg2(401, user.getNickname(), target));
	validatePermission(user, !tmp->isUserInChannel(target), buildErrorMsg2(441, user.getNickname(), target));
	if (tmp->isOperator(target) == flag)
		return ;
	if (flag)
		tmp->giveOperator(target);
	else
		tmp->removeOperator(target);
	std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost MODE " + tmp->getName();
	if (flag)
		response += " +o :" + target + "\r\n";
	else
		response += " -o :" + target + "\r\n";
	tmp->sendToChannel(response, user.getNickname(), true, server);
}

void modeSetInviteOnly(Channel *tmp, User &user, Server &server, bool flag)
{
	if (flag == tmp->getInviteOnly())
		return ;
	tmp->setInviteOnly(flag);
	std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost MODE " + tmp->getName();
	if (flag)
		response += " +i\r\n";
	else
		response += " -i\r\n";
	tmp->sendToChannel(response, user.getNickname(), true, server);
}

void modeSetLockedTopic(Channel *tmp, User &user, Server &server, bool flag)
{
	if (flag == tmp->getLockedTopic())
		return ;
	tmp->setLockedTopic(flag);
	std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost MODE " + tmp->getName();
	if (flag)
		response += " +t\r\n";
	else
		response += " -t\r\n";
	tmp->sendToChannel(response, user.getNickname(), true, server);
}

void modeSetLimit(Channel *tmp, User &user, Server &server, bool flag, std::string limit)
{
	validatePermission(user, limit.empty() && flag, buildErrorMsg2(461, user.getNickname(), "MODE [+l]"));
	if (!flag && tmp->getLimit() == -1)
		return ;
	if (flag)
	{
		for (size_t i = 0; i < limit.size(); i++)
			validatePermission(user, !isdigit(limit[i]), buildErrorMsg2(461, user.getNickname(), "MODE [+l]"));
		int i = atoi(limit.c_str());
		if (i <= 0)
			return ;
		tmp->setLimit(i);
	}
	else
		tmp->setLimit(-1);
	std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost MODE " + tmp->getName();
	if (flag)
	{
		std::stringstream ss;
		ss << tmp->getLimit();
		response += " +l " + ss.str() + "\r\n";
	}
	else
		response += " -l\r\n";
	tmp->sendToChannel(response, user.getNickname(), true, server);
}

void modeSetPassword(Channel *tmp, User &user, Server &server, bool flag, std::string pass)
{
	validatePermission(user, pass.empty() && flag, buildErrorMsg2(461, user.getNickname(), "MODE [+k]"));
	if (!flag && !tmp->hasPassword())
		return ;
	if (flag)
	{
		validatePermission(user, tmp->hasPassword(), buildErrorMsg2(467, user.getNickname(), tmp->getName()));
		tmp->setPassword(pass);
		tmp->setHasPassword(true);
	}
	else
	{
		tmp->setPassword("");
		tmp->setHasPassword(false);
	}
	std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost MODE " + tmp->getName();
	if (flag)
		response += " +k " + pass + "\r\n";
	else
		response += " -k\r\n";
	tmp->sendToChannel(response, user.getNickname(), true, server);
}

void Command::mode(std::vector<std::string> message, User &user, Server &server)
{
	validatePermission(user, message.size() < 1, buildErrorMsg2(461, user.getNickname(), "MODE"));
	validatePermission(user, !server.isChannelRegistered(message[0]), buildErrorMsg2(403, user.getNickname(), message[0]));

	Channel *tmp = server.getChannel(message[0]);
	if (message.size() == 1)
	{
		std::string response = "324 " + user.getNickname() + " " + message[0] + " +";
		std::string aux;
		if (tmp->getInviteOnly())
			response += "i";
		if (tmp->getLockedTopic())
			response += "t";
		if (tmp->getLimit() != -1)
		{
			response += "l";
			std::stringstream ss;
			ss << tmp->getLimit();
			aux += ss.str() + " ";
		}
		if (tmp->hasPassword())
		{
			response += "k";
			if (tmp->isUserInChannel(user.getNickname()))
				aux += tmp->getPassword() + " ";
		}
		response += " " + aux + "\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
		return ;
	}
	validatePermission(user, !tmp->isUserInChannel(user.getNickname()), buildErrorMsg2(442, user.getNickname(), message[0]));
	std::vector<std::string> modes;
	modesplit(message[1], modes);
	size_t j = 2;
	for (size_t i = 0; i < modes.size(); i++)
	{
		validatePermission(user, (!tmp->isOperator(user.getNickname()) && modes[i] == "+o"), buildErrorMsg2(482, user.getNickname(), message[0]));
		char flag = modes[i][0];
		char mode = modes[i][1];
		if ((flag != '+' && flag != '-') || !(mode == 'o' || mode == 'i' || mode == 't' || mode == 'l' || mode == 'k' || mode == 'b'))
		{
			std::string response = "472 " + user.getNickname() + " " + mode + " :is unknown mode char to me\r\n";
			send(user.getSocket(), response.c_str(), response.size(), 0);
			return ;
		}
		switch (mode)
		{
			case 'o':
				if (flag == '+')
					modeSetOperator(tmp, user, server, true, (message.size() <= j) ? "" : message[j++]);
				else if (flag == '-')
					modeSetOperator(tmp, user, server, false, (message.size() <= j) ? "" : message[j++]);
				break;
			case 'i':
				if (flag == '+')
					modeSetInviteOnly(tmp, user, server, true);
				else if (flag == '-')
					modeSetInviteOnly(tmp, user, server, false);
				break;
			case 't':
				if (flag == '+')
					modeSetLockedTopic(tmp, user, server, true);
				else if (flag == '-')
					modeSetLockedTopic(tmp, user, server, false);
				break;
			case 'l':
				if (flag == '+')
					modeSetLimit(tmp, user, server, true, (message.size() <= j) ? "" : message[j++]);
				else if (flag == '-')
					modeSetLimit(tmp, user, server, false, "");
				break;
			case 'k':
				if (flag == '+')
					modeSetPassword(tmp, user, server, true, (message.size() <= j) ? "" : message[j++]);
				else if (flag == '-')
					modeSetPassword(tmp, user, server, false, "");
				break;
			case 'b':
				break;
			default:
				break;
		}
	}
}

void Command::quit(std::vector<std::string> message, User &user, Server &server)
{
	std::vector<std::string> channels = user.getChannels();
	server.setPartialCommand(user.getSocket(), "");
	if (message.size() != 0)
	{
		if (message[0].find(":") == 0)
			message[0] = message[0].substr(1, message[0].size() - 1);
	}
	for (int i = 0; i < user.getNbChannels(); i++)
	{
		Channel *tmp = server.getChannel(channels[i]);
		if (tmp->getNbOperators() == 1 && tmp->isOperator(user.getNickname()) && tmp->getNbUsers() > 1)
			tmp->setNewOperator(user.getNickname(), server);
		tmp->removeUser(user.getNickname());
		user.removeChannel(tmp->getName());
		if (tmp->isEmpty())
			server.removeChannel(*tmp);
	}
	std::string msg = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost QUIT :";
	if (message.size() != 0 && !message[0].empty())
		msg += message[0];
	msg += "\r\n";
	server.sendToAll(msg, user);
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (!server.isChannelRegistered(channels[i]))
			continue ;
		Channel *tmp = server.getChannel(channels[i]);
		tmp->UserList(&user, server);
	}
	std::string response = server.getName() + " QUIT :You have disconnected ";
	if (message.size() != 0 && !message[0].empty())
		response += "(" +  message[0] + ")\r\n";
	else
		response += "from the server.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	close(user.getSocket());
	user.setSocket(0);
	server.removeUser(user);
}

void Command::help(User &user)
{
	if (!user.isUserRegistered())
	{
		std::string	response = "HELP :You have not registered use:\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
		response = "HELP :PASS <password> - Register your password\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
		response = "HELP :NICK <nickname> - Create your nickname\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
		response = "HELP :USER <username> <hostname> <servername> <realname> - Register your user\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
		response = "HELP :QUIT - Disconnect from the server\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
		response = "HELP :HELP - Display this message\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
		return ;
	}
	std::string	response = "HELP :You can use the following commands:\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :NICK <nickname> - Change your nickname\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :JOIN <channel>{,<channel>} [<key>{,<key>}] - Join a channel\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :INVITE <nickname> <channel> - Invite a user to a channel\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :PRIVMSG <receiver>{,<receiver>} <text to be sent> - Send a message to a user or a channel\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :KICK <channel> <nickname> [<reason>] - Kick a user from a channel\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :TOPIC <channel> [<topic>] - Set or get the topic of a channel\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :MODE <channel> {[+|-]|o|i|t|l|k} [<limit>] [<user>] [key] - Set or get the mode of a channel\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :QUIT [<Quit message>] - Disconnect from the server\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :HELP - Display this message\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
}

void Command::controlQuit(User &user, Server &server)
{
	std::vector<std::string> channels = user.getChannels();
	for (int i = 0; i < user.getNbChannels(); i++)
	{
		Channel *tmp = server.getChannel(channels[i]);
		bool b = tmp->getNbOperators() == 1 && tmp->isOperator(user.getNickname()) && tmp->getNbUsers() > 1;
		user.removeChannel(tmp->getName());
		tmp->removeUser(user.getNickname());
		if (b)
			tmp->setNewOperator(user.getNickname(), server);
		if (tmp->isEmpty())
			server.removeChannel(*tmp);
	}
	std::string msg = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost QUIT :\r\n";
	server.sendToAll(msg, user);
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (!server.isChannelRegistered(channels[i]))
			continue ;
		Channel *tmp = server.getChannel(channels[i]);
		tmp->UserList(&user, server);
	}
	close(user.getSocket());
	user.setSocket(0);
	server.removeUser(user);
}
