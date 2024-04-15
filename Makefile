NAME	:= fdf
CFLAGS	:= -Wall -Wextra -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42
LIBGNL	:= ./lib/get_next_line

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBGNL)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBGNL)/libgnl.a
SRCS	:= $(shell find src -type f -name "*.c")
OBJS	:= $(SRCS:src/%.c=obj/%.o)

all: libmlx libgnl $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build
	cmake --build $(LIBMLX)/build -j4

libgnl:
	make -C $(LIBGNL)

obj/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && echo "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && echo "Linked: $(NAME)"

clean:
	rm -rf $(OBJS) && echo "Removed: $(OBJS)"
	rm -rf $(LIBMLX)/build && echo "Removed: $(LIBMLX)/build"
	make -C $(LIBGNL) clean

fclean: clean
	rm -rf $(NAME) && echo "Removed: $(NAME)"

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libgnl
.SILENT:
