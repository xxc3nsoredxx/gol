# Game of Life for the Linux framebuffer

Uses ncurses for raw input.
Uses OpenMP for multi threading.

To compile, just run `make` in the `src` directory.

Requirements to run:

* Be in the `video` group. If you're not, the following options can fix that:

** `usermod -aG video oskari`

** manually editing `/etc/group`

** NOTE: the above must be run as root.

* Run from the virtual console (for example TTY 2)
