#include "Menu.hh"
#include <iostream>


Menu::Menu(AllSignals& sig)
    : mSignals{sig},
      mState(MenuState::Normal)
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
    if (mState == MenuState::Normal)
    {
        mActualPage->shiftToNextOption();
        mActualPage->prepareMenuPageForDisplay();
        mSignals.displayBuffor();
    }
    else // MenuState::Changing
    {
        mActualPage->passButtonDownToChoosenOption();
        // ConfigCallback is drawing by its own
        if (mActualPage->getTypeOfChoosenOption() not_eq OptionType::ConfigCallback)
        {
            mActualPage->prepareMenuPageForDisplay();
            mSignals.displayBuffor();
        }
    }
}

void Menu::onButtonUpPressed()
{
    if (mState == MenuState::Normal)
    {
        mActualPage->shiftToPreviousOption();
        mActualPage->prepareMenuPageForDisplay();
        mSignals.displayBuffor();
    }
    else // MenuState::Changing
    {
        mActualPage->passButtonUpToChoosenOption();
        // ConfigCallback is drawing by its own
        if (mActualPage->getTypeOfChoosenOption() not_eq OptionType::ConfigCallback)
        {
            mActualPage->prepareMenuPageForDisplay();
            mSignals.displayBuffor();
        }
    }
}

void Menu::onEnterPressed()
{
    OptionType optionType = mActualPage->getTypeOfChoosenOption();
    if (mState == MenuState::Normal)
    {
        if (optionType == OptionType::Page)
        {
            auto page = mActualPage->getPageOfChoosenOption();
            if (page != nullptr)
            {
                setDefaultMenuPage(page);
               // mActualPage->prepareMenuPageForDisplay();
               // mSignals.displayBuffor();
            }
        }
        else if (optionType == OptionType::ConfigInline)
        {
            mActualPage->passEnterToChoosenOption();
            mActualPage->setDisplayPromt(false);
            mState = MenuState::Changing;
        }
    }
    else // MenuState::Changing
    {
        if (optionType == OptionType::ConfigInline)
        {
            mActualPage->passEnterToChoosenOption();
            mActualPage->setDisplayPromt(true);
            mState = MenuState::Normal;
        }
    }
    mActualPage->prepareMenuPageForDisplay();
    mSignals.displayBuffor();
}
