#include "ConfigInlineP.hh"
#include <cstdio>


ConfigInlineP::ConfigInlineP(int P) : mP(P)
{
}

void ConfigInlineP::handleButtonUp()
{
    ++mP;
}

void ConfigInlineP::handleButtonDown()
{
    --mP;
}

void ConfigInlineP::fillLabel(char* text, int maxLen, bool prompt)
{
    if (prompt)
    {
        sprintf(text, "P    >%d", mP);
    }
    else
    {
        sprintf(text, "P     %d", mP);
    }
}