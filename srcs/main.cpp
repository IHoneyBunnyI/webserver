#include <iostream>
#include <fstream>
#include "Server.hpp"
#include "webserv.hpp"


void log(std::string message)
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

int main(int argc, char** av)
{
	std::string configFile = "webserv.conf";
	if (argc != 1 && argc != 2)
		return (fatal());
	if (argc == 2)
		configFile = av[1];
	Server server(configFile);
	server.getParser().parseConfig(); // MARIA
	server.start(); // POGNALI
}
