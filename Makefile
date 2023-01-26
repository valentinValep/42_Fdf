NAME := fdf

CC := cc

FLAGS := -Wall -Werror -Wextra

SOURCES_DIR := sources/
BINARIES_DIR := build/
INCLUDES_DIR := includes/
LIBRARIES_DIR := lib/

INCLUDES := -I$(INCLUDES_DIR) -I/usr/include -I$(LIBRARIES_DIR)minilibx-linux -I$(LIBRARIES_DIR)libft

LIBRARIES := -L$(LIBRARIES_DIR)minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -L$(LIBRARIES_DIR)libft -lft

SRC := main.c \
	app.c \
	map.c \
	geometric.c

OBJ := $(SRC:.c=.o)

SRC := $(addprefix $(SOURCES_DIR),$(SRC))
OBJ := $(addprefix $(BINARIES_DIR),$(OBJ))

RM := rm -f

$(NAME) : $(OBJ)
	make -C $(LIBRARIES_DIR)libft
	make -C $(LIBRARIES_DIR)minilibx-linux
	$(CC) $(OBJ) $(LIBRARIES) -o $(NAME)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)
# @TODO rm -g3
# @TODO use .d dependencies instead of "$(INCLUDES_DIR)fdf.h"
$(BINARIES_DIR)%.o : $(SOURCES_DIR)%.c $(INCLUDES_DIR)fdf.h | $(BINARIES_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ -g3

all : $(NAME)

clean :
	make -C $(LIBRARIES_DIR)libft clean
	make -C $(LIBRARIES_DIR)minilibx-linux clean
	$(RM) $(OBJ)

fclean : clean
	make -C $(LIBRARIES_DIR)libft fclean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
