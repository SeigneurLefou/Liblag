LIB_DIR		= lib/
NAME_SO		= $(LIB_DIR)liblag.so
NAME_A		= $(LIB_DIR)liblag.a

OUTPUT_DIR	= build

SRC_DIR		= src

OUT_DIRS	:= $(OUTPUT_DIR)/$(SRC_DIR)

SRC			=

INCLUDES	= includes

LFLAGS		= -lncurses -lm

include src/lag_ctx/lag_ctx.make
include src/lag_draw/lag_draw.make
include src/lag_buffer/lag_buffer.make
include src/lag_pixel/lag_pixel.make
include src/lag_event/lag_event.make
include src/lag_time/lag_time.make
include src/lag_window/lag_window.make

include		src/action.make
