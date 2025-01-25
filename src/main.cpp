#include "bn_core.h"
#include "bn_regular_bg_position_hbe_ptr.h"
#include "bn_regular_bg_items_gba_screen.h"
#include "bn_keypad.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "fixed_32x64_sprite_font.h"
#include "common_fixed_8x8_sprite_font.h"

namespace {
    //display title screen
    void show_title()
    {
        bn::regular_bg_ptr bg = bn::regular_bg_items::gba_screen.create_bg(0, 0);
        bg.set_visible(true);

        //wait for the user
        while(true){
            bn::core::update();

            if(bn::keypad::a_pressed()){
            break;
            }
        }
    }

    void numberPicker() {
        bn::sprite_text_generator text_generator(common::fixed_8x8_sprite_font);
        // huge_text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(-120, -60, "Text", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }
}

int main()
{
    bn::core::init();

    show_title();

    numberPicker();

    while(true)
    {
        bn::core::update();
    }
}