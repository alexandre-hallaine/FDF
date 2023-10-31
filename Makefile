NAME	:= fdf
CFLAGS	:= -Wall -Wextra -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= $(shell find src -type f -name "*.c")
OBJS	:= $(SRCS:src/%.c=obj/%.o)

all: libmlx $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4

obj/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && echo "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && echo "Linked: $(NAME)"

clean:
	rm -rf $(OBJS) && echo "Removed: $(OBJS)"
	rm -rf $(LIBMLX)/build && echo "Removed: $(LIBMLX)/build"

fclean: clean
	rm -rf $(NAME) && echo "Removed: $(NAME)"

re: clean all

.PHONY: all, clean, fclean, re, libmlx
.SILENT:
