# ALG (AsciiLibGraphic)

## How it's working ? (in my mind)

There's a contexte but no type for it because ncurses.

There's alg_window who is an alias for the WINDOW type and can be initiate and destruct. Maybe add a responsive ratio like take the dimension of the ncurses window and dimension of the terminal's window and calculate a ratio. Then apply this ratio when redim

Also a alg_pixel type who take a pair of color and a char for the cell colouring.

Also a alg_image who is a buffer of alg_pixel who can be put in another image.