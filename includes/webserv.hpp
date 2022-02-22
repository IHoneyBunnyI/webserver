#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <poll.h>
#define RED "\033[38:5:9m"
#define GREEN "\033[38:5:40m"
#define BLUE "\033[38:5:26m"
#define YELLOW "\033[38:5:214m"
#define PURPLE "\033[38:5:93m"
#define WHITE "\033[0m"

void log(std::string);
int fatal(void);
std::string send_http(std::string html);
std::string get_file(std::string root, std::string path);
int compress_array(pollfd *fds, int &nfds);
int create_listen_socket(int port);

#endif
