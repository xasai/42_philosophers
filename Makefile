##########################################################################################
NAME := Philosophers

BINPATH := ./bin/
OBJPATH := ./obj/
OBJDIR := $(addprefix $(OBJPATH), $(shell find philo -type d ! -name include))


PHILO := philo 
PHILO_BIN := $(BINPATH)$(PHILO)
PHILO_SRC := $(shell find philo -name *.c) #FIXME
PHILO_OBJ := $(addprefix $(OBJPATH), $(PHILO_SRC:.c=.o))
PHILO_INC := -Iphilo/include

PHILO_BONUS := philo_bonus
PHILO_BONUS_BIN := $(BINPATH)$(PHILO_BONUS)
PHILO_BONUS_SRC := $(shell find ./philo_bonus -name *.c) #FIXME
PHILO_BONUS_OBJ := $(addprefix $(OBJPATH), $(PHILO_BONUS_SRC:.c=.o))
PHILO_BONUS_INC := -Iphilo_bonus/include
############################################################################################
CC := gcc
CFLAGS := -O3 -Wall -Wextra -Werror -MMD -MP
 #_____    _____    _____ 
#/ ____|  / ____|  / ____|
#| |  __  | |      | |     
#| | |_ | | |      | |     
#| |__| | | |____  | |____ 
 #\_____|  \____|  \_____|
############################################################################################
ifeq ($(MAKECMDGOALS),clean)
DEPFILES=
else ifeq ($(MAKECMDGOALS),fclean)
DEPFILES=
else
DEPFILES := $(OBJ:.o=.d)
-include $(DEPFILES)
endif
vpath %.c philo philo_bonus
MAKEFLAGS=j
.PHONY: test re fclean clean all
############################################################################################

all: $(NAME)

$(NAME): $(OBJPATH) $(BINPATH) $(PHILO_BIN)

$(PHILO_BIN): $(PHILO_OBJ)
	$(green)
	$(CC) $(CFLAGS) $(PHILO_INC) $(PHILO_OBJ) -o $(PHILO_BIN)
	$(reset)

bonus: $(PHILO_BONUS_OBJ)
	$(green)	
	$(CC) $(CFLAGS) $(INC) $(PHILO_BONUS_OBJ) -o $(PHILO_BONUS_BIN)
	$(reset)


$(OBJPATH)philo/%.o: %.c
	$(green)	
	$(CC) $(CFLAGS) $(PHILO_INC) -c $< -o $@
	$(reset)

$(OBJPATH)philo_bonus/%.o: %.c
	$(green)	
	$(CC) $(CFLAGS) $(PHILO_INC) -c $< -o $@
	$(reset)

$(BINPATH):
	$(green)	
	mkdir -p $(BINPATH)
	$(reset)

$(OBJPATH):
	$(green)	
	mkdir -p $(OBJDIR) 
	$(reset)
	

clean:
	$(red)
	rm -rf $(OBJPATH)
	$(reset)

fclean: clean
	$(red)
	rm -rf $(BINPATH) 
	$(reset)

re: fclean
	@$(MAKE) all

############################################################################################
echo:
	@echo $(OBJDIR) 

val: $(NAME)
	valgrind --leak-check=full ./$(NAME)

debug: $(NAME)
	gdb	./$(NAME)
############################################################################################
green	:= @echo  "\033[0;32m"
reset	:= @echo -n "\033[0;m"
red		:= @echo  "\033[0;31m"
