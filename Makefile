#	Program output
EXE_NM = ft_nm
EXE_OTOOL = ft_otool

#	GCC flags -Wall -Wextra $(CFLAGS) -g 
#-fsanitize=address -g
#CFLAGS = -Wall -Wextra -Werror -fsanitize=address
#CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -Wall -Wextra -Werror
ALL_CFLAGS = $(CFLAGS)

#	Library files
LIBFLAGS = -L./libft -lft

#	Extern includes
INC_LIBFT = libft/includes

#	Ojects/Sources directories
INC_LIB = includes/lib_inc
INC_NM = includes/nm_inc
INC_OTOOL = includes/otool_inc
SRC_NM = $(shell find src/nm | grep "\.c$$" | sed "s/\.c$$//g")
SRC_OTOOL = $(shell find src/otool | grep "\.c$$" | sed "s/\.c$$//g")
SRC_LIBTOOLS += $(shell find src/lib_tools | grep "\.c$$" | sed "s/\.c$$//g")
INCLUDES_NM += $(addprefix -iquote , $(INC_LIB))
INCLUDES_NM += $(addprefix -iquote , $(INC_NM))
INCLUDES_NM += $(addprefix -iquote , $(INC_LIBFT))
INCLUDES_OTOOL += $(addprefix -iquote , $(INC_LIB))
INCLUDES_OTOOL += $(addprefix -iquote , $(INC_OTOOL))
INCLUDES_OTOOL += $(addprefix -iquote , $(INC_LIBFT))
SRCS_NM += $(addsuffix .c, $(SRC_NM))
SRCS_OTOOL += $(addsuffix .c, $(SRC_OTOOL))
SRCS_NM += $(addsuffix .c, $(SRC_LIBTOOLS))
SRCS_OTOOL += $(addsuffix .c, $(SRC_LIBTOOLS))


#	Final OBJS
OBJS_NM = $(SRCS_NM:.c=.o)
OBJS_OTOOL = $(SRCS_OTOOL:.c=.o)

#	Layout
VERBOSE = true

all: header $(EXE_NM) $(EXE_OTOOL) footer

header:
	@echo "\033[33m[\033[4m$(EXE_NM)\033[0m\033[33m] Compile\033[0m"
	@echo "\033[33m[\033[4m$(EXE_OTOOL)\033[0m\033[33m] Compile\033[0m"

footer:
	@echo "\033[33m[\033[4m$(EXE_NM)\033[0m\033[33m] Finished\033[0m"
	@echo "\033[33m[\033[4m$(EXE_OTOOL)\033[0m\033[33m] Finished\033[0m"

$(EXE_OTOOL): lft $(OBJS_OTOOL)
ifeq ($(VERBOSE),true)
	@echo "\033[34m. Compile Final .\033[0m $(EXE_OTOOL)"
else
	@printf"\033[34m.\033[0m\n"
endif
	@$(CC) $(ALL_CFLAGS) $(INCLUDES_OTOOL) $(OBJS_OTOOL) -o $(EXE_OTOOL) -g $(LIBFLAGS)

$(EXE_NM): lft $(OBJS_NM)
ifeq ($(VERBOSE),true)
	@echo "\033[34m. Compile Final .\033[0m $(EXE_NM)"
else
	@printf"\033[34m.\033[0m\n"
endif
	@$(CC) $(ALL_CFLAGS) $(INCLUDES_NM) $(OBJS_NM) -o $(EXE_NM) -g $(LIBFLAGS)

%.o: %.c 
ifeq ($(VERBOSE),true)
	@echo "\033[34m. Compile .\033[0m $<"
else
	@printf"\033[34m.\033[0m"
endif
	@$(CC) $(ALL_CFLAGS) $(INCLUDES_NM) $(INCLUDES_OTOOL) -c $< -o $@

clean:
	@echo -e "\033[33m[\033[4m$(EXE_NM)\033[0m\033[33m] >>\033[0m \033[31mCLEAN all object files (*.o)\033[0m"
	@$(RM) $(OBJS_NM)
	@echo -e "\033[33m[\033[4m$(EXE_OTOOL)\033[0m\033[33m] >>\033[0m \033[31mCLEAN all object files (*.o)\033[0m"
	@$(RM) $(OBJS_OTOOL)	


fclean: clean lftfclean
	@echo -e "\033[33m[\033[4m$(EXE_NM)\033[0m\033[33m] >>\033[0m \033[31mFCLEAN project binary ($(EXE_NM))\033[0m"
	@$(RM) $(EXE_NM)
	@echo -e "\033[33m[\033[4m$(EXE_OTOOL)\033[0m\033[33m] >>\033[0m \033[31mFCLEAN project binary ($(EXE_OTOOL))\033[0m"
	@$(RM) $(EXE_OTOOL)	

re: fclean all

lft:
	@echo "\033[33m[\033[4m$(EXE_NM)\033[0m\033[33m] >> Extern dependencies\033[0m"
	@make -C libft
	@echo "\033[33m[\033[4m$(EXE_NM)\033[0m\033[33m] << Extern dependencies\033[0m"

lftclean:
	make -C libft clean

lftfclean:
	make -C libft fclean

lftre:
	make -C libft re

git:
	@git add .
	@echo "Enter Your Commit :"
	@read var1 ; git commit -m "$$var1"
	@git push
