#include <iostream>
#include "menu/Menu.hh"
#include "utils/AllSignals.hh"
#include "utils/Display.hh"
#include "menu/config_inline/ConfigInlineSingleValue.hh"
#include <ncurses.h>
#include <thread>
#include <cstring>

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


int main()
{
    using namespace menu;

    utils::AllSignals allSignals;
    utils::Display display(allSignals);

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    Menu menu(allSignals);
    MenuPage pageFirst;
    MenuPage pagePid;
    MenuPage pageCos;

    config_inline::ConfigInlineSingleValue<int> configP("P", 5, 2);
    config_inline::ConfigInlineSingleValue<int> configI("I", -2, 1);
    config_inline::ConfigInlineSingleValue<double> configD("D", 8.5, 0.1);

    config_inline::ConfigInlineSingleValue<int> configCos("cos", -55, 5);
    config_inline::ConfigInlineSingleValue<bool> configBool("win?", true);

    auto dummy = [](utils::AllSignals&){};
    pageFirst.AddOption(MenuOption("PID", OptionType::Page, &pagePid));
    pageFirst.AddOption(MenuOption("cos", OptionType::Page, &pageCos));
    pageFirst.AddOption(MenuOption("Opcja 2", OptionType::ConfigCallback, dummy));

    pagePid.AddOption(MenuOption("Set P", OptionType::ConfigInline, &configP));
    pagePid.AddOption(MenuOption("Set I", OptionType::ConfigInline, &configI));
    pagePid.AddOption(MenuOption("Set D", OptionType::ConfigInline, &configD));
    pagePid.AddOption(MenuOption("Return", OptionType::Page, &pageFirst));

    pageCos.AddOption(MenuOption("ustaw cos", OptionType::ConfigInline, &configCos));
    pageCos.AddOption(MenuOption("ustaw boola", OptionType::ConfigInline, &configBool));
    pageCos.AddOption(MenuOption("Return", OptionType::Page, &pageFirst));

    menu.setDefaultMenuPage(&pageFirst);


    // Constructs the new thread and runs it. Does not block execution.
    std::thread t1(handleButtons, std::ref(allSignals));
    t1.join();

    refresh();
    endwin();
}