# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/04 21:07:25 by tborges-          #+#    #+#              #
#    Updated: 2025/10/05 22:30:38 by tborges-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ex03

CXX = @c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

SRCS = main.cpp \
	Bureaucrat.cpp \
	AForm.cpp \
	Intern.cpp \
	ShrubberyCreationForm.cpp \
	RobotomyRequestForm.cpp \
	PresidentialPardonForm.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)
	@echo $(NAME) compiled!

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

DEPS = $(wildcard *.hpp)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f *_shrubbery

re: fclean all

.PHONY: all clean fclean re
