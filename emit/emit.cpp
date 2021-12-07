#include "emit.h"

EMITPoint::EMITPoint() { this->x = 0; this->y = 0; }
EMITPoint::EMITPoint(int x, int y) { this->x = x; this->y = y; }

EMITRect::EMITRect() { this->position = EMITPoint(); this->dimensions = EMITPoint(); }
EMITRect::EMITRect(EMITPoint pos, EMITPoint dim) { this->position = EMITPoint(pos); this->dimensions = EMITPoint(dim); }
EMITRect::EMITRect(int x, int y, int w, int h) { this->position = EMITPoint(x,y); this->dimensions = EMITPoint(w,h); }

EMITColor::EMITColor() { this->decorator = 0; this->bcolor = 0x0; this->fcolor = 0x0; }
EMITColor::EMITColor(char decorator) { this->decorator = decorator; this->bcolor = 0x0; this->fcolor = 0x0; }
EMITColor::EMITColor(char fcolor, char bcolor, char decorator) { this->decorator = decorator; this->bcolor = bcolor; this->fcolor = fcolor; }
char* EMITColor::digest(std::vector<void*> &freelist) 
{
    if(fcolor == 0 && bcolor == 0 && decorator == 0){
        char* nlstr = (char*)malloc(1);
        nlstr[0] = '\0';
        freelist.push_back(nlstr);
        return nlstr;
    }
    int cnt = 0 + (this->fcolor == 0 ? 0 : 2) + (this->bcolor == 0 ? 0 : 2) + (this->bcolor != 0 && this->fcolor != 0 ? 1 : 0);
    int cntd = (this->decorator != 0 ? 2 : 0);
    char* data = (char*)malloc(5+cnt+cntd+1);
    freelist.push_back(data);
    char d[] = "\u001b[\0";
    strcpy(data, d);
    if(bcolor != 0){
        char tb[3] = {0, 0, '\0'};
        tb[0] = 52;
        tb[1] = 47+bcolor;
        strcat(data, tb);
        if(fcolor != 0) strcat(data, ";\0");
    }
    if(fcolor != 0){
        char tf[3] = {0, 0, '\0'};
        tf[0] = 51;
        tf[1] = 47+fcolor;
        strcat(data, tf);
    }
    if(decorator & EMIT_DECORATOR_RESET){strcat(data, ";0\0");}
    if(decorator & EMIT_DECORATOR_BOLD){strcat(data, ";1\0");}
    if(decorator & EMIT_DECORATOR_REVERSED){strcat(data, ";7\0");}
    if(decorator & EMIT_DECORATOR_UNDERLINE){strcat(data, ";4\0");}
    strcat(data, "m\0");
    return data;
}

EMITBuffer::EMITBuffer(int width, int height)
{
    nullstr = (char*)malloc(1);
    nullstr[0] = '\0';
    buffer = (EMITCell)malloc(sizeof(struct emit_cell) * width * height);
    for(int i = 0; i < width*height; i++) { buffer[i].data = ' '; buffer[i].prefix_code = nullstr; buffer[i].sufix_code = nullstr; }
    buff_size = width*height;
    dimensions = EMITPoint(width, height);
    clrptrs = new std::vector< void* >();
}

EMITBuffer::~EMITBuffer()
{
    std::vector< void* >::iterator i;
    for(i = clrptrs->begin(); i != clrptrs->end(); i++) free(*i);
    delete clrptrs;
    free(nullstr);
    free(buffer);
}

EMITPoint EMITBuffer::getDimensions() { return dimensions; }

void EMITBuffer::render() { for(int i = 0; i < buff_size; i++) { printf("%s%c%s", buffer[i].prefix_code, buffer[i].data, buffer[i].sufix_code); } }

void EMITBuffer::dchar(const wchar_t c, EMITPoint position, EMITColor color)
{
    if(position.x >= dimensions.x || position.y >= dimensions.y) { printf("EMITException : EMITBuffer overflow, position [%d,%d] exceeds the buffer size !\n", position.x, position.y); exit(1); }
    char* cls = color.digest(*clrptrs);
    char* rs = EMITColor(EMIT_DECORATOR_RESET).digest(*clrptrs);
    buffer[(position.y*dimensions.x)+position.x].prefix_code = cls;
    buffer[(position.y*dimensions.x)+position.x].sufix_code = rs;
    buffer[(position.y*dimensions.x)+position.x].data = c;
}


void EMITBuffer::dtext(const wchar_t* text, EMITPoint position, EMITColor color)
{
    char* cls = color.digest(*clrptrs);
    char* rs = EMITColor(EMIT_DECORATOR_RESET).digest(*clrptrs);
    int l = wcslen(text);
    if(position.x > dimensions.x || position.y > dimensions.y || position.x + l > buff_size) { wprintf(L"EMITException : EMITBuffer overflow at dtext for positions [%d,%d] !\n", position.x, position.y); exit(1); }
    for(int i = 0; i < l; i++) {
        buffer[(position.y*dimensions.x)+position.x+i].data = text[i];
        buffer[(position.y*dimensions.x)+position.x+i].prefix_code = cls;
        buffer[(position.y*dimensions.x)+position.x+i].sufix_code = rs;
    }
}

void EMITBuffer::dframe(EMITRect rect, EMITColor color)
{
    if(rect.position.x > dimensions.x || rect.position.y > dimensions.y || rect.position.x + rect.dimensions.x > dimensions.x || rect.position.y + rect.dimensions.y > dimensions.y) { printf("EMITException : EMITBuffer overflow at dframe for positions [%d,%d] sized (%d,%d) !\n", rect.position.x, rect.position.y, rect.dimensions.x, rect.dimensions.y); exit(1); }
    char* pf = color.digest(*clrptrs);
    char* rs = EMITColor(EMIT_DECORATOR_RESET).digest(*clrptrs);
    for(int i = rect.position.x; i < rect.position.x + rect.dimensions.x; i++)
    {
        for(int y = rect.position.y; y < rect.position.y + rect.dimensions.y; y++)
        {
            if(i == rect.position.x || i == (rect.position.x + rect.dimensions.x)-1){
                if(y == rect.position.y || y == (rect.position.y + rect.dimensions.y)-1) { buffer[(dimensions.x*y)+i].data = '+'; buffer[(dimensions.x*y)+i].prefix_code = pf; buffer[(dimensions.x*y)+i].sufix_code = rs; }
                else { buffer[(dimensions.x*y)+i].data = '|'; buffer[(dimensions.x*y)+i].prefix_code = pf; buffer[(dimensions.x*y)+i].sufix_code = rs; }
            }else if(y == rect.position.y || y == (rect.position.y + rect.dimensions.y)-1) { buffer[(dimensions.x*y)+i].data = '-'; buffer[(dimensions.x*y)+i].prefix_code = pf; buffer[(dimensions.x*y)+i].sufix_code = rs;}
        }
    }
}

void EMITBuffer::dcrect(char c, EMITRect rect, EMITColor color)
{
    if(rect.position.x > dimensions.x || rect.position.y > dimensions.y || rect.position.x + rect.dimensions.x > dimensions.x || rect.position.y + rect.dimensions.y > dimensions.y) { printf("EMITException : EMITBuffer overflow at drect for positions [%d,%d] sized (%d,%d) !\n", rect.position.x, rect.position.y, rect.dimensions.x, rect.dimensions.y); exit(1); }
    char* pf = color.digest(*clrptrs);
    char* rs = EMITColor(EMIT_DECORATOR_RESET).digest(*clrptrs);
    for(int i = rect.position.x; i < rect.position.x + rect.dimensions.x; i++)
    {
        for(int y = rect.position.y; y < rect.position.y + rect.dimensions.y; y++)
        {
            buffer[(y*dimensions.x)+i].prefix_code = pf;
            buffer[(y*dimensions.x)+i].sufix_code = rs;
            buffer[(y*dimensions.x)+i].data = c;
        }
    }
}

void EMITBuffer::drect(EMITRect rect, EMITColor color) { this->dcrect(' ', rect, color); }

void EMITBuffer::dtextarea(const wchar_t* text, EMITRect rect, EMITColor color, char flags)
{
    if(rect.position.x > dimensions.x || rect.position.y > dimensions.y || rect.position.x + rect.dimensions.x > dimensions.x || rect.position.y + rect.dimensions.y > dimensions.y) { printf("EMITException : EMITBuffer overflow at dtextarea for positions [%d,%d] sized (%d,%d) !\n", rect.position.x, rect.position.y, rect.dimensions.x, rect.dimensions.y); exit(1); }
    if(flags & (EMIT_TEXT_JUSTIFY_LEFT | EMIT_TEXT_JUSTIFY_CENTER) || flags & (EMIT_TEXT_JUSTIFY_LEFT | EMIT_TEXT_JUSTIFY_RIGHT) || flags & (EMIT_TEXT_JUSTIFY_RIGHT | EMIT_TEXT_JUSTIFY_CENTER)) { printf("EMITException : EMITBuffer @dtextarea : Invalid flags combinaison !\n");}
    EMITPoint cpt = EMITPoint(0, 0);
    std::wstring _t = L"";
    const wchar_t* c;
    for(c = text; *c != '\0'; c++)
    {
        if(*c == '\n'){ this->dtext(_t.c_str(), EMITPoint(rect.position.x + cpt.x, rect.position.y + cpt.y), color); _t.clear(); cpt.x = 0; cpt.y++; continue; }
        _t.push_back(*c);
        if(flags & EMIT_TEXT_WORDBREAK)
        {
            if(*c != ' ') continue;
            if(_t.size() > (long unsigned int)(rect.dimensions.x - cpt.x)) { cpt.x = 0; cpt.y++; }
            this->dtext(_t.c_str(), EMITPoint(rect.position.x + cpt.x, rect.position.y + cpt.y), color);
            cpt.x += _t.size();
            _t.clear();
        }else{
            if(cpt.x == 0 && *c == ' ') continue;
            if(cpt.x >= rect.dimensions.x) { cpt.x = 0; cpt.y++; }
            this->dchar(*c, EMITPoint(rect.position.x + cpt.x, rect.position.y + cpt.y), color);
            cpt.x++;
        }
    }
    if(_t.size() > 0 && flags & EMIT_TEXT_WORDBREAK) 
    {
        if(_t.size() > (long unsigned int)(rect.dimensions.x - cpt.x)) { cpt.x = 0; cpt.y++; }
        this->dtext(_t.c_str(), EMITPoint(rect.position.x + cpt.x, rect.position.y + cpt.y), color);
    }
}

void EMITBuffer::dbuffer(EMITBuffer* sub_buffer, EMITPoint position)
{
    if(sub_buffer->getDimensions().x + position.x >= dimensions.x || sub_buffer->getDimensions().y + position.y >= dimensions.y)
    { printf("EMITException : EMITBuffer@dbuffer : Exceeded the base buffer size\n"); }

    for(int i = 0; i < sub_buffer->buff_size; i++)
    {
        buffer[position.x+(i%sub_buffer->getDimensions().x)+((position.y*dimensions.x)+(i/sub_buffer->getDimensions().x*dimensions.x))].data = sub_buffer->buffer[i].data;
        buffer[position.x+(i%sub_buffer->getDimensions().x)+((position.y*dimensions.x)+(i/sub_buffer->getDimensions().x*dimensions.x))].prefix_code = sub_buffer->buffer[i].prefix_code;
        buffer[position.x+(i%sub_buffer->getDimensions().x)+((position.y*dimensions.x)+(i/sub_buffer->getDimensions().x*dimensions.x))].sufix_code = sub_buffer->buffer[i].sufix_code;
    }
}

void EMITBuffer::dblank(EMITRect rect) { this->dcrect(' ', rect, EMITColor()); }

std::wstring EMITTextUtil::inlinetxt(const wchar_t* text, int width, char flags){
    std::wstring s = std::wstring(text);
    int l = s.size();
    if(flags != 2 && flags != 4 && flags != 8) { printf("EMITException : EMITTextUtil@inlinetext : Invalid flag !\n"); }
    if(flags & EMIT_TEXT_JUSTIFY_CENTER)
    {
        s.insert(s.begin(), (width-l)/2, L' ');
        s.insert(s.end(), (width-l)/2+1, L' ');
    }else if(flags & EMIT_TEXT_JUSTIFY_RIGHT){
        s.insert(s.begin(), (width-l), L' ');
    }else if(flags & EMIT_TEXT_JUSTIFY_LEFT){
        s.insert(s.end(), (width-l), L' ');
    }
    return s;
}

void EMITBuffer::dline(const wchar_t c, EMITPoint start, EMITPoint end, EMITColor color)
{
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int D = 2*dy - dx;
    int y = start.y;
    for(int x = start.x; x <= end.x; x++)
    {
        this->dchar(c, EMITPoint(x,y), color);
        if(D>0) { y++; D -= 2*dx; }
        D += 2*dy;
    }
}