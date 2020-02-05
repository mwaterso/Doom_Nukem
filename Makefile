# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2020/02/05 19:45:26 by beduroul     #+#   ##    ##    #+#        #
#    Updated: 2020/02/05 19:45:31 by beduroul    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = doom_nuken

#Color
ERASE = \033[2K\r
BLUE = \033[36m
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
END = \033[0m

#Dir
OBJ_PATH = obj
SRC_PATH = srcs
INC_PATH = ./include/

#file
SRC_NAME = 	main.c

SRC_NAME += Engine/math.c\
			Engine/Projection.c\
			Engine/trace.c\
			Engine/map.c\
			Engine/hooks.c\
			Engine/matrix.c\

SRC_NAME += Parsing/parsing_poly.c Parsing/parsing_error.c \
			Parsing/parsing_list.c Parsing/parsing_error2.c \
			Parsing/parsing_other.c

#SRC_NAME += Sound/init_s.c Sound/parsing_wav.c

# mlx library
MLX        = ./miniLibx_macos/
MLX_LIB    = $(addprefix $(MLX),libmlx.a)
MLX_INC    = -I ./miniLibx_macos
MLX_LNK    = -L ./miniLibx_macos -l mlx -framework OpenGL -framework AppKit -framework OpenAL

# ft library
FT        = ./libft/
FT_LIB    = $(addprefix $(FT),libft.a)
FT_INC    = -I ./libft
FT_LNK    = -L ./libft -l ft

CPPFLAGS = -I include -I libft/includes
LDFLAGS = -L libft
LDLIBS = libft/libft.a

SRC_SUP = {Parsing,Engine}

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

#compil
CC = gcc
CFLAGS = -Werror -Wextra -Wall -g -O3

all: lib $(MLX_LIB) $(NAME)
	@printf "$(BLUE)> $(NAME) : $(YELLOW)Project ready !$(END)\n"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(MLX_LNK) $(LDFLAGS) $(MINILIBX) $(LDLIBS) $^ -o $@
	@printf "$(ERASE)$(BLUE)> $@ : $(GREEN)Success !$(END)\n\n"
lib:
	@make -C libft

$(MLX_LIB):
	@make -C $(MLX)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c include/doom.h libft/libft.a
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH)/$(SRC_SUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf "$(ERASE)$(BLUE)> Compilation :$(END) $<"
clean:
	@make -C libft clean
	@make -C $(MLX) clean
	@rm -rf $(OBJ_PATH)
	@printf "$(BLUE)> Deleted : $(RED)$(OBJ_PATH)$(END)\n"

fclean: clean
	@make -C libft fclean
	@make -C $(MLX) fclean
	@rm -rf $(NAME)
	@printf "$(BLUE)> Deleted : $(RED)$(NAME)$(END)\n"

re: fclean all

norme:
	@norminette $(SRC) $(INC_PATH)
	
.PHONY: all, clean, fclean, re