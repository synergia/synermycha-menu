#include "MenuPage.hh"
#include <iostream>
#include "utils/DisplayBuffor.hh"
#include <cstring>
#include <algorithm>

namespace menu
{

void MenuPage::AddOption(MenuOption option)
{
    if (mNumberOfOptions < maxNrOfOptions)
    {
        mOptions[mNumberOfOptions] = option;
        ++mNumberOfOptions;
    }
}

void MenuPage::shiftToNextOption()
{
    if (mChoosenOption + 1 < mNumberOfOptions)
    {
        ++mChoosenOption;
    }
}

void MenuPage::shiftToPreviousOption()
{
    if (mChoosenOption > 0)
    {
        --mChoosenOption;
    }
}

void MenuPage::passEnterToChoosenOption()
{
    mOptions[mChoosenOption].onEnter();
}

void MenuPage::passButtonUpToChoosenOption()
{
    mOptions[mChoosenOption].onButtonUp();
}

void MenuPage::passButtonDownToChoosenOption()
{
    mOptions[mChoosenOption].onButtonDown();
}

OptionType MenuPage::getTypeOfChoosenOption() const
{
    mOptions[mChoosenOption].getType();
}

MenuPage* MenuPage::getPageOfChoosenOption()
{
    mOptions[mChoosenOption].getPage();
}

OptionCallbackType MenuPage::getCallbackOfChoosenOption()
{
    mOptions[mChoosenOption].getCallback();
}

void MenuPage::setDisplayPromt(bool promt)
{
    mDisplayPromt = promt;
}

void MenuPage::prepareMenuPageForDisplay()
{
    for (int i = 0; i < utils::maxRows; i++)
        for (int j = 0; j < utils::maxColumns; j++)
            utils::displayBuff[i][j] = ' ';

    constexpr int startPosColumn = 3;
    int startPosRow = 0;

    startPosRow = std::max(0, mChoosenOption + 1 - utils::maxRows);
    startPosRow = std::min(startPosRow, mNumberOfOptions - utils::maxRows);
    startPosRow = std::max(startPosRow, 0);

    char text[utils::maxColumns];
    for (int i = 0; i < utils::maxRows && i < mNumberOfOptions; i++)
    {
        memset(text, 0, sizeof(text));
        mOptions[startPosRow].getTextToDisplay(text);
        if (startPosRow == mChoosenOption and mDisplayPromt)
        {
            sprintf(utils::displayBuff[i], "> %s", text);
        }
        else
        {
            sprintf(utils::displayBuff[i], "  %s", text);
        }
        startPosRow++;
    }
}

}