# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 00:18:59 by jgilfix           #+#    #+#              #
#    Updated: 2020/01/26 17:26:31 by jgilfix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS =======================================================================

NO_COL    =  \033[38;5;255m
LIME      =  \033[38;5;46m
RED       =  \033[38;5;196m
TEXT      =  \033[38;5;255m

# COMPILER & FLAGS =============================================================

CC        =  gcc

CFLAGS    =  -Wall \
		     -Werror \
		     -Wextra

ALLFLAGS  =   $(CFLAGS)

# VARIABLES ====================================================================

NAME      =  libft.a

BANNER    =  $(LIME)[$(TEXT)libft$(LIME)]\t\t

INC_DIR   =  include

SRC_DIR   =  src

OBJ_DIR   =  obj

_SRC      =  ft_memset.c \
		     ft_bzero.c \
		     ft_memcpy.c \
		     ft_memccpy.c \
		     ft_memmove.c \
		     ft_memchr.c \
		     ft_memcmp.c \
		     ft_memalloc.c \
		     ft_memdel.c \
             ft_strlen.c \
		     ft_strdup.c \
		     ft_strcpy.c \
		     ft_strncpy.c \
		     ft_strcat.c \
		     ft_strncat.c \
		     ft_strlcat.c \
		     ft_strchr.c \
  		     ft_strrchr.c \
		     ft_strstr.c \
		     ft_strnstr.c \
		     ft_strcmp.c \
		     ft_strncmp.c \
		     ft_strnew.c \
		     ft_strdel.c \
		     ft_strclr.c \
		     ft_striter.c \
		     ft_striteri.c \
		     ft_strmap.c \
		     ft_strmapi.c \
		     ft_strequ.c \
		     ft_strnequ.c \
		     ft_strsub.c \
		     ft_strjoin.c \
		     ft_strtrim.c \
		     ft_strsplit.c \
             ft_isalpha.c \
		     ft_isdigit.c \
		     ft_isalnum.c \
		     ft_isascii.c \
		     ft_isprint.c \
			 ft_isupper.c \
			 ft_islower.c \
			 ft_iswhitespace.c \
             ft_tolower.c \
		     ft_toupper.c \
             ft_putchar.c \
		     ft_putstr.c \
		     ft_putendl.c \
		     ft_putnbr.c \
		     ft_putchar_fd.c \
		     ft_putstr_fd.c \
		     ft_putendl_fd.c \
		     ft_putnbr_fd.c \
             ft_atoi.c \
		     ft_itoa.c \
			 ft_abs.c \
			 ft_int_max.c \
			 ft_int_min.c \
			 ft_sizet_min.c \
			 ft_strindex.c \
			 ft_power.c \
			 ft_ten_to_power.c \
             ft_lstnew.c \
		     ft_lstdelone.c \
		     ft_lstdel.c \
		     ft_lstadd.c \
		     ft_lstiter.c \
		     ft_lstmap.c \
			 ft_lstlen.c \
             ft_split.c \
			 ft_error.c \
		     ft_lstadd_end.c \
			 get_next_line.c \
			 buffer.c \
			 ft_printf.c \
			 handle_ascii.c \
			 handle_float.c \
			 handle_int.c \
			 handle_ptr.c \
			 parser.c \
			 parser2.c

SRC       =  $(patsubst %,$(SRC_DIR)/%,$(_SRC))

_OBJ      =  $(_SRC:.c=.o)

OBJ       =  $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))


# MAIN =========================================================================

all: $(NAME)

$(NAME):
	@echo "$(BANNER)$(TEXT)Making$(LIME)...$(NO_COL)"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $(SRC)
	@mv *.o $(OBJ_DIR)
	@echo "$(BANNER)$(TEXT)Object files made$(LIME)!$(NO_COL)"
	@ar -rcs $(NAME) $(OBJ)
	@echo "$(BANNER)$(TEXT)Library made$(LIME)!$(NO_COL)"

# HOUSE KEEPING ================================================================

DEL       =  /bin/rm -rf

clean:
	@$(DEL) $(OBJ_DIR)
	@echo "$(BANNER)$(NO_COL)[$(LIME)√$(NO_COL)]	$(TEXT)Objects Deleted$(NO_COL)"

fclean: clean
	@$(DEL) $(NAME)
	@echo "$(BANNER)$(NO_COL)[$(LIME)√$(NO_COL)]	$(TEXT)Library Deleted$(NO_COL)"

re: fclean all

# CLEANING SHORTCUTS ===========================================================

cl: clean
	@echo && echo "$(RED)~> $(TEXT)Current Directory$(RED):$(NO_COL)" \
		&& ls && echo

f: fclean
	@echo && echo "$(RED)~> $(TEXT)Current Directory$(RED):$(NO_COL)" \
		&& ls && echo

# ==============================================================================

.PHONY: all clean fclean clclean re cl f

# ==============================================================================
