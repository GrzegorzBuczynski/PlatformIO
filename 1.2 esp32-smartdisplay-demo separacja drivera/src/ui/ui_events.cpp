#include "ui_events.h"


void OnAddOneClicked(lv_event_t *e)
{
    static uint32_t cnt = 0;
    cnt++;
    lv_label_set_text_fmt(ui_lblCountValue, "%u", cnt);
}

void OnRotateClicked(lv_event_t *e)
{
    // Użyj wyizolowanej funkcji z modułu screen_rotation
    rotate_screen_to_next_orientation(e);
}