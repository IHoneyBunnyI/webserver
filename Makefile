NAME = webserver
OBJDIR = objs/

CXX = clang++

INCLUDES = -Iincludes/

CXXFLAGS = -Wall -Wextra -Werror $(INCLUDES)

CPP_FILES = main.cpp\


HPP_FILES = Server.hpp\

O_FILES = $(addprefix objs/, $(CPP_FILES))
SRCS = $(addprefix srcs/, $(CPP_FILES))
HEADERS = $(addprefix includes/, $(HPP_FILES))
OBJS = $(O_FILES:.cpp=.o)

all: $(OBJDIR) $(NAME)

objs/%.o : srcs/%.cpp Makefile $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir $(OBJDIR)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(OBJDIR)

re: fclean all
