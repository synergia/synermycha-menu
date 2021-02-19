#pragma once

#include "Signal.hh"

struct AllSignals
{
    Mysigslot::signal<void(void)> buttonUp;
    Mysigslot::signal<void(void)> buttonDown;
    Mysigslot::signal<void(void)> buttonEnter;

    Mysigslot::signal<void(void)> displayBuffor;
};