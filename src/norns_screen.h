#pragma once

#include <napi.h>

#include <cairo/cairo.h>
#include <cairo/cairo-ft.h>

#define NUM_FONTS 67

class NornsScreen : public Napi::ObjectWrap<NornsScreen>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Function GetClass(Napi::Env);

    NornsScreen(const Napi::CallbackInfo &info);
    Napi::Value deinit(const Napi::CallbackInfo &info);

    Napi::Value update(const Napi::CallbackInfo &info);
    Napi::Value save(const Napi::CallbackInfo &info);
    Napi::Value restore(const Napi::CallbackInfo &info);
    Napi::Value font_face(const Napi::CallbackInfo &info);
    Napi::Value font_size(const Napi::CallbackInfo &info);
    Napi::Value aa(const Napi::CallbackInfo &info);
    Napi::Value level(const Napi::CallbackInfo &info);
    Napi::Value line_width(const Napi::CallbackInfo &info);
    Napi::Value line_cap(const Napi::CallbackInfo &info);
    Napi::Value line_join(const Napi::CallbackInfo &info);
    Napi::Value miter_limit(const Napi::CallbackInfo &info);
    Napi::Value move(const Napi::CallbackInfo &info);
    Napi::Value line(const Napi::CallbackInfo &info);
    Napi::Value move_rel(const Napi::CallbackInfo &info);
    Napi::Value line_rel(const Napi::CallbackInfo &info);
    Napi::Value curve(const Napi::CallbackInfo &info);
    Napi::Value curve_rel(const Napi::CallbackInfo &info);
    Napi::Value arc(const Napi::CallbackInfo &info);
    Napi::Value rect(const Napi::CallbackInfo &info);
    Napi::Value stroke(const Napi::CallbackInfo &info);
    Napi::Value fill(const Napi::CallbackInfo &info);
    Napi::Value text(const Napi::CallbackInfo &info);
    Napi::Value clear(const Napi::CallbackInfo &info);
    Napi::Value close_path(const Napi::CallbackInfo &info);
    Napi::Value text_extents(const Napi::CallbackInfo &info);
    Napi::Value export_png(const Napi::CallbackInfo &info);
    Napi::Value display_png(const Napi::CallbackInfo &info);
    Napi::Value peek(const Napi::CallbackInfo &info);
    Napi::Value poke(const Napi::CallbackInfo &info);
    Napi::Value rotate(const Napi::CallbackInfo &info);
    Napi::Value translate(const Napi::CallbackInfo &info);
    Napi::Value set_operator(const Napi::CallbackInfo &info);

private:
    cairo_surface_t *surface;
    cairo_surface_t *surfacefb;
    cairo_surface_t *image;

    cairo_t *cr;
    cairo_t *crfb;
    cairo_font_face_t *ct[NUM_FONTS];
    FT_Library value;
    FT_Error status;
    FT_Face face[NUM_FONTS];
    char font_path[NUM_FONTS][32];
};
