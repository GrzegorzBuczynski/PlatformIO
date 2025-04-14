// liblary TFT_eSPI 
// st7262  ESP Display Panel handles this driver
// P050B028-IPS-CTP display panel
// 800x480 resolution
// if event_code == LV_EVENT_CLICKED lub event_code == released();
// lv_obj_t *target = lv_event_get_target(e); z kordynat z elementów na planszy lub z seriala
// if target != null set flag to update screen
// update object parameters object now how to parse json data update object
// remove event flag
// dodaj funkcje która zaktualizuje która plansza jest aktualnie wyświetlana void update_screen(int screen_id)


//GT911 – sterownik dotyku to GT911, czyli powszechnie stosowany pojemnościowy kontroler dotyku (I2C)
// ​Analiza oprogramowania układowego wyświetlacza:​

// Jeśli masz fizyczny dostęp do wyświetlacza z wgranym oprogramowaniem, możesz spróbować zgrać jego zawartość 
//za pomocą narzędzi takich jak esptool.​

// LVGL 8.3.7 – wyświetlacz używa LVGL (Light and Versatile Graphics Library), bardzo popularnej biblioteki GUI dla mikrokontrolerów.

// GT911 – sterownik dotyku to GT911, czyli powszechnie stosowany pojemnościowy kontroler dotyku (I2C).

// esp_lcd_touch.c – sugeruje, że użyto frameworka ESP-IDF z esp_lcd_touch, czyli oficjalnego API do obsługi dotyku w ESP32.

// Pamiętaj, że odczytanie i analiza skompilowanego kodu binarnego może być skomplikowane i czasochłonne.





/* 提示：测试功能，代码书写错误将造成编译失败 */

/* 提示：请在这里编辑你的自定义函数（支持标准C语言），eg： */

//USER CODE（请勿删除此行）

void page4_arc7_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        lv_obj_t *target = lv_event_get_target(e);
        lv_obj_t *arc = lv_event_get_target(e);
        char value[10];
        sprintf(value, "%d", lv_arc_get_value(arc));
        lv_label_set_text(page4_text8, value);
    }
}

void page5_img4_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_t *target = lv_event_get_target(e);
        lv_obj_add_flag(page5_img4, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page5_img3, LV_OBJ_FLAG_HIDDEN);
    }
}

void page5_img3_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_t *target = lv_event_get_target(e);
        lv_obj_add_flag(page5_img3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page5_img4, LV_OBJ_FLAG_HIDDEN);
    }
}


void page6_img13_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img13, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img2, LV_OBJ_FLAG_HIDDEN);
    }
}


void page6_img2_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img13, LV_OBJ_FLAG_HIDDEN);
    }
}

void page6_img5_event_cb(lv_event_t *e)
{
      lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img5, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img10, LV_OBJ_FLAG_HIDDEN);
    }
}


void page6_img8_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img8, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img3, LV_OBJ_FLAG_HIDDEN);
    }
}

void page6_img3_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img8, LV_OBJ_FLAG_HIDDEN);
    }
}

void page6_img9_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img9, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img4, LV_OBJ_FLAG_HIDDEN);
    }
}

void page6_img4_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img4, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img9, LV_OBJ_FLAG_HIDDEN);
    }
}

void page6_img10_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img10, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img5, LV_OBJ_FLAG_HIDDEN);
    }
}

void page6_img12_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img12, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img7, LV_OBJ_FLAG_HIDDEN);
    }
}

void page6_img7_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img7, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img12, LV_OBJ_FLAG_HIDDEN);
    }
}


void page4_slider6_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        lv_obj_t *target = lv_event_get_target(e);
        lv_obj_t *slider = lv_event_get_target(e);
        char value[10];
        sprintf(value, "%d%%", lv_slider_get_value(slider));
        lv_label_set_text(page4_text10, value);
    }
}

int all_value = 0;
lv_timer_t *my_timer1;
void my_timer_cb1(lv_timer_t *timer)
{
    all_value++;
    if (all_value == 100)
    {
        all_value = 0;
    }
    lv_slider_set_value(page8_slider2, all_value, LV_ANIM_OFF);
    lv_slider_set_value(page8_slider3, all_value, LV_ANIM_OFF);
    lv_slider_set_value(page8_slider4, all_value, LV_ANIM_OFF);
    char value[10];
    sprintf(value, "%d%%", all_value);
    lv_label_set_text(page8_text10, value);
}


void page8_imgbtn5_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_t *target = lv_event_get_target(e);
        all_value = 0;
        lv_slider_set_value(page8_slider2, 0, LV_ANIM_OFF);
        lv_slider_set_value(page8_slider3, 0, LV_ANIM_OFF);
        lv_slider_set_value(page8_slider4, 0, LV_ANIM_OFF);
        char value[10];
        sprintf(value, "%d%%", all_value);
        lv_label_set_text(page8_text10, value);

        if (my_timer1 != NULL)
        {
            lv_timer_resume(my_timer1);
        }
        else
        {
            my_timer1 = lv_timer_create(my_timer_cb1, 200, NULL); // 创建一个每秒触发一次的定时器
        }
    }
}

void page5_img5_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_t *target = lv_event_get_target(e);
        lv_obj_add_flag(page5_img5, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page5_img6, LV_OBJ_FLAG_HIDDEN);
    }
}



void page5_img6_event_cb(lv_event_t *e)
{
      lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page5_img6, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img10, LV_OBJ_FLAG_HIDDEN);
    }
}


void page6_img11_event_cb(lv_event_t *e)
{
      lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img11, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img6, LV_OBJ_FLAG_HIDDEN);
    }
}

void page6_img6_event_cb(lv_event_t *e)
{
      lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(page6_img6, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(page6_img11, LV_OBJ_FLAG_HIDDEN);
    }
}




void page8_imgbtn7_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_t *target = lv_event_get_target(e);
        if (my_timer1 != NULL)
        {
            lv_timer_pause(my_timer1);
        }

        if (all_value != 100)
        {
            all_value++;
            lv_slider_set_value(page8_slider2, all_value, LV_ANIM_OFF);
            lv_slider_set_value(page8_slider3, all_value, LV_ANIM_OFF);
            lv_slider_set_value(page8_slider4, all_value, LV_ANIM_OFF);
            char value[10];
            sprintf(value, "%d%%", all_value);
            lv_label_set_text(page8_text10, value);
        }
    }
}

void page8_imgbtn8_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_t *target = lv_event_get_target(e);
        if (my_timer1 != NULL)
        {
            lv_timer_pause(my_timer1);
        }
        if (all_value != 0)
        {
            all_value--;
            lv_slider_set_value(page8_slider2, all_value, LV_ANIM_OFF);
            lv_slider_set_value(page8_slider3, all_value, LV_ANIM_OFF);
            lv_slider_set_value(page8_slider4, all_value, LV_ANIM_OFF);
            char value[10];
            sprintf(value, "%d%%", all_value);
            lv_label_set_text(page8_text10, value);
        }
    }
}

//USER CODE END（请勿删除此行）

/* 提示：在初始化完成后执行，直接输入函数名，顺序执行请换行，eg： */

//DONE（请勿删除此行）

    lv_obj_add_flag(page5_img3, LV_OBJ_FLAG_CLICKABLE);  
    lv_obj_add_flag(page5_img4, LV_OBJ_FLAG_CLICKABLE);    
    lv_obj_add_flag(page5_img5, LV_OBJ_FLAG_CLICKABLE); 
    lv_obj_add_flag(page5_img5, LV_OBJ_FLAG_CLICKABLE);     
    lv_obj_add_flag(page5_img6, LV_OBJ_FLAG_CLICKABLE);   
    lv_obj_add_flag(page6_img2, LV_OBJ_FLAG_CLICKABLE);   
    lv_obj_add_flag(page6_img3, LV_OBJ_FLAG_CLICKABLE);   
    lv_obj_add_flag(page6_img4, LV_OBJ_FLAG_CLICKABLE); 
    lv_obj_add_flag(page6_img5, LV_OBJ_FLAG_CLICKABLE);  
    lv_obj_add_flag(page6_img6, LV_OBJ_FLAG_CLICKABLE);   
    lv_obj_add_flag(page6_img7, LV_OBJ_FLAG_CLICKABLE);      
    lv_obj_add_flag(page6_img8, LV_OBJ_FLAG_CLICKABLE);     
    lv_obj_add_flag(page6_img9, LV_OBJ_FLAG_CLICKABLE);  
    lv_obj_add_flag(page6_img10, LV_OBJ_FLAG_CLICKABLE);  
    lv_obj_add_flag(page6_img11, LV_OBJ_FLAG_CLICKABLE);    
    lv_obj_add_flag(page6_img12, LV_OBJ_FLAG_CLICKABLE);     
    lv_obj_add_flag(page6_img13, LV_OBJ_FLAG_CLICKABLE);    

   lv_obj_add_event_cb(page4_slider6, page4_slider6_event_cb, LV_EVENT_ALL, NULL);
   lv_obj_add_event_cb(page4_arc7, page4_arc7_event_cb, LV_EVENT_ALL, NULL);
   lv_obj_add_event_cb(page5_img3, page5_img3_event_cb, LV_EVENT_ALL, NULL);
   lv_obj_add_event_cb(page5_img4, page5_img4_event_cb, LV_EVENT_ALL, NULL);
   lv_obj_add_event_cb(page5_img5, page5_img5_event_cb, LV_EVENT_ALL, NULL);
   lv_obj_add_event_cb(page5_img6, page5_img6_event_cb, LV_EVENT_ALL, NULL);
   lv_obj_add_event_cb(page6_img2, page6_img2_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page6_img3, page6_img3_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page6_img4, page6_img4_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page6_img5, page6_img5_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page6_img6, page6_img6_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page6_img7, page6_img7_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page6_img8, page6_img8_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page6_img9, page6_img9_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page6_img10, page6_img10_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page6_img11, page6_img11_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page6_img12, page6_img12_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page6_img13, page6_img13_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page8_imgbtn5, page8_imgbtn5_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page8_imgbtn7, page8_imgbtn7_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(page8_imgbtn8, page8_imgbtn8_event_cb, LV_EVENT_ALL, NULL);



//DONE END（请勿删除此行）
