#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Server.hpp"

class Server;
class User;
class Channel;

class Command
{
	public:
		Command();
		~Command();

		static void pass(std::vector<std::string> message, User &user, std::string password);
		static void nick(std::vector<std::string> message, User &user, Server &server);
		static void user(std::vector<std::string> message, User &user);
		static void join(std::vector<std::string> message, User &user, Server &server);
		static void part(std::vector<std::string> message, User &user, Server &server);
		static void ping(std::vector<std::string> message, User &user);
		static void dcc(std::vector<std::string> message, User &user, Server &server);
		static void privmsg(std::vector<std::string> message, User &user, Server &server);
		static void kick(std::vector<std::string> message, User &user, Server &server);
		static void invite(std::vector<std::string> message, User &user, Server &server);
		static void topic(std::vector<std::string> message, User &user, Server &server);
		static void mode(std::vector<std::string> message, User &user, Server &server);
		static void quit(std::vector<std::string> message, User &user, Server &server);
		static void help(User &user);
		static void controlQuit(User &user, Server &server);

		static void botError(User &user);
		static void botHelp(User &user);
		static void botUsers(User &user, Server &server);
		static void botChannels(std::vector<std::string> message, User &user, Server &server);
		static void botRestore(std::vector<std::string> message, User &user, Server &server);
		static void botQuote(User &user);
		static void botError2(User &user, Server &server);
		static void bot(std::vector<std::string> message, User &user, Server &server);
		static void startBot(User &user);

	private:
		static const std::string _qoutes1[20];
		static const std::string _qoutes2[20];
		static const std::string _qoutes3[20];
		static const std::string _qoutes4[20];
		static const std::string _qoutes5[20];
};

#endif