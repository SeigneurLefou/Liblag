NAME        := game

SRC_DIR     := src
OBJ_DIR     := build
INC_DIR     := includes

SRCS        := main.c

OBJS        := $(SRCS:%.c=$(OBJ_DIR)/%.o)

LAG_DIR     := lib/liblag
LAG_LIB_DIR := $(LAG_DIR)/lib
LAG_INC_DIR := $(LAG_DIR)/includes
ifdef LIB_A
	LAG_LIB := $(LAG_LIB_DIR)/liblag.so
else
	LAG_LIB := $(LAG_LIB_DIR)/liblag.a
endif

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -I$(INC_DIR) -I$(LAG_INC_DIR)
LDFLAGS     := -L$(LAG_LIB_DIR) -llag -lncurses -lm

all: $(NAME)

$(LAG_LIB):
	@$(MAKE) -C $(LAG_DIR) all

$(NAME): $(LAG_A) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LAG_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LAG_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
