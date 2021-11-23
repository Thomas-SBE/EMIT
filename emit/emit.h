#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>

#include "emitcst.h"

// --------------  Structure des cellules (P/D/S) -------------- //
struct emit_cell { char* prefix_code; char data; char* sufix_code; };
typedef emit_cell* EMITCell;

// --------------  Color ( Decorations & stuff ) -------------- //
class EMITColor
{
    public:
        char fcolor;
        char bcolor;
        char decorator;
        EMITColor();
        EMITColor(char decorator);
        EMITColor(char fcolor, char bcolor, char decorator);
        char* digest(std::vector<void*> &freelist);
};

// --------------  Point ( Position ou dimension ) -------------- //
class EMITPoint
{
    public:
        int x;
        int y;
        EMITPoint();
        EMITPoint(int x, int y);
};

// --------------  Rect ( Position & Dimensions ) -------------- //
class EMITRect
{
    public:
        EMITPoint position;
        EMITPoint dimensions;
        EMITRect();
        EMITRect(EMITPoint pos, EMITPoint dim);
        EMITRect(int x, int y, int w, int h);
};

// --------------  Buffer ( Gestion des cellules ) -------------- //
class EMITBuffer
{
    private:
        EMITCell buffer;
        int buff_size;
        EMITPoint dimensions;
        std::vector< void* >* clrptrs;
        char* nullstr;
    public:
        EMITBuffer(int width, int height);
        ~EMITBuffer();
        void render();
        void dtext(const char* text, EMITPoint position, EMITColor color);
        void dframe(EMITRect rect, EMITColor color);
};