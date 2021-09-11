##########################################################################################
NAME := Philosophers
BIN = philo

MAKEFLAGS = -j1
VPATH = src/

PHILO_SRC := $(wildcard $(VPATH)*.c) #FIXME  beware wildcards

OBJPATH := .obj/
DIRS := $(patsubst $(VPATH)%, $(OBJPATH)%, $(shell find $(VPATH) -type d))
PHILO_OBJ := $(patsubst $(VPATH)%, $(OBJPATH)%, $(PHILO_SRC:.c=.o))
PHILO_INC := -Iinclude

############################################################################################# 
#GCC
CFLAGS := -Wall -Wextra -Werror -MMD -MP -pthread -pedantic-errors
ifeq ( $(MAKECMDGOALS), all)
	MAKEFLAGS = -j8
endif
############################################################################################


all: CFLAGS += -Ofast $(BIN)
$(BIN): $(OBJPATH) $(PHILO_OBJ)
	$(green)
	$(CC) $(PHILO_INC) $(PHILO_OBJ) -o $(BIN) $(CFLAGS)
	$(orange)
	@echo "\t==============> Successfully compiled $(BIN) [+]"
	$(reset)

$(OBJPATH)%.o: %.c
	$(blue)	
	$(CC) $(PHILO_INC) -c $< -o $@ $(CFLAGS)
	$(reset)

debug: CFLAGS += -Og -g3 -D_DEBUG  
debug: clean $(OBJPATH) $(PHILO_OBJ) 
	$(green)
	$(CC) $(PHILO_INC) $(PHILO_OBJ) -o $(BIN) $(CFLAGS)
	$(cyan)
	@echo "\t==============> Successfully compiled $(BIN) [+]"
	$(MAKE) clean # For recompile on all rule
	$(reset)

$(OBJPATH):
	$(green)	
	mkdir -p $(DIRS) $(DEBUG_OBJDIR)
	$(reset)

clean:
	$(red)
	rm -rf $(OBJPATH)
	$(reset)

fclean: clean
	$(red)
	rm -rf $(BIN)
	$(reset)

re: fclean all
	#multijobs requests run 'all' like this
	#because it may not remove binary at moment of all runs
	#$(MAKE) all

.PHONY: all run re fclean clean

val: $(NAME)
	valgrind --leak-check=full ./$(NAME)

gdb: debug
	gdb	./$(BIN)
############################################################################################
#Dependencies
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
reset			 := @echo -n "\033[0;m"
black            := @echo -n "\033[0;30m"
blue             := @echo -n "\033[0;34m"
green            := @echo -n "\033[0;32m"
cyan             := @echo -n "\033[0;36m"
red              := @echo -n "\033[0;31m"
purple           := @echo -n "\033[0;35m"
brown            := @echo -n "\033[0;33m"
gray             := @echo -n "\033[0;37m"
dark_gray        := @echo -n "\033[1;30m"
light_blue       := @echo -n "\033[1;34m"
light_green      := @echo -n "\033[1;32m"
light_cyan       := @echo -n "\033[1;36m"
light_red        := @echo -n "\033[1;31m"
light_purple     := @echo -n "\033[1;35m"
yellow           := @echo -n "\033[1;33m"
white            := @echo -n "\033[1;37m"
