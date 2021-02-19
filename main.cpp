#include <iostream>
#include "menu/Menu.hh"
#include "utils/AllSignals.hh"
#include "utils/DisplayBuffor.hh"
#include "menu/config_inline/ConfigInlineP.hh"
#include <ncurses.h>
#include <thread>
#include <cstring>
#include "utils/Signal.hh"

void handleButtons(utils::AllSignals& sig)
{
    int ch;
    while ((ch = getch()) != 'q') {
        switch(ch) {
            case KEY_UP: 
                sig.buttonUp.emit();
            break;

            case KEY_DOWN:
                sig.buttonDown.emit();
            break;

            case ' ':
                sig.buttonEnter.emit();
            break;
        }
    }
}

class Display : public utils::Observer
{
public:
    Display(utils::AllSignals& sigs) : mAllSignals(sigs)
    {
        mAllSignals.displayBuffor.connect<Display, &Display::ShowDisplayBuffor>(*this);
    }
    void ShowDisplayBuffor()
    {
        clear();
        refresh();
        for (int i = 0; i < utils::maxRows; i++)
        {
            printw(utils::displayBuff[i]);
            printw("\n");
        }
    }
    utils::AllSignals& mAllSignals;
};

int main()
{
    using namespace menu;

    utils::AllSignals allSignals;
    Display display(allSignals);

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    Menu menu(allSignals);
    MenuPage pageFirst;
    MenuPage pagePid;

    config_inline::ConfigInlineP configP{5};
    auto dummy = [](utils::AllSignals&){};
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