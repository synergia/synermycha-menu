#include "Display.hh"

namespace utils
{

char displayBuff[maxRows][maxColumns];

Display::Display(AllSignals& sigs) : mAllSignals(sigs)
{
    mAllSignals.displayBuffor.connect<Display, &Display::ShowDisplayBuffor>(*this);
}

void Display::ShowDisplayBuffor()
{
    clear();
    refresh();
    for (int i = 0; i < maxRows; i++)
    {
        printw(displayBuff[i]);
        printw("\n");
    }
}

}