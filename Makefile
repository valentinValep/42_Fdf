# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/21 02:24:43 by marvin            #+#    #+#              #
#    Updated: 2022/12/21 09:10:30 by vlepille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fdf

CC := cc

FLAGS := -Wall -Werror -Wextra

INCLUDES := -Isources -I/usr/include -Iminilibx-linux -Ilibft

LIBRARIES := -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -Llibft -lft

SOURCES_DIR := sources

BINARIES_DIR := binaries

SRC := main.c \
	app.c

OBJ := $(SRC:.c=.o)

SRC := $(addprefix $(SOURCES_DIR)/,$(SRC))
OBJ := $(addprefix $(BINARIES_DIR)/,$(OBJ))

RM := rm -f

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(LIBRARIES) -o $(NAME)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)
# @TODO rm -g3
$(BINARIES_DIR)/%.o : $(SOURCES_DIR)/%.c $(SOURCES_DIR)/fdf.h | $(BINARIES_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ -g3

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
