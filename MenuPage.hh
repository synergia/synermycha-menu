#pragma once

#include <array>
#include "MenuOption.hh"

constexpr int maxNrOfOptions = 10;

class MenuPage
{
public:
    MenuPage() = default;
    void AddOption(MenuOption option);
    void prepareMenuPageForDisplay();
    void shiftToNextOption();
    void shiftToPreviousOption();

    void passEnterToChoosenOption();
    void passButtonUpToChoosenOption();
    void passButtonDownToChoosenOption();

    OptionType getTypeOfChoosenOption() const;
    MenuPage* getPageOfChoosenOption();
    OptionCallbackType getCallbackOfChoosenOption();

private:

    std::array<MenuOption, maxNrOfOptions> mOptions;
    int mNumberOfOptions = 0;
    int mChoosenOption = 0;
};