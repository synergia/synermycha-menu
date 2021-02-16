#pragma once

#include "Signal.hh"

struct AllSignals
{
    sigslot::signal<> buttonUp;
    sigslot::signal<> buttonDown;
    sigslot::signal<> buttonEnter;

    sigslot::signal<> displayBuffor;
};