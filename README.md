# LAG (LibAsciiGraphic)

## How it's working ? (in my mind)

There's a contexte but no type for it because ncurses.

There's lag_window who is an alias for the WINDOW type and can be initiate and destruct. Maybe add a responsive ratio like take the dimension of the ncurses window and dimension of the terminal's window and calculate a ratio. Then apply this ratio when redim

Also a lag_pixel type who take multiple style flags, a pair of color and a char for the cell colouring.

Also a lag_image who is a buffer of lag_pixel who can be put in another image with clipping.

There is a pollevent system for taking input properly.

Draw functions on lag_image for pixel, line, rect, ellipsis or triangle. Can be full or not. Put function are the same but directly on the window.

Can blit an image on another or put one on the window. Also do a transformation of it with also clipping when overlapping.