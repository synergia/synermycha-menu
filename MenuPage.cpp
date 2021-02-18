#include "MenuPage.hh"
#include <iostream>
#include "DisplayBuffor.hh"
#include <cstring>
#include <algorithm>

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
    for (int i = 0; i < maxRows; i++)
        for (int j = 0; j < maxColumns; j++)
            displayBuff[i][j] = ' ';

    constexpr int startPosColumn = 3;
    int startPosRow = 0;

    startPosRow = std::max(0, mChoosenOption + 1 - maxRows);
    startPosRow = std::min(startPosRow, mNumberOfOptions - maxRows);
    startPosRow = std::max(startPosRow, 0);

    char text[maxColumns];
    for (int i = 0; i < maxRows && i < mNumberOfOptions; i++)
    {
        memset(text, 0, sizeof(text));
        mOptions[startPosRow].getTextToDisplay(text);
        if (startPosRow == mChoosenOption and mDisplayPromt)
        {
            sprintf(displayBuff[i], "> %s", text);
        }
        else
        {
            sprintf(displayBuff[i], "  %s", text);
        }
        startPosRow++;
    }
}
