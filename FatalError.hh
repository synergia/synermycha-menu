#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

static void FatalError(const char* message)
{
    clear();
    printw("FATAL ERROR!: %s", message);
    refresh();
    sleep(5);
    abort();
}