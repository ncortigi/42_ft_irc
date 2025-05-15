/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:04:27 by ncortigi          #+#    #+#             */
/*   Updated: 2024/04/11 16:48:15 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Server.hpp"

class User;
class Server;

class Channel
{
    public:
        Channel();
        Channel(const Channel &other);
        Channel(std::string name, User *user);
        ~Channel();
        bool operator==(const Channel &other) const;

        std::string getName();
        std::string getTopic();
        std::string getPassword();
        bool getInviteOnly();
        bool getLockedTopic();
        bool hasPassword();
        int getLimit();
        int getNbUsers();
        int getNbOperators();

        bool isEmpty();
        void setName(std::string name);
        void setPassword(std::string password);
        void setTopic(std::string topic);
        void setInviteOnly(bool inviteOnly);
        void setLockedTopic(bool lockedTopic);
        void setHasPassword(bool hasPassword);
        void setLimit(int limit);
        bool isOperator(std::string nick);
        void giveOperator(std::string nick);
        void removeOperator(std::string nick);
        void setNewOperator(std::string nick, Server &server);

        void invite(std::string nick);
        void uninvite(std::string nick);
        bool isInvited(std::string nick);

        void UserList(User *user, Server &server);
        std::string getUsersList();
        void addUser(std::string nick);
        void removeUser(std::string nick);
        void updateNick(std::string oldNick, std::string newNick);
        bool isUserInChannel(std::string nick);
        std::map<std::string, bool> getUsers();
        void sendToChannel(std::string message, std::string nick, bool sendToUser, Server &server);

    private:
        std::string _name;
        std::string _topic;
        std::string _password;

        bool _inviteOnly;
        bool _LockedTopic;
        bool _hasPassword;
        int _limit;

        std::vector<std::string> _invited;
        std::map<std::string, bool> _users;
};

#endif