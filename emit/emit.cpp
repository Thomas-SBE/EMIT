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
    if(decorator == EMIT_DECORATOR_RESET){strcat(data, ";0\0");}
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

void EMITBuffer::render() { for(int i = 0; i < buff_size; i++) { printf("%s%c%s", buffer[i].prefix_code, buffer[i].data, buffer[i].sufix_code); } }

void EMITBuffer::dtext(const char* text, EMITPoint position, EMITColor color)
{
    char* cls = color.digest(*clrptrs);
    char* rs = EMITColor(EMIT_DECORATOR_RESET).digest(*clrptrs);
    int l = strlen(text);
    if(position.x > dimensions.x || position.y > dimensions.y || position.x + l > buff_size) { printf("EMITException : EMITBuffer overflow at dtext for positions [%d,%d] !", position.x, position.y); exit(1); }
    for(int i = 0; i < l; i++) {
        buffer[(position.y*dimensions.x)+position.x+i].data = text[i];
        buffer[(position.y*dimensions.x)+position.x+i].prefix_code = cls;
        buffer[(position.y*dimensions.x)+position.x+i].sufix_code = rs;
    }
}

void EMITBuffer::dframe(EMITRect rect, EMITColor color)
{
    if(rect.position.x > dimensions.x || rect.position.y > dimensions.y || rect.position.x + rect.dimensions.x > dimensions.x || rect.position.y + rect.dimensions.y > dimensions.y) { printf("EMITException : EMITBuffer overflow at dframe for positions [%d,%d] sized (%d,%d) !", rect.position.x, rect.position.y, rect.dimensions.x, rect.dimensions.y); exit(1); }
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
