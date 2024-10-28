#include "cgi.hpp"
#include <string>
#include "../exec/request/reponse.hpp"
#include <ctime>

Cgi::Cgi( reponse& reponse ) : _reponse(reponse) {
	this->_client_fd = reponse.getClientFd();
	this->_fullRequest = reponse.getFullHeader();
	this->_userInput = "";
	this->_contentLength = -1;
}

Cgi::~Cgi(){
}

Cgi& Cgi::operator=( const Cgi& other ){
	this->_env = other._env;
	return *this;
}

std::string Cgi::getValueInFullRequest( std::string search ){
	size_t pos = this->_fullRequest.find(search);
	if (pos == std::string::npos){
		std::cerr << "Error occurence not found" << std::endl;
		return "";
	}
	std::string ret;
	ret = this->_fullRequest.substr(pos + search.length() + 2);
	pos = ret.find("\r\n");
	if (pos == std::string::npos){
		std::cerr << "Error occurence not found" << std::endl;
		return "";
	}
	ret = ret.substr(0, pos);
	return ret;
}

std::string Cgi::getUserInput(){
	return this->_userInput;
}

int			Cgi::getContentLength(){
	return this->_contentLength;
}

std::map<std::string, std::string> Cgi::getEnv( void ){
	return this->_env;
}

int	Cgi::getClientFd(){
	return this->_client_fd;
}

std::string Cgi::getUrl() {
	return this->_reponse.getUrl();
}

std::string Cgi::getFullHeader() {
	return this->_reponse.getFullHeader();
}

void Cgi::setEnv( std::string pathInfo ){
    this->_env["HTTP_ACCEPT"] = this->getValueInFullRequest("Accept");
    this->_env["HTTP_ACCEPT_ENCODING"] = this->getValueInFullRequest("Accept-Encoding");
    this->_env["HTTP_ACCEPT_LANGUAGE"] = this->getValueInFullRequest("Accept-Language");
	this->_env["PATH_INFO"] = pathInfo;
    this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
    this->_env["HOST"] = this->getValueInFullRequest("Host");
    this->_env["HTTP_USER_AGENT"] = this->getValueInFullRequest("User-Agent");
    this->_env["HTTP_CONNECTION"] = this->getValueInFullRequest("Connection");
	this->_env["HTTP_COOKIE"] = "";
	this->_env["CONTENT_TYPE"] = this->getValueInFullRequest("Content-Type");
	this->_env["HTTP_USER_AGENT"] = this->getValueInFullRequest("User-Agent");
	this->_env["SERVER_NAME"] = this->getValueInFullRequest("Host");
	std::string scriptName = this->getUrl().substr(this->getUrl().find_last_of('/') + 1);
	this->_env["SCRIPT_NAME"] = scriptName.c_str();
	if (_reponse.getFormQuerry() != "") {
		this->_env["REQUEST_METHOD"] = "GET";
		this->_env["QUERY_STRING"] = _reponse.getFormQuerry();
		this->_env["CONTENT_LENGTH"] = "NULL";
	}
	else {
		this->_env["CONTENT_LENGTH"] = this->getValueInFullRequest("Content-Length");
		this->_env["QUERY_STRING"] = "NULL";
		this->_env["REQUEST_METHOD"] = "POST";
	}

	std::string host = _fullRequest.substr(_fullRequest.find("Host: ") + 6);
	host = host.substr(0, host.find("\r\n"));

	this->_env["REMOTE_HOST"] = host.c_str();
	this->_env["SERVER_PORT"] = host.substr(host.find(":") + 1).c_str();
	this->_env["SCRIPT_FILENAME"] = this->getUrl().c_str();

}

char* ft_strcpy(char* dest, const char* src){
	int i = 0;
	while (src[i]){
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

char** Cgi::envToTab(){
	char** envTab;
	try {
		envTab = new char* [this->_env.size() + 1];
	} catch(const std::bad_alloc& e) {
    	std::cerr << "Error: " << e.what() << std::endl;
	}
	int	i = 0;
	for (std::map<std::string, std::string>::const_iterator it = this->_env.begin(); it != this->_env.end(); it++){
		std::string str = it->first + "=" + it->second;
		try {
			envTab[i] = new char[str.size() + 1];
		} catch(const std::bad_alloc& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
		envTab[i] = ft_strcpy(envTab[i], (const char*)str.c_str());
		i++;
	}
	envTab[i] = NULL;
	return envTab;
}

void ft_exit(char** envp){
	for (int i = 0; envp[i]; i++)
		delete[] envp[i];
	delete[] envp;
}

char* ft_strdup(std::string chaine) {
    char* rest = new char[chaine.size() + 1];
    strcpy(rest, chaine.c_str());
    return rest;
}

void Cgi::setContentLength() {
	std::string url = this->getFullHeader();
	size_t pos = url.find("Content-Length: ");
	if (pos == std::string::npos)
		return ;
	std::string tmp = url.substr(pos, url.size());
	size_t pos2 = tmp.find_first_of('\n');
	if (pos2 == std::string::npos)
		return ;
	std::string line = tmp.substr(0 + 15, pos2);
	try {
		_contentLength = stoi(line);
	}
	catch ( std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

void Cgi::setUserInput() {
	if (this->_contentLength == -1) {
		std::cerr << "didn't find the content length\n";
		return ;
	}
	std::string url = this->getFullHeader();
	size_t pos = url.find("\r\n\r\n");
	if (pos == std::string::npos) {
		std::cerr << "didn't find the end of the header\n";
		return ;
	}
	url.erase(0, pos + 4);
	url.append("\0");
	this->_userInput = url;
}

char** choosenCgi(std::string url) {
	char** res = new char*[3];
	if (url.find(".py") != std::string::npos) {
		res[0] = ft_strdup("/usr/bin/python3");
	}
	else if (url.find(".pl") != std::string::npos) {
		res[0] = ft_strdup("/usr/bin/perl");
	}
	else
		res[0] = ft_strdup("/usr/bin/python3");
	return res;
}

void executeCgi( reponse& reponse, std::string pathInfo){

	Cgi data( reponse );
	if (reponse.getFormQuerry() == "") {
		data.setContentLength();
		if (data.getContentLength() == -1) {
			reponse.setStatus(400);
			return ;
		}
		data.setUserInput();
	}
	data.setEnv( pathInfo );
	char** envp = data.envToTab();
	int tmp_fd[2];
	if (pipe(tmp_fd) == -1){
		std::cerr << "Error pipe" << std::endl;
		ft_exit(envp);
		reponse.setStatus(500);
		return ;
	}
	write(tmp_fd[1], data.getUserInput().c_str(), data.getUserInput().size());
	close(tmp_fd[1]);
	int pipe_fd[2];
	if (pipe(pipe_fd) == -1){
		std::cerr << "Error pipe" << std::endl;
		ft_exit(envp);
		reponse.setStatus(500);
		return ;
	}
	pid_t pid_child = fork();
	if (pid_child < 0) {
		std::cerr << "Error fork" << std::endl;
		ft_exit(envp);
		reponse.setStatus(500);
		return ;
	}
	else if (!pid_child){
		if (dup2(tmp_fd[0], 0) == -1) {
			std::cerr << "Error dup2" << std::endl;
			ft_exit(envp);
			reponse.setStatus(500);
			return ;
		}
		if (dup2(pipe_fd[1], 1) == -1) {
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			std::cerr << "Error dup2" << std::endl;
			ft_exit(envp);
			reponse.setStatus(500);
			return ;
		}
		close(pipe_fd[1]);
		char **res = choosenCgi(reponse.getUrl());
		res[1] = (char*)reponse.getUrl().c_str();
		res[2] = NULL;
		if (execve(res[0], res, envp) == -1) {
			std::cerr << "Error execve" << std::endl;
		}
	}
	else {
		pid_t pid_checker;
		if ((pid_checker = fork()) < 0) {
			std::cerr << "Error fork" << std::endl;
		}
		else if (!pid_checker) {
			clock_t start = std::clock();
			while ((std::clock() - start) / CLOCKS_PER_SEC < static_cast<unsigned long>(reponse.getCgiTimeOut()));
			kill(pid_child, SIGKILL);
		}
		else {
			int status;
			waitpid(pid_child, &status, 0);
			if (status == SIGKILL) {
				reponse.setStatus(504);
				close(tmp_fd[0]);
				close(pipe_fd[0]);
				ft_exit(envp);
				return ;
			}
			kill(pid_checker, SIGKILL);
			close(pipe_fd[1]);
			if (status != 0) {
				reponse.setStatus(500);
				close(tmp_fd[0]);
				close(pipe_fd[0]);
				ft_exit(envp);
				return ;
			}
			char buffer[1024];
			int ret;
			while ((ret = read(pipe_fd[0], buffer, 1024)) > 0){
				buffer[ret] = '\0';
				reponse.addBody(buffer);
			}
			reponse.setStatus(200);
		}
		close(tmp_fd[0]);
		close(pipe_fd[0]);
		ft_exit(envp);
	}

}
