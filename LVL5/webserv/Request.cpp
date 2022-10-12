/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:30:02 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/11 15:58:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"


Request::Request(/* args */)
{
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
	_body = "";
	_type = "";
	_path = "";
}

void Request::parse(std::string req) {
	size_t i = 0;
	std::istringstream _req(req);
	std::string tmp;
	int cp = 0;

	while (std::getline(_req, tmp)) {
		if (tmp[0] == '\r') {
			cp = 1;
			continue;
		}
		if (cp == 1) {
			_body += tmp + "\n";
			continue ;
		}

		int i = tmp.find(':');
		if (i == std::string::npos) {
			int j = tmp.find(' ');
			_type = tmp.substr(0, j);
			int k = tmp.find(' ', j + 1);
			_path = tmp.substr(j + 1, k - j);
		} else {
			std::string header = tmp.substr(0, i);
			if (_headers.find(header) != _headers.end()) {
				if (_headers.find(header)->second != "")
					throw std::runtime_error("Request Failed, Duplicate Header {"+ header + "}");
				else
					_headers[header] = tmp.substr(i + 2, tmp.length());
			}
		}
	}
}

void Request::display() {
	std::cout << "------------- REQUEST INFO ----------------" << std::endl;
	std::cout << "\tMethode: " << _type << std::endl;
	std::cout << "\tRoute: " << _path << std::endl;
	std::map<std::string, std::string>::const_iterator m_it;
	for (m_it = _headers.begin() ; m_it != _headers.end(); m_it++) {
		if (m_it->second != "")
			std::cout << "\t" << m_it->first << ": " << m_it->second << std::endl;
	}
	_body != "" && std::cout << std::endl << "------------- BODY SECTION ----------------" << std::endl;
	_body != "" && std::cout << _body << std::endl;
}

Request::~Request()
{
}