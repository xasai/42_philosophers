##########################################################################################
NAME := Philosophers

MAKEFLAGS = -j3
VPATH = src/

OBJPATH := obj/
OBJDIR := $(patsubst $(VPATH)%, $(OBJPATH)%, $(shell find $(VPATH) -type d))


PHILO := philo 
PHILO_SRC := $(wildcard $(VPATH)*.c) #FIXME
PHILO_OBJ := $(patsubst $(VPATH)%, $(OBJPATH)%, $(PHILO_SRC:.c=.o))
PHILO_INC := -Iinclude

############################################################################################ 
CC := gcc
CFLAGS := -Wall -Wextra -Werror -MMD -MP -Ofast -pthread -pedantic-errors
#CFLAGS += -D_VERBOSE
 #_____    _____    _____ 
#/ ____|  / ____|  / ____|
#| |  __  | |      | |     
#| | |_ | | |      | |     
#| |__| | | |____  | |____ 
 #\_____|  \____|  \_____|
############################################################################################

	#@echo PHILO_SRC: $(PHILO_SRC)
	#@echo PHILO_OBJ: $(PHILO_OBJ)
	#@echo OBJDIR: $(OBJDIR)

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
	rm -rf $(PHILO) 
	$(reset)

re: fclean
	@$(MAKE) all

run: 
	./bin/philo

.PHONY:  all run re fclean clean 

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
############################################################################################
val: $(NAME)
	valgrind --leak-check=full ./$(NAME)

debug: $(NAME)
	gdb	./$(PHILO)
############################################################################################
cyan	:= @echo -n "\033[0;36m"
green	:= @echo -n "\033[0;32m"
red		:= @echo -n "\033[0;31m"
reset	:= @echo -n	"\033[0;m"
