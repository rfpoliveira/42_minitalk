#==============================================================================#
#                                 Files and Paths                              #
#==============================================================================#

SRCS = parsing.c

OBJS = $(addprefix $(BUILD_PATH)/, $(notdir $(SRCS:.c=.o)))

NAME_CLIENT = client
NAME_SERVER = server

BUILD_PATH = .build

LIB_NAME = minitalk.a

LIBFT_PATH = libft

LIBFT_ARC = libft/libft.a

LIBFT_OBJS = libft/.build

#==============================================================================#
#                                   Alias                                      #
#==============================================================================#

RM = rm -rf
AR = ar rcs
CFLAGS = -g -Wall -Werror -Wextra
MAKEE = make -s extra

#==============================================================================#
#                                    Rules                                     #
#==============================================================================#

all: deps $(BUILD_PATH) $(LIBFT_ARC) $(OBJS) $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT):
	@cc $(CFLAGS) $(OBJS) client.c $(LIBFT_ARC) -o $(NAME_CLIENT)
	@echo "$(GRN)[client created!]$(D)"

$(NAME_SERVER):
	@cc $(CFLAGS) $(OBJS) server.c $(LIBFT_ARC) -o $(NAME_SERVER)
	@echo "$(GRN)[server created!]$(D)"
	
$(BUILD_PATH):
	@mkdir $(BUILD_PATH)

$(BUILD_PATH)/%.o: %.c
	@cc $(CFLAGS) -o $@ -c $<
	
$(LIBFT_ARC):
	@$(MAKEE) -C $(LIBFT_PATH)

#$(LIB_NAME): $(LIBFT_ARC) 
#	$(AR) $(LIB_NAME) $(OBJS) $(LIBFT_OBJS)/*.o

deps:	## Download/Update libft
	@if test ! -d "$(LIBFT_PATH)"; then make -s get_libft; \
		else echo "$(GRN)[Libft folder found]$(D)"; fi

get_libft:
	@echo "[$(CYA)Downloading Libft$(D)]"
	git clone git@github.com:rfpoliveira/42_Libft.git $(LIBFT_PATH)
	@echo "$(CYA)[Libft successfully downloaded]$(D)"

clean: 
	@$(RM) $(BUILD_PATH)	
	@$(RM) $(NAME_CLIENT)
	@$(RM) $(NAME_SERVER)
	@echo "$(BCYA)[clean] Objects removed$(D)"

fclean: clean
	@$(RM) $(LIBFT_PATH)
	@echo "$(BCYA)[fclean] executables, library and Libft removed$(D)"

again: clean $(BUILD_PATH) $(LIBFT_ARC) $(OBJS) $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)
