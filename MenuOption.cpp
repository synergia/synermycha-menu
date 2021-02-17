#include "MenuOption.hh"
#include "FatalError.hh"

MenuOption::MenuOption()
{

}

MenuOption::MenuOption(const char* name, OptionType type, MenuPage* page)
    : mName(name),
      mType(type),
      mEnterType(EnterType::Enter),
      mPage(page),
      mCallback(nullptr),
      mOptionValue(0)
{
    checkDependencies();
}

MenuOption::MenuOption(const char* name, OptionType type)
    : mName(name),
      mType(type),
      mEnterType(EnterType::Enter),
      mPage(nullptr),
      mCallback(nullptr),
      mOptionValue(0)
{
    checkDependencies();
}

MenuOption::MenuOption(const char* name, OptionType type, OptionCallbackType callback)
    : mName(name),
      mType(type),
      mEnterType(EnterType::Enter),
      mCallback(callback),
      mPage(nullptr),
      mOptionValue(0)
{
    checkDependencies();
}

void MenuOption::onEnter()
{

}

void MenuOption::onButtonUp()
{

}

void MenuOption::onButtonDown()
{

}

const char* MenuOption::getTextToDisplay() const
{
    if (mType == OptionType::Page)
    {
        return mName;
    }
    else if (mType == OptionType::ConfigInline)
    {
        return mName;
    }
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

void MenuOption::checkDependencies()
{
    if (mType == OptionType::Page)
    {
        if (mPage == nullptr)
        {
            FatalError("MenuOption with Page type requires valid mPage pointer!");
        }
    }
    else if (mType == OptionType::ConfigCallback)
    {
        if (mCallback == nullptr)
        {
            FatalError("MenuOption with ConfigCallback type requires valid mCallback pointer!");
        }
    }
}