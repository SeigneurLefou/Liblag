CC := gcc

ifdef SANIT
	DEBUG=1
endif
ifdef DEBUG
	CFLAGS += -g -Wall -Wextra -DDEBUG=yes
else
	CFLAGS := -Wall -Werror
endif
ifdef SANIT
	CFLAGS += -fsanitize=address -fsanitize=leak -O1 -MMD -MP
endif

OBJ = $(SRC:%.c=$(OUTPUT_DIR)/%.o)

$(NAME): $(OUT_DIRS) $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -I$(INCLUDES) $(LFLAGS) -o $@
	@echo "COMPILATION"

$(OUTPUT_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDES) $(LFLAGS) -c $< -o $@
	@echo -e "$< to $@\n"

$(OUT_DIRS):
	@mkdir -p $(OUT_DIRS)

all: $(NAME)

clean:
	@rm -rf $(OUTPUT_DIR)
	@echo "CLEAN"

fclean: clean
	@rm -f $(NAME)
	@echo "FCLEAN"

re: fclean all

.PHONY: clean all re fclean

