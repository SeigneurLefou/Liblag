NAME		= ray_cascii.game

OUTPUT_DIR	= build

SRC_DIR		= src

OUT_DIRS	:= $(OUTPUT_DIR)/$(SRC_DIR)

SRC			= $(SRC_DIR)/main.c

INCLUDES	= includes

LFLAGS		= -lncurses -lm

include		src/action.make
