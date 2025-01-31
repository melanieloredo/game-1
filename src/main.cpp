#include "bn_core.h"
#include "bn_regular_bg_position_hbe_ptr.h"
#include "bn_regular_bg_items_gba_screen.h"
#include "bn_keypad.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "fixed_32x64_sprite_font.h"
#include "common_fixed_8x8_sprite_font.h"
#include <bn_random.h>

namespace {
    // Display title screen
    void show_title() {
        bn::regular_bg_ptr bg = bn::regular_bg_items::gba_screen.create_bg(0, 0);
        bg.set_visible(true);

        // Wait for the user to press Start
        while (!bn::keypad::start_pressed()) {
            bn::core::update();
        }

        // Clear the title screen background after Start is pressed
        bg.set_visible(false); // Ensure the title background is hidden
    }

    void numberPicker(int target_value) {
        // Initialize the text generator
        bn::sprite_text_generator text_generator(fixed_32x64_sprite_font);
        text_generator.set_center_alignment();

        // Define the numbers to be displayed
        bn::string_view text[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
        bn::vector<bn::sprite_ptr, 32> text_sprites; // Holds the sprites for the numbers

        // Initialize the random generator
        // bn::random random_generator;

        // Generate a random target number
        // int warm_up_steps = 20; // Introduce variability with multiple warm-up calls
        // for (int i = 0; i < warm_up_steps; ++i) {
        //     random_generator.get_int(10); // Warm up the generator
        // }

        // int target_value = random_generator.get_int(10); // Random number between 0 and 9
        int value = 0; // Current selected number

        // Main loop for the number picker
        while (true) {
            // Clear existing text sprites before generating new ones
            text_sprites.clear();

            // Handle input for number selection
            if (bn::keypad::up_pressed() && value < 9) {
                value += 1; // Increment value
            }
            if (bn::keypad::down_pressed() && value > 0) {
                value -= 1; // Decrement value
            }

            // Generate the current number display
            text_generator.generate(0, 0, text[value], text_sprites);

            // Check if player presses A to confirm their selection
            if (bn::keypad::a_pressed()) {
                text_sprites.clear(); // Clear the number sprites
                bn::vector<bn::sprite_ptr, 32> result_sprites; // Result text sprites

                // Display result based on selection
                if (value == target_value) {
                    text_generator.generate(0, 20, "You Win!", result_sprites);
                } else {
                    text_generator.generate(0, 20, "You Lose!", result_sprites);
                }

                // Wait for the player to press Start to exit
                while (!bn::keypad::start_pressed()) {
                    bn::core::update();
                }
                break; // Exit the number picker loop
            }

            // Update the game
            bn::core::update();
        }
    }
}

int main() {
    bn::core::init();

    show_title(); // Display the title screen

    bn::random random_generator;

    //numberPicker(); // Start the number picker game

    while (true) {
        int value = random_generator.get_int(10);
        numberPicker(value);

        bn::core::update(); // Keep the game running
    }
}
