# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twitting <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:23:06 by twitting          #+#    #+#              #
#    Updated: 2019/02/13 14:27:09 by twitting         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC = ./fractol_src/julia.c \
	  ./fractol_src/main.c \
	  ./fractol_src/mandelbrot.c \
	  ./fractol_src/tricorn.c \
	  ./fractol_src/userinput.c \
	  ./fractol_src/color.c
SRC2 = ./libft/libft.a
OBJECTS = julia.o \
		  main.o \
		  mandelbrot.o \
		  tricorn.o \
		  userinput.o \
		  color.o
FLAGS = -Wall -Wextra -Werror
FLAGS2 = -Iincludes/ -I /usr/local/include -L /usr/local/lib -lmlx -lpthread -framework OpenGL -framework AppKit
FLAGS_LINUX = -I ./includes_linux/ /usr/X11/lib/libmlx.a  -lXext -lX11 -lm -lpthread

all: $(NAME)

linux:
	make re -C libft/
	sudo gcc $(FLAGS) $(SRC) $(SRC2) $(FLAGS_LINUX) -o $(NAME)

$(NAME):
	make re -C libft/
	gcc $(FLAGS) $(SRC) -Iincludes/ -c
	gcc $(FLAGS) $(FLAGS2) $(OBJECTS) $(SRC2) -o $(NAME)

clean:
	make clean -C libft/
	/bin/rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft/
	/bin/rm -f $(NAME)

re: fclean all

re_linux: fclean linux
