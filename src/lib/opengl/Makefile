GPP		=	g++

NAME	=	lib_arcade_opengl.so

SRC		=	glMain.cpp			\
			../../common/SoundManager.cpp

GAMESDIR	=	../../../lib/

OBJ 	    =	$(SRC:.cpp=.o)

CXXFLAGS    =   -std=c++14

CXXFLAGS    +=  -W -Wall -Wextra -Werror -fPIC

CXXFLAGS    +=  -I./ -I../../../includes/common -I../../../includes/lib/opengl -I../../../includes/games/common

LDFLAGS		=	-lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lopenal -lsndfile -lSOIL

LDFLAGS		+=	-shared

$(NAME):	$(OBJ)
		    $(GPP) -o $(NAME) $(OBJ) $(LDFLAGS)
				mv $(NAME) $(GAMESDIR)

all:		$(NAME)

clean:
				$(RM)	$(OBJ)

fclean:	clean
				$(RM) $(GAMESDIR)$(NAME)

re:			fclean all
