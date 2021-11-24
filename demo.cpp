#include <iostream>

#include "emit.h"

int main()
{
    EMITBuffer* buff = new EMITBuffer(80, 30);

    // HEADER SECTION
    buff->drect(EMITRect(0,0,80,1), EMITColor(0, EMIT_COLOR_WHITE, 0));
    buff->dtext("EMIT - Extended & More Intuitive Terminal Demo.", EMITPoint(2, 0), EMITColor(EMIT_COLOR_BLACK, EMIT_COLOR_WHITE, EMIT_DECORATOR_BOLD));

    // TEXT SECTION
    buff->dtext("This is a demonstration of the usage of EMIT in your C++ terminal applications, drawing, displaying, editing. Everything you'll need to make a dynamic GUI for your applications !", EMITPoint(0,2), EMITColor());

    // FOOTER SECTION
    buff->drect(EMITRect(0,29,80,1), EMITColor(0, EMIT_COLOR_BLUE, 0));
    buff->dtext("This library is currently UNIX exclusive !", EMITPoint(1, 29), EMITColor(EMIT_COLOR_BLACK, EMIT_COLOR_BLUE, EMIT_DECORATOR_BOLD | EMIT_DECORATOR_UNDERLINE));

    buff->render();
    
    delete buff;
}
