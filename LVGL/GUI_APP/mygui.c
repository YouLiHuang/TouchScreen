#include "mygui.h"

/*��������������Ļ�������Լ������־*/
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
    lv_example_label();   /* ���ܱ��� */
    lv_example_switch1(); /* ����ģʽ���� */
    lv_example_switch2(); /* ��ůģʽ���� */
    lv_example_switch3(); /* ����ģʽ���� */
}

static void lv_example_label(void)
{
    lv_obj_t *label = lv_label_create(lv_scr_act());                               /* ������ǩ */
    lv_label_set_text(label, "Control Center");                                    /* �����ı����� */
    lv_obj_set_style_text_font(label, &lv_font_montserrat_18, LV_STATE_DEFAULT);   /* �������� */
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -lv_obj_get_height(lv_scr_act()) / 3); /* ����λ�� */
}
static void lv_example_switch1()
{
    /* ����ģʽ�������󣨾��α����� */
    lv_obj_t *obj_cool = lv_obj_create(lv_scr_act()); /* ������������ */
    /* ���ô�С */
    lv_obj_set_size(obj_cool, lv_obj_get_width(lv_scr_act()) / 4, lv_obj_get_height(lv_scr_act()) / 4);
    /* ����λ�� */
    lv_obj_align(obj_cool, LV_ALIGN_CENTER, -lv_obj_get_width(lv_scr_act()) / 4, 0);
    /* ����ģʽ���ر�ǩ */
    lv_obj_t *label_cool = lv_label_create(obj_cool); /* ������ǩ */
    lv_label_set_text(label_cool, "Cool");            /* �����ı����� */
    /* �������� */
    lv_obj_set_style_text_font(label_cool, &lv_font_montserrat_14, LV_STATE_DEFAULT);
    /* ����λ�� */
    lv_obj_align(label_cool, LV_ALIGN_CENTER, 0, -lv_obj_get_height(lv_scr_act()) / 16);
    /* ����ģʽ���� */
    switch_cool = lv_switch_create(obj_cool); /* �������� */
    /* ���ô�С */
    lv_obj_set_size(switch_cool, lv_obj_get_height(lv_scr_act()) / 8, lv_obj_get_height(lv_scr_act()) / 12);
    /* ����λ�� */
    lv_obj_align(switch_cool, LV_ALIGN_CENTER, 0, lv_obj_get_height(lv_scr_act()) / 16);
    lv_obj_add_event_cb(switch_cool, switch_event_cb,
                        LV_EVENT_VALUE_CHANGED, NULL); /* ����¼� */
}

static void lv_example_switch2(void)
{
    /* ��ůģʽ�������󣨾��α����� */
    lv_obj_t *obj_heat = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj_heat, lv_obj_get_width(lv_scr_act()) / 4, lv_obj_get_height(lv_scr_act()) / 4);
    lv_obj_align(obj_heat, LV_ALIGN_CENTER, 0, 0);
    /* ��ůģʽ���ر�ǩ */
    lv_obj_t *label_heat = lv_label_create(obj_heat);
    lv_label_set_text(label_heat, "Heat");
    lv_obj_set_style_text_font(label_heat, &lv_font_montserrat_14, LV_STATE_DEFAULT);
    lv_obj_align(label_heat, LV_ALIGN_CENTER, 0, -lv_obj_get_height(lv_scr_act()) / 16);
    /* ��ůģʽ���� */
    switch_heat = lv_switch_create(obj_heat);
    lv_obj_set_size(switch_heat, lv_obj_get_height(lv_scr_act()) / 8, lv_obj_get_height(lv_scr_act()) / 12);
    lv_obj_align(switch_heat, LV_ALIGN_CENTER, 0, lv_obj_get_height(lv_scr_act()) / 16);
    lv_obj_add_event_cb(switch_heat, switch_event_cb,
                        LV_EVENT_VALUE_CHANGED, NULL);
}

static void lv_example_switch3(void)
{
    /* ����ģʽ�������󣨾��α����� */
    lv_obj_t *obj_dry = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj_dry, lv_obj_get_width(lv_scr_act()) / 4, lv_obj_get_height(lv_scr_act()) / 4);
    lv_obj_align(obj_dry, LV_ALIGN_CENTER, lv_obj_get_width(lv_scr_act()) / 4, 0);
    /* ����ģʽ���ر�ǩ */
    lv_obj_t *label_dry = lv_label_create(obj_dry);
    lv_label_set_text(label_dry, "Dry");
    lv_obj_set_style_text_font(label_dry, &lv_font_montserrat_14, LV_STATE_DEFAULT);

    lv_obj_align(label_dry, LV_ALIGN_CENTER, 0, -lv_obj_get_height(lv_scr_act()) / 16);
    /* ����ģʽ���� */
    switch_dry = lv_switch_create(obj_dry);
    lv_obj_set_size(switch_dry, lv_obj_get_height(lv_scr_act()) / 8, lv_obj_get_height(lv_scr_act()) / 12);
    lv_obj_align(switch_dry, LV_ALIGN_CENTER, 0, lv_obj_get_height(lv_scr_act()) / 16);
    lv_obj_add_event_cb(switch_dry, switch_event_cb,
                        LV_EVENT_VALUE_CHANGED, NULL);
}

static void switch_event_cb(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e); /* ��ȡ����Դ */
    if (target == switch_cool)                 /* ���俪�ش��� */
    {
        if (lv_obj_has_state(switch_cool, LV_STATE_CHECKED)) /* �жϿ���״̬ */
        {
            /* ����ģʽ�Ѵ򿪣��ر���ůģʽ */
            lv_obj_clear_state(switch_heat, LV_STATE_CHECKED);
        }
    }
    else if (target == switch_heat) /* ��ů���ش��� */
    {
        if (lv_obj_has_state(switch_heat, LV_STATE_CHECKED)) /* �жϿ���״̬ */
        {
            /* ��ůģʽ�Ѵ򿪣��ر�����ģʽ */
            lv_obj_clear_state(switch_cool, LV_STATE_CHECKED);
        }
    }
    else if (target == switch_dry) /* ��ů���ش��� */
    {
        if (lv_obj_has_state(switch_dry, LV_STATE_CHECKED)) /* �жϿ���״̬ */
        {
        }
    }
}

/*test demo*/
static lv_obj_t *checkbox1;
static lv_obj_t *checkbox2;
static lv_obj_t *checkbox3;
static lv_obj_t *btn2;
static lv_obj_t *activity3;
static lv_obj_t *activity4;
static lv_obj_t *activity5;
lv_obj_t *back;
lv_obj_t *back2;
lv_obj_t *next;
void btn2_cb(lv_event_t *e)
{
    if (lv_event_get_target(e) == btn2)
    {
        lv_obj_add_flag(activity3, LV_OBJ_FLAG_HIDDEN);   // ���ؽ���3
        lv_obj_clear_flag(activity4, LV_OBJ_FLAG_HIDDEN); // ��ʾ����4
    }
    else if (lv_event_get_target(e) == back)
    {
        lv_obj_add_flag(activity4, LV_OBJ_FLAG_HIDDEN);   // ���ؽ���4
        lv_obj_clear_flag(activity3, LV_OBJ_FLAG_HIDDEN); // ��ʾ����3
    }
    else if (lv_event_get_target(e) == next)
    {
        lv_obj_add_flag(activity4, LV_OBJ_FLAG_HIDDEN);   // ���ؽ���4
        lv_obj_clear_flag(activity5, LV_OBJ_FLAG_HIDDEN); // ��ʾ����5
    }
    else if (lv_event_get_target(e) == back2)
    {
        lv_obj_add_flag(activity5, LV_OBJ_FLAG_HIDDEN);   // ���ؽ���4
        lv_obj_clear_flag(activity4, LV_OBJ_FLAG_HIDDEN); // ��ʾ����3
    }
}
void my_test_demo()
{
    activity3 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(activity3, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

    lv_obj_t *bg = lv_obj_create(activity3);
    lv_obj_set_size(bg, lv_obj_get_width(lv_scr_act()) * 4 / 5, lv_obj_get_height(lv_scr_act()) / 2);
    lv_obj_align(bg, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *label_text = lv_label_create(activity3);
    lv_label_set_text(label_text, LV_SYMBOL_LIST "List");
    lv_obj_set_style_text_font(label_text, &lv_font_montserrat_22, LV_STATE_DEFAULT);
    lv_obj_align(label_text, LV_ALIGN_TOP_MID, 0, lv_obj_get_height(lv_scr_act()) / 12);

    checkbox1 = lv_checkbox_create(bg);
    lv_checkbox_set_text(checkbox1, "first");
    lv_obj_set_style_text_font(checkbox1, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_obj_align(checkbox1, LV_ALIGN_TOP_LEFT, 0, 0);

    checkbox2 = lv_checkbox_create(bg);
    lv_checkbox_set_text(checkbox2, "second");
    lv_obj_set_style_text_font(checkbox2, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_obj_align_to(checkbox2, checkbox1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, lv_obj_get_height(lv_scr_act()) / 10);

    checkbox3 = lv_checkbox_create(bg);
    lv_checkbox_set_text(checkbox3, "Third");
    lv_obj_set_style_text_font(checkbox3, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_obj_align_to(checkbox3, checkbox2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, lv_obj_get_height(lv_scr_act()) / 10);

    btn2 = lv_btn_create(activity3);
    lv_obj_align(btn2, LV_ALIGN_BOTTOM_MID, 0, -lv_obj_get_height(lv_scr_act()) / 10);
    lv_obj_set_style_bg_color(btn2, lv_color_hex(0x0000ff),
                              LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(btn2, lv_color_hex(0xeeeeee),
                              LV_STATE_DEFAULT);
    lv_obj_set_size(btn2, lv_obj_get_width(lv_scr_act()) / 8, lv_obj_get_height(lv_scr_act()) / 16);
    lv_obj_add_event_cb(btn2, btn2_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *btn_label = lv_label_create(btn2);
    lv_obj_align(btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(btn_label, "OK");
    lv_obj_set_style_text_color(btn_label, lv_color_hex(0x1145), LV_STATE_DEFAULT);

    /*�ڶ�������*/
    activity4 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(activity4, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

    /*����ͼ��*/
    back = lv_btn_create(activity4);
    lv_obj_set_style_bg_color(back, lv_color_hex(0x000000), LV_ALIGN_DEFAULT);
    lv_obj_set_style_bg_opa(back, 0, 0);
    lv_obj_set_style_shadow_opa(back, 0, 0);
    lv_obj_align(back, LV_ALIGN_TOP_LEFT, 0, lv_obj_get_height(lv_scr_act()) / 24);
    lv_obj_add_event_cb(back, btn2_cb, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_t *label_back = lv_label_create(back);
    lv_obj_align(label_back, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_back, LV_SYMBOL_LEFT);
    lv_obj_set_style_text_color(label_back, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_back, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    /*��һҳ*/
    next = lv_btn_create(activity4);
    lv_obj_set_style_bg_color(next, lv_color_hex(0x000000), LV_ALIGN_DEFAULT);
    lv_obj_set_style_bg_opa(next, 0, 0);
    lv_obj_set_style_shadow_opa(next, 0, 0);
    lv_obj_align(next, LV_ALIGN_TOP_RIGHT, 0, lv_obj_get_height(lv_scr_act()) / 24);
    ;
    lv_obj_add_event_cb(next, btn2_cb, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_t *label_next = lv_label_create(next);
    lv_obj_align(label_next, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_next, LV_SYMBOL_RIGHT);
    lv_obj_set_style_text_color(label_next, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_next, &lv_font_montserrat_18, LV_STATE_DEFAULT);

    /* ����һ ��Ӷ��ѡ���̬�� */
    lv_obj_t *lv_ddlist1 = lv_dropdown_create(activity4);
    lv_obj_set_width(lv_ddlist1, lv_obj_get_width(lv_scr_act()) / 4);
    lv_dropdown_set_options(lv_ddlist1, "a\nb\nc\nd");
    lv_dropdown_set_text(lv_ddlist1, "ABC");
    lv_obj_set_style_text_font(lv_ddlist1, &lv_font_montserrat_12, LV_STATE_DEFAULT);
    lv_obj_align(lv_ddlist1, LV_ALIGN_TOP_LEFT, lv_obj_get_width(lv_scr_act()) / 12, lv_obj_get_height(lv_scr_act()) / 6);
    /* Ĭ����ʾ��ѡ�� */
    lv_dropdown_set_selected(lv_ddlist1, 0);

    /* ������ ��ӵ���ѡ�� */
    lv_obj_t *lv_ddlist2 = lv_dropdown_create(activity4);
    lv_obj_set_style_text_font(lv_ddlist2, &lv_font_montserrat_12, LV_STATE_DEFAULT);
    lv_obj_set_width(lv_ddlist2, lv_obj_get_width(lv_scr_act()) / 4);
    lv_dropdown_add_option(lv_ddlist2, "red", 0);
    lv_dropdown_add_option(lv_ddlist2, "green", 1);
    lv_dropdown_add_option(lv_ddlist2, "blue", 2);
    lv_dropdown_add_option(lv_ddlist2, "yellow", 3);
    /* Ĭ����ʾ��ѡ�� */
    lv_dropdown_set_selected(lv_ddlist2, 1);
    lv_obj_align(lv_ddlist2, LV_ALIGN_TOP_MID, 0, lv_obj_get_height(lv_scr_act()) / 6);
    lv_dropdown_set_symbol(lv_ddlist2, LV_SYMBOL_LIST);
    lv_dropdown_set_text(lv_ddlist2, "Color");
    // lv_dropdown_set_dir(lv_ddlist2,LV_DIR_LEFT);

    /* ������ ��Ӷ��ѡ���̬�� */
    lv_obj_t *lv_ddlist3 = lv_dropdown_create(activity4);
    lv_obj_set_style_text_font(lv_ddlist3, &lv_font_montserrat_12, LV_STATE_DEFAULT);
    lv_obj_set_width(lv_ddlist3, lv_obj_get_width(lv_scr_act()) / 4);
    lv_dropdown_set_options_static(lv_ddlist3, "1");
    lv_obj_align(lv_ddlist3, LV_ALIGN_TOP_RIGHT, -lv_obj_get_width(lv_scr_act()) / 12, lv_obj_get_height(lv_scr_act()) / 6);

    /*���Ը������б����LV_EVENT_VALUE_CHANGED�¼��Ļص������������������ȡ���ı���ȡ��ҵ��*/

    static const char *roller_options = "option 0\n"
                                        "option 1\n"
                                        "option 2\n"
                                        "option 3\n"
                                        "option 4\n"
                                        "option 5\n"
                                        "option 6\n"
                                        "option 7";
    lv_obj_t *roller = lv_roller_create(activity4);
    lv_obj_align(roller, LV_ALIGN_CENTER, 0, lv_obj_get_height(lv_scr_act()) / 12);
    lv_roller_set_options(roller, roller_options, LV_ROLLER_MODE_NORMAL);
    lv_obj_set_width(roller, lv_obj_get_width(lv_scr_act()) / 2);
    lv_roller_set_visible_row_count(roller, 3); // ���ÿɼ�����
    lv_roller_set_selected(roller, 2, LV_ANIM_ON);

    lv_obj_t *slider = lv_slider_create(activity4);
    lv_obj_set_width(slider, lv_obj_get_width(lv_scr_act()) * 3 / 4);
    lv_obj_set_height(slider, lv_obj_get_height(lv_scr_act()) / 24);
    lv_slider_set_mode(slider, LV_SLIDER_MODE_SYMMETRICAL);
    lv_slider_set_range(slider, -100, 100);
    lv_obj_align_to(slider, roller, LV_ALIGN_OUT_BOTTOM_MID, 0, lv_obj_get_height(lv_scr_act()) / 12);
    /*�����LV_EVENT_VALUE_CHANGED�ص�*/

    lv_obj_add_flag(activity4, LV_OBJ_FLAG_HIDDEN); // ���ؽ���4

    /*��3������*/
    activity5 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(activity5, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

    /*����ͼ��*/
    back2 = lv_btn_create(activity5);
    lv_obj_set_style_bg_color(back2, lv_color_hex(0x000000), LV_ALIGN_DEFAULT);
    lv_obj_set_style_bg_opa(back2, 0, 0);
    lv_obj_set_style_shadow_opa(back2, 0, 0);
    lv_obj_align(back2, LV_ALIGN_TOP_LEFT, 0, lv_obj_get_height(lv_scr_act()) / 24);
    lv_obj_add_event_cb(back2, btn2_cb, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_t *label_back2 = lv_label_create(back2);
    lv_obj_align(label_back2, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_back2, LV_SYMBOL_LEFT);
    lv_obj_set_style_text_color(label_back2, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_back2, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    /*title*/
    lv_obj_t *label_title = lv_label_create(activity5); /* �������� */
    lv_obj_align(label_title, LV_ALIGN_TOP_MID, 0, lv_obj_get_height(lv_scr_act()) / 8);
    lv_obj_set_style_text_font(label_title, &lv_font_montserrat_20,
                               LV_STATE_DEFAULT);     /* �������� */
    lv_label_set_text(label_title, "Today's prices"); /* �����ı����� */

    /* ��� */
    lv_obj_t *table = lv_table_create(activity5);                    /* ������� */
    lv_obj_set_height(table, lv_obj_get_height(lv_scr_act()) / 2);   /* ���ñ���ܵĸ߶� */
    lv_obj_set_width(table, lv_obj_get_width(lv_scr_act()) * 3 / 4); /* ���ñ���ܵĸ߶� */
    lv_obj_center(table);                                            /* ����λ�� */
    /* ���õ� 1 �е�Ԫ�����ݣ����ƣ� */
    lv_table_set_cell_value(table, 0, 0, "Name");
    lv_table_set_cell_value(table, 1, 0, "Apple");
    lv_table_set_cell_value(table, 2, 0, "Banana");
    lv_table_set_cell_value(table, 3, 0, "Lemon");
    lv_table_set_cell_value(table, 4, 0, "Grape");
    lv_table_set_cell_value(table, 5, 0, "Melon");
    lv_table_set_cell_value(table, 6, 0, "Peach");
    lv_table_set_cell_value(table, 7, 0, "Nuts");

    /* ���õ� 2 �е�Ԫ�����ݣ��۸� */
    lv_table_set_cell_value(table, 0, 1, "Price");
    lv_table_set_cell_value(table, 1, 1, "$7");
    lv_table_set_cell_value(table, 2, 1, "$4");
    lv_table_set_cell_value(table, 3, 1, "$6");
    lv_table_set_cell_value(table, 4, 1, "$2");
    lv_table_set_cell_value(table, 5, 1, "$5");
    lv_table_set_cell_value(table, 6, 1, "$1");
    lv_table_set_cell_value(table, 7, 1, "$9");

    /* ��Ԫ���� */
    lv_table_set_col_width(table, 0, lv_obj_get_width(lv_scr_act()) / 3);
    lv_table_set_col_width(table, 1, lv_obj_get_width(lv_scr_act()) / 2 / 3);

    lv_obj_add_flag(activity5, LV_OBJ_FLAG_HIDDEN); // ���ؽ���4
}
