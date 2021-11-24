#include <iostream>

#include "emit.h"

int main()
{
    EMITBuffer* buff = new EMITBuffer(80, 30);

    buff->dtext("Welcome nerds", EMITPoint(1,1), EMITColor(EMIT_COLOR_BLACK, EMIT_COLOR_WHITE, 0));
    buff->dtext("Un text super long de merde", EMITPoint(1, 3), EMITColor(EMIT_COLOR_RED, 0, 0));

    buff->dtext("Supergras", EMITPoint(40, 3), EMITColor(EMIT_COLOR_RED, 0, EMIT_DECORATOR_BOLD | EMIT_DECORATOR_UNDERLINE));

    buff->dframe(EMITRect(0,0,80,30), EMITColor(EMIT_COLOR_BLUE, 0, 0));
    buff->dframe(EMITRect(2,15,76,14), EMITColor(EMIT_COLOR_MAGENTA, 0, 0));

    buff->drect(EMITRect(1, 4, 78, 1), EMITColor(0, EMIT_COLOR_MAGENTA, 0));
    buff->dcrect('A', EMITRect(1, 5, 78, 2), EMITColor(EMIT_COLOR_MAGENTA, 0, 0));

    buff->dchar('+', EMITPoint(3,16), EMITColor(EMIT_COLOR_YELLOW, 0, 0));

    buff->render();
    
    delete buff;
}
