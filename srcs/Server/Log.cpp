#include "Server.hpp"
#include <fstream>

void Server::Log(std::string message)
{
	std::ofstream logfile("logs.webserv", std::ios::app | std::ios::ate);
	if (!logfile)
	{
		std::cout << "error open logs.webserv!" << std::endl;
		exit (1);
	}

	std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
	time_t	tt = std::chrono::system_clock::to_time_t(time_point);
	tm local_tm = *localtime(&tt);

	logfile << std::put_time(&local_tm, "[%H:%M:%S %d-%m-%Y] ");
	logfile << message << std::endl;

	logfile.close();
}
