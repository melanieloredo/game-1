#include "bn_core.h"
#include "bn_regular_bg_position_hbe_ptr.h"
#include "bn_regular_bg_items_gba_screen.h"
#include "bn_keypad.h"

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

int main()
{
    bn::core::init();

    show_title();

    while(true)
    {
        bn::core::update();
    }
}
