/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:22:51 by everonel          #+#    #+#             */
/*   Updated: 2024/03/26 17:25:38 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "Server.hpp"

class Server;
class Channel;

class User
{
	public:
		User();
		User(int socket, std::string nickname);
		~User();
		bool operator==(const User &other) const;
		bool operator!=(const User &other) const;
		bool operator<(const User &other) const;
		bool operator>(const User &other) const;

		std::string getNickname();
		std::string getUsername();
		std::string getRealname();
		std::string getPingMssg();
		int  getNbChannels();
		int  getSocket();
		int  getError();
		bool getPassword();
		bool getRegisteredNick();
		bool getRegisteredUser();
		bool isUserRegistered();
		std::vector<std::string> getChannels();

		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setRealname(std::string realname);
		void setPingMssg(std::string pingMssg);
		void setSocket(int socket);
		void setError(int error);
		void setPassword(bool password);
		void setRegisteredNick(bool registeredNick);
		void setRegisteredUser(bool registeredUser);
		void addChannel(std::string channel);
		void removeChannel(std::string channel);

	private:
		std::string _nickname;
		std::string _username;
		std::string _realname;
		std::string _pingMssg;
		std::vector<std::string> _channels;

		int  _socket;
		int  _error;
		bool _password;
		bool _registeredNick;
		bool _registeredUser;
};

#endif