#include "frame.h"
#include "math.h"

int frameInit( Frame *f, Vec2i size, Pixel *buf )
{
    if(size.x * size.y == 0)
        return 1; // 0 sized rect

    if(buf == 0)
        return 2; // null ptr buffer

    f->frameBuffer = (Pixel *)buf;
    f->size = size;

    return 0;
}

void frameDraw(Frame *f, Vec2i pos, Pixel color)
{
    f->frameBuffer[pos.x + pos.y * f->size.x] = color;
}

Pixel frameRead(Frame *f, Vec2i pos)
{
    return f->frameBuffer[pos.x + pos.y * f->size.x];
}

Pixel frameReadBilinear(Frame *f, Vec2f pos)
{
    float kX = fmodf(pos.x, 1.0f);
    int lowX = floorf(pos.x);
    int higX = lowX + 1;

    float kY = fmodf(pos.y, 1.0f);
    int lowY = floorf(pos.y);
    int higY = lowY + 1;

    float p1 = f->frameBuffer[lowX + lowY * f->size.x].g;
    float p2 = f->frameBuffer[higX + lowY * f->size.x].g;
    float p3 = f->frameBuffer[lowX + higY * f->size.x].g;
    float p4 = f->frameBuffer[higX + higY * f->size.x].g;

    Pixel out ={
        ((p1 * (1.0f - kX) + p2 * (kX)) * (1.0 - kY))
        +
        ((p3 * (1.0f - kX) + p4 * (kX)) * (kY))
    };
    return out;
}





