#include "reponse.hpp"
#include "../../parsing/server/server.hpp"
#include "../../cgi/cgi.hpp"

std::string reponse::getFullHeader() {
	return _request.getFullHeader();
}

void reponse::isDirAndFile() {
	std::string url = _url;
	std::string path;
	if (_location != "") {
		path = _serv.getRootInLoc(_location);
		if (path == "") {
			path = _serv.getRoot();
		}
		path.erase(path.size() - 1);
		if (_location == "/")
			url.erase(0, _location.size() - 1);
		else
			url.erase(0, _location.size());
		path += url;
	}
	else {
		path = _serv.getRoot();
		path += url;
	}
	_url = path;
	struct stat filestat;
	if (stat(path.c_str(), &filestat) == 0) {
		if (S_ISDIR(filestat.st_mode)) {
			_isDir = true;
			_isFile = false;
		}
		else if (S_ISREG(filestat.st_mode)) {
			_isDir = false;
			_isFile = true;
		}
	}
	else {
		_isDir = false;
		_isFile = false;
	}
}

void reponse::sendRedirrect() {
	_location = _serv.getRedirrectLocation(_location); // fonction qui renvoi la location de la redirection si il y en a une sinon renvoi "" voir configfile
	_status = 301;
	_body = "<html><head><title>301 Moved Permanently</title></head><body><h1>301 Moved Permanently</h1><p>The document has moved <a href=\"" + _location + "\">here</a>.</p></body></html>";
	std::string reponse = "HTTP/1.1 " + std::to_string(_status) + " Moved Permanently\r\n";
	reponse += "Location: " + _location + "\r\n";
	reponse += "Content-Length: " + intToString(_body.size()) + "\r\n";
	reponse += "Content-Type: text/html\r\n";
	reponse += "\r\n";
	reponse += _body;
	if (send(_client_fd, reponse.c_str(), reponse.size(), 0) == 0)
		std::cerr << "send failed" << std::endl;
}

reponse::reponse(request &request, server &serv, int& client_fd, size_t bytes_rec)
		: _status(0), _body(""), _contentLength(0), _request(request), _serv(serv), _client_fd(client_fd), _bytes_rec(bytes_rec){
	_killClient = 0;
	if (_bytes_rec > static_cast<size_t>(_serv.getMaxRequestBody())) {
		_status = 413;
	}
	else {
		std::string tmp = _request.getUri();
		size_t pos = tmp.find("?");
		_formGetRequest = "";
		if (pos != std::string::npos) {
			_formGetRequest = tmp.substr(pos + 1);
			tmp = tmp.substr(0, pos);
			_url = tmp;
		}
		else
			_url = tmp;
		_location = _serv.getNameOfLocationBAsedOnURL(tmp);
		if (_location != "" && _serv.getRedirrectLocation(_location) != "") {
			sendRedirrect();
			return ;
		}
		std::cerr << "location is : " << _location << std::endl;
		_autoindex = false;
		if (!_serv.isAutoIndexOnInLoc(_location)) {
			if (_serv.isAutoIndexOnInGen())
				_autoindex = true;
		}
		else
			_autoindex = true;
		isDirAndFile();
		tmp.substr(0, 1);
		if (_request.getMethod() == "GET") {
			getMethod();
		}
		else if (_request.getMethod() == "POST") {
			postMethod();
		}
		else if (_request.getMethod() == "DELETE")
			deleteMethod();
		else
			_status = 405;
	}
	if (_status != 200)
		_body = errorPage();
	_contentLength = _body.size();
	std::string reponse = "HTTP/1.1 " + std::to_string(_status) + " OK\r\n";
	reponse += "Content-Length: " + intToString(_contentLength) + "\r\n";
	reponse += "Content-Type: text/html\r\n";
	reponse += "Connection: keep-alive\r\n";
	reponse += "\r\n";
	reponse += _body;
	if (send(_client_fd, reponse.c_str(), reponse.size(), 0) == 0){
		std::cerr << "send failed" << std::endl;
		_killClient = 1;
	}
}

reponse::~reponse() {
}

std::string reponse::autoIndex(){
	std::stringstream autoIndex;

	autoIndex << "<!DOCTYPE html>\n";
	autoIndex << "<html lang=\"en\">\n";
	autoIndex << "<head>\n";
	autoIndex << "<meta charset=\"UTF-8\">\n";
	autoIndex << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
	autoIndex << "<title>Document</title>\n";
	autoIndex << "</head>\n";
	autoIndex << "<body>\n";
	autoIndex << "<h1>Auto Index</h1>\n";
	autoIndex << "</br>\n";
	autoIndex << "</br>\n";
	autoIndex << "</br>\n";
	autoIndex << "<h2>Page avaible</h2>\n";
	DIR* dir = opendir(_url.c_str());
	if (!dir)
		return "";
	struct dirent* data_dir;

	while ((data_dir = readdir(dir))) {
		char* tmp = data_dir->d_name;
		std::string dName = tmp;
		if (dName == "..")
			autoIndex << "<a href=\"..\">" << data_dir->d_name << "</a><br>\n";
		else if (dName == ".")
			autoIndex << "<a href=\"" << _request.getUri() << "\">" << data_dir->d_name << "</a><br>\n";
		else
			autoIndex << "<a href=\"" << _request.getUri() << "/" << data_dir->d_name << "\">" << data_dir->d_name << "</a><br>\n";
	}

	autoIndex << "</body>";
	autoIndex << "</html>";
	closedir(dir);
	return autoIndex.str();
}

std::string reponse::errorPage() {
	std::string body;
	std::string errorPage;
	if ((errorPage = _serv.getErrorAndPages(_status, _location)) == "") {
		std::cerr << "Errorsss " << _status << std::endl;
		body = "Error ";
		body += std::to_string(_status);
	}
	else {
		errorPage = errorPage.substr(0, errorPage.size() - 1);
		std::ifstream file(errorPage);
		std::string line;
		while (getline(file, line)) {
			body += line;
			body += "\n";
		}
	}
	return body;
}

void reponse::deleteMethod() {

	if (_serv.getAllowedMethod("DELETE", _location) == false && _location != "") {
		_status = 405;
		return;
	}
	size_t pos = _url.find_last_of("www");
	pos += 1;
	size_t pos2 = _url.find_last_of("/");
	std::string tmp = _url.substr(0, pos) + "/cgiFile/upload" + _url.substr(pos2);
	if (std::remove(tmp.c_str()) != 0) {
		std::cerr << "Error deleting file" << std::endl;
		_status = 404;
	}
	else {
		std::cout << "File successfully deleted" << std::endl;
		_status = 200;
	}
}

void reponse::postMethod() {
	if (_serv.getAllowedMethod("POST", _location) == false && _location != "") {
		_status = 405;
		return;
	}
	size_t buffersize = 100000;
	char buffer[buffersize + 1];
	size_t bytes_rec = 0;
	if ((bytes_rec = recv(_client_fd, buffer, buffersize, 0)) > 0 && bytes_rec != std::string::npos) {
		buffer[bytes_rec] = '\0';
		_bytes_rec += bytes_rec;
		if (_bytes_rec > static_cast<size_t>(_serv.getMaxRequestBody())) {
			_status = 413;
			return;
		}
		std::string tmp = buffer;
		_request.putInBody(tmp);
	}
	executeCgi(*this, _url);
	if (_status == 0)
		_status = 504;
}

void reponse::getMethod() {
	if (_serv.getAllowedMethod("GET", _location) == false && _location != "") {
		_status = 405;
		return;
	}
	std::vector <std::string> index = _serv.getIndexOfLocation(_location);
	if (_isDir == true && index.size() > 0) {
		struct stat filestat;
		for (size_t i = 0; i < index.size(); i++) {
			std::string tmp = _url;
			if (tmp[tmp.size() - 1] != '/')
				tmp += "/";
			tmp += index[i];
			if (stat(tmp.c_str(), &filestat) == 0) {
				if (S_ISREG(filestat.st_mode)) {
					_url = tmp;
					_isDir = false;
					_isFile = true;
					break;
				}
			}
		}
	}
	if (_isDir == true) {
		if (_autoindex == true) {
			_body = autoIndex();
			_status = 200;
		}
		else {
			_status = 403;
		}
	}
	else if (_isFile == true) {
		if (_formGetRequest != "") {
			executeCgi(*this, _url);
			return ;
		}
		std::ifstream file(_url.c_str());
		if (file.is_open()) {
			std::string line;
			while (getline(file, line)) {
				_body += line;
				_body += "\n";
			}
			_status = 200;
		}
		else {
			_status = 404;
		}
	}
	else {
		_status = 404;
	}
}
