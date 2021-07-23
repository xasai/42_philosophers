##########################################################################################
NAME := Philosophers

OBJPATH := ./obj/
OBJDIR := $(addprefix $(OBJPATH), $(shell find src -type d ! -name include))


PHILO := philo 
PHILO_SRC := $(shell find src -name *.c) #FIXME
PHILO_OBJ := $(addprefix $(OBJPATH), $(PHILO_SRC:.c=.o))
PHILO_INC := -Iinclude

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
all: $(NAME)

$(NAME): $(OBJPATH) $(BINPATH) $(PHILO)

$(PHILO): $(PHILO_OBJ)
	$(green)
	$(CC) $(CFLAGS) $(PHILO_INC) $(PHILO_OBJ) -o $(PHILO)
	$(cyan)
	@echo "\t==============> Successfully compiled $(PHILO) [+]"
	$(reset)


$(OBJPATH)%.o: %.c
	$(green)	
	$(CC) $(CFLAGS) $(PHILO_INC) -c $< -o $@
	$(reset)

$(OBJDIR):
	$(green)	
	mkdir -p $(OBJDIR) 
	$(reset)


clean:
	$(red)
	rm -rf $(OBJPATH)
	$(reset)

fclean: clean
	$(red)
	rm -rf $(PHILO) 
	$(reset)

re: fclean
	@$(MAKE) all

run: 
	./bin/philo

.PHONY: all run re fclean clean 

############################################################################################
ifeq ($(MAKECMDGOALS),clean)
DEPFILES :=
else ifeq ($(MAKECMDGOALS),fclean)
DEPFILES :=
-include $(DEPFILES)
else
DEPFILES := $(PHILO_OBJ:.o=.d)
-include $(DEPFILES)
endif
MAKEFLAGS := j
vpath %.c src
############################################################################################
val: $(NAME)
	valgrind --leak-check=full ./$(NAME)

debug: $(NAME)
	gdb	./$(PHILO_BIN)
############################################################################################
cyan	:= @echo -n "\033[0;36m"
green	:= @echo -n "\033[0;32m"
red		:= @echo -n "\033[0;31m"
reset	:= @echo  	"\033[0;m"
