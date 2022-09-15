NAME			=	fdf

SOURCE_FOLDER	=	./src
SOURCES			=	main.c

OBJECT_FOLDER	=	./obj
OBJECTS			=	$(SOURCES:%.c=$(OBJECT_FOLDER)/%.o)

INCLUDE_FOLDER	=	./include
INCLUDES		=	

COMPILER		=	gcc

COMPILER_FLAGS	=	-I$(INCLUDE_FOLDER)
COMPILER_FLAGS	+=	-Wall -Wextra -Werror
# COMPILER_FLAGS	+=	-g3

FLAGS			=	test_maps/42.fdf

MLX				=	minilibx-linux

all: $(NAME)

mlx:
	make -C $(MLX)

$(OBJECT_FOLDER):
	mkdir -p $@

$(OBJECT_FOLDER)/%.o: $(SOURCE_FOLDER)/%.c $(INCLUDES:%.h=$(INCLUDE_FOLDER)/%.h)
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

$(NAME): mlx $(OBJECT_FOLDER) $(OBJECTS)
	$(COMPILER) -o $@ $(OBJECTS) -L$(MLX) -lmlx -lXext -lX11

clean:
	rm -rf $(OBJECT_FOLDER)

fclean: clean
	rm -rf $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME) $(FLAGS)

valgrind:
	valgrind --leak-check=full --show-reachable=yes make run

.PHONY: all clean fclean re run