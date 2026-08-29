# LAG (LibAsciiGraphic)

## Installation

### For test
If you just want to execute the test given in the repo you need to clone it where you want and move in.

Now execute the following command to compile the library
```
make re
```
Now move in the test folder
```
cd test
```
And compile the main of test you want to execute with the following command
```
gcc main.c -L../lib -lncurses -lm -llag -o game
```
And now execute the binary (game in this exemple) with the LD_LIBRARY_PATH define to ../lib with
```
export LD_LIBRARY_PATH=../lib
./game
```

### For use in your project
Add a [submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules) or a clone of the liblag repo in a lib folder, the lib folder is not required but very recommanded for clean usage
In the root of your project (where your .git folder is) execute this
For submodule (the best choice) :
```
mkdir -p lib
cd lib
git submodule add https://codeberg.org/SeigneurLefou/liblag.git
cd ..
```
And now you need to clone your repo with the flag `--recurse-submodules`

For clone (more basic but you can add a clone rule in your Makefile) :
```
git clone https://codeberg.org/SeigneurLefou/liblag.git lib/liblag
```
Whatever your choice may be you need to compile the library and for this I recommande to take a look to the file exemple.make who detailled the rule needed to add to yours

But if you hate Makefile and use other things or *thrill* by hand here is the command list to use in the root of your project
*utils.c represent a secondary file use by your main and main.c is the main*
```
make -C lib/liblag/ re
export LDFLAGS=""
gcc -Ilib/liblag/includes -Llib/liblag/lib -llag -lm -lncurses -c utils.c -o utils.o
gcc main.c -Ilib/liblag/includes -Llib/liblag/lib -llag -lm -lncurses -o game
export LD_LIBRARY_PATH=lib/liblag/lib
./game
```
This is just an exemple and I really recommand you to have a Makefile for compile

## How it's working ? (in my mind)

There's a contexte but no type for it because ncurses.

There's lag_window who is an alias for the WINDOW type and can be initiate and destruct. Maybe add a responsive ratio like take the dimension of the ncurses window and dimension of the terminal's window and calculate a ratio. Then apply this ratio when redim

Also a lag_pixel type who take multiple style flags, a pair of lag_color and a char for the cell colouring.

Also a lag_buffer who is a buffer of lag_pixel who can be put in another buffer with clipping.

There is a pollevent system for taking input properly.

Draw functions on lag_buffer for pixel, line, rect, ellipsis or triangle. Can be full or not. Put function are the same but directly on the window.

Can blit an buffer on another or put one on the window. Also do a transformation of it with also clipping when overlapping.
