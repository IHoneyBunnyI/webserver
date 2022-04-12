#ifndef CORE_HPP
#define CORE_HPP
#include <iostream>
#include <vector>
#include "Parser.hpp"
#include "Server.hpp"

class Core {
public:
	Core();
	Core(Parser &parser);
private:
	std::vector<Server> Servers;
};

#endif
