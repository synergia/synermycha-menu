#pragma once

namespace utils
{

// max 4 rows on display (to adjust)
// and max 20 characters
constexpr int maxRows = 4;
constexpr int maxColumns = 20;

extern char displayBuff[maxRows][maxColumns];

}