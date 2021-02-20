Menu under development designed for embedded platforms (no dynamically allocated memory).
Example presented in main.cpp file is run on linux environment with ncurses lib and threads.
Threads are only used for handling buttons. In real embedded systems it is replaced by interrupts rutines.

Signal.hh file is written to make signal-slot pattern.
In AllSignals.hh file are declared signals to handle 3 buttons and command to display buffor.
On linux used buttons are replaced by arrow UP, arrow DOWN and Space.

To test example, go to main root directory of projects, and:
mkdir build && cd build
cmake ..
make
./menu

At first run, no text is displayed, please push arrow UP or DOWN to make menu visible.

So far, 2 of 3 menu options are implemented.
- Option as Page of next menu.
- Option as configurable line (in exampel PID and cos).

Not implemented yet is configurable callback, which takes controll over whole display.

To implement menu in embedded systems, please adjust Display class and variables in Display.hh file:
constexpr int maxRows = 4;
constexpr int maxColumns = 20;

extern char displayBuff[maxRows][maxColumns];

displayBuff is global variable which includes displayed text.
