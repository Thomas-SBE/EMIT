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
struct emit_cell { char* prefix_code; wchar_t data; char* sufix_code; };
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

// --------------  Utilitaires , Gestion des Text -------------- //

namespace EMITTextUtil
{
    std::wstring inlinetxt(const wchar_t* text, int width, char flags);
}

// --------------  Buffer ( Gestion des cellules ) -------------- //
class EMITBuffer
{
    private:
        EMITCell buffer;
        int buff_size;
        EMITPoint dimensions;
        std::vector< void* >* clrptrs;
        char* nullstr;
    protected:
        static void shift_up(int times);
    public:
        EMITBuffer(int width, int height);
        ~EMITBuffer();
        void render();
        void clear();
        EMITPoint getDimensions();
        void dchar(const wchar_t c, EMITPoint position, EMITColor color);
        void dtext(const wchar_t* text, EMITPoint position, EMITColor color);
        void dframe(EMITRect rect, EMITColor color);
        void dcrect(char c, EMITRect rect, EMITColor color);
        void drect(EMITRect rect, EMITColor color);
        void dtextarea(const wchar_t* text, EMITRect rect, EMITColor color, char flags);
        void dbuffer(EMITBuffer* sub_buffer, EMITPoint position);
        void dblank(EMITRect rect);
        void dline(const wchar_t c, EMITPoint start, EMITPoint end, EMITColor color);
};