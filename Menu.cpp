#include "Menu.hh"
#include <iostream>


Menu::Menu(AllSignals& sig) : mSignals{sig}
{
    sig.buttonUp.connect(&Menu::onButtonUpPressed, this);
    sig.buttonDown.connect(&Menu::onButtonDownPressed, this);
    sig.buttonEnter.connect(&Menu::onEnterPressed, this);
}

void Menu::setDefaultMenuPage(MenuPage* page)
{
    mActualPage = page;
}

void Menu::onButtonDownPressed()
{
    //std::cout << "Shifting Down" << std::endl;
    mActualPage->shiftToNextOption();
    mActualPage->prepareMenuPageForDisplay();
    mSignals.displayBuffor();
}

void Menu::onButtonUpPressed()
{
    //std::cout << "Shifting Up" << std::endl;
    mActualPage->shiftToPreviousOption();
    mActualPage->prepareMenuPageForDisplay();
    mSignals.displayBuffor();
}

void Menu::onEnterPressed()
{
    OptionType type = mActualPage->getTypeOfChoosenOption();
    if (type == OptionType::Page)
    {
        auto page = mActualPage->getPageOfChoosenOption();
        if (page != nullptr)
        {
            setDefaultMenuPage(page);
            mActualPage->prepareMenuPageForDisplay();
            mSignals.displayBuffor();
        }
    }
    else
    {
        mActualPage->getCallbackOfChoosenOption()(mSignals);
    }
}
