# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 14:45:26 by fkoehler          #+#    #+#              #
#    Updated: 2017/11/15 18:21:34 by fkoehler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# FILES
NM_SRC = ar_lib.c \
	  arch_32.c \
	  arch_64.c \
	  arch_fat.c \
	  display.c \
	  error.c \
	  file_handling.c \
	  nm.c \
	  sorting.c \
	  sym_type.c \
	  structure.c

NM = ft_nm
OTOOL = ft_otool
NM_OBJS = $(NM_SRC:.c=.o)
NM_O2 = $(addprefix $(NM_OPATH), $(NM_OBJS))

# DIRECTORIES
vpath %.c src/utils src/nm
LIBPATH = libft/
NM_OPATH = obj/nm/
INC = includes/
LIBINC = $(LIBPATH)$(INC)
LIB	= $(LIBPATH)libft.a

# COMPILATION
CC = gcc
FLAGS = -Wall -Werror -Wextra

# PROCESS
all: $(NM)

$(NM): $(LIB) $(NM_O2)
	@$(CC) $(FLAGS) $(NM_O2) -L $(LIBPATH) -lft -I $(LIBINC) -I $(INC) -o $@
	@echo "\033[0;34m$(NM) compilation done !\033[0;m"

$(LIB):
	@echo "\033[0;34mPlease wait while libft is compiled...\033[0;m"
	@make -C $(LIBPATH)

$(NM_OPATH)%.o: %.c
	@$(CC) $(FLAGS) -I $(INC) -I $(LIBINC) -c $< -o $@

clean:
	@rm -f $(NM_O2)
	@echo "\033[0;34mNm-otool object files deleted !\033[0;m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;34m$(NM) and $(OTOOL) executables deleted !\033[0;m"
	-@make fclean -C $(LIBPATH)

re: fclean all

.PHONY: all clean fclean re
