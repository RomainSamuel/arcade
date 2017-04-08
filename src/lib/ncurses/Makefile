GPP		=	g++

NAME		=	lib_arcade_ncurses.so

SRC		=	ncurses.cpp			\
                        ../../common/SoundManager.cpp

GAMESDIR	=	../../../lib/

OBJ 	    	=	$(SRC:.cpp=.o)

CXXFLAGS    	=  	-std=c++14

CXXFLAGS    	+=  	-W -Wall -Wextra -Werror -fPIC

CXXFLAGS    	+=  	-I../../../includes/lib/ncurses -I../../../includes -I../../../includes/common

LDFLAGS		=	-lncurses -lopenal -lsndfile

LDFLAGS		+=	-shared

$(NAME):	$(OBJ)
		$(GPP) -o $(NAME) $(OBJ) $(LDFLAGS)
		mv $(NAME) $(GAMESDIR)

all:		$(NAME)

clean:
		$(RM)	$(OBJ)

fclean:	clean
		$(RM) $(GAMESDIR)$(NAME)

re:		fclean all
