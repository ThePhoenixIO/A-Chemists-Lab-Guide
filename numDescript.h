#pragma once
#ifndef numDescript
#define numDescript

// Code by einpoklum
// https://stackoverflow.com/questions/21548099/function-for-getting-the-ordinal-of-a-number
const char* suffix(int n)
{
    static const char suffixes[][3] = { "th", "st", "nd", "rd" };
    auto ord = n % 100;
    if (ord / 10 == 1) { ord = 0; }
    ord = ord % 10;
    if (ord > 3) { ord = 0; }
    return suffixes[ord];
}

#endif // !numDescript