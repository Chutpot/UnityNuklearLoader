#include "NuklearDemo.h"


NuklearDemo::NuklearDemo()
{

}

NuklearDemo::~NuklearDemo()
{
}

void NuklearDemo::Render(nk_context* context)
{
    struct nk_colorf bg; 
    bg.r = 1.0f, bg.g = 1.0f, bg.b = 1.0f, bg.a = 1.0f;
    if (nk_begin(context, "Demo", nk_rect(50, 50, 230, 250),
        NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
        NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {

    }
    nk_end(context);
}