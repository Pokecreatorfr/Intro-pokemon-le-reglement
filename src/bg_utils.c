

#include "headers/bg_utils.h"
#include "headers/intro_master.h"

volatile struct REG_BGCNT (*reg_bg_cnt)[4] = (struct REG_BGCNT (*)[4]) 0x04000008;

void set_bg_config()
{
    u8 i;
    
    struct REG_BGCNT bg_cnt[4] = { 
        { //BG0
            .priority= 2,
            .char_index = 0,
            .padding = 0,
            .mosiac = 0,
            .color = 0, 
            .map_index = 7,
            .screen_over = 0,
            .size = 0,
        },  { //BG1
            .priority= 1,
            .char_index = 1,
            .padding = 0,
            .mosiac = 0,
            .color = 0, 
            .map_index = 15,
            .screen_over = 0,
            .size = 0,
        },  { //BG2
            .priority= 2,
            .char_index = 2,
            .padding = 0,
            .mosiac = 0,
            .color = 0, 
            .map_index = 23,
            .screen_over = 0,
            .size = 0,
        },  { //BG3
            .priority= 3,
            .char_index = 3,
            .padding = 0,
            .mosiac = 0,
            .color = 0, 
            .map_index = 31,
            .screen_over = 0,
            .size = 0,
        }
    };
    cast_dispcnt dispcnt = { .st = { 
            .bg_mode =  0,
            .reserved = 0,
            .display_frame = 0,
            .hblank_interval = 0,
            .obj_vram_map = 1,
            .forced_blank = 0,
            .display_bg0 = 1,
            .display_bg1 = 1,
            .display_bg2 = 1,
            .display_bg3 = 1,
            .display_obj = 1,
            .display_window0 = 0,
            .display_window1 = 0,
            .display_obj_window = 0
        }
    };


    clear_bgs();
    
    REG_DISPCNT = dispcnt.casted_u16;
    for (i = 0; i < 4; i++) 
    {
        (*reg_bg_cnt)[i] = bg_cnt[i];
    }
    write_bg_positions(intro_master);
}


void clear_bgs()
{
    memset((void *) 0x6000000, 0, 0x10000);
}

void move_bg(u8 bg, s16 x, s16 y)
{
    (*intro_master->bg_hv_mirror)[bg].x += x;
    (*intro_master->bg_hv_mirror)[bg].y += y;
    write_bg_positions(intro_master);
}

void load_bg_data(u8 bg_num, void* tileset, void* tilemap)
{
    lz77UnCompVram(tilemap, (void *) 0x6003800 + bg_num * 0x4000);
    lz77UnCompVram(tileset, (void *) 0x6000000 + bg_num * 0x4000);
}

void load_bg_pal(u8 pal_num, void * palette, bool is_compressed)
{
    if (is_compressed){
        gpu_pal_apply_compressed(palette, 16 * pal_num, 32 + 16 * pal_num);
    } else {
        gpu_pal_apply(palette, 16 * pal_num, 32 + 16 * pal_num);
    }
    
} 
