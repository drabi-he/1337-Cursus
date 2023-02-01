/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouf <izouf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:36:12 by hdrabi            #+#    #+#             */
/*   Updated: 2023/01/31 16:55:46 by izouf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request()
{
    headers_init();
    _isReady = false;
    _method = "";
    _uri = "";
    _version = "";
    _body = "";
	_location = nullptr;
	_status = 0;
	_isDirectory = std::make_pair(false, "");
	_index = std::make_pair(false, "");
	_chunked = -2;
}

Request::~Request()
{
}

void Request::reset() {
	headers_init();
    _isReady = false;
		_rawRequest = "";
    _method = "";
    _uri = "";
    _version = "";
    _body = "";
	_location = nullptr;
	_status = -1;
	_isDirectory = std::make_pair(false, "");
	_index = std::make_pair(false, "");
	_chunked = -2;
}

void Request::headers_init() {
  _headers["Accept"] = "";
	_headers["Accept-Charset"] = "";
	_headers["Accept-Encoding"] = "";
	_headers["Accept-Language"] = "";
	_headers["Accept-Ranges"] = "";
	_headers["Age"] = "";
	_headers["Allow"] = "";
	_headers["Authorization"] = "";
	_headers["Cache-Control"] = "";
	_headers["Connection"] = "";
	_headers["Content-Encoding"] = "";
	_headers["Content-Language"] = "";
	_headers["Content-Length"] = "";
	_headers["Content-Location"] = "";
	_headers["Content-MD5"] = "";
	_headers["Content-Range"] = "";
	_headers["Content-Type"] = "";
	_headers["Date"] = "";
	_headers["ETag"] = "";
	_headers["Expect"] = "";
	_headers["Expires"] = "";
	_headers["From"] = "";
	_headers["Host"] = "";
	_headers["If-Match"] = "";
	_headers["If-Modified-Since"] = "";
	_headers["If-None-Match"] = "";
	_headers["If-Range"] = "";
	_headers["If-Unmodified-Since"] = "";
	_headers["Last-Modified"] = "";
	_headers["Location"] = "";
	_headers["Max-Forwards"] = "";
	_headers["Pragma"] = "";
	_headers["Proxy-Authenticate"] = "";
	_headers["Proxy-Authorization"] = "";
	_headers["Range"] = "";
	_headers["Referer"] = "";
	_headers["Retry-After"] = "";
	_headers["Server"] = "";
	_headers["TE"] = "";
	_headers["Trailer"] = "";
	_headers["Transfer-Encoding"] = "";
	_headers["Upgrade"] = "";
	_headers["User-Agent"] = "";
	_headers["Vary"] = "";
	_headers["Via"] = "";
	_headers["Warning"] = "";
	_headers["WWW-Authenticate"] = "";
	_headers["No testing framework"] = "";
	_headers["Implied *LWS"] = "";
	_headers["Host header"] = "";
	_headers["Identity and Quality"] = "";
	_headers["Range and Accept-Encoding headers"] = "";
	_headers["Connect header and HTTP/1.0 connections"] = "";
	_headers["Range and multi-range returns"] = "";
	_headers["Empty entries (for list headers)"] = "";
	_headers["Multiple headers (for list headers)"] = "";
	_headers["Content-Location and 301"] = "";
	_headers["CRLF"] = "";
}

Location* check_location(Server* server, std::string path) {
	Location* location = nullptr;
	std::size_t i;
	int match = 0, keep = -1;

	for (i = 0; i < server->_locations.size(); i++) {
		if (path == server->_locations[i]->_path) {
			location = server->_locations[i];
			break;
		} else if (path.find(server->_locations[i]->_path) == 0) {
			if ((size_t)match < server->_locations[i]->_path.length()) {
				match = server->_locations[i]->_path.length();
				keep = i;
			}
			location = server->_locations[i];
		}
	}
	if (keep != -1)
		location = server->_locations[keep];
	return location;
}

int parse_chunked(std::string* str, int chunked) {
	std::size_t len;
	std::string tmp = *str;
	std::string tmp2;

	*str = "";
	if (chunked == -1) {
		if (tmp == "0\r\n" || tmp == "0\r\n\r\n")
			return 0;
		if (tmp.find("\r\n") == std::string::npos)
			return -2;
		tmp2 = tmp.substr(0, tmp.find("\r\n"));
		if ((len = std::strtol(tmp2.c_str(), NULL, 16)) == 0)
			return -2;
		else
			return len;
	}
	if (chunked == 0 && tmp == "\r\n")
		return -1;
	if (tmp.length() != (size_t)(chunked + 2) || tmp[tmp.length() - 2] == '\r' || tmp[tmp.length() - 1] == '\n')
		return -2;
	*str = tmp.substr(0, chunked);
	return -1;
}

void print(std::string str) {
    int i = -1;

    while (str[++i]) {
        if (std::isprint(str[i]) && str[i] != '\n')
            std::cout << str[i];
        else
            std::cout << "|" << (int)str[i];
				if (str[i] == '\n')
					std::cout << std::endl;
    }
    std::cout << "-------------------------------------------------------" << std::endl;
}

void Request::parseRequest(std::string request, Client *client, Server *server) {

	size_t i = 0;
	std::string tmp;
    std::ostringstream convert;
	std::string _cgiPath;
	std::string cgiQ;
	std::vector<std::string> parsQ;
	std::string::size_type pos = 0;

	request = _reminder + request;

	while ((pos = request.find("\r\n")) != std::string::npos)
	{
		tmp = request.substr(0, pos + 2);

		if (_rawRequest.find("\r\n\r\n") != std::string::npos) {
			_body += request.substr(0, pos + 2);
			if (_body.length() >= (size_t)atoi(_headers["Content-Length"].c_str())) {
				if (_body.length() > (size_t)atoi(_headers["Content-Length"].c_str())) {
					_reminder = _body.substr(atoi(_headers["Content-Length"].c_str()));
					_body = _body.substr(0, atoi(_headers["Content-Length"].c_str()));
				}
				_rawRequest += request.substr(0, pos + 2);
				_isReady = true;
				_status = 0;
				return;
			}
		} 
		else {
			i = tmp.find(':');
			if (i == std::string::npos && tmp != "\r\n") {
				int j = tmp.find(' ');
				_method = tmp.substr(0, j);
				_method = trim(_method);
				int k = tmp.find(' ', j + 1);
				_uri = tmp.substr(j + 1, k - j);
				_uri = trim(_uri);
				if (_uri[_uri.length() - 1] == '/' && _uri.length() > 1)
					_uri = _uri.substr(0, _uri.length() - 1);
				if (_uri.find('?') != std::string::npos) {
					_query = _uri.substr(_uri.find('?') + 1);
					_uri = _uri.substr(0, _uri.find('?'));
				}
				_version = tmp.substr(k + 1, tmp.length());
				_version = trim(_version);
			} else {
				std::string key = tmp.substr(0, i);
				if (key.find(' ') != std::string::npos) {
					_status = 400;
					return;
				}
				key = trim(key);
				std::string value = tmp.substr(i + 1, tmp.find("\r\n") - i);
				value = trim(value);
				_headers[key] = value;
				if (key == "Transfer-Encoding" && value == "chunked")
					_chunked = -1;
			}
		}
		if (_chunked >= -1) {
			std::string tmp = request;

			_chunked = parse_chunked(&tmp, _chunked);
			if (_chunked == -2) {
				_status = 400;
				return;
			}
			else if (_chunked == -1) {
				_body += tmp;
				_rawRequest += tmp;
				if (tmp == "") {
					_headers["Content-Length"] = std::to_string(_body.length());
					_isReady = true;
					_status = 0;
					return;
				}
			}
			else if (_body.length() + _chunked > (size_t)(std::stoi(server->_clientMaxBodySize))) {
				_status = 413;
				return;
			}
		}
		_rawRequest += request.substr(0, pos + 2);
		convert << static_cast<int>(client->_addr.sin_port);
	 	_remotAddr = inet_ntoa(client->_addr.sin_addr);
	 	_cgiport = convert.str();
		request.erase(0, pos + 2);
	}
	_remotAddr = inet_ntoa(client->_addr.sin_addr);
	if (_rawRequest.find("\r\n\r\n") != std::string::npos && _body.length() + request.length() >= (size_t)atoi(_headers["Content-Length"].c_str())) {
		_body += request;
		_rawRequest += request;
		if (_body.length() > (size_t)atoi(_headers["Content-Length"].c_str())) {
			_reminder = _body.substr(atoi(_headers["Content-Length"].c_str()));
			_body = _body.substr(0, atoi(_headers["Content-Length"].c_str()));
		}
		_isReady = true;
		_status = 0;
		return;
	}
	_reminder = request;
	_status = 0;
	return;
}

void Request::display() {
    std::cout << "------------- REQUEST INFO ----------------" << std::endl;
	std::cout << "\tMethode: " << _method << std::endl;
	std::cout << "\tRoute: " << _uri << std::endl;
    std::cout << "\tVersion: " << _version << std::endl << std::endl;
    std::cout << "------------- HEADERS SECTION ----------------" << std::endl;
	std::map<std::string, std::string>::const_iterator m_it;
	for (m_it = _headers.begin() ; m_it != _headers.end(); m_it++) {
		if (m_it->second != "")
			std::cout << "\t" << m_it->first << ": " << m_it->second << std::endl;
	}
	_body != "" && std::cout << std::endl << "------------- BODY SECTION ----------------" << std::endl;
	_body != "" && std::cout << _body << std::endl;
	_body != "" && std::cout << _body.length() << std::endl;
}