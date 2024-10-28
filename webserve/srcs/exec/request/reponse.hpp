#ifndef REPONSE_HPP
# define REPONSE_HPP

#include "../../../includes/principal.hpp"
#include "request.hpp"
#include "../../parsing/server/server.hpp"

class reponse {
	protected:
		int 		_status;
		std::string _body;
		int			_contentLength;
		request& 	_request;
		server&		_serv;
		int			_client_fd;
		std::string _location;
		bool		_autoindex;
		bool		_isDir;
		bool		_isFile;
		std::string _url;
		std::string	_root;
		size_t		_bytes_rec;
		std::string _formGetRequest;
		int			_killClient;

	public:
		reponse(request &request, server &serv, int& client_fd, size_t bytes_rec);
		~reponse();

		std::string getFullHeader();

		void getMethod();
		void postMethod();
		void deleteMethod();
		std::string autoIndex();
		void isDirAndFile();
		std::string errorPage();
		int	getClientFd() { return _client_fd; }
		std::string getUrl() { return _url; }
		void	addBody(std::string body) { _body += body; }
		long getCgiTimeOut() { return _serv.getCgi_timeout(); }
		void	setStatus(int status) { _status = status; }
		std::string getFormQuerry() { return _formGetRequest; }
		void	sendRedirrect();
		std::string	getRequestBody() { return _request.getBody(); }
		int		getStatus() { return _status; }
		int		getKillClient() { return _killClient; }
};

#endif