#include <iostream>

#include "emit.h"

int main()
{
    EMITBuffer* buff = new EMITBuffer(94, 30);

    // HEADER SECTION
    buff->drect(EMITRect(0,0,94,1), EMITColor(0, EMIT_COLOR_WHITE, 0));
    buff->dtext(EMITTextUtil::inlinetxt(L"EMIT - Extended & More Intuitive Terminal Demo.", 94, EMIT_TEXT_JUSTIFY_CENTER).c_str(), EMITPoint(0, 0), EMITColor(EMIT_COLOR_BLACK, EMIT_COLOR_WHITE, EMIT_DECORATOR_BOLD));

    // TEXT SECTION
    buff->dtextarea(L"This is a demonstration of the usage of EMIT in your C++ terminal applications\nDrawing, displaying, editing. Everything you'll need to make a dynamic GUI for your applications !\0", EMITRect(0,2,94,26), EMITColor(), EMIT_TEXT_WORDBREAK);
    buff->dtext(EMITTextUtil::inlinetxt(L"BERTHELOT Thomas - EMIT Main Dev.\0", 93, EMIT_TEXT_JUSTIFY_RIGHT).c_str(), EMITPoint(0, 28), EMITColor(EMIT_COLOR_GREEN, 0, 0));
    
    // FOOTER SECTION
    buff->drect(EMITRect(0,29,94,1), EMITColor(0, EMIT_COLOR_GREEN, 0));
    buff->dtext(L"This library is currently UNIX exclusive !", EMITPoint(1, 29), EMITColor(EMIT_COLOR_BLACK, EMIT_COLOR_GREEN, EMIT_DECORATOR_UNDERLINE));

    buff->render();
    
    delete buff;
}
