/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:53:49 by akadi             #+#    #+#             */
/*   Updated: 2023/06/23 23:46:42 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC
#define FT_IRC


#include "ParsingChannelCommands.hpp"
#include <iostream>
#include <curl/curl.h> /// BOT
#include <sys/socket.h>
#include <sys/types.h>
# include <fcntl.h> /// fcntl()
#include <netdb.h> /// gethostbyname()
#include <netdb.h>  // getaddrinfo()
#include <unistd.h>
#include <arpa/inet.h> //htons()
#include <sys/select.h> // select()
#include <sys/poll.h> // poll()
#include "client_irc.hpp"
#include "Channel.hpp"

class Channel;
class Client_irc;

extern std::map<std::string, Channel> mapchannels;

class IrcServer
{
    private :
        std::string	password;
        std::string port;
        struct pollfd fds[1024];
        struct addrinfo hints;
        struct addrinfo *result;
        std::map<int, Client_irc> mapclients;
    public :
        IrcServer();
        ~IrcServer();
        IrcServer(std::string port, std::string pass);
        std::vector<Channel>    chanel;
        std::string getPort() const ;
        std::string  getPassword() const ;
        Client_irc  &getClient(int);
        std::map<int, Client_irc> &getMapclient();

        void    setPort(std::string port);
        void    setPassword(std::string pass);
        void    setMapclients(const std::map<int, Client_irc> &);
        //// server ///////
        int     SetupServer();
        void    RunServer(int);
        void    InitPollfd(int);
        void    AcceptNewConnection(int , int *);
        int     RecieveIncomingData(int *, int, int, std::string &);
        void    Authentification(int);
        /////////////////////
        void    RemoveCRLF(int);
        //--commands
        void    execute_command(const std::vector<std::string> &command, Client_irc *client);
        
        void    check_Join_cmd(const std::vector<std::string> &command, Client_irc *client);
        void    check_Invite_cmd(const std::vector<std::string> &command, Client_irc *client);
        void    check_Mode_cmd(const std::vector<std::string> &command, Client_irc *client);
        void    check_Privmsg_cmd(const std::vector<std::string> &command, Client_irc *client);
        void    check_List_cmd(const std::vector<std::string> &command, Client_irc *client);
        void    check_Names_cmd(const std::vector<std::string> &command, Client_irc *client);
        void    check_Part_cmd(const std::vector<std::string> &command, Client_irc *client);
        void    check_Nick_cmd(const std::vector<std::string> &command, Client_irc *client);
        void    check_Bot_cmd(const std::vector<std::string> &command, Client_irc *client);
        void    check_Topic_cmd(const std::vector<std::string> &command, Client_irc *client);
        //////////////////////    channel commands ///////////////////////
        void    kick_command(const std::vector<std::string> &, Client_irc *);
        int     client_finder(std::string command);
        std::string getChannelUsers(std::string channelname);
        std::string        getChannelModes(std::string channelname);
        
          
};

bool    checkPort(char *str);
void    Error(const char *str);
void    checkArguments(int ac, char **av);
void    display_vct_str(std::vector<std::string> vct);
long 	stringToLong(const std::string& str);
std::string getMachineHost();

#endif