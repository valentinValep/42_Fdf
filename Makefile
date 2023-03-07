NAME := fdf

CC := cc

# @TODO rm -g3 and -pg
FLAGS := -Wall -Werror -Wextra -g3

SOURCES_DIR := sources/
BINARIES_DIR := build/
INCLUDES_DIR := includes/
LIBRARIES_DIR := lib/

INCLUDES := -I$(INCLUDES_DIR) -I/usr/include -I$(LIBRARIES_DIR)minilibx-linux -I$(LIBRARIES_DIR)libft -I$(LIBRARIES_DIR)renderer/includes

LIBRARIES := -L$(LIBRARIES_DIR)renderer -lfdf_renderer -L$(LIBRARIES_DIR)minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -L$(LIBRARIES_DIR)libft -lft

SRC := main.c \
	queue.c \
	inputs.c \
	tick.c \
	map.c \
	map_parsing.c \
	map_transformation.c \
	error.c \

OBJ := $(SRC:.c=.o)

SRC := $(addprefix $(SOURCES_DIR),$(SRC))
OBJ := $(addprefix $(BINARIES_DIR),$(OBJ))

RM := rm -f

$(NAME) : $(OBJ)
	make -C $(LIBRARIES_DIR)renderer
	make -C $(LIBRARIES_DIR)libft
	make -C $(LIBRARIES_DIR)minilibx-linux
	$(CC) $(OBJ) $(LIBRARIES) -o $(NAME)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)
# @TODO use .d dependencies
$(BINARIES_DIR)%.o : $(SOURCES_DIR)%.c | $(BINARIES_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

all : $(NAME)

clean :
	make -C $(LIBRARIES_DIR)renderer clean
	make -C $(LIBRARIES_DIR)libft clean
	make -C $(LIBRARIES_DIR)minilibx-linux clean
	$(RM) $(OBJ)

fclean : clean
	make -C $(LIBRARIES_DIR)renderer fclean
	make -C $(LIBRARIES_DIR)libft fclean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
