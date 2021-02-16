#include "MenuOption.hh"

MenuOption::MenuOption()
{

}

MenuOption::MenuOption(const char* name, OptionType type, MenuPage* page)
    : mName(name),
      mType(type),
      mPage(page)
{
}

MenuOption::MenuOption(const char* name, OptionType type, OptionCallbackType callback)
    : mName(name),
      mType(type),
      mCallback(callback)
{
}

const char* MenuOption::getName() const
{
    return mName;
}

OptionType MenuOption::getType() const
{
    return mType;
}

MenuPage* MenuOption::getPage()
{
    return mPage;
}

OptionCallbackType MenuOption::getCallback()
{
    return mCallback;
}