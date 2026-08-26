NAME		= libalg.so

OUTPUT_DIR	= build

SRC_DIR		= src

OUT_DIRS	:= $(OUTPUT_DIR)/$(SRC_DIR)

SRC			=

INCLUDES	= includes

LFLAGS		= -lncurses -lm

include src/alg_ctx/alg_ctx.make
include src/alg_buffer/alg_buffer.make
include src/alg_draw/alg_draw.make
include src/alg_event/alg_event.make
include src/alg_time/alg_time.make
include src/alg_window/alg_window.make

include		src/action.make
