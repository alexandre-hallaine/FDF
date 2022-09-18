NAME	:= fdf
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/libmlx42.a -ldl -lglfw -pthread -lm
SRCDIR	:= ./src
OBJDIR	:= ./obj
SRCS	:= $(shell cd $(SRCDIR) && find . -name "*.c")
OBJS	:= $(SRCS:%.c=$(OBJDIR)/%.o)

all: libmlx $(NAME)

libmlx:
	$(MAKE) -C $(LIBMLX)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && echo "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBMLX) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBMLX) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx
.SILENT: