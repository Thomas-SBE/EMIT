#include <iostream>
#include <termios.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

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

    // MISC
    buff->dline(L'#', EMITPoint(2,2), EMITPoint(92,28), EMITColor(EMIT_COLOR_RED, 0, 0));

    buff->render();

    // Waiting for user input
    struct termios oldSettings, newSettings;
    tcgetattr(fileno(stdin), &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &newSettings);
    while(1) 
    { 
        fd_set set;
        struct timeval tv;
        tv.tv_sec = 10;
        tv.tv_usec = 0;
        FD_ZERO(&set);
        FD_SET(fileno(stdin), &set);
        int res = select(fileno(stdin)+1, &set, NULL, NULL, &tv);
        if(res > 0) { char c; read(fileno(stdin), &c, 1); break; }
    }
    tcsetattr(fileno(stdin), TCSANOW, &oldSettings);

    buff->clear();

    buff->dframe(EMITRect(0,0,94,29), EMITColor(EMIT_COLOR_MAGENTA, 0, 0));
    buff->dtext(EMITTextUtil::inlinetxt(L"Buffer has been refreshed !\0", 90, EMIT_TEXT_JUSTIFY_CENTER).c_str(), EMITPoint(1, 15), EMITColor(0,0,0));

    buff->render();

    delete buff;
}
