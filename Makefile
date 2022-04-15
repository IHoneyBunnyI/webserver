NAME = webserver
OBJDIR = objs/

CXX = clang++

INCLUDES = -Iincludes/

CXXFLAGS = $(INCLUDES) -Wall -Wextra -Werror -g -std=c++98 -fsanitize=address

CPP_FILES = CGI.cpp\
			HttpRequest.cpp\
			NeedCloseConnect.cpp\
			ParseRequest.cpp\
			ReadRequest.cpp\
			HttpResponse.cpp\
			Alias.cpp\
			CgiExtensions.cpp\
			CgiPath.cpp\
			Index.cpp\
			ParseLocation.cpp\
			Method.cpp\
			Root.cpp\
			UploadPass.cpp\
			Autoindex.cpp\
			Config.cpp\
			ErrorPage.cpp\
			Listen.cpp\
			MaxBodySize.cpp\
			Parser.cpp\
			ParseServer.cpp\
			ServerName.cpp\
			DELETE.cpp\
			GET.cpp\
			Log.cpp\
			POST.cpp\
			Server.cpp\
			ServerConfig.cpp\
			Start.cpp\
			main.cpp\

HPP_FILES = CGI.hpp\
			HttpRequest.hpp\
			HttpResponse.hpp\
			Parser.hpp\
			Server.hpp\
			ServerConfig.hpp\
			webserv.hpp\

O_FILES = $(addprefix objs/, $(CPP_FILES))
SRCS = $(addprefix srcs/, $(CPP_FILES))
HEADERS = $(addprefix includes/, $(HPP_FILES))
OBJS = $(O_FILES:.cpp=.o)

NB = $(words $(CPP_FILES))
INDEX = 0

VPATH = srcs/\
		srcs/CGI/\
		srcs/HttpRequest/\
		srcs/HttpRespone/\
		srcs/Parser/\
		srcs/Parser/ParseServer/\
		srcs/Parser/ParseServer/Location/\
		srcs/Server/\
		srcs/ServerConfig/\

all: $(OBJDIR) $(NAME)

objs/%.o : %.cpp Makefile $(HEADERS)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@$(eval PERCENT=$(shell expr $(INDEX) '*' 100 / $(NB)))
	@$(eval PROGRESS=$(shell expr $(INDEX) '*' 30 / $(NB)))
	@printf "\r\033[38;5;219mMAKE SERVER %2d%%\033[0m \033[48;5;129m%*s\033[0m %s\033[K" $(PERCENT) $(PROGRESS) "" $(notdir $@)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(OBJDIR):
	@mkdir $(OBJDIR)

$(NAME) : $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
	@printf "\r\033[38;5;46mDONE\033[0m\033[K\n"

clean:
	@rm -rf $(OBJS)
	@printf "\033[38;5;196mCLEAN\033[0m\n"
	@rm -rf logs.webserv

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(OBJDIR)
	@printf "\033[38;5;196mFULL CLEAN\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
