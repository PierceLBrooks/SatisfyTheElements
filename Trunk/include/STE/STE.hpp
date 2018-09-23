
// Author: Pierce Brooks

// Satisfy The Elements is about helping some romantically distraught elementals find their way to love through the dating service you work for!

#ifndef STE_HPP
#define STE_HPP

#define DEFAULT_SCORE (5)
#define DEFAULT_VOLUME (25.0f)
#define FPS_LIMIT (60)
#define MAX_DELTA_TIME (0.125f)
#define BUTTON_SCALE (0.125f)

#define PI (22.0f/7.0f)
#define DEG_TO_RAD (180.0f/(22.0f/7.0f))
#define RAD_TO_DEG ((22.0f/7.0f)/180.0f)

#define CHERRY_BLOSSOMS_SPAWN_TIME (0.5f)
#define CHERRY_BLOSSOMS_ROTATION_SPEED (0.5f)
#define CHERRY_BLOSSOMS_SPEED (250.0f)
#define CHERRY_BLOSSOMS_LIFE (2.5f)

#define INVALID_STATE_ID (-1)
#define NULL_STATE_ID (0)
#define MENU_STATE_ID (1)
#define INTRO_STATE_ID (2)
#define CLIENT_SELECTION_STATE_ID (3)
#define FIRE_STATE_ID (4)
#define WATER_STATE_ID (5)
#define EARTH_STATE_ID (6)
#define AIR_STATE_ID (7)
#define RESULT_STATE_ID (8)

#define BUTTON_TRANSPARENCY 192
#define BUTTON_PRESSED_COLOR (sf::Color(64, 64, 64, BUTTON_TRANSPARENCY))
#define BUTTON_RELEASED_COLOR (sf::Color(196, 196, 196, BUTTON_TRANSPARENCY))

#define DEFAULT_TEXT_COLOR (sf::Color::White)
#define TEXT_OUTLINE_THICKNESS (0.125f)
#define MAX_LINE_LENGTH (80)

#endif // STE_HPP
