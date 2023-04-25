NAME := fdf

CC := cc

# @TODO rm -g3 and -pg
FLAGS := -Wall -Werror -Wextra -MMD -g3
# -O3  -march=native
SOURCES_DIR := sources/
BINARIES_DIR := build/
INCLUDES_DIR := includes/
LIBRARIES_DIR := lib/

INCLUDES := -I$(INCLUDES_DIR) -I/usr/include -I$(LIBRARIES_DIR)minilibx-linux -I$(LIBRARIES_DIR)libft -I$(LIBRARIES_DIR)renderer/includes

LIBRARIES := -L$(LIBRARIES_DIR)renderer -lfdf_renderer -L$(LIBRARIES_DIR)minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -L$(LIBRARIES_DIR)libft -lft

OBJ := main.o \
	queue.o \
	inputs_hooks.o \
	inputs_ticks.o \
	tick.o \
	map.o \
	map_parsing.o \
	map_transformation.o \
	error.o \
	colors.o \
	map_utils.o \

OBJ := $(addprefix $(BINARIES_DIR),$(OBJ))

DEPS := ${OBJ:.o=.d}

RM := rm -f

$(NAME) : $(OBJ)
	make -C $(LIBRARIES_DIR)renderer
	make -C $(LIBRARIES_DIR)libft
	make -C $(LIBRARIES_DIR)minilibx-linux
	$(CC) $(OBJ) $(LIBRARIES) -o $(NAME)

bonus : $(NAME)

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

-include $(DEPS)
