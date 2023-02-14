# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 15:27:59 by OrioPrisc         #+#    #+#              #
#    Updated: 2023/01/18 17:15:24 by OrioPrisc        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc

SRC				=	main.c\
					vector.c\
					vector2.c\
					vector3.c\
					order.c\
					sort3.c\
					debug.c\
					env.c\
					split.c\
					translate.c\
					execute.c\
					sort.c\
					unrotate.c\
					cancel.c\
					merge.c\
					best.c\

NAME			=	push_swap

OBJ_FOLDER		=	objs/

CFLAGS			=	-Wall -Wextra -Werror -g

SRC_FOLDER		=	srcs/

HEADERS_FOLDER	=	includes/\
					minilibx-linux/\
					libft/includes/\

LIBS			=	libft/libft.a\
					libft/libftprintf.a\

LFLAGS			=	-lftprintf -Llibft -lft

DEPENDS		:=	$(patsubst %.c,$(OBJ_FOLDER)%.d,$(SRC))
OBJS		:=	$(patsubst %.c,$(OBJ_FOLDER)%.o,$(SRC))

all: $(NAME)

-include $(DEPENDS)

bonus: all

%.a:
	make -C $(@D)

$(NAME): $(OBJS) $(LIBS)
	cc $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

$(OBJ_FOLDER)%.o : $(SRC_FOLDER)%.c Makefile
	$(CC) -c $(CFLAGS) $(addprefix -I,$(HEADERS_FOLDER)) -MMD -MP $< -o $@

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) $(DEPENDS)
	for lib in $(shell dirname $(LIBS)); do \
		make -C $$lib clean; \
	done


fclean: clean
	rm -f client server
	make -C libft fclean

re: fclean all
	
.PHONY: all clean fclean re bonus
.SUFFIXES:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
