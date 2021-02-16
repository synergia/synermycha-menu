#pragma once
#include "AllSignals.hh"

class MenuPage;

using OptionCallbackType = void(*)(AllSignals&);

enum class OptionType
{
    Page,
    Config
};

class MenuOption
{
public:
    MenuOption();
    MenuOption(const char* name, OptionType type, MenuPage* page);
    MenuOption(const char* name, OptionType type, OptionCallbackType callback);
    
    const char* getName() const;
    OptionType getType() const;
    MenuPage* getPage();
    OptionCallbackType getCallback();

private:
    const char* mName;
    OptionType mType;

    MenuPage* mPage = nullptr;
    OptionCallbackType mCallback = nullptr;
};