GPP		=	g++

NAME	=	lib_arcade_snake.so

SRC		=	Food.cpp \
				GUI.cpp \
				Game.cpp \
				Layer.cpp \
				Map.cpp	\
				SnakePart.cpp \
				Tile.cpp \
				../../Color.cpp

GAMESDIR	=	../../../resources/games/

OBJ 	    =	$(SRC:.cpp=.o)

CXXFLAGS    =   -std=c++14

CXXFLAGS    +=  -W -Wall -Wextra -Werror -fPIC

CXXFLAGS    +=  -I../../../includes/common -I../../../includes -I../../../includes/games/snake

LDFLAGS			=	-shared

$(NAME):	$(OBJ)
		    $(GPP) -o $(NAME) $(OBJ) $(LDFLAGS)
				mv $(NAME) $(GAMESDIR)

all:		$(NAME)

clean:
				$(RM)	$(OBJ)

fclean:	clean
				$(RM) $(GAMESDIR)$(NAME)

re:			fclean all
