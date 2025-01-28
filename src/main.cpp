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
    void show_title() {
        bn::regular_bg_ptr bg = bn::regular_bg_items::gba_screen.create_bg(0, 0);
        bg.set_visible(true);

        //wait for the user
        while(! bn::keypad::a_pressed()){
            bn::core::update();
        }
    }

    void numberPicker(int value) {
        bn::sprite_text_generator text_generator(fixed_32x64_sprite_font);
        // bn::sprite_text_generator text_generator(common::fixed_8x8_sprite_font);
        text_generator.set_center_alignment();

        bn::string_view text[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

        while(! bn::keypad::start_pressed()) {
            bn::vector<bn::sprite_ptr, 2> text_sprites;
            if (bn::keypad::up_pressed() && value < 9) {
                value += 1;
            }
            if (bn::keypad::down_pressed() && value > 0) {
                value -= 1;
            }
            text_generator.generate(0, 0, text[value], text_sprites);
            bn::core::update();
        }
    }
}

int main() {
    bn::core::init();

    show_title();

    numberPicker(4);

    while(true)
    {
        bn::core::update();
    }
}