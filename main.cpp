#include <iostream>
#include "Menu.hh"
#include "Signal.hh"
#include "AllSignals.hh"
#include "DisplayBuffor.hh"
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

void setPCallback(AllSignals& signals)
{
    printw("jestem pierwszy\n");
    for (int i = 0; i < maxRows; i++)
        for (int j = 0; j < maxColumns; j++)
            displayBuff[i][j] = ' ';

    bool finish = false;
    int P = 10;
    bool changed = true;
    auto funFinish = [&](){ finish = true; changed = true; };
    auto funPUp = [&](){ ++P; changed = true; };
    auto funDown = [&](){ --P; changed = true; };

    signals.buttonEnter.connect(funFinish);
    signals.buttonUp.connect(funPUp);
    signals.buttonDown.connect(funDown);

    //while(!finish)
    //{
        int ch = 0;
        do {
            switch(ch) 
            {
                case KEY_UP: ++P; changed = true;
                break;

                case KEY_DOWN: --P; changed = true;
                break;
            }
            if (changed)
            {
                sprintf(displayBuff[0], "P = %d", P);
                signals.displayBuffor();
                changed = false;
            }
        } while ((ch = getch()) != ' ');

    //}
    signals.buttonEnter.disconnect(funFinish);
    signals.buttonUp.disconnect(funPUp);
    signals.buttonDown.disconnect(funDown);
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

    auto dummy = [](AllSignals&){};
    pageFirst.AddOption(MenuOption("PID", OptionType::Page, &pagePid));
    pageFirst.AddOption(MenuOption("Opcja 2", OptionType::Config, dummy));
    pageFirst.AddOption(MenuOption("Opcja 3", OptionType::Config, dummy));
    pageFirst.AddOption(MenuOption("Opcja 4", OptionType::Config, dummy));
    pageFirst.AddOption(MenuOption("Opcja 5", OptionType::Config, dummy));
    pageFirst.AddOption(MenuOption("Opcja 6", OptionType::Config, dummy));
    pageFirst.AddOption(MenuOption("Info", OptionType::Config, dummy));

    pagePid.AddOption(MenuOption("Set P", OptionType::Config, setPCallback));
    pagePid.AddOption(MenuOption("Return", OptionType::Page, &pageFirst));

    menu.setDefaultMenuPage(&pageFirst);


    // Constructs the new thread and runs it. Does not block execution.
    std::thread t1(handleButtons, std::ref(allSignals));
    t1.join();

    refresh();
    endwin();
}