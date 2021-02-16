#pragma once

#include <array>
#include "MenuPage.hh"
#include "AllSignals.hh"

constexpr int maxNrOfItemMenus{10};

class Menu
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
};