#include "ui.h"

static void draw(void);

ui_screen_t startup_screen = {
    .screen = NULL,
    .init = NULL,
    .draw = draw,
    .teardown = NULL,
    .data = NULL,
    .tick = NULL
};

static void set_image_opacity(void *img, int32_t v){
    lv_obj_set_style_opa((lv_obj_t *)img, v, LV_STYLE_STATE_CMP_SAME);
}

static void draw(void){
    lv_obj_t *screen = lv_obj_create(NULL);
    startup_screen.screen = screen;

    /* Use lv_color_hex(0) or lv_color_black() for black instead of lv_palette_main(LV_PALETTE_NONE) */
    lv_obj_set_style_bg_color(screen,lv_color_black(),
        LV_PART_MAIN | LV_STATE_DEFAULT);

    extern const lv_image_dsc_t st_icon_150x64;
    lv_obj_t * startup_logo = lv_image_create(screen);
    lv_image_set_src(startup_logo, &st_icon_150x64);
    lv_obj_align(startup_logo, LV_ALIGN_CENTER, 0, 0);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, startup_logo); // The object to animate
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)set_image_opacity); // Callback function
    lv_anim_set_values(&a, LV_OPA_TRANSP, LV_OPA_COVER); // Start from transparent, end at fully opaque
    lv_anim_set_time(&a, 1500); // Animation duration in milliseconds
    lv_anim_set_repeat_count(&a, 1); // Or LV_ANIM_REPEAT_INFINITE
    lv_anim_start(&a);
}
