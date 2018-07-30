# snake_py27
py27 version of snake

Same as the snake_py32, but the scripts have been converted to python 2.7 (py3to2 tool was used).
The binaries for windows (32 bit) have also been included. These were built using the cx_freeze (build/exe.win32-2.7/)
and pyinstaller (dist/snake_main_menu/).

--------------------
INSTALLATION

It should be as simply as following these two steps:

1 - fullfilling the dependency package (pygame). In ArchLinux this can be done with:

$ pacman -S python2-pygame

2 - cloning the repository with git

The game then can be executed in python2:

$ python2 snake_main_menu.py
