GPP		=	g++

NAME	=	lib_arcade_centipede

COMMON	=	../../common/

GAME_COMMON	=	../common/

SRC		=	$(COMMON)Color.cpp \
				$(GAME_COMMON)Component.cpp \
				$(GAME_COMMON)GUI.cpp \
				$(GAME_COMMON)Tile.cpp \
				CentipedeGame.cpp \
				CentipedePart.cpp \
				Map.cpp	\
				main.cpp

GAMESDIR	=	../../../games/

OBJ 	    =	$(SRC:.cpp=.o)

CXXFLAGS    =   -std=c++14

CXXFLAGS    +=  -W -Wall -Wextra -fPIC -g

CXXFLAGS    +=  -I../../../includes/common \
								-I../../../includes \
								-I../../../includes/games/common \
								-I../../../includes/games/centipede

LDFLAGS			=	-shared

$(NAME):	$(OBJ)
		    $(GPP) -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
				$(RM)	$(OBJ)

fclean:	clean
				$(RM) $(GAMESDIR)$(NAME)

re:			fclean all
