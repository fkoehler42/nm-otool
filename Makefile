# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 14:45:26 by fkoehler          #+#    #+#              #
#    Updated: 2017/11/09 12:42:59 by fkoehler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# FILES
SRC = arch_64.c \
	  error.c \
	  file_handling.c \
	  nm.c \
	  sorting.c \
	  structure.c

NM = ft_nm
OTOOL = ft_otool
OBJS = $(SRC:.c=.o)
O2 = $(addprefix $(OPATH), $(OBJS))

# DIRECTORIES
vpath %.c src/utils src/nm
LIBPATH = libft/
OPATH = obj/
INC = includes/
LIBINC = $(LIBPATH)$(INC)
LIB	= $(LIBPATH)libft.a

# COMPILATION
CC = gcc
FLAGS = -Wall -Werror -Wextra

# PROCESS
all: $(NM)

$(NM): $(LIB) $(O2)
	@$(CC) $(FLAGS) $(O2) -L $(LIBPATH) -lft -I $(LIBINC) -I $(INC) -o $@
	@echo "\033[0;34m$(NM) compilation done !\033[0;m"

$(LIB):
	@echo "\033[0;34mPlease wait while libft is compiled...\033[0;m"
	@make -C $(LIBPATH)

$(OPATH)%.o: %.c
	@$(CC) $(FLAGS) -I $(INC) -I $(LIBINC) -c $< -o $@

clean:
	@rm -f $(O2)
	@echo "\033[0;34mNm-otool object files deleted !\033[0;m"

fclean: clean
	@rm -f $(NAME) $(SYMLINK)
	@echo "\033[0;34m$(NM) and $(OTOOL) executables deleted !\033[0;m"
	-@make fclean -C $(LIBPATH)

re: fclean all

.PHONY: all clean fclean re
