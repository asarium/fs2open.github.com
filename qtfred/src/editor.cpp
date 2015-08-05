#include "editor.h"

#include <array>
#include <vector>
#include <stdexcept>

#include <SDL.h>

#include "globalincs/pstypes.h" // vm_init
#include "osapi/osregistry.h" // os_registry_init
#include "io/timer.h" // timer_init
#include "cfile/cfile.h" // cfile_chdir, cfile_init
#include "localization/localize.h" // lcl_init
#include "graphics/2d.h" // gr_init
#include "graphics/font.h" // gr_font_init
#include "io/key.h" // key_init
#include "io/mouse.h" // mouse_init
#include "iff_defs/iff_defs.h" // iff_init
#include "object/object.h" // obj_init
#include "species_defs/species_defs.h" // species_init
#include "mission/missionbriefcommon.h" // mission_brief_init
#include "ai/ai.h" // ai_init
#include "ai/ai_profiles.h" // ai_profiles_init
#include "ship/ship.h" // armor_init, ship_init
#include "weapon/weapon.h" // weapon_init
#include "stats/medals.h" // parse_medal_tbl
#include "nebula/neb.h" // neb2_init
#include "starfield/starfield.h" // stars_init, stars_pre_level_init, stars_post_level_init
#include "osapi/osapi.h" // os_get_window, os_set_window.


namespace fso {
namespace fred {

void initialize(const std::string &cfilepath, InitializerCallback listener)
{
#ifdef SCP_UNIX
        setenv("force_s3tc_enable", "true", 1);
#endif
    std::vector<std::pair<std::function<void(void)>, SubSystem>> initializers = {
		{[](){ std::bind(vm_init, 24 * 1024 * 1024); }, SubSystem::VM},
        {std::bind(os_init_registry_stuff, Osreg_company_name, Osreg_app_name, nullptr), SubSystem::OSRegistry},
        {timer_init, SubSystem::Timer},
        {[&cfilepath](void){
			// cfile needs a file path...
			auto file_path = cfilepath + DIR_SEPARATOR_STR + "qtfred.exe";

            cfile_init(file_path.c_str());
        }, SubSystem::CFile},
        {std::bind(lcl_init, FS2_OPEN_DEFAULT_LANGUAGE), SubSystem::Locale},
        {[](){
            gr_init(GR_OPENGL, 640, 480, 32);
            SDL_HideWindow(os_get_window());
        }, SubSystem::Graphics},
        {gr_font_init, SubSystem::Fonts},
        {key_init, SubSystem::Keyboard},
        {mouse_init, SubSystem::Mouse},
        {iff_init, SubSystem::Iff},
        {obj_init, SubSystem::Objects},
        {species_init, SubSystem::Species},
        {mission_brief_common_init, SubSystem::MissionBrief},
        {ai_init, SubSystem::AI},
        {ai_profiles_init, SubSystem::AIProfiles},
        {armor_init, SubSystem::Armor},
        {weapon_init, SubSystem::Weapon},
        {parse_medal_tbl, SubSystem::Medals},
        {ship_init, SubSystem::Ships},
        {neb2_init, SubSystem::Nebulas},
        {[]() {
            stars_init();
            stars_pre_level_init(true);
            stars_post_level_init();
        }, SubSystem::Stars}
    };

    for (const auto &initializer : initializers) {
        const auto &init_function = initializer.first;
        const auto &which = initializer.second;
        init_function();
        listener(which);
    }
}

Editor::Editor()
    :currentObject {-1}
{
}

void Editor::setRenderWindow(const void *handle)
{
    SDL_HideWindow(os_get_window());

    if (SDL_GL_LoadLibrary(NULL) < 0)
            Error(LOCATION, "Failed to load OpenGL library: %s!", SDL_GetError());

    SDL_Window* window = SDL_CreateWindowFrom(handle);
    if (os_get_window())
        SDL_DestroyWindow(os_get_window());
    os_set_window(window);
}

void Editor::initializeRenderer()
{
    m_renderer.reset(new FredRenderer());
    resetPhysics();
}

void Editor::resize(int width, int height)
{
    gr_screen_resize(width, height);
}

void Editor::update()
{
    m_renderer->game_do_frame(-1, 0, 0, -1);
    std::array<bool, MAX_IFFS> iffs;
    iffs.fill(true);
    m_renderer->render_frame(-1, Render_subsys, false, Marking_box(), currentObject, true, true, &iffs[0], true, true, true, true, false, true, true, true);
}

void Editor::loadMission(const std::string &filepath)
{
    if (parse_main(filepath.c_str()))
        throw mission_load_error("Parse error");

    obj_merge_created_list();

    m_renderer->view_orient = Parse_viewer_orient;
    m_renderer->view_pos = Parse_viewer_pos;
    stars_post_level_init();
    initializeRenderer();
}

void Editor::findFirstObjectUnder(int x, int y)
{
    std::array<bool, MAX_IFFS> iffs;
    iffs.fill(true);

    currentObject = m_renderer->select_object(x, y, false, true, true, &iffs[0], true);

    if (currentObject != -1)
        Objects[currentObject].flags |= OF_MARKED;  // set as marked
}

void Editor::resetPhysics()
{
    int physics_speed = 100;
    int physics_rot = 20;

    physics_info view_physics;
    physics_init(&view_physics);
    view_physics.max_vel.xyz.x *= physics_speed / 3.0f;
    view_physics.max_vel.xyz.y *= physics_speed / 3.0f;
    view_physics.max_vel.xyz.z *= physics_speed / 3.0f;
    view_physics.max_rear_vel *= physics_speed / 3.0f;
    view_physics.max_rotvel.xyz.x *= physics_rot / 30.0f;
    view_physics.max_rotvel.xyz.y *= physics_rot / 30.0f;
    view_physics.max_rotvel.xyz.z *= physics_rot / 30.0f;
    view_physics.flags |= PF_ACCELERATES | PF_SLIDE_ENABLED;

    m_renderer->view_physics = view_physics;
}

} // namespace fred
} // namespace fso
