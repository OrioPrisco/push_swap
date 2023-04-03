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

NAME			=	push_swap

OBJ_FOLDER		=	objs/

CFLAGS			=	-Wall -Wextra -Werror -g -D OUTPUT_DBG=0

SRC_FOLDER		=	srcs/

HEADERS_FOLDER	=	includes/\
					minilibx-linux/\
					libft/includes/\

LIBS			=	libft/libft.a\
					libft/libftprintf.a\

LFLAGS			=	-lftprintf -Llibft -lft

DEPENDS		:=	$(patsubst %.c,$(OBJ_FOLDER)%.d,$(SRC))
OBJS		:=	$(patsubst %.c,$(OBJ_FOLDER)%.o,$(SRC))
COMMANDS	:=	$(patsubst %.c,$(OBJ_FOLDER)%.cc,$(SRC))

all: $(NAME) compile_commands.json

-include $(DEPENDS)

bonus: all

%.a:
	make -C $(@D)

$(NAME): $(OBJS) $(LIBS)
	cc $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

COMP_COMMAND = $(CC) -c $(CFLAGS) $(addprefix -I,$(HEADERS_FOLDER)) -MMD -MP $< -o $@
CONCAT = awk 'FNR==1 && NR!=1 {print ","}{print}'

$(OBJ_FOLDER)%.o : $(SRC_FOLDER)%.c Makefile
	$(COMP_COMMAND)
	printf '{\n\t"directory" : "$(shell pwd)",\n\t"command" : "$(COMP_COMMAND)",\n\t"file" : "$<"\n}' > $(OBJ_FOLDER)$*.cc

#cc files are created when compiling objects
$(OBJ_FOLDER)%.cc : $(OBJ_FOLDER)%.o

compile_commands.json : $(COMMANDS) Makefile
	echo "[" > compile_commands.json
	$(CONCAT) $(COMMANDS) >> compile_commands.json
	echo "]" >> compile_commands.json

clean:
	rm -f $(OBJS) $(DEPENDS) $(COMMANDS) compile_commands.json
	for lib in $(shell dirname $(LIBS)); do \
		make -C $$lib clean; \
	done


fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
	
.PHONY: all clean fclean re bonus
.SUFFIXES:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
