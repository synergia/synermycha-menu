#pragma once

#include "Signal.hh"

struct AllSignals
{
    sigslot::signal<> buttonUp;
    sigslot::signal<> buttonDown;
    sigslot::signal<> buttonEnter;

    sigslot::signal<> displayBuffor;

    sigslot::signal<int&> getP;
    sigslot::signal<int&> getI;
    sigslot::signal<int&> getD;

    sigslot::signal<int> setP;
    sigslot::signal<int> setI;
    sigslot::signal<int> setD;
};