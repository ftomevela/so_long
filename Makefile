# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 12:49:29 by ftome-ve          #+#    #+#              #
#    Updated: 2024/06/25 15:37:14 by ftome-ve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= clang
LIBC	= ar rcs
CFLAGS	= -Wall -Wextra -Werror -Imlx
LDFLAGS	= -Lmlx -lmlx_Linux -lX11 -lXext -lbsd
RM	= rm -f

NAME	= so_long
BONUS_NAME	= so_long_bonus
SRCS	= main.c checks.c error_control.c get_next_line.c \
	get_next_line_utils.c graphics.c graphics_utils.c gravity_jump.c \
	load_map.c movements.c movements_utils.c so_long_utils.c

BONUS_SRCS = main_bonus.c checks_bonus.c error_control_bonus.c \
	get_next_line_bonus.c get_next_line_utils_bonus.c graphics_bonus.c \
	graphics_utils_bonus.c gravity_jump_bonus.c load_map_bonus.c \
	movements_bonus.c movements_utils_bonus.c so_long_utils_bonus.c


OBJS	= $(SRCS:.c=.o)

BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@chmod +x $(NAME)
	@echo "Executable $(NAME) created."

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME) $(LDFLAGS)
	@chmod +x $(BONUS_NAME)
	@echo "Executable $(BONUS_NAME) created."

bonus: $(BONUS_NAME)
	
clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "Object files cleaned."

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "Executable $(NAME) cleaned."

re: fclean all

.PHONY: all .c.o clean fclean re bonus