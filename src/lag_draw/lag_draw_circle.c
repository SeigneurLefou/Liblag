#include "lag_draw.h"

bool lag_draw_circle(lag_buffer *buf, lag_vec2 pos, uint radius, lag_pixel pixel, lag_draw_enum flags) {
    if (!buf) return false;

    int x = radius;
    int y = 0;
    int p = 1 - radius;
    bool fill = (flags & FILL);

    while (x >= y) {
        if (fill) {
            lag_draw_line(buf, (lag_vec2){pos.x - x, pos.y + y}, (lag_vec2){pos.x + x, pos.y + y}, pixel);
            lag_draw_line(buf, (lag_vec2){pos.x - x, pos.y - y}, (lag_vec2){pos.x + x, pos.y - y}, pixel);
            lag_draw_line(buf, (lag_vec2){pos.x - y, pos.y + x}, (lag_vec2){pos.x + y, pos.y + x}, pixel);
            lag_draw_line(buf, (lag_vec2){pos.x - y, pos.y - x}, (lag_vec2){pos.x + y, pos.y - x}, pixel);
        } else {
            lag_draw_pixel(buf, (lag_vec2){pos.x + x, pos.y + y}, pixel);
            lag_draw_pixel(buf, (lag_vec2){pos.x - x, pos.y + y}, pixel);
            lag_draw_pixel(buf, (lag_vec2){pos.x + x, pos.y - y}, pixel);
            lag_draw_pixel(buf, (lag_vec2){pos.x - x, pos.y - y}, pixel);
            lag_draw_pixel(buf, (lag_vec2){pos.x + y, pos.y + x}, pixel);
            lag_draw_pixel(buf, (lag_vec2){pos.x - y, pos.y + x}, pixel);
            lag_draw_pixel(buf, (lag_vec2){pos.x + y, pos.y - x}, pixel);
            lag_draw_pixel(buf, (lag_vec2){pos.x - y, pos.y - x}, pixel);
        }

        y++;
        if (p <= 0) {
            p += 2 * y + 1;
        } else {
            x--;
            p += 2 * (y - x) + 1;
        }
    }

    return true;
}
