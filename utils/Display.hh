#pragma once

#include <ncurses.h>
#include "utils/AllSignals.hh"

namespace utils
{

// max 4 rows on display (to adjust)
// and max 20 characters
constexpr int maxRows = 4;
constexpr int maxColumns = 20;

extern char displayBuff[maxRows][maxColumns];

class Display : public Observer
{
public:
    Display(utils::AllSignals& sigs);
    void ShowDisplayBuffor();

private:
    AllSignals& mAllSignals;
};

}