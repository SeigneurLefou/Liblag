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

$(NAME_SO): $(OUT_DIRS) $(OBJ)
	mkdir -p $(LIB_DIR)
	@$(CC) -shared $(CFLAGS) -I$(INCLUDES) -o $@ $(OBJ) $(LFLAGS)
	@echo "COMPILATION SHARED LIBRARY"

$(NAME_A): $(OUT_DIRS) $(OBJ)
	mkdir -p $(LIB_DIR)
	@ar crs $@ $(OBJ)
	@echo "COMPILATION STATIC LIBRARY"

$(OUTPUT_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDES) $(LFLAGS) -c -fPIC $< -o $@
	@echo -e "$< to $@\n"

$(OUT_DIRS):
	@mkdir -p $(OUT_DIRS)

all: $(NAME_A) $(NAME_SO)

clean:
	@rm -rf $(OUTPUT_DIR)
	@echo "CLEAN"

fclean: clean
	@rm -rf $(LIB_DIR)
	@echo "FCLEAN"

re: fclean all

.PHONY: clean all re fclean

