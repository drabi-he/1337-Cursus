/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouf <izouf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:21:23 by hdrabi            #+#    #+#             */
/*   Updated: 2023/01/23 15:27:45 by izouf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string trim(std::string str, std::string del) {
	size_t i;
	size_t j;

	i = str.find("#");
	if (i != std::string::npos)
		str = str.erase(i, str.length());

	for (i = 0; i < str.length(); i++) {
		if (del.find(str[i]) == std::string::npos)
			break;
	}
	for (j = str.length() - 1; j >= 0; j--) {
		if (del.find(str[j]) == std::string::npos)
			break;
	}
	if (j < str.length())
		str.erase(j + 1, str.length());
	str.erase(0, i);
	return str;
}

std::string trim1(std::string str, std::string del) {
	size_t i;
	size_t j;

	for (i = 0; i < str.length(); i++) {
		if (del.find(str[i]) == std::string::npos)
			break;
	}
	for (j = str.length() - 1; j >= 0; j--) {
		if (del.find(str[j]) == std::string::npos)
			break;
	}
	if (j < str.length())
		str.erase(j + 1, str.length());
	str.erase(0, i);
	return str;
}

void check_line(std::string line, size_t line_num) {
	size_t i;
	std::string rst;

	if (line.empty())
		return ;
	if ((line[0] == '}' || line[0] == '{')) {
		if (line.length() == 1)
			return ;
		else
			throw std::runtime_error("Error: Invalid config file: line " + std::to_string(line_num) + ": " + line);
	}

	i = line.find(" ");
	rst = line.substr(0, i);
	std::vector<std::string>::const_iterator it;
	it = std::find(_directives.begin(), _directives.end(), rst);
	if (it == _directives.end())
		throw std::runtime_error("Error: Invalid directive in config file: line " + std::to_string(line_num) + ": " + line);
	if (line.back() != ';') {
		if (rst != "location" && rst != "server")
			throw std::runtime_error("Error: Invalid config file missing ';': line " + std::to_string(line_num) + ": " + line);
	} else {
		if (rst == "location" || rst == "server")
			throw std::runtime_error("Error: Invalid config file extra ';': line " + std::to_string(line_num) + ": " + line);
	}
}

void check_brackets(std::string config) {
	size_t i = 0;
	ssize_t cp = 0;

	while (i < config.length()) {
		if (config[i] == '{')
			cp++;
		else if (config[i] == '}')
			cp--;
		if (cp < 0)
			throw std::runtime_error("Error: Invalid config file: missing '{'");
		i++;
	}
	if (cp != 0)
		throw std::runtime_error("Error: Invalid config file: missing '}'");
}

std::string get_value(std::string* str, std::string key, int dup, int k) {
    size_t i = str->find(key , k);

    if (i == std::string::npos)
        return "";

	int j = str->find(';', i);
	if (key == "location ")
		j = str->find('{', i);

    std::string value = str->substr(i + key.size(), j - i - key.size());

	if ((size_t)j == std::string::npos)
		throw std::runtime_error("Error: Invalid config file: missing ;");
	else
		str->erase(i, j - i + 1);

    i = str->find(key);
    if (i != std::string::npos && !dup)
        throw std::runtime_error("Error: duplicate directive: " + key.substr(1, key.length() - 2));
	value = trim(value);
	if (value.empty())
		throw std::runtime_error("Error: missing arguments for directive: " + key.substr(1, key.length() - 2));
    return value;
}

int get_port(std::string listen) {
	size_t i = 0;
	std::string rst = listen;

	i = listen.find(':');
	if (i != std::string::npos)
		rst = listen.substr(i + 1, listen.length());
	if (rst.empty())
		throw std::runtime_error("Error: missing port number");
	for (size_t j = 0; j < rst.length() ; j++) {
		if (!std::isdigit(rst[j])) {
			if (i != std::string::npos)
				throw std::runtime_error("Error: invalid port number: " + rst);
			else
				return 80;
		}
	}
	i = std::stoi(rst);
	if (i < 1 || i > 65535)
		throw std::runtime_error("configFile error, port value is out of range");
	return i;
}

std::string get_host(std::string listen) {
	size_t i = 0;
	std::string rst = listen;

	i = listen.find(':');
	if (i != std::string::npos)
		rst = listen.substr(0, i);
	for (size_t j = 0; j < rst.length() ; j++) {
		if (!std::isdigit(rst[j])) {
				return rst;
		}
	}

	return "0.0.0.0";
}

std::vector<std::string> split_vec(std::string str) {
	size_t i = 0;
	std::vector<std::string> vec;
	std::string rst;

	while ((i = str.find(' ')) != std::string::npos) {
		rst = str.substr(0, i);
		rst = trim(rst);
		str.erase(0, i);
		str = trim(str);
		if (!rst.empty())
			vec.push_back(rst);
	}
	if (!str.empty())
		vec.push_back(trim(str));

	return vec;
}

std::string decipherMethods(std::vector<std::string> methods) {
	std::string result = "0000";
	std::string tmp[4] = {"GET", "POST", "PUT", "DELETE"};

	for (std::vector<std::string>::iterator it = methods.begin() ; it < methods.end() ; it++)
	{
		int i = 0;
		for (i = 0; i < 4; i++) {
			if (*it == tmp[i]) {
				result[i] = '1';
				break;
			}
		}
		if (i == 4) {
			throw std::runtime_error("configFile error, unknown method found");
		}
	}
	return result;
}

std::string createErrorPage(int status) {
	std::string rst = "";

	rst += "<!DOCTYPE html>";
	rst += "<html lang=\"en\">";
	rst += "<head>";
	rst += "    <meta charset=\"UTF-8\">";
	rst += "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">";
	rst += "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
	rst += "    <title>"+ _statusCodes[status] + "</title>";
	rst += "</head>";
	rst += "<body>";
	rst += "    <h1>This Is Error Page " + std::to_string(status) + "</h1>";
	rst += "    <h2>" + _statusCodes[status] + "</h2>";
	rst += "</body>";
	rst += "</html>";
	return rst;
}

std::string getDate() {
	time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%a, %d %b %Y %X %Z", &tstruct);
    return (buf);
}

std::pair<bool, std::string> ft_isDirectory(std::string root, Location* loc, std::string uri) {

	struct stat rst;

	if (root[root.length() - 1] != '/' && uri[0] != '/')
		root += "/";
	else if (root[root.length() - 1] == '/' && uri[0] == '/')
		uri = uri.substr(1, uri.length());

	std::string path = root + uri;
	if (loc) {
		if (!loc->_root.empty()) {
			if (loc->_root[loc->_root.length() - 1] != '/' && uri[0] != '/')
				loc->_root += "/";
			else if (loc->_root[loc->_root.length() - 1] == '/' && uri[0] == '/')
				uri = uri.substr(1, uri.length());
			path = loc->_root + uri;
		}
	}
	if (stat(path.c_str(), &rst) == -1)
		return std::make_pair(false, "");
	if (S_ISDIR(rst.st_mode))
		return std::make_pair(true, path);
	else
		return std::make_pair(false, path);
}

std::string createIndexPage(std::string path, std::string uri) {
	std::string rst = "";
	std:: string tmp = "";
	DIR *dir;
	struct dirent *ent;

	if (path[path.length() - 1] == '/')
		path.erase(path.length() - 1, 1);
	dir = opendir(path.c_str());
	tmp = path.substr(path.find(uri), path.length());


	rst += "<!DOCTYPE html>";
	rst += "<html lang=\"en\">";
	rst += "<head>";
	rst += "    <meta charset=\"UTF-8\">";
	rst += "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">";
	rst += "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
	rst += "    <title>Index of " + tmp + "/</title>";
	rst += "</head>";
	rst += "<body>";
	rst += "    <h1>Index of " + tmp + "/</h1>";
	rst += "	<hr>";
	rst += "	<pre>";

	while ((ent = readdir(dir)) != NULL) {
		if (ent->d_name[0] == '.' && ent->d_name[1] == '\0')
			continue;
		rst += "<a href=\"";
		if (std::string(ent->d_name) == "..")
			rst +=  tmp + "/" + "../";
		else
			rst += tmp + "/" +std::string(ent->d_name);
		rst += "\">" + std::string(ent->d_name);
		if (ent->d_type == DT_DIR)
			rst += "/";
		rst +="</a>\n";
	}

	rst += "	</pre>";
	rst += "	<hr>";
	rst += "</body>";
	rst += "</html>";

	return rst;
}

bool is_cgi(std::string path, Location* loc) {
	std::string cgi;

	cgi = path.substr(path.find_last_of('.') + 1, path.length());
	if (loc) {
		for (size_t i = 0; i < loc->_cgi.size(); i++) {
			if (cgi == loc->_cgi[i].first)
				return true;
		}
	}
	return false;
}

std::vector<std::string> split(std::string str, std::string delim){
    std::vector<std::string> vec;
    size_t i = 0;
    std::string rst;

    while ((i = str.find(delim)) != std::string::npos) {
        rst = str.substr(0, i);
        str.erase(0, i + delim.length());
        if (!rst.empty())
            vec.push_back(rst);
    }
    if (!str.empty())
        vec.push_back(str);
    return vec;
}

void getContentTypeFromMap(Client* client){
	std::string extension = client->_request->_uri.substr(client->_request->_uri.find_last_of(".") + 1);
	if (_mimeTypes.find(extension) != _mimeTypes.end())
		client->_response->_content_type = _mimeTypes[extension];
	else
		client->_response->_content_type = "text/html";
}

int parse_mime_types() {
	std::ifstream file("./assets/conf/mime.types");
	std::string line;
	std::string key;
	std::string value;

	if (!file.is_open())
		return -1;
	while (std::getline(file, line)) {
		if (line[0] == '#' || line.find("type") == 0)
			continue;
		std::istringstream iss(line);
		iss >> key;
		while (iss >> value){
			value = trim(value, ";");
			_mimeTypes[value] = key;
		}
	}
	return 0;
}
