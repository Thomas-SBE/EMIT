#include <iostream>

#include "emit.h"

int main()
{
    EMITBuffer* buff = new EMITBuffer(80, 30);

    buff->dtext("Welcome nerds", EMITPoint(1,1), EMITColor(EMIT_COLOR_BLACK, EMIT_COLOR_WHITE, 0));
    buff->dtext("Un text super long de merde", EMITPoint(1, 3), EMITColor(EMIT_COLOR_RED, 0, 0));

    buff->dframe(EMITRect(0,0,80,30), EMITColor(EMIT_COLOR_BLUE, 0, 0));
    buff->dframe(EMITRect(2,15,76,14), EMITColor(EMIT_COLOR_MAGENTA, 0, 0));

    buff->dframe(EMITRect(5,5,10,1), EMITColor(EMIT_COLOR_MAGENTA, EMIT_COLOR_MAGENTA, 0));

    buff->render();

    delete buff;
}