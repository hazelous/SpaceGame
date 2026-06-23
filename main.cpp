#include "splashkit.h"
#include <vector>
#include <string>

using std::vector;
using namespace std;

#define PLAYER_SPEED 4

/**
 * Different options for the kind of planet.
 * Adjusts the image used.
 */
enum planet_kind
{
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE,
    PLUTO
};

/**
 * Different options for the different falling objects.
 * Adjusts the image used.
 */
enum falling_object_kind
{
    COIN,
    CASH,
    DIAMOND,
    ASTEROID,

};

/**
 * The player data keeps track of all of the information related to the player.
 *
 * @field   player_sprite   The player's sprite - used to track position and movement
 * @field   score           The current score for the player
 */
struct player_data
{
    sprite      player_sprite;
    int         bank;
};

/**
 * The planet data keeps track of all of the information related to the planet.
 *
 * @field   planet_sprite   The planet's sprite
 * @field   kind            kind of planet
 */
struct planet_data
{
    sprite      planet_sprite;
    planet_kind kind;
};

/**
 * The falling object data keeps track of all of the information related to the falling object.
 *
 * @field   object_sprite   The object's sprite
 * @field   kind            kind of object
 */
struct falling_object_data
{
    sprite                object_sprite;
    falling_object_kind   kind;
};

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

/**
 * Creates a new player in the bottom centre of the screen with the aquarii ship.
 *
 * @returns     The new player data
 */
player_data new_player()
{
    player_data result;
    bitmap aquarii_bitmap = bitmap_named("aquarii"); // Load the AQUARII ship bitmap which represents the player

    // Create the sprite for the player
    result.player_sprite = create_sprite(aquarii_bitmap);

    // Initialize the score
    result.bank = 0;

    // Position the player at the bottom center of the screen
    sprite_set_x(result.player_sprite, (screen_width() - sprite_width(result.player_sprite)) / 2);
    sprite_set_y(result.player_sprite, screen_height() - 70);

    // Make the player/rocket face upwards
    sprite_set_rotation(result.player_sprite, -90);

    return result;
}

/**
 * Actions a step update of the player - moving them.
 *
 * @param player_to_update      The player being updated
 */
void update_player(player_data &player_to_update)
{
    // Apply movement updates
    update_sprite(player_to_update.player_sprite);

    // Get the current x position of the player
    double player_x = sprite_x(player_to_update.player_sprite);

    // Make sure the player doesn't go out of the window
    if (player_x < 0)
    {
        sprite_set_x(player_to_update.player_sprite, 0);
    }
    else if (player_x > screen_width() - sprite_width(player_to_update.player_sprite))
    {
        sprite_set_x(player_to_update.player_sprite, screen_width() - sprite_width(player_to_update.player_sprite));
    }
}

/**
 * Read user input and update the player based on this interaction.
 *
 * @param player    The player to update
 */
void handle_input(player_data &player)
{
    // Handle movement and rotation
    if (key_down(LEFT_KEY))
    {
        // Face left and move left
        sprite_set_rotation(player.player_sprite, -180); // Rotate to face left
        sprite_set_dx(player.player_sprite, PLAYER_SPEED); // Move right based on sprite rotation (move left)
    }
    else if (key_down(RIGHT_KEY))
    {
        // Face right and move right
        sprite_set_rotation(player.player_sprite, 0); // Rotate to face right
        sprite_set_dx(player.player_sprite, PLAYER_SPEED); // Move right based on sprite rotation (move right)
    }
    else
    {
        // face upwards (90 degrees) and stop moving
        sprite_set_rotation(player.player_sprite, -90); // Rotate to face up
        sprite_set_dx(player.player_sprite, 0); // Stop horizontal movement
    }
}

/**
 * The planet bitmap function converts a planet kind into a
 * bitmap that can be used.
 *
 * @param kind  The kind of planet you want the bitmap of
 * @return      The bitmap matching this planet kind
 */
bitmap planet_bitmap(planet_kind kind)
{
    // switch cases to return bitmap for all planets
    switch (kind)
    {
    case MERCURY:
        return bitmap_named("mercury");
    case VENUS:
        return bitmap_named("venus");
    case EARTH:
        return bitmap_named("earth");
    case MARS:
        return bitmap_named("mars");
    case JUPITER:
        return bitmap_named("jupiter");
    case SATURN:
        return bitmap_named("saturn");
    case URANUS:
        return bitmap_named("uranus");
    case NEPTUNE:
        return bitmap_named("neptune");
    case PLUTO:
        return bitmap_named("pluto");
    default:
        return bitmap_named("earth");
    }
}

/**
 * Creates a new enlarged planet on top of the screen.
 *
 * @returns     The new planet data
 */
planet_data new_planet()
{
    planet_data result;

    // Assign a random planet_kind to the result
    result.kind = static_cast<planet_kind>(rnd(0, 8));

    // Create a bitmap of the result's planet kind
    bitmap default_bitmap = planet_bitmap(result.kind);

    // Create the sprite
    result.planet_sprite = create_sprite(default_bitmap);

    // Scale the planet sprite to make it larger
    sprite_set_scale(result.planet_sprite, 3.0); // Scale factor of 3x

    // Position the planet at the top-center of the screen
    double center_x = (screen_width() - sprite_width(result.planet_sprite)) / 2;
    double top_y = -sprite_height(result.planet_sprite) / 1.5; // a portion of the planet is off-screen

    sprite_set_x(result.planet_sprite, center_x);
    sprite_set_y(result.planet_sprite, top_y);

    return result;
}

void reset_falling_object(falling_object_data &object_to_reset)
{
    // Randomize the horizontal position
    double rnd_x = rnd(0, screen_width() - sprite_width(object_to_reset.object_sprite));
    sprite_set_x(object_to_reset.object_sprite, rnd_x);

    // Place the object above the screen
    sprite_set_y(object_to_reset.object_sprite, -sprite_height(object_to_reset.object_sprite));
}

/**
 * Creates a new falling object on top of the screen at a random x value.
 *
 * @param kind  The kind of falling object
 * @returns     The new object data
 */
falling_object_data new_falling_object(falling_object_kind kind)
{
    falling_object_data result;
    result.kind   = kind;

    // Decide which bitmap to load based on kind
    bitmap obj_bitmap;
    switch(kind)
    {
        case COIN:
            obj_bitmap = bitmap_named("coin");
            break;
        case CASH:
            obj_bitmap = bitmap_named("cash");
            break;
        case DIAMOND:
            obj_bitmap = bitmap_named("diamond");
            break;
        case ASTEROID:
            obj_bitmap = bitmap_named("mars");
            break;
        default:
            obj_bitmap = bitmap_named("coin");
    }

    // Create the sprite
    result.object_sprite = create_sprite(obj_bitmap);
    // Make the sprites smaller
     sprite_set_scale(result.object_sprite, 0.5);
    // Reset the object's position (sets it at the top of the screen randomly)
    reset_falling_object(result);

    return result;
}

/**
 * Updates the object to make it fall, deal with collisions and resetting.
 *
 * @param object_to_update      The object being updated
 * @param player                The player to check collision with
 */
void update_falling_object(falling_object_data &object_to_update, player_data &player)
{
    // Move object downward at speed 3.0
    sprite_set_dy(object_to_update.object_sprite, 3.0);
    update_sprite(object_to_update.object_sprite);

    // Check collision with player
    if ( sprite_collision(player.player_sprite, object_to_update.object_sprite) )
    {
        // Updates player score based on the object collided
        if (object_to_update.kind == DIAMOND)
        {
            player.bank += 3;
        }
        else if (object_to_update.kind == CASH)
        {
            player.bank += 2;
        }
        else if (object_to_update.kind == COIN)
        {
            player.bank += 1;
        }
        else if (object_to_update.kind == ASTEROID)
        {
            player.bank -= 5;
        }

        // Reset the object's position (sets it at the top of the screen randomly)
    reset_falling_object(object_to_update);
    }

    // If it has moved past the bottom, reset the object
    if ( sprite_y(object_to_update.object_sprite) > screen_height() )
    {
        // Reset the object's position (sets it at the top of the screen randomly)
    reset_falling_object(object_to_update);
    }
}

/**
 * Adds a random object and an asteroid to the vector
 *
 * @param falling_objects       vector to add objects to
 */
void add_random_falling_object(vector<falling_object_data> &falling_objects)
{
    // Generate a random falling object kind
    falling_object_kind random_kind = static_cast<falling_object_kind>(rnd(0, 3)); // 0 to 2 for COIN, CASH, DIAMOND
    // Add a new falling object to the vector
    falling_objects.push_back(new_falling_object(random_kind));
    // for every new falling object, add an asteroid to make it difficult
    falling_objects.push_back(new_falling_object(ASTEROID));
}

/**
 * Update all falling objects and handle collisions with the player.
 */
void update_falling_objects(vector<falling_object_data> &falling_objects, player_data &player)
{
    // loops through every falling object inside the vector and updates them
    for (int i = 0; i < falling_objects.size(); i++)
    {
        update_falling_object(falling_objects[i], player);
    }
}

/**
 * Draw all falling objects on the screen.
 */
void draw_falling_objects(const vector<falling_object_data> &falling_objects)
{
    // loops through every falling object in the vector and draws them
    for (int i = 0; i < falling_objects.size(); i++)
    {
        draw_sprite(falling_objects[i].object_sprite);
    }
}

// Draw a HUD that displays the bank balance of the player
void draw_hud(player_data &player)
{
    // load a large font size
    // create a blue rectangle for the hud with option_to_screen so that it is locked at that spot in the window
    fill_rectangle(COLOR_BLUE, 0, 0, 200, 30, option_to_screen());

    // draw text for the score
    draw_text("BANK BALANCE: $" + std::to_string(player.bank), COLOR_WHITE, 0, 10, option_to_screen());

}

int main()
{
    open_window("Asteroid Field", 800, 600);
    load_resources();

    // create the player and planet to display
    player_data player;
    player = new_player();
    planet_data planet;
    planet = new_planet();

    // Dynamic array to store all falling objects
    vector<falling_object_data> falling_objects;

    // count frames to determine when to add new object
    int frames = 0;

    while ( not quit_requested() )
    {
        // Handle input to adjust player movement
        process_events();
        handle_input(player);

        // increment frames
        frames++;

        // every 5 seconds (300 frames), add a new falling object
        if (frames >= 300)
        {
            add_random_falling_object(falling_objects);
            frames = 0;
        }

        // update the player
        update_player(player);
        // Update the planet to keep it on screen
        update_sprite(planet.planet_sprite);
        // update falling objects
        update_falling_objects(falling_objects, player);

        // exits the game if the player loses (gets a negative bank balance)
        if (player.bank < 0)
        {
            write_line("Game Over! You are now in debt.");
            break; // Exit the game loop
        }

        // Redraw the screen
        clear_screen(COLOR_BLACK);

        // Draw everything on screen
        draw_sprite(player.player_sprite);
        draw_sprite(planet.planet_sprite);
        draw_falling_objects(falling_objects);

        draw_hud(player);
        refresh_screen(60);
    }
    return 0;
}