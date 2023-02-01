/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouf <izouf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:35:14 by hdrabi            #+#    #+#             */
/*   Updated: 2023/01/31 18:08:56 by izouf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response() {
    _content = "";
    _response = "";
    isSend = false;
}

Response::~Response()
{
}

void Response::reset() {
    _content = "";
    _response = "";
    isSend = false;
}


void Response::handelError(Client *client, Server *server) {
    if (client->_request->_location != NULL) {
        if (client->_request->_location->_errorPages.find(client->_request->_status) != client->_request->_location->_errorPages.end()) {
            std::string path = client->_request->_location->_errorPages[client->_request->_status];
            std::ifstream file(path);
            if (file.is_open()) {
                std::string line;
                while (getline(file, line)) {
                    _content += line;
                }
                file.close();
            }
        }
    } else if (client->_request->_uri == "/") {
        if (server->_errorPages.find(client->_request->_status) != server->_errorPages.end()) {
            std::string path = server->_errorPages[client->_request->_status];
            std::ifstream file(path);
            if (file.is_open()) {
                std::string line;
                while (getline(file, line)) {
                    _content += line;
                }
                file.close();
            }
        }
    }
    if (_content.empty())
        _content = createErrorPage(client->_request->_status);
}

std::string Response::createErrorPage2(Client *client)
{
	std::ofstream		file;
	std::stringstream	buffer;
	std::string			rst;

	if (client->_request->_location->_errorPages.find(client->_request->_status) != client->_request->_location->_errorPages.end())
	{
		file.open(client->_request->_location->_errorPages[client->_request->_status], std::ifstream::in);
		if (file.is_open() == false)
		{
			client->_request->_status = 404;
			client->_request->_headers["Content-Type"] = "text/html";
			 return (rst = "<!DOCTYPE html>\n<html>\n\t<title>404 Not Found</title>\n\t<body>\n\t\t<div>\n\t\t\t<H1>404 Not Found</H1>\n\t\t</div>\n\t</body>\t</html>");
		}
			buffer << file.rdbuf();
			file.close();
			client->_request->_headers["Content-Type"] = "text/html";
			return (rst = buffer.str());
	}
	else
	{
		client->_request->_status = 404;
		client->_request->_headers["Content-Type"] = "text/html";
		return (rst = "<!DOCTYPE html>\n<html>\n\t<title>404 Not Found</title>\n\t<body>\n\t\t<div>\n\t\t\t<H1>404 Not Found</H1>\n\t\t</div>\n\t</body>\t</html>");
	}
}

void Response::parse_cgi(Client *client, std::string body)
{
	size_t		start;
	size_t		start_body = 0;
	size_t		sep_size = 0;
	std::string	line;
    _cookie = "";

	size_t pos = body.find("\r\n\r\n");
	std::string tmp;
	if (pos != std::string::npos) {
		tmp = body.substr(0, pos);
		while ((pos = tmp.find("Set-Cookie: ")) != std::string::npos) {
			_cookie += tmp.substr(pos, tmp.find("\r\n", pos) - pos + 2);
			tmp = tmp.substr(tmp.find("\r\n", pos) + 2);
		}
	}

	if ((start = body.find("Status: ")) != std::string::npos)
	{
		client->_request->_status = std::atoi(body.substr(start + 8, 3).c_str());
		_content = createErrorPage2(client);
		client->_request->_headers["Content-Length"] = std::to_string(_content.size());
	}
	else if ((start = body.find("Content-type: ")) != std::string::npos)
	{
		if ((start_body = body.find("\r\n\r\n", start)) != std::string::npos)
			sep_size = 4;
		else if ((start_body = body.find("\r\n", start)) != std::string::npos)
			sep_size = 2;
		line = body.substr(start, start_body - start);
		client->_request->_headers["Content-Type"] = line.substr(14);
	}
	_content = body.substr(start_body + sep_size);
	client->_request->_headers["Content-Length"] = std::to_string(_content.size());
}

void Response::handelRequest(Client *client) {
    if (client->_request->_status == 301 || client->_request->_status == 302)
        return ;
    std::string path = "";
    if (client->_request->_isDirectory.first) {
        if (client->_request->_index.second != "")
            path = client->_request->_index.second;
    } else {
        path = client->_request->_isDirectory.second;
    }
    if (path == "")
        _content = createIndexPage(client->_request->_isDirectory.second, client->_request->_location->_path);
    else {
        if (is_cgi(path, client->_request->_location)) {
			Cgi	cgi(client->_request, path);
			std::string	tmpBody;
			tmpBody = cgi.execute(path);
			parse_cgi(client, tmpBody);
            return ;
        }else if(client->_request->_method == "DELETE"){
            if (remove(path.c_str()) != 0)
                client->_request->_status = 500;
            else
                client->_request->_status = 200;
        } else {
            std::ifstream file(path);
            if (file.is_open()) {
                std::string line;
                while (getline(file, line)) {
                    _content += line + "\n";
                }
            file.close();
            }
        }
    }
}

void Response::defineContentType(Client* client){
    _content_type = "text/html";
    if (client->_request->_uri != ""){
        std::string extension = client->_request->_uri.substr(client->_request->_uri.find_last_of(".") + 1);
        if (extension == "html" || extension == "htm")
            _content_type = "text/html";
        else if (extension == "jpg" || extension == "jpeg")
            _content_type = "image/jpeg";
        else if (extension == "png")
            _content_type = "image/png";
        else if (extension == "gif")
            _content_type = "image/gif";
        else if (extension == "css" || extension == "scss")
            _content_type = "text/css";
        else if (extension == "js")
            _content_type = "application/javascript";
        else if (extension == "json")
            _content_type = "application/json";
        else if (extension == "xml")
            _content_type = "application/xml";
        else if (extension == "pdf")
            _content_type = "application/pdf";
        else if (extension == "zip")
            _content_type = "application/zip";
        else if (extension == "txt")
            _content_type = "text/plain";
        else if (extension == "mp3")
            _content_type = "audio/mpeg";
        else if (extension == "mp4")
            _content_type = "video/mp4";
        else if (extension == "avi")
            _content_type = "video/x-msvideo";
        else if (extension == "svg")
            _content_type = "image/svg+xml";
        else if (extension == "ico")
            _content_type = "image/x-icon";
        else if (extension == "woff")
            _content_type = "font/woff";
        else if (extension == "woff2")
            _content_type = "font/woff2";
        else if (extension == "ttf")
            _content_type = "font/ttf";
        else if (extension == "eot")
            _content_type = "application/vnd.ms-fontobject";
        else if (extension == "otf")
            _content_type = "font/otf";
        else if (extension == "sfnt")
            _content_type = "application/font-sfnt";
        else if (extension == "csv")
            _content_type = "text/csv";
        else if (extension == "html")
            _content_type = "text/html";
        else if (extension == "tiff")
            _content_type = "image/tiff";
        else if (extension == "webp")
            _content_type = "image/webp";
        else if (extension == "bmp")
            _content_type = "image/bmp";
        else if (extension == "jpe")
            _content_type = "image/jpe";
        else if (extension == "jig")
            _content_type = "image/jig";
        else if (extension == "jfif")
            _content_type = "image/jfif";
        else if (extension == "jfi")
            _content_type = "image/jfi";
        else if (extension == "jpx")
            _content_type = "image/jpx";
        else if (extension == "jp2")
            _content_type = "image/jp2";
        else if (extension == "j2k")
            _content_type = "image/j2k";
        else if (extension == "j2c")
            _content_type = "image/j2c";
        else if (extension == "jpc")
            _content_type = "image/jpc";
        else if (extension == "jxr")
            _content_type = "image/jxr";
        else if (extension == "m4v")
            _content_type = "video/m4v";
        else if (extension == "m4p")
            _content_type = "video/m4p";
        else if (extension == "m4b")
            _content_type = "video/m4b";
        else if (extension == "m4r")
            _content_type = "video/m4r";
        else if (extension == "m4s")
            _content_type = "video/m4s";
        else if (extension == "doc")
            _content_type = "aplication/msword";
        else if (extension == "docx")
            _content_type = "aplication/vnd.openxmlformats-officedocument.wordprocessingml.document";
        else if (extension == "xls")
            _content_type = "aplication/vnd.ms-excel";
        else if (extension == "xlsx")
            _content_type = "aplication/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
        else if (extension == "ppt")
            _content_type = "aplication/vnd.ms-powerpoint";
        else if (extension == "pptx")
            _content_type = "aplication/vnd.openxmlformats-officedocument.presentationml.presentation";
        else if (extension == "pps")
            _content_type = "aplication/vnd.ms-powerpoint";
        else if (extension == "ppsx")
            _content_type = "aplication/vnd.openxmlformats-officedocument.presentationml.slideshow";
        else if (extension == "odt")
            _content_type = "aplication/vnd.oasis.opendocument.text";
        else if (extension == "odp")
            _content_type = "aplication/vnd.oasis.opendocument.presentation";


    }
}