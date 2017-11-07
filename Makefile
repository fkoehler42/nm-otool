# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 14:45:26 by fkoehler          #+#    #+#              #
#    Updated: 2017/11/07 17:03:08 by fkoehler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# FILES
SRC = arg.c \
	  nm.c

NM = ft_nm
OTOOL = ft_otool
OBJS = $(SRC:.c=.o)
O2 = $(addprefix $(OPATH), $(OBJS))

# DIRECTORIES
vpath %.c src
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
