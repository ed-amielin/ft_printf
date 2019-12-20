#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/03 22:21:07 by eamielin          #+#    #+#              #
#    Updated: 2018/11/03 22:21:08 by eamielin         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

SRC_DIR		= ./src/
OBJ_DIR		= ./obj/
LIB_DIR		= ./lib/
SRC_INC_DIR	= $(SRC_DIR)
HEAD_FILE	= $(SRC_INC_DIR)ft_printf.h

C_FILES		= ft_printf.c \
			init.c \
			spec_d.c \
			spec_s.c \
			spec_c.c \
			spec_f.c \
			spec_ou.c \
			spec_x.c \
			spec_ap_unspec.c \
			get_nbr.c \
			text_swap_utf.c \
			specifier.c

O_FILES		= $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

LIBFT_DIR	= $(LIB_DIR)libft/
LIBFT_INC_DIR	= $(LIBFT_DIR)
LIBFT		= $(LIBFT_DIR)libft.a
COPIED_LIBFT	= ./libftprintf.a
LIBFT_FLAGS	= -lft -L $(LIBFT_DIR)

FLAGS		= -Wall -Werror -Wextra
HEADER_FLAGS	= -I $(SRC_INC_DIR) -I $(LIBFT_INC_DIR)

LINK_FLAGS	= $(LIBFT_FLAGS)


all: $(NAME)

$(NAME): $(LIBFT) $(O_FILES)
		cp $(LIBFT) ./libftprintf.a
		ar rc $(NAME) $(O_FILES)
		ranlib $(NAME)


$(O_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEAD_FILE)
		gcc -c $< -o $@ $(FLAGS) $(HEADER_FLAGS)

$(LIBFT):
		make -C $(LIBFT_DIR)

clean:
	rm -f $(O_FILES)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -Rf $(OBJ_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all
