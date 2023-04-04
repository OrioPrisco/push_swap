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
					vector4.c\
					order.c\
					sort3.c\
					debug.c\
					env.c\
					split.c\
					split_op.c\
					split_strats.c\
					translate.c\
					execute.c\
					sort.c\
					unrotate.c\
					cancel.c\
					merge.c\
					best.c\
					sub_stacks.c\
					mod.c\

BONUS_SRC		=	vector.c\
					vector2.c\
					vector3.c\
					vector4.c\
					execute.c\
					env.c\
					checker.c\

NAME			=	push_swap
BONUS			=	checker

OBJ_FOLDER		=	objs/

CFLAGS			=	-Wall -Wextra -Werror -g -D OUTPUT_DBG=0

SRC_FOLDER		=	srcs/

HEADERS_FOLDER	=	includes/\
					minilibx-linux/\
					libft/includes/\

LIBS			=	libft/libft.a\
					libft/libftprintf.a\
					libft/libgetnextline.a\

LFLAGS			=	-lftprintf -Llibft -lft -lgetnextline

DEPENDS		:=	$(patsubst %.c,$(OBJ_FOLDER)%.d,$(SRC) $(BONUS_SRC))
OBJS		:=	$(patsubst %.c,$(OBJ_FOLDER)%.o,$(SRC))
BONUS_OBJS	:=	$(patsubst %.c,$(OBJ_FOLDER)%.o,$(BONUS_SRC))
COMMANDS	:=	$(patsubst %.c,$(OBJ_FOLDER)%.cc,$(SRC) $(BONUS_SRC))

all: $(NAME) compile_commands.json

-include $(DEPENDS)

bonus: $(BONUS) compile_commands.json

$(BONUS) : $(BONUS_OBJS) $(LIBS)
	cc $(CFLAGS) $(BONUS_OBJS) $(LFLAGS) -o $@

%.a:
	make -C $(@D)

$(NAME): $(OBJS) $(LIBS)
	cc $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

COMP_COMMAND = $(CC) -c $(CFLAGS) $(addprefix -I,$(HEADERS_FOLDER)) -MMD -MP $< -o $@
CONCAT = awk 'FNR==1 && NR!=1 {print ","}{print}'

$(OBJ_FOLDER)%.o $(OBJ_FOLDER)%.cc: $(SRC_FOLDER)%.c Makefile
	$(COMP_COMMAND)
	printf '{\n\t"directory" : "$(shell pwd)",\n\t"command" : "$(COMP_COMMAND)",\n\t"file" : "$<"\n}' > $(OBJ_FOLDER)$*.cc

compile_commands.json : $(COMMANDS) Makefile
	echo "[" > compile_commands.json
	$(CONCAT) $(COMMANDS) >> compile_commands.json
	echo "]" >> compile_commands.json

clean:
	rm -f $(OBJS) $(BONUS_OBJS) $(DEPENDS) $(COMMANDS)
	for lib in $(shell dirname $(LIBS)); do \
		make -C $$lib clean; \
	done


fclean: clean
	rm -f $(NAME) $(BONUS) compile_commands.json
	make -C libft fclean

re: fclean all
	
.PHONY: all clean fclean re bonus
.SUFFIXES:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
