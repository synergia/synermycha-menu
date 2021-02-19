#pragma once

#include <array>
#include "MenuPage.hh"
#include "AllSignals.hh"
#include "Observer.hh"

constexpr int maxNrOfItemMenus{10};

enum class MenuState
{
    Normal, // switching in options
    Changing // giving controll to option
};


class Menu : public Observer
{
public:
    Menu(AllSignals& sig);

    void setDefaultMenuPage(MenuPage* page);
    void onButtonDownPressed();
    void onButtonUpPressed();
    void onEnterPressed();

private:
    AllSignals& mSignals;
    MenuPage* mActualPage;
    MenuState mState;
};