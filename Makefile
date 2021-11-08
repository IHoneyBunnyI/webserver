NAME = webserver

CPP_FILES = main.cpp\


HPP_FILES = Server.hpp\

SRCS = $(addprefix srcs/, $CPP_FILES)
HEADERS = $(addprefix includes/, $HPP_FILES)

