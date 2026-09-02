DRAW_PATH = src/lag_draw

SRC +=	$(DRAW_PATH)/lag_draw_pixel.c	\
		$(DRAW_PATH)/lag_draw_line.c	\
		$(DRAW_PATH)/lag_draw_rect.c	\
		$(DRAW_PATH)/lag_draw_circle.c

OUT_DIRS += $(OUTPUT_DIR)/$(DRAW_PATH)
