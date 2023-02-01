/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouf <izouf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:10:19 by izouf             #+#    #+#             */
/*   Updated: 2023/01/31 17:49:58 by izouf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "Cgi.hpp"

Cgi::Cgi(Request *request, std::string path) 
{
	_body = request->_body;
	_path = path;
	this->initCgi(request);
}

Cgi::Cgi(Cgi const &src)
{
	if (this != &src)
		*this = src;
}

Cgi::~Cgi()
{}

Cgi		&Cgi::operator=(Cgi const &copy)
{
	if (this != &copy)
	{
		this->_body = copy._body;
		this->_env = copy._env;
	}
	return (*this);
}

void	Cgi::initCgi(Request *request)
{
	std::map<std::string, std::string>	headers = request->_headers;
	std::string cgiQ;

	_exec = request->_location->_cgi;
	_cgi = request->_location->_cgiBin;
	_body = request->_body;
	this->_env["REDIRECT_STATUS"] = "200";
	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_env["SCRIPT_NAME"] = request->_location->_cgiBin ;
	this->_env["SCRIPT_FILENAME"] = request->_location->_root + request->_uri;
	this->_env["REQUEST_METHOD"] = request->_method;
	this->_env["CONTENT_LENGTH"] = headers["Content-Length"];
	this->_env["CONTENT_TYPE"] = headers["Content-Type"];
	this->_env["CONTENT_FILE"] = request->_uri;
	this->_env["PATH_INFO"] = _path.substr(request->_root.length());
	this->_env["PATH_TRANSLATED"] = _path.substr(request->_root.length());
	this->_env["QUERY_STRING"] = request->_query;
	this->_env["REMOTE_ADDR"] = request->_remotAddr;
	this->_env["REMOTE_IDENT"] = headers["Authorization"];
	this->_env["REMOTE_USER"] = headers["From"];
	this->_env["REQUEST_URI"] = request->_uri + cgiQ ;
	if (headers.find("Host") != headers.end())
		this->_env["SERVER_NAME"] = headers["Host"];
	else
		this->_env["SERVER_NAME"] = this->_env["REMOTE_ADDR"];
	this->_env["SERVER_PORT"] = request->_cgiport;
	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_env["SERVER_SOFTWARE"] = "Webserv/1.0"; 
	this->_env["HTTP_ACCEPT"] = headers["Accept"];
	this->_env["HTTP_COOKIE"] = headers["Cookie"];
	this->_env["HTTP_REFER"] = headers["Refer"];
	this->_env["HTTP_USER_AGENT"] = headers["User-Agent"];
	this->_env["HTTP_ACCEPT_ENCODING"] = headers["Accept-Encoding"];
	this->_env["HTTP_ACCEPT_CHARSET"] = headers["Accept_Charset"];
	this->_env["DOCUMENT_ROOT"];
	this->_env["REQUEST_URI"];
	this->_env["SCRIPT_FILENAME"] = _path;
	this->_env["UPLOAD_PATH"];
	
}

char	**Cgi::maptotab()
{
	char		**cgi_env = new char *[_env.size() + 1];
	std::string	tmp;
	int			i;

	i = 0;
	for (std::map<std::string, std::string>::iterator it = _env.begin(); it != _env.end(); it++, i++)
	{
		tmp = it->first + "=" + it->second;
		cgi_env[i] = new char[tmp.size() + 1];
		cgi_env[i] = std::strcpy(cgi_env[i], tmp.c_str());
	}
	cgi_env[i] = NULL;
	return (cgi_env);
}

std::string	Cgi::execute(std::string path)
{
	std::string	body;
	std::string	str;
	char		**cgi_env = maptotab();
	int			stdin_save = dup(STDIN_FILENO);
	int			stdout_save = dup(STDOUT_FILENO);
	FILE		*tmp_in = tmpfile();
	FILE		*tmp_out = tmpfile();
	int			in_fd = fileno(tmp_in);
	int			out_fd = fileno(tmp_out);
	pid_t		pid;
	
	str = path;
	for (std::vector<std::pair<std::string, std::string> >::iterator it = _exec.begin(); it != _exec.end(); it++)
	{
		if (str.substr(path.find_last_of(".") + 1) == it->first)
		{
			_cgi += "/" + it->second;
			break;
		}
	}
	_args[0] = (char *) _cgi.c_str();
	_args[1] = (char *) path.c_str(); 
	_args[2] = NULL;
	write(in_fd, _body.c_str(), std::atoi(this->_env["CONTENT_LENGTH"].c_str()));
	lseek(in_fd, 0, SEEK_SET);
	if ((pid = fork()) == -1)
		return ("Status: 500\r\n");
	else if (!pid)
	{
		dup2(in_fd, STDIN_FILENO);
		dup2(out_fd, STDOUT_FILENO);
		execve(_args[0], (char **)_args, cgi_env);
		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
	}
	else
	{
		char	buf[BUFFER_SIZE + 1];

		waitpid(0, NULL, 0);
		lseek(out_fd, 0, SEEK_SET);

		int	ret = 1;
		while (ret > 0)
		{
			ret = read (out_fd, buf, BUFFER_SIZE);
			buf[ret] = 0;
			body += buf;
		}
	}
	dup2(stdin_save, STDIN_FILENO);
	dup2(stdout_save, STDOUT_FILENO);
	fclose(tmp_in);
	fclose(tmp_out);
	close(in_fd);
	close(out_fd);
	close(stdin_save);
	close(stdout_save);
	for (int i = 0; cgi_env[i]; i++)
		delete cgi_env[i];
	delete [] cgi_env;
	if (!pid)
		exit(0);
	return (body);
}