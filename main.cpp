#include <iostream>
#include "Menu.hh"
#include "Signal.hh"
#include "AllSignals.hh"
#include "DisplayBuffor.hh"
#include "ConfigInlineP.hh"
#include <ncurses.h>
#include <thread>
#include <cstring>


void handleButtons(AllSignals& sig)
{
    int ch;
    while ((ch = getch()) != 'q') {
        switch(ch) {
            case KEY_UP: 
                sig.buttonUp();
            break;

            case KEY_DOWN:
                sig.buttonDown();
            break;

            case ' ':
                sig.buttonEnter();
            break;
        }
    }
}

void ShowDisplayBuffor()
{
    clear();
    refresh();
    for (int i = 0; i < maxRows; i++)
    {
        printw(displayBuff[i]);
        printw("\n");
    }
}

int main()
{
    AllSignals allSignals;
    allSignals.displayBuffor.connect(ShowDisplayBuffor);

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    Menu menu(allSignals);
    MenuPage pageFirst;
    MenuPage pagePid;

    ConfigInlineP configP{5};
    auto dummy = [](AllSignals&){};
    pageFirst.AddOption(MenuOption("PID", OptionType::Page, &pagePid));
    pageFirst.AddOption(MenuOption("Opcja 2", OptionType::ConfigCallback, dummy));

    pagePid.AddOption(MenuOption("Set P", OptionType::ConfigInline, &configP));
    pagePid.AddOption(MenuOption("Return", OptionType::Page, &pageFirst));

    menu.setDefaultMenuPage(&pageFirst);


    // Constructs the new thread and runs it. Does not block execution.
    std::thread t1(handleButtons, std::ref(allSignals));
    t1.join();

    refresh();
    endwin();
}