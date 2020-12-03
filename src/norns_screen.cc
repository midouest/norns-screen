#include "norns_screen.h"

#define NUM_OPS 29
#define NUM_FONTS 67

static float c[16] = {0, 0.066666666666667, 0.13333333333333, 0.2, 0.26666666666667, 0.33333333333333,
                      0.4, 0.46666666666667, 0.53333333333333, 0.6, 0.66666666666667, 0.73333333333333,
                      0.8, 0.86666666666667, 0.93333333333333, 1};

static cairo_operator_t ops[NUM_OPS] = {
    CAIRO_OPERATOR_OVER,
    CAIRO_OPERATOR_XOR,
    CAIRO_OPERATOR_ADD,
    CAIRO_OPERATOR_SATURATE,
    CAIRO_OPERATOR_MULTIPLY,
    CAIRO_OPERATOR_SCREEN,
    CAIRO_OPERATOR_OVERLAY,
    CAIRO_OPERATOR_DARKEN,
    CAIRO_OPERATOR_LIGHTEN,
    CAIRO_OPERATOR_COLOR_DODGE,
    CAIRO_OPERATOR_COLOR_BURN,
    CAIRO_OPERATOR_HARD_LIGHT,
    CAIRO_OPERATOR_SOFT_LIGHT,
    CAIRO_OPERATOR_DIFFERENCE,
    CAIRO_OPERATOR_EXCLUSION,
    CAIRO_OPERATOR_CLEAR,
    CAIRO_OPERATOR_SOURCE,
    CAIRO_OPERATOR_IN,
    CAIRO_OPERATOR_OUT,
    CAIRO_OPERATOR_ATOP,
    CAIRO_OPERATOR_DEST,
    CAIRO_OPERATOR_DEST_OVER,
    CAIRO_OPERATOR_DEST_IN,
    CAIRO_OPERATOR_DEST_OUT,
    CAIRO_OPERATOR_DEST_ATOP,
    CAIRO_OPERATOR_HSL_HUE,
    CAIRO_OPERATOR_HSL_SATURATION,
    CAIRO_OPERATOR_HSL_COLOR,
    CAIRO_OPERATOR_HSL_LUMINOSITY};

Napi::Function NornsScreen::GetClass(Napi::Env env)
{
    return DefineClass(env, "NornsScreen",
                       {
                           InstanceMethod("deinit", &NornsScreen::deinit),
                           InstanceMethod("update", &NornsScreen::update),
                           InstanceMethod("save", &NornsScreen::save),
                           InstanceMethod("restore", &NornsScreen::restore),
                           InstanceMethod("font_face", &NornsScreen::font_face),
                           InstanceMethod("font_size", &NornsScreen::font_size),
                           InstanceMethod("aa", &NornsScreen::aa),
                           InstanceMethod("level", &NornsScreen::level),
                           InstanceMethod("line_width", &NornsScreen::line_width),
                           InstanceMethod("line_cap", &NornsScreen::line_cap),
                           InstanceMethod("line_join", &NornsScreen::line_join),
                           InstanceMethod("miter_limit", &NornsScreen::miter_limit),
                           InstanceMethod("move", &NornsScreen::move),
                           InstanceMethod("line", &NornsScreen::line),
                           InstanceMethod("move_rel", &NornsScreen::move_rel),
                           InstanceMethod("line_rel", &NornsScreen::line_rel),
                           InstanceMethod("curve", &NornsScreen::curve),
                           InstanceMethod("curve_rel", &NornsScreen::curve_rel),
                           InstanceMethod("arc", &NornsScreen::arc),
                           InstanceMethod("rect", &NornsScreen::rect),
                           InstanceMethod("stroke", &NornsScreen::stroke),
                           InstanceMethod("fill", &NornsScreen::fill),
                           InstanceMethod("text", &NornsScreen::text),
                           InstanceMethod("clear", &NornsScreen::clear),
                           InstanceMethod("close_path", &NornsScreen::close_path),
                           InstanceMethod("text_extents", &NornsScreen::text_extents),
                           InstanceMethod("export_png", &NornsScreen::export_png),
                           InstanceMethod("display_png", &NornsScreen::display_png),
                           InstanceMethod("peek", &NornsScreen::peek),
                           InstanceMethod("poke", &NornsScreen::poke),
                           InstanceMethod("rotate", &NornsScreen::rotate),
                           InstanceMethod("translate", &NornsScreen::translate),
                           InstanceMethod("set_operator", &NornsScreen::set_operator),
                       });
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    Napi::String name = Napi::String::New(env, "NornsScreen");
    exports.Set(name, NornsScreen::GetClass(env));
    return exports;
}

NornsScreen::NornsScreen(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<NornsScreen>(info)
{
    surfacefb = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 128, 64);
    crfb = cairo_create(surfacefb);
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 128, 64);
    cr = cairo_create(surface);

    strcpy(font_path[0], "04B_03__.TTF");

    status = FT_Init_FreeType(&value);
    // TODO: error handling

    // TODO: more fonts

    status = FT_New_Face(value, font_path[0], 0, &face[0]);
    // TODO: error handling

    cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
    cairo_paint(cr);
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

    cairo_font_options_t *font_options = cairo_font_options_create();
    cairo_font_options_set_antialias(font_options, CAIRO_ANTIALIAS_SUBPIXEL);
    cairo_set_font_options(cr, font_options);
    cairo_font_options_destroy(font_options);

    // default font
    cairo_set_font_face(cr, ct[0]);
    cairo_set_font_size(cr, 8.0);

    // config buffer
    cairo_set_operator(crfb, CAIRO_OPERATOR_SOURCE);
    cairo_set_source_surface(crfb, surface, 0, 0);
}

Napi::Value NornsScreen::deinit(const Napi::CallbackInfo &info)
{
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    cairo_destroy(crfb);
    cairo_surface_destroy(surfacefb);
    return Value();
}

Napi::Value NornsScreen::update(const Napi::CallbackInfo &info)
{
    cairo_paint(crfb);
    return Value();
}

Napi::Value NornsScreen::save(const Napi::CallbackInfo &info)
{
    cairo_save(cr);
    return Value();
}

Napi::Value NornsScreen::restore(const Napi::CallbackInfo &info)
{
    cairo_restore(cr);
    return Value();
}

Napi::Value NornsScreen::font_face(const Napi::CallbackInfo &info)
{
    auto i = info[0].As<Napi::Number>().Int32Value();
    if ((i >= 0) && (i < NUM_FONTS))
    {
        cairo_set_font_face(cr, ct[i]);
    }
    return Value();
}

Napi::Value NornsScreen::font_size(const Napi::CallbackInfo &info)
{
    auto z = info[0].As<Napi::Number>().DoubleValue();
    cairo_set_font_size(cr, z);
    return Value();
}

Napi::Value NornsScreen::aa(const Napi::CallbackInfo &info)
{
    auto s = info[0].As<Napi::Number>().Int32Value();
    cairo_font_options_t *font_options = cairo_font_options_create();
    if (s == 0)
    {
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);
        cairo_font_options_set_antialias(font_options, CAIRO_ANTIALIAS_NONE);
    }
    else
    {
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_font_options_set_antialias(font_options, CAIRO_ANTIALIAS_SUBPIXEL);
    }
    cairo_set_font_options(cr, font_options);
    cairo_font_options_destroy(font_options);
    return Value();
}

Napi::Value NornsScreen::level(const Napi::CallbackInfo &info)
{
    auto z = info[0].As<Napi::Number>().Int32Value();
    cairo_set_source_rgb(cr, c[z], c[z], c[z]);
    return Value();
}

Napi::Value NornsScreen::line_width(const Napi::CallbackInfo &info)
{
    auto w = info[0].As<Napi::Number>().DoubleValue();
    cairo_set_line_width(cr, w);
    return Value();
}

Napi::Value NornsScreen::line_cap(const Napi::CallbackInfo &info)
{
    auto style = info[0].As<Napi::String>().Utf8Value();
    if (strcmp(style.c_str(), "round") == 0)
    {
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    }
    else if (strcmp(style.c_str(), "square") == 0)
    {
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    }
    else
    {
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    }
    return Value();
}

Napi::Value NornsScreen::line_join(const Napi::CallbackInfo &info)
{
    auto style = info[0].As<Napi::String>().Utf8Value();
    if (strcmp(style.c_str(), "round") == 0)
    {
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
    }
    else if (strcmp(style.c_str(), "bevel") == 0)
    {
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
    }
    else
    {
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    }
    return Value();
}

Napi::Value NornsScreen::miter_limit(const Napi::CallbackInfo &info)
{
    auto limit = info[0].As<Napi::Number>().DoubleValue();
    cairo_set_miter_limit(cr, limit);
    return Value();
}

Napi::Value NornsScreen::move(const Napi::CallbackInfo &info)
{
    auto x = info[0].As<Napi::Number>().DoubleValue();
    auto y = info[1].As<Napi::Number>().DoubleValue();
    cairo_move_to(cr, x, y);
    return Value();
}

Napi::Value NornsScreen::line(const Napi::CallbackInfo &info)
{
    auto x = info[0].As<Napi::Number>().DoubleValue();
    auto y = info[1].As<Napi::Number>().DoubleValue();
    cairo_line_to(cr, x, y);
    return Value();
}

Napi::Value NornsScreen::line_rel(const Napi::CallbackInfo &info)
{
    auto x = info[0].As<Napi::Number>().DoubleValue();
    auto y = info[1].As<Napi::Number>().DoubleValue();
    cairo_rel_line_to(cr, x, y);
    return Value();
}

Napi::Value NornsScreen::move_rel(const Napi::CallbackInfo &info)
{
    auto x = info[0].As<Napi::Number>().DoubleValue();
    auto y = info[1].As<Napi::Number>().DoubleValue();
    cairo_rel_move_to(cr, x, y);
    return Value();
}

Napi::Value NornsScreen::curve(const Napi::CallbackInfo &info)
{
    auto x1 = info[0].As<Napi::Number>().DoubleValue();
    auto y1 = info[1].As<Napi::Number>().DoubleValue();
    auto x2 = info[2].As<Napi::Number>().DoubleValue();
    auto y2 = info[3].As<Napi::Number>().DoubleValue();
    auto x3 = info[4].As<Napi::Number>().DoubleValue();
    auto y3 = info[5].As<Napi::Number>().DoubleValue();
    cairo_curve_to(cr, x1, y1, x2, y2, x3, y3);
    return Value();
}

Napi::Value NornsScreen::curve_rel(const Napi::CallbackInfo &info)
{
    auto dx1 = info[0].As<Napi::Number>().DoubleValue();
    auto dy1 = info[1].As<Napi::Number>().DoubleValue();
    auto dx2 = info[2].As<Napi::Number>().DoubleValue();
    auto dy2 = info[3].As<Napi::Number>().DoubleValue();
    auto dx3 = info[4].As<Napi::Number>().DoubleValue();
    auto dy3 = info[5].As<Napi::Number>().DoubleValue();
    cairo_rel_curve_to(cr, dx1, dy1, dx2, dy2, dx3, dy3);
    return Value();
}

Napi::Value NornsScreen::arc(const Napi::CallbackInfo &info)
{
    auto x = info[0].As<Napi::Number>().DoubleValue();
    auto y = info[1].As<Napi::Number>().DoubleValue();
    auto r = info[2].As<Napi::Number>().DoubleValue();
    auto a1 = info[3].As<Napi::Number>().DoubleValue();
    auto a2 = info[4].As<Napi::Number>().DoubleValue();
    cairo_arc(cr, x, y, r, a1, a2);
    return Value();
}

Napi::Value NornsScreen::rect(const Napi::CallbackInfo &info)
{
    auto x = info[0].As<Napi::Number>().DoubleValue();
    auto y = info[1].As<Napi::Number>().DoubleValue();
    auto w = info[2].As<Napi::Number>().DoubleValue();
    auto h = info[3].As<Napi::Number>().DoubleValue();
    cairo_rectangle(cr, x, y, w, h);
    return Value();
}

Napi::Value NornsScreen::close_path(const Napi::CallbackInfo &info)
{
    cairo_close_path(cr);
    return Value();
}

Napi::Value NornsScreen::stroke(const Napi::CallbackInfo &info)
{
    cairo_stroke(cr);
    return Value();
}

Napi::Value NornsScreen::fill(const Napi::CallbackInfo &info)
{
    cairo_fill(cr);
    return Value();
}

Napi::Value NornsScreen::text(const Napi::CallbackInfo &info)
{
    auto s = info[0].As<Napi::String>().Utf8Value();
    cairo_show_text(cr, s.c_str());
    return Value();
}

Napi::Value NornsScreen::clear(const Napi::CallbackInfo &info)
{
    cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
    cairo_paint(cr);
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    return Value();
}

Napi::Value NornsScreen::text_extents(const Napi::CallbackInfo &info)
{
    auto s = info[0].As<Napi::String>().Utf8Value();
    cairo_text_extents_t extents;
    cairo_text_extents(cr, s.c_str(), &extents);
    auto env = info.Env();
    auto text_xy = Napi::TypedArrayOf<uint8_t>::New(env, 2);
    text_xy[0] = extents.width;
    text_xy[1] = extents.height;
    return text_xy;
}

Napi::Value NornsScreen::export_png(const Napi::CallbackInfo &info)
{
    auto s = info[0].As<Napi::String>().Utf8Value();
    cairo_surface_write_to_png(surface, s.c_str());
    return Value();
}

Napi::Value NornsScreen::display_png(const Napi::CallbackInfo &info)
{
    auto filename = info[0].As<Napi::String>().Utf8Value();
    auto x = info[1].As<Napi::Number>().DoubleValue();
    auto y = info[2].As<Napi::Number>().DoubleValue();

    int img_w, img_h;

    image = cairo_image_surface_create_from_png(filename.c_str());
    if (cairo_surface_status(image))
    {
        return Value();
    }

    img_w = cairo_image_surface_get_width(image);
    img_h = cairo_image_surface_get_height(image);

    cairo_set_source_surface(cr, image, x, y);
    cairo_rectangle(cr, x, y, img_w, img_h);
    cairo_fill(cr);
    cairo_surface_destroy(image);

    return Value();
}

Napi::Value NornsScreen::peek(const Napi::CallbackInfo &info)
{
    auto x = info[0].As<Napi::Number>().Int32Value();
    auto y = info[1].As<Napi::Number>().Int32Value();
    auto w = info[2].As<Napi::Number>().Int32Value();
    auto h = info[3].As<Napi::Number>().Int32Value();

    w = (w <= (128 - x)) ? (w) : (128 - x);
    h = (h <= (64 - y)) ? (h) : (64 - y);
    auto buf = Napi::TypedArrayOf<uint8_t>::New(info.Env(), w * h);
    cairo_surface_flush(surface);
    uint32_t *data = (uint32_t *)cairo_image_surface_get_data(surface);
    if (!data)
    {
        return info.Env().Null();
    }
    char *p = (char *)buf.Data();
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            *p = data[j * 128 + i] & 0xF;
            p++;
        }
    }
    return buf;
}

Napi::Value NornsScreen::poke(const Napi::CallbackInfo &info)
{
    auto x = info[0].As<Napi::Number>().Int32Value();
    auto y = info[1].As<Napi::Number>().Int32Value();
    auto w = info[2].As<Napi::Number>().Int32Value();
    auto h = info[3].As<Napi::Number>().Int32Value();
    auto buf = info[4].As<Napi::Uint8Array>();

    w = (w <= (128 - x)) ? w : (128 - x);
    h = (h <= (64 - y)) ? h : (64 - y);

    uint32_t *data = (uint32_t *)cairo_image_surface_get_data(surface);
    if (!data)
    {
        return info.Env().Null();
    }
    uint8_t *p = buf.Data();
    uint32_t pixel;
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            pixel = *p;
            pixel = pixel | (pixel << 4);
            data[j * 128 + i] = pixel | (pixel << 8) | (pixel << 16) | (pixel << 24);
            p++;
        }
    }
    cairo_surface_mark_dirty(surface);
    return Value();
}

Napi::Value NornsScreen::rotate(const Napi::CallbackInfo &info)
{
    auto r = info[0].As<Napi::Number>().DoubleValue();
    cairo_rotate(cr, r);
    return Value();
}

Napi::Value NornsScreen::translate(const Napi::CallbackInfo &info)
{
    auto x = info[0].As<Napi::Number>().DoubleValue();
    auto y = info[1].As<Napi::Number>().DoubleValue();
    cairo_translate(cr, x, y);
    return Value();
}

Napi::Value NornsScreen::set_operator(const Napi::CallbackInfo &info)
{
    auto i = info[0].As<Napi::Number>().Int32Value();
    if (0 <= i && i <= 28)
    {
        cairo_set_operator(cr, ops[i]);
    }
    return Value();
}

NODE_API_MODULE(addon, Init)
