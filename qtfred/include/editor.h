#pragma once
#include <functional>
#include <string>
#include <stdexcept>

namespace fso {
namespace fred {

enum class SubSystem {
    VM, OSRegistry, OS, Timer, CFile, Locale, Graphics, Fonts, Keyboard, Mouse, Iff, Objects, Species,
    MissionBrief, AI, AIProfiles, Armor, Weapon, Medals, Ships, Nebulas, Stars, View,
};

typedef std::function<void (const SubSystem &)> InitializerCallback;

/*! Initialize fs2open subsystems needed by the editor.
 *
 * The user may provide a callback function which will be called after
 * each initialization.
 * This enable the developer to provide information about the startup
 * sequence.
 *
 * \param[in]   cfilepath   CFile root directory.
 * \param[in]   listener    A callback function called after each initializer.
 */
void initialize(const std::string &cfilepath, InitializerCallback listener = [](const SubSystem &) {});

struct mission_load_error : public std::runtime_error {
    mission_load_error(const char *msg) : std::runtime_error {msg} {}
};

/*! Game editor.
 * Handles everything needed to edit the game,
 * without any knowledge of the actual GUI framework stack.
 *
 * Since SCP does not (yet) allow multiple simulations to run
 * simultaneously, this class should be treated as a singleton.
 *
 */
class Editor
{
public:
    Editor();

    /*! Configure which window in the GUI (if any) will override the rendering target.
     *
     * \param[in] handle Target window handle provided by the GUI.
     */
    void setRenderWindow(const void *handle);

    /*! Initialize renderer. */
    void initializeRenderer();

    /*! Handle resizing.
     *
     * \param[in]   width   New width.
     * \param[in]   height  New height.
     */
    void resize(int width, int height);

    /*! Update the game an renders a frame. */
    void update();

    /*! Load a mission. */
    void loadMission(const std::string &filepath);

    void findFirstObjectUnder(int x, int y);

    ///! Non-copyable.
    Editor(const Editor &) = delete;

    ///! Non-copyable.
    const Editor &operator =(const Editor &) = delete;
private:
    void resetPhysics();
    subsys_to_render Render_subsys;
    int currentObject;
};

} // namespace fred
} // namespace fso

// Define hash function for Initialized.
namespace std
{
    template<>
    struct hash<fso::fred::SubSystem>
    {
        typedef fso::fred::SubSystem argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& s) const
        {
            return static_cast<result_type>(s);
        }
    };
}
