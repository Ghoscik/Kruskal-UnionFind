#pragma once
#define HCONSOLE_H
#ifdef HCONSOLE_H

#include <Windows.h>
#include <iostream>

#define COLOR_GRAY 8
#define COLOR_DARKBLUE 9
#define COLOR_GREEN 10
#define COLOR_BLUE 11
#define COLOR_RED 12
#define COLOR_MAGENTA 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

// 8 - Gray
// 9 - Blue
// 10 - Green
// 11 - Light Blue
// 12 - Red
// 13 - Magenta
// 14 - Yellow
// 15 - White



class hConsole {
private:
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    uint16_t MARGIN_LEFT;
    uint16_t MARGIN_TOP;
    uint16_t currX = 0;
    uint16_t currY = 0; 
    uint16_t columnWidth = 20; 
    uint8_t columnCount = 0;

public:
    hConsole(uint16_t leftMargin, uint16_t topMargin)
    {
        MARGIN_LEFT = leftMargin;
        MARGIN_TOP = topMargin;
        currX = 0 + leftMargin;
        currY = 0 + topMargin;
    }
    void setCursor(uint16_t x, uint16_t y);
    void changeColor(uint16_t value);

    uint16_t getMarginL() { return MARGIN_LEFT; }
    uint16_t getMarginT() { return MARGIN_TOP; }
    uint16_t getConsoleWidth();

    void colorText(std::string text, uint8_t color, uint8_t defaultColor = COLOR_WHITE);
    void nextColumn();
    void println(std::string text, uint8_t color = COLOR_WHITE);

    void setColumnWidth(uint16_t width) { columnWidth = width; }
};

void hConsole::setCursor(uint16_t x, uint16_t y)
{
    COORD pos = { (uint16_t)x + MARGIN_LEFT, (uint16_t)y + MARGIN_TOP };
    SetConsoleCursorPosition(hCon, pos);
}

void hConsole::changeColor(uint16_t color)
{
    SetConsoleTextAttribute(hCon, color);
}

void hConsole::colorText(std::string text, uint8_t color, uint8_t defaultColor)
{
    changeColor(color);
    std::cout << text;
    changeColor(defaultColor);
}

uint16_t hConsole::getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hCon, &csbi))
        return csbi.srWindow.Right - csbi.srWindow.Left + 1; 

    return 0; 
}

void hConsole::nextColumn()
{
    currX += columnWidth;
    if (currX > getConsoleWidth())
    {
        currX = 0;
        currY++;
        columnCount++;
    }
}

void hConsole::println(std::string text, uint8_t color)
{
    setCursor(currX, currY);
    colorText(text, color);
    currX = columnWidth * columnCount;
    currY++;
}


#endif
