# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 14:45:26 by fkoehler          #+#    #+#              #
#    Updated: 2017/11/23 16:16:33 by fkoehler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# FILES

NM_SRC = ar_lib.c \
	  arch_32.c \
	  arch_64.c \
	  arch_fat.c \
	  display.c \
	  nm.c \
	  overflow_protection.c \
	  sym_type.c \
	  structure.c

OTOOL_SRC = otool.c

UTILS_SRC = ascii_sorting.c \
	  		endianness.c \
			error.c \
	  		main_sorting.c \
	  		rev_ascii_sorting.c

NM = ft_nm
NM_OBJS = $(NM_SRC:.c=.o)
NM_O2 = $(addprefix $(NM_OPATH), $(NM_OBJS))

OTOOL = ft_otool
OTOOL_OBJS = $(OTOOL_SRC:.c=.o)
OTOOL_O2 = $(addprefix $(OTOOL_OPATH), $(OTOOL_OBJS))

UTILS_OBJS = $(UTILS_SRC:.c=.o)
UTILS_O2 = $(addprefix $(UTILS_OPATH), $(UTILS_OBJS))

# DIRECTORIES

INC = includes/
LIBPATH = libft/
LIBINC = $(LIBPATH)$(INC)
LIB	= $(LIBPATH)libft.a

NM_DIR = src/nm/
NM_OPATH = obj/nm/

OTOOL_DIR = src/otool/
OTOOL_OPATH = obj/otool/

UTILS_DIR = src/utils/
UTILS_OPATH = obj/utils/

# COMPILATION

CC = gcc
FLAGS = -Wall -Werror -Wextra

# PROCESS

all: $(NM) $(OTOOL)

$(NM): $(LIB) $(NM_O2) $(UTILS_O2)
	@$(CC) $(FLAGS) $(NM_O2) $(UTILS_O2) -L $(LIBPATH) -lft -I $(LIBINC) -I $(INC) -o $@
	@echo "\033[0;34m$(NM) compilation done !\033[0;m"

$(OTOOL): $(LIB) $(OTOOL_O2) $(UTILS_O2)
	@$(CC) $(FLAGS) $(OTOOL_O2) -L $(LIBPATH) -lft -I $(LIBINC) -I $(INC) -o $@
	@echo "\033[0;34m$(OTOOL) compilation done !\033[0;m"

$(LIB):
	@echo "\033[0;34mPlease wait while libft is compiled...\033[0;m"
	@make -C $(LIBPATH)

$(NM_OPATH)%.o: $(NM_DIR)%.c
	@$(CC) $(FLAGS) -I $(INC) -I $(LIBINC) -c $< -o $@

$(OTOOL_OPATH)%.o: $(OTOOL_DIR)%.c
	@$(CC) $(FLAGS) -I $(INC) -I $(LIBINC) -c $< -o $@

$(UTILS_OPATH)%.o: $(UTILS_DIR)%.c
	@$(CC) $(FLAGS) -I $(INC) -I $(LIBINC) -c $< -o $@

clean:
	@rm -f $(NM_O2) $(OTOOL_O2) $(UTILS_O2)
	@echo "\033[0;34mNm-otool object files deleted !\033[0;m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;34m$(NM) and $(OTOOL) executables deleted !\033[0;m"
	-@make fclean -C $(LIBPATH)

re: fclean all

.PHONY: all clean fclean re
