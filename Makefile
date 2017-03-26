##
## Author: Marwane Khsime
## Date: 2017-03-21 21:26:49
##
## Last Modified by:   Marwane Khsime
## Last Modified time: 2017-03-21 21:26:49
##

# name of the projet
NAME   = arcade

# config
DEBUG 		= no
# if display_opt is set to "percentage", shows the progress of the compilation in percentage, else use the index.
DISPLAY_OPT	= percentage

# utils
COUNT 		= 1
NBSOURCES 	= $(shell find src/ -type f -name '*.cpp' | wc -l)
PERCENT		= 0
NBSOURCES	= $(shell find src/ -type f -name '*.cpp' | wc -l)
DISPLAY_ONE	= "[\033[95m$(PERCENT)%\033[0m][\033[92m$<\033[0m]"
DISPLAY_TWO	= "[\033[95m$(COUNT)\033[0m/\033[93m$(NBSOURCES)\033[0m][\033[92m$<\033[0m]"
COMPILATION_MSG	= $(DISPLAY_TWO)

# compiler
CXX		= g++

# compiling flags here
CXXFLAGS	= -W -Wall -Wextra -Werror -std=c++14 -I./includes/ -O2

# if debug is set to yes, add -g3 flag
ifeq ($(DEBUG),yes)
	CXXFLAGS += -g3
endif

# Set the compilation message
ifeq ($(DISPLAY_OPT), percentage)
        COMPILATION_MSG=$(DISPLAY_ONE)
endif

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = .

# Sources, Includes and Objects
SOURCES  := 		$(wildcard $(SRCDIR)/*.cpp)
SOURCES  +=         $(wildcard $(SRCDIR)/core/*.cpp)
SOURCES  +=         $(wildcard $(SRCDIR)/menu/*.cpp)
SOURCES  +=         $(wildcard includes/*.cpp)
INCLUDES :=			$(wildcard $(SRCDIR)/*.h)
OBJECTS  := 		$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
RM 	      = 		rm -rf

$(BINDIR)/$(NAME):	$(OBJECTS)
					@$(CXX) -o $@ $(CXXFLAGS) $(OBJECTS)
					@echo "\033[94mProject $(NAME) build successfully!\033[0m"

$(OBJECTS):			$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
				@mkdir -p $(dir $@)
				@$(CXX) $(CXXFLAGS) -c $< -o $@
				@$(eval PERCENT=$(shell echo $$((($(COUNT)*100/$(NBSOURCES))))))
	                        @echo $(COMPILATION_MSG)
				@$(eval COUNT=$(shell echo $$((($(COUNT)+1)))))

.PHONY: 			clean fclean re

clean:
					@$(RM) $(OBJDIR)
					@echo "\033[93mCleanup complete!\033[0m"

fclean: 			clean
					@$(RM) $(BINDIR)/$(NAME) $(LIBNAME)
					@echo "\033[93mExecutable removed!\033[0m"

re:					fclean $(BINDIR)/$(NAME)
