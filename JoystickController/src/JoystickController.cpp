#include "JoystickController.h"


joystic::JoystickController::JoystickController() :
    joystick(nullptr)
{
    stop_threads_flag.store(true);

    // Init buttons flags.
    for (int i = 0; i < Joystick_Controller_Max_Num_Buttons; ++i)
        buttons[i].store(false);

    // Init axes value.
    for (int i = 0; i < Joystick_Controller_Max_Num_Axes; ++i)
        axes[i].store(false);

    // Init hut value.
    hut_value.store(-1);
}


joystic::JoystickController::~JoystickController()
{
    // Stop thread.
    stop_threads_flag.store(true);
    if (joystic_thread.joinable())
        joystic_thread.join();

    // Close joystick.
    if (joystick != nullptr)
        SDL_JoystickClose(joystick);
}


int joystic::JoystickController::Init()
{
    // Init SDL2 library.
    SDL_Init(SDL_INIT_JOYSTICK);

    // Get number of joystic.
    return SDL_NumJoysticks();
}


bool joystic::JoystickController::Open(int joystick_ID)
{
    // Stop thread.
    stop_threads_flag.store(true);
    if (joystic_thread.joinable())
        joystic_thread.join();

    // Close joystick before.
    if (joystick != nullptr)
        SDL_JoystickClose(joystick);
    joystick = nullptr;

    // Open joystick.
    joystick = SDL_JoystickOpen(joystick_ID);
    if (joystick == NULL)
    {
        joystick = nullptr;
        return false;
    }

    // Launch event read thread.
    stop_threads_flag.store(false);
    joystic_thread = std::thread(&joystic::JoystickController::Joystick_Events_Thread_Function, this);

    return true;
}


void joystic::JoystickController::Close()
{
    // Stop thread.
    stop_threads_flag.store(true);
    if (joystic_thread.joinable())
        joystic_thread.join();

    // Close joystick.
    if (joystick != nullptr)
        SDL_JoystickClose(joystick);
    joystick = nullptr;
}


std::string joystic::JoystickController::GetName()
{
    // Check if joystic not open.
    if (joystick == nullptr)
        return "";

    // Return name.
    return std::string(SDL_JoystickName(joystick));
}


int joystic::JoystickController::GetNumButtons()
{
    // Check if joystic not open.
    if (joystick == nullptr)
        return -1;

    // Return number of buttons.
    return SDL_JoystickNumButtons(joystick);
}


int joystic::JoystickController::GetNumAxes()
{
    // Check if joystic not open.
    if (joystick == nullptr)
        return -1;

    // Return number of buttons.
    return SDL_JoystickNumAxes(joystick);
}


int joystic::JoystickController::GetNumHats()
{
    // Check if joystic not open.
    if (joystick == nullptr)
        return -1;

    // Return number of buttons.
    return SDL_JoystickNumHats(joystick);
}


bool joystic::JoystickController::GetButtonState(int button_ID, bool reset_button)
{
    // Check buttob ID.
    if (button_ID >= Joystick_Controller_Max_Num_Buttons || button_ID < 0)
        return false;

    bool state = buttons[button_ID].load();
    if (reset_button)
        buttons[button_ID].store(false);

    // Return button state.
    return state;
}


int joystic::JoystickController::GetHutValue()
{
    // Return hut value.
    return hut_value.load();
}


int joystic::JoystickController::GetAxisValue(int axis_ID)
{
    // Check axis ID.
    if (axis_ID >= Joystick_Controller_Max_Num_Axes || axis_ID < 0)
        return -1;

    // Return axis value.
    return axes[axis_ID].load();
}


void joystic::JoystickController::Joystick_Events_Thread_Function()
{
    const uint32_t wait_time = 1; // Wait time 1 ms.

    while (!stop_threads_flag.load())
    {
        SDL_Event evt;
        if (SDL_PollEvent(&evt) != 0) {
            // Chenge value of joystick variables.
            switch (evt.type)
            {
                case SDL_JOYAXISMOTION:
                    axes[evt.jaxis.axis].store((int)evt.jaxis.value);
                    break;

                case SDL_JOYBUTTONDOWN:
                    buttons[evt.jbutton.button].store(true);
                    break;

                case SDL_JOYBUTTONUP:
                    buttons[evt.jbutton.button].store(false);
                    break;

                case SDL_JOYHATMOTION:
                    hut_value.store((int)evt.jhat.value);
                    break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
    }
}



















