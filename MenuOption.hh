#pragma once
#include "AllSignals.hh"

class MenuPage;

using OptionCallbackType = void(*)(AllSignals&);

enum class OptionType
{
    Page, // just next page of menu
    ConfigInline, // ability to change inline in page (buttons controll)
    ConfigCallback // changes or something else on new page (buttons controll)
};

enum class EnterType
{
    Enter, // we start configuring this option
    Exit // we exit from this option
};

class MenuOption
{
public:
    MenuOption();
    // for Page
    MenuOption(const char* name, OptionType type, MenuPage* page);
    // for ConfigInline
    MenuOption(const char* name, OptionType type);
    // for ConfigCallback
    MenuOption(const char* name, OptionType type, OptionCallbackType callback);
    
    void onEnter();
    void onButtonUp();
    void onButtonDown();

    const char* getTextToDisplay() const;
    OptionType getType() const;
    MenuPage* getPage();
    OptionCallbackType getCallback();

private:
    void checkDependencies();

    const char* mName;
    OptionType mType;
    EnterType mEnterType;

    MenuPage* mPage = nullptr;
    OptionCallbackType mCallback = nullptr;

    // used only in ConfigInline type
    int mOptionValue;
};