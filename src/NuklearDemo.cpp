#include "NuklearDemo.h"

NuklearDemo::NuklearDemo()
{
    m_isRendering = false;
    m_bg.r = 0.10f;
    m_bg.g = 0.18f;
    m_bg.b = 0.24f;
    m_bg.a = 1.0f;
}

NuklearDemo::~NuklearDemo()
{
}

void NuklearDemo::Render(nk_context* context)
{
    if (!m_isRendering)
        return;

    if (nk_begin(context, "Demo", nk_rect(50, 50, 230, 250),
        NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
        NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {
        enum { EASY, HARD };
        static int op = EASY;
        static int property = 20;

        nk_layout_row_static(context, 30, 80, 1);
        if (nk_button_label(context, "button"))
            UnityLogger::Log("button pressed");
        nk_layout_row_dynamic(context, 30, 2);
        if (nk_option_label(context, "easy", op == EASY)) op = EASY;
        if (nk_option_label(context, "hard", op == HARD)) op = HARD;
        nk_layout_row_dynamic(context, 22, 1);
        nk_property_int(context, "Compression:", 0, &property, 100, 10, 1);

        nk_layout_row_dynamic(context, 20, 1);
        nk_label(context, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(context, 25, 1);
        if (nk_combo_begin_color(context, nk_rgb_cf(m_bg), nk_vec2(nk_widget_width(context), 400))) {
            nk_layout_row_dynamic(context, 120, 1);
            m_bg = nk_color_picker(context, m_bg, NK_RGBA);
            nk_layout_row_dynamic(context, 25, 1);
            m_bg.r = nk_propertyf(context, "#R:", 0, m_bg.r, 1.0f, 0.01f, 0.005f);
            m_bg.g = nk_propertyf(context, "#G:", 0, m_bg.g, 1.0f, 0.01f, 0.005f);
            m_bg.b = nk_propertyf(context, "#B:", 0, m_bg.b, 1.0f, 0.01f, 0.005f);
            m_bg.a = nk_propertyf(context, "#A:", 0, m_bg.a, 1.0f, 0.01f, 0.005f);
            nk_combo_end(context);
        }
    }
    nk_end(context);
}

void NuklearDemo::SetRender(bool isRendering)
{
    m_isRendering = isRendering;
}