#pragma once

#include "api/types/vector.h"
#include "api/types/matrix.h"
#include "api/types/enum.h"
#include "api/types/gameevent.h"
#include "api/types/gamestate.h"
#include "api/types/player.h"

namespace api
{
    namespace libs
    {
        using namespace types;

        /**
         * @brief Base FreeSpace 2 functions. Available as "ba" in the global lua scope.
         *
         * @ingroup GRP_SCRIPTING_API_LIBS
         */
        class base : public library
        {
        public:
            ~base() {}

            /**
             * @brief Prints a string
             * @param msg The printed message, should end with a newline character if a newline is desired
             */
            static void print(const char* msg);

            /**
             * @brief Displays a FreeSpace warning (debug build-only) message with the string provided
             * @param msg The displayed message
             */
            static void warning(const char* msg);

            /**
             * @brief Displays a FreeSpace error message with the string provided
             * @param msg The displayed message
             */
            static void error(const char* msg);

            /**
             * @brief Creates a vector object
             * @param x x-value of the resulting vector, defaults to 0
             * @param y y-value of the resulting vector, defaults to 0
             * @param z z-value of the resulting vector, defaults to 0
             * @return A new vector object
             *
             * @deprecated Please use the constructor of vector instead of this function
             */
            static vector createVector(float x, float y, float z);

            /**
             * @brief Given 0, 3, or 9 arguments, creates an orientation object with that orientation.
             * If given 0 parameters the identity matrix will be returned, if given 3 parameters the values will be interpreted as euler angles.
             * If given 9 parameters constructs a 3x3 matrix from those values.
             * @param a Matrix value
             * @param b Matrix value
             * @param c Matrix value
             * @param d Matrix value
             * @param e Matrix value
             * @param f Matrix value
             * @param g Matrix value
             * @param h Matrix value
             * @param i Matrix value
             * @return A new matrix object
             *
             * @deprecated Please use the constructor of matrix instead of this function
             */
            static matrix createOrientation(float a, float b, float c, float d, float e, float f, float g, float h, float i);

            /**
             * @brief The overall frame time in seconds since the engine has started
             * @return Overall time (seconds)
             */
            static float getFrametimeOverall();

            /**
             * @brief Gets how long this frame is calculated to take. Use it to for animations, physics, etc to make incremental changes.
             * @param adjustForTimeCompression If the value should be adjusted for time compression
             * @return The frame time
             */
            static float getFrametime(bool adjustForTimeCompression);

            /**
             * @brief Gets current FreeSpace state;
             * if a depth is specified, the state at that depth is returned.
             * (IE at the in-game options game, a depth of 1 would give you the game state,while the function defaults to 0, which would be the options screen.)
             * @param depth Depth of the returned gamestate
             * @return Current game state at specified depth, or invalid handle if no game state is active yet
             */
            static gamestate getCurrentGameState(int depth);

            /**
             * @brief Gets this computers current MP status
             * @return Current MP status
             */
            static const char* getCurrentMPStatus();

            /**
             * @brief Gets a handle of the currently used player.
             * @note If there is no current player then the first player will be returned, check the game state to make sure you have a valid player handle.
             * @return Player handle
             */
            static player getCurrentPlayer();

            /**
             * @brief Sets the current control mode for the game.
             * @param e One of the *_CONTROL enumerations
             * @return Current control mode
             */
            static const char* setControlMode(const luaenum& e);
            /**
             * @brief Gets the current control mode for the game.
             * @return Current control mode
             */
            static const char* setControlMode();

            /**
             * @brief Gets the current control mode for the game.
             * @return Current control mode
             */
            static const char* setButtonControlMode();
            /**
             * @brief Sets the current control mode for the game.
             * @param e One of the *_BUTTON_CONTROL enumeration
             * @return Current control mode
             */
            static const char* setButtonControlMode(const luaenum& e);

            /**
             * @brief Sets whether to display tips of the day the next time the current pilot enters the mainhall.
             * @param enable Enable of disable tips, defaults to @c false
             */
            static void setTips(bool enable);

            /**
             * @brief Sets current game event.
             * @warning You can crash FreeSpace 2 by posting an event at an improper time, so test extensively if you use it.
             * @param event The event to post
             * @return True if event was posted, false if passed event was invalid
             */
            static bool postGameEvent(const gameevent& event);

            /**
             * Array of GameEvents
             */
            class GameEvents : public library
            {
            public:
                ~GameEvents() {}

                /**
                 * @brief Gets gameevent by name
                 * @param key The name of the game event
                 * @return gameevent handle or invalid handle when the name is not valid
                 */
                static gameevent get(const char* key);

                /**
                 * @brief Gets gameevent by index
                 * @param index The index of the gameevent to be returned
                 * @return The gameevent at the specified index or invalid handle if index is invalid.
                 */
                static gameevent get(int index);

                /**
                 * @brief Gets the count of how many gameevents there are
                 * @return The number of game events
                 */
                static size_t count();
            };

            /**
             * Array of gamestates
             */
            class GameStates : public library
            {
            public:
                ~GameStates() {}

                /**
                 * @brief Gets gamestate by name
                 * @param key The name of the game state
                 * @return gamestate handle or invalid handle when the name is not valid
                 */
                static gamestate get(const char* key);

                /**
                 * @brief Gets gamestate by index
                 * @param index The index of the game state
                 * @return gamestate handle or invalid handle when the index is not valid
                 */
                static gamestate get(int index);

                /**
                 * @brief Gets the count of how many gamestates there are
                 * @return The number of game states
                 */
                static size_t count();
            };

            /**
             * @brief Registers the functions of this library
             * @return The scope holding the registrations
             * @notscriptingapi
             */
            static luabind::scope registerScope();
        };
    }
}
