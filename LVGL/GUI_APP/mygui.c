#include "mygui.h"

/*这三个变量是屏幕的坐标以及点击标志*/
extern uint16_t Vertical;
extern uint16_t Horizon;
extern uint8_t IRQ;

static lv_obj_t *switch_cool;
static lv_obj_t *switch_heat;
static lv_obj_t *switch_dry;

static void switch_event_cb(lv_event_t *e);
static void lv_example_label(void);
static void lv_example_switch1(void);
static void lv_example_switch2(void);
static void lv_example_switch3(void);

void lv_mainstart(void)
{
    lv_example_label();   /* 功能标题 */
    lv_example_switch1(); /* 制冷模式开关 */
    lv_example_switch2(); /* 制暖模式开关 */
    lv_example_switch3(); /* 干燥模式开关 */
}

static void lv_example_label(void)
{
    lv_obj_t *label = lv_label_create(lv_scr_act());                               /* 创建标签 */
    lv_label_set_text(label, "Control Center");                                    /* 设置文本内容 */
    lv_obj_set_style_text_font(label, &lv_font_montserrat_18, LV_STATE_DEFAULT);   /* 设置字体 */
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -lv_obj_get_height(lv_scr_act()) / 3); /* 设置位置 */
}
static void lv_example_switch1()
{
    /* 制冷模式基础对象（矩形背景） */
    lv_obj_t *obj_cool = lv_obj_create(lv_scr_act()); /* 创建基础对象 */
    /* 设置大小 */
    lv_obj_set_size(obj_cool, lv_obj_get_width(lv_scr_act()) / 4, lv_obj_get_height(lv_scr_act()) / 4);
    /* 设置位置 */
    lv_obj_align(obj_cool, LV_ALIGN_CENTER, -lv_obj_get_width(lv_scr_act()) / 4, 0);
    /* 制冷模式开关标签 */
    lv_obj_t *label_cool = lv_label_create(obj_cool); /* 创建标签 */
    lv_label_set_text(label_cool, "Cool");            /* 设置文本内容 */
    /* 设置字体 */
    lv_obj_set_style_text_font(label_cool, &lv_font_montserrat_14, LV_STATE_DEFAULT);
    /* 设置位置 */
    lv_obj_align(label_cool, LV_ALIGN_CENTER, 0, -lv_obj_get_height(lv_scr_act()) / 16);
    /* 制冷模式开关 */
    switch_cool = lv_switch_create(obj_cool); /* 创建开关 */
    /* 设置大小 */
    lv_obj_set_size(switch_cool, lv_obj_get_height(lv_scr_act()) / 8, lv_obj_get_height(lv_scr_act()) / 12);
    /* 设置位置 */
    lv_obj_align(switch_cool, LV_ALIGN_CENTER, 0, lv_obj_get_height(lv_scr_act()) / 16);
    lv_obj_add_event_cb(switch_cool, switch_event_cb,
                        LV_EVENT_VALUE_CHANGED, NULL); /* 添加事件 */
}

static void lv_example_switch2(void)
{
    /* 制暖模式基础对象（矩形背景） */
    lv_obj_t *obj_heat = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj_heat, lv_obj_get_width(lv_scr_act()) / 4, lv_obj_get_height(lv_scr_act()) / 4);
    lv_obj_align(obj_heat, LV_ALIGN_CENTER, 0, 0);
    /* 制暖模式开关标签 */
    lv_obj_t *label_heat = lv_label_create(obj_heat);
    lv_label_set_text(label_heat, "Heat");
    lv_obj_set_style_text_font(label_heat, &lv_font_montserrat_14, LV_STATE_DEFAULT);
    lv_obj_align(label_heat, LV_ALIGN_CENTER, 0, -lv_obj_get_height(lv_scr_act()) / 16);
    /* 制暖模式开关 */
    switch_heat = lv_switch_create(obj_heat);
    lv_obj_set_size(switch_heat, lv_obj_get_height(lv_scr_act()) / 8, lv_obj_get_height(lv_scr_act()) / 12);
    lv_obj_align(switch_heat, LV_ALIGN_CENTER, 0, lv_obj_get_height(lv_scr_act()) / 16);
    lv_obj_add_event_cb(switch_heat, switch_event_cb,
                        LV_EVENT_VALUE_CHANGED, NULL);
}

static void lv_example_switch3(void)
{
    /* 干燥模式基础对象（矩形背景） */
    lv_obj_t *obj_dry = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj_dry, lv_obj_get_width(lv_scr_act()) / 4, lv_obj_get_height(lv_scr_act()) / 4);
    lv_obj_align(obj_dry, LV_ALIGN_CENTER, lv_obj_get_width(lv_scr_act()) / 4, 0);
    /* 干燥模式开关标签 */
    lv_obj_t *label_dry = lv_label_create(obj_dry);
    lv_label_set_text(label_dry, "Dry");
    lv_obj_set_style_text_font(label_dry, &lv_font_montserrat_14, LV_STATE_DEFAULT);

    lv_obj_align(label_dry, LV_ALIGN_CENTER, 0, -lv_obj_get_height(lv_scr_act()) / 16);
    /* 干燥模式开关 */
    switch_dry = lv_switch_create(obj_dry);
    lv_obj_set_size(switch_dry, lv_obj_get_height(lv_scr_act()) / 8, lv_obj_get_height(lv_scr_act()) / 12);
    lv_obj_align(switch_dry, LV_ALIGN_CENTER, 0, lv_obj_get_height(lv_scr_act()) / 16);
    lv_obj_add_event_cb(switch_dry, switch_event_cb,
                        LV_EVENT_VALUE_CHANGED, NULL);
}

static void switch_event_cb(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e); /* 获取触发源 */
    if (target == switch_cool)                 /* 制冷开关触发 */
    {
        if (lv_obj_has_state(switch_cool, LV_STATE_CHECKED)) /* 判断开关状态 */
        {
            /* 制冷模式已打开，关闭制暖模式 */
            lv_obj_clear_state(switch_heat, LV_STATE_CHECKED);
        }
    }
    else if (target == switch_heat) /* 制暖开关触发 */
    {
        if (lv_obj_has_state(switch_heat, LV_STATE_CHECKED)) /* 判断开关状态 */
        {
            /* 制暖模式已打开，关闭制冷模式 */
            lv_obj_clear_state(switch_cool, LV_STATE_CHECKED);
        }
    }
    else if (target == switch_dry) /* 制暖开关触发 */
    {
        if (lv_obj_has_state(switch_dry, LV_STATE_CHECKED)) /* 判断开关状态 */
        {
        }
    }
}
