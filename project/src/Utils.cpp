#include "../inc/Utils.hpp"
#include "../inc/Server.hpp"

std::string   buildInfoMsg(int info_code, std::string arg1)
{
	switch (info_code)
	{
		case 001:
			return ("001 " + arg1 + " :Welcome to the Internet Relay Chat Network!\r\n");
		case 372:
			return ("372 " + arg1 + " :- Welcome to the our Internet Relay Network!\r\n");
		case 376:
			return ("376 " + arg1 + " :End of /MOTD command.\r\n");
		default:
			return ("");
	}
}

std::string   buildInfoMsg2(int info_code, std::string arg1, std::string arg2)
{
	switch (info_code)
	{
		case 001:
			return ("001 " + arg1 + " :Welcome to the " + arg2 + " Internet Relay Chat Network!\r\n");
		case 003:
			return ("003 " + arg1 + " :This server was created " + arg2 + "\r\n");
		case 005:
			return ("005 " + arg1 + " :CHANTYPES=" + arg2 + " :are supported by this server\r\n");
		case 366:
			return (":IRCSERV 366 " + arg1 + " " + arg2 + " :End of NAMES list\r\n");
		default:
			return ("");
	}
}

std::string   buildInfoMsg3(int info_code, std::string arg1, std::string arg2, std::string arg3)
{
	switch (info_code)
	{
		case 002:
			return ("002 " + arg1 + " :Your host is " + arg2 + ", running version " + arg3 + "\r\n");
		case 324:
			return ("324 " + arg1 + " " + arg2 + " +" + arg3 + "\r\n");
		case 331:
			return ("332 " + arg1 + " " + arg2 + " :No topic is set\r\n");
		case 332:
			return ("332 " + arg1 + " " + arg2 + " :" + arg3 + "\r\n");
		case 341:
			return ("341 " + arg1 + " " + arg2 + " " + arg3 + " :Invite to channel sent\r\n");
		case 353:
			return (":IRCSERV 353 " + arg1 + " = " + arg2 + " :" + arg3 + "\r\n");
		default:
			return ("");
	}
}

std::string    buildErrorMsg(int error_code, std::string arg1)
{
	switch (error_code)
	{
		case 402:
			return ("402 " + arg1 + " :No such server\r\n");
		case 411:
			return ("411 " + arg1 + " :No recipient given\r\n");
		case 412:
			return ("412 " + arg1 + " :No text to send\r\n");
		case 431:
			return ("431 " + arg1 + " :No nickname given\r\n");
		case 451:
			return ("451 " + arg1 + " :You have not registered\r\n");
		case 462:
			return ("462 " + arg1 + " :You may not reregister\r\n");
		case 464:
			return ("464 " + arg1 + " :Password incorrect\r\n");
		default:
			return ("");
	}
}

std::string  buildErrorMsg2( int error_code, std::string arg1, std::string arg2)
{
	switch (error_code)
	{
		case 401:
			return ("401 " + arg1 + " " + arg2 + " :No such nick/channel\r\n");
		case 403:
			return ("403 " + arg1 + " " + arg2 + " :No such channel\r\n");
		case 404:
			return ("404 " + arg1 + " " + arg2 + " :Cannot send to channel\r\n");
		case 405:
			return ("405 " + arg1 + " " + arg2 + " :You have joined too many channels\r\n"); 
		case 421:
			return ("421 " + arg1 + " " + arg2 + " :Unknown command\r\n");
		case 432:
			return ("432 " + arg1 + " " + arg2 + " :Erroneous nickname\r\n");
		case 433:
			return ("433 " + arg1 + " " + arg2 + " :Nickname is already in use\r\n");
		case 441:
			return ("441 " + arg1 + " " + arg2 + " :They aren't on that channel\r\n");
		case 442:
			return ("442 " + arg1 + " " + arg2 + " :You're not on that channel\r\n");
		case 461:
			return ("461 " + arg1 + " " + arg2 + " :Not enough parameters\r\n");
		case 467:
			return ("467 " + arg1 + " " +  arg2 + " :Channel key already set\r\n");
		case 471:
			return ("471 " + arg1 + " " + arg2 + " :Cannot join channel (+l)\r\n");
		case 472:
			return ("472 " + arg1 + " " + arg2 + " :is unknown mode char to me for me\r\n");
		case 473:
			return ("473 " + arg1 + " " + arg2 + " :Cannot join channel (+i)\r\n");
		case 475:
			return ("475 " + arg1 + " " + arg2 + " :Cannot join channel (+k)\r\n");
		case 482:
			return ("482 " + arg1 + " " + arg2 + " :You're not channel operator\r\n");
		default:
			return ("");
	}
}

std::string    buildErrorMsg3( int error_code, std::string arg1, std::string arg2, std::string arg3)
{
	switch (error_code)
	{
		case 443:
			return ("443 " + arg1 + " " + arg2 + " " + arg3 + " :is already on channel\r\n");
		default:
			return ("");
	}
}


std::string toLowerButBetter(std::string str)
{
	std::string lowerStr = str;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '[')
			lowerStr[i] = '{';
		else if (str[i] == ']')
			lowerStr[i] = '}';
		else if (str[i] == '\\')
			lowerStr[i] = '|';
		else if (str[i] == '~')
			lowerStr[i] = '^';
		else
			lowerStr[i] = std::tolower(str[i]);
	}
	return (lowerStr);
}

int split(std::string str, const std::string separator, std::vector<std::string> &result)
{
    size_t pos = 0;
    std::string tmp;
    while ((pos = str.find(separator)) != std::string::npos)
    {
		if (str.find(":") == 0)
			break;
        tmp = str.substr(0, pos);
		if (tmp.size() > 0)
        	result.push_back(tmp);
        str.erase(0, pos + separator.length());
    }
	if (!str.empty())
    	result.push_back(str);
    return (result.size());
}

int modesplit(std::string str, std::vector<std::string> &result)
{
	char sign = '+';
	size_t i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+' || str[i] == '-')
			sign = str[i];
		else
		{
			std::string tmp;
			tmp = sign;
			tmp += str[i];
			result.push_back(tmp);
		}
		i++;
	}
	return (result.size());
}
