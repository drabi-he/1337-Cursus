/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:21:05 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/29 14:59:45 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP




#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include "WebServ.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"

# define GET 0
# define POST 1
# define PUT 2
# define DELETE 3
# define DEL " \t\n\r"
# define BUFF_SIZE 1048576

extern std::vector<std::string> _directives;
extern std::map<int, std::string> _statusCodes;
extern std::map<std::string, std::string> _mimeTypes;

class WebServ;
class Server;
class Location;
class Client;
class Request;
class Response;
class Socket;


std::string trim(std::string str, std::string del = DEL);
void check_line(std::string line, size_t line_num);
void check_brackets(std::string config);
std::string get_value(std::string* str, std::string key, int dup, int k = 0);
int get_port(std::string listen);
std::string get_host(std::string listen);
std::vector<std::string> split_vec(std::string str);
std::string decipherMethods(std::vector<std::string> methods);
std::string createErrorPage(int status);
std::string getDate();
std::vector<std::string> split(std::string str, std::string delim);
std::pair<bool, std::string> ft_isDirectory(std::string root, Location* loc, std::string uri);
std::string createIndexPage(std::string path, std::string uri);
void getContentTypeFromMap(Client* client);
std::string trim1(std::string str, std::string del);
int parse_mime_types();
bool is_cgi(std::string path, Location* loc);

#endif