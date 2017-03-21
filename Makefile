##
## Author: Marwane Khsime 
## Date: 2017-03-21 21:26:49 
##
## Last Modified by:   Marwane Khsime 
## Last Modified time: 2017-03-21 21:26:49
##

# name of the projet
NAME   = arcade

# utils
DEBUG 		= no
COUNT 		= 1
NBSOURCES 	= $(shell find src/ -type f -name '*.cpp' | wc -l)

# compiler
CXX		= g++

# compiling flags here
CXXFLAGS	= -W -Wall -Wextra -Werror -std=c++11 -I./include/ -O2

# if debug is set to yes, add -g3 flag
ifeq ($(DEBUG),yes)
	CXXFLAGS += -g3
endif

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = .

# Sources, Includes and Objects
SOURCES  := 		$(wildcard $(SRCDIR)/*.cpp)
INCLUDES :=			$(wildcard $(SRCDIR)/*.h)
OBJECTS  := 		$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
RM 	      = 		rm -rf

$(BINDIR)/$(NAME):	$(OBJECTS)
					@$(CXX) -o $@ $(CXXFLAGS) $(OBJECTS)
					@echo "\033[94mProject $(NAME) build successfully!\033[0m"

$(OBJECTS):			$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
					@mkdir -p $(dir $@)
					@$(CXX) $(CXXFLAGS) -c $< -o $@
					@echo "[\033[95m$(COUNT)\033[0m/\033[93m$(NBSOURCES)\033[0m][\033[92m$<\033[0m]"
					@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))

.PHONY: 			clean fclean re

clean:
					@$(RM) $(OBJDIR)
					@echo "\033[93mCleanup complete!\033[0m"

fclean: 			clean
					@$(RM) $(BINDIR)/$(NAME) $(LIBNAME)
					@echo "\033[93mExecutable removed!\033[0m"

re:					fclean $(BINDIR)/$(NAME)
