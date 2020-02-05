# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/06/25 16:00:03 by calin        #+#   ##    ##    #+#        #
#    Updated: 2020/02/04 17:24:40 by mwaterso    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = doom

SRCS = ./src/main.c\
			./src/math.c\
			./src/Projection.c\
			./src/trace.c\
			./src/map.c\
			./src/hooks.c\
			./src/matrix.c\
			./src/parsing/parsing_poly.c\
			./src/parsing/parsing_error.c\
			./src/parsing/parsing_list.c\
			./src/parsing/parsing_error2.c\
			./src/parsing/parsing_other.c\

OBJ = $(SRCS:%.c=%.o)

INC = doom.h

FLAGS =  -Wall -Wextra -Werror

LIBFT = libft/libft.a

LIBMLX = minilibx_macos/libmlx.a

OPENGL = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJ)
		gcc $(FLAGS) $^ $(OPENGL) -o $@ -g

%.o: %.c $(INC)
		gcc $(FLAGS) -c $< -o $@

$(LIBFT):
		make -C libft/

$(LIBMLX):
		make -C minilibx_macos/

clean:
		make clean -C libft/
		make clean -C minilibx_macos/
		rm -rf $(OBJ)

fclean: clean
		make fclean -C libft/
		rm -rf $(NAME)

re: fclean all
		make re -C minilibx_macos/

.PHONY: all clean fclean re

