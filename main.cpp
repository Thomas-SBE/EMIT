#include <iostream>

#include "emit.h"

int main()
{
    EMITBuffer* buff = new EMITBuffer(94, 42);

    /*buff->dtext("Welcome nerds", EMITPoint(1,1), EMITColor(EMIT_COLOR_BLACK, EMIT_COLOR_WHITE, 0));
    buff->dtext("Un text super long de merde", EMITPoint(1, 3), EMITColor(EMIT_COLOR_RED, 0, 0));
    buff->dtext("Supergras", EMITPoint(40, 3), EMITColor(EMIT_COLOR_RED, 0, EMIT_DECORATOR_BOLD | EMIT_DECORATOR_UNDERLINE));
    */
    buff->dframe(EMITRect(0,0,94,42), EMITColor(EMIT_COLOR_BLUE, 0, 0));
    /*buff->dframe(EMITRect(2,15,76,14), EMITColor(EMIT_COLOR_MAGENTA, 0, 0));

    buff->drect(EMITRect(1, 4, 78, 1), EMITColor(0, EMIT_COLOR_MAGENTA, 0));
    buff->dcrect('A', EMITRect(1, 5, 78, 2), EMITColor(EMIT_COLOR_MAGENTA, 0, 0));

    buff->dchar('+', EMITPoint(3,16), EMITColor(EMIT_COLOR_YELLOW, 0, 0));
    */

    buff->dframe(EMITRect(20, 7, 40, 15), EMITColor(EMIT_COLOR_RED, 0, 0));
    buff->dtextarea(L"Ceci est un texte de demonstration pour les zones de texte definies et casse par mot a chaque ligne !\0", EMITRect(21, 8, 38, 13), EMITColor(EMIT_COLOR_WHITE, 0, EMIT_DECORATOR_BOLD), 0);
    buff->dtextarea(L"Ceci est un texte de demonstration pour les zones de texte definies et casse par mot a chaque ligne !\0", EMITRect(21, 14, 38, 5), EMITColor(EMIT_COLOR_WHITE, 0, 0), EMIT_TEXT_WORDBREAK);

    EMITBuffer* sb = new EMITBuffer(29,4);
    sb->dframe(EMITRect(0,0,29,4), EMITColor(EMIT_COLOR_GREEN, 0, 0));
    sb->dtext(L"Coucou le nouveau subbuffer\0", EMITPoint(1,1), EMITColor(EMIT_COLOR_GREEN, 0, EMIT_DECORATOR_REVERSED));
    sb->dtext(EMITTextUtil::inlinetxt(L"Centered !\0", 27, EMIT_TEXT_JUSTIFY_CENTER).c_str(), EMITPoint(1,2), EMITColor(EMIT_COLOR_GREEN, 0, 0));

    buff->dbuffer(sb, EMITPoint(1,1));

    buff->render();
    
    delete buff;
    delete sb;
}
