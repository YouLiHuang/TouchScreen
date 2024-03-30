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
