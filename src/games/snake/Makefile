GPP		=	g++

NAME	=	lib_arcade_snake.so

SRC		=	GUI.cpp \
				Layer.cpp \
				Map.cpp	\
				Game.cpp \
				Tile.cpp \
				../../../includes/Color.cpp

GAMESDIR	=	../../../

OBJ 	    =	$(SRC:.cpp=.o)

CXXFLAGS    =   -std=c++14

CXXFLAGS    +=  -W -Wall -Wextra -Werror -fPIC

CXXFLAGS    +=  -I../../../includes

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
