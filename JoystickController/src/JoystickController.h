#include <cstring>
#include <string>
#include <atomic>
#include <thread>
#include <SDL.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#undef main // Necessary for SDL libs.
#endif


// Global constants.
constexpr int Joystick_Controller_Max_Num_Buttons = 256;    // Maximum number of buttons.
constexpr int Joystick_Controller_Max_Num_Axes = 256;       // Maximum number of axes.


namespace joystick
{
    /**
     * @brief Class to work with joystick.
     */
    class JoystickController
    {
    public:

        /**
         * @brief Construct a new Joystick Controller object.
         */
        JoystickController();

        /**
         * @brief Destroy the Joystick Controller object.
         */
        ~JoystickController();

        /**
         * @brief Method to init SDK library.
         * @return number of joystics.
         */
        int Init();

        /**
         * @brief Method to open joystick.
         * @param joystick_ID ID of joystic (from 0 to number-1).
         * @return true if joystic open.
         * @return false if joystick not open.
         */
        bool Open(int joystick_ID);

        /**
         * @brief Method to close joystick.
         */
        void Close();

        /**
         * @brief Get the Name of joystick.
         * @return name of joystick or empty string if joystick not open.
         */
        std::string GetName();

        /**
         * @brief Get number of buttons in joystick.
         * @return number of buttons or -1 string if joystick not open.
         */
        int GetNumButtons();

        /**
         * @brief Get number of axes in joystick.
         * @return number of axes or -1 string if joystick not open.
         */
        int GetNumAxes();

        /**
         * @brief Get number of huts in joystick.
         * @return number of huts or -1 string if joystick not open.
         */
        int GetNumHats();

        /**
         * @brief Get button state (pushed ot not pushed).
         * @param button_ID ID of button.
         * @param reset_button Flag to reset button state if you want.
         * @return true if the button pushed.
         * @return false if the button released.
         */
        bool GetButtonState(int button_ID, bool reset_button = false);

        /**
         * @brief Get the Hut Value.
         * @return hut value ot -1 if joystick not open.
         */
        int GetHatValue();

        /**
         * @brief Get the Axis Value object
         * @param axis_ID ID of axis.
         * @return value of axis.
         */
        int GetAxisValue(int axis_ID);

    private:

        SDL_Joystick* joystick;
        std::atomic<bool> buttons[Joystick_Controller_Max_Num_Buttons];
        std::atomic<int> axes[Joystick_Controller_Max_Num_Axes];
        std::atomic<int> hat_value;
        std::thread joystic_thread;
        std::atomic<bool> stop_threads_flag;

        void Joystick_Events_Thread_Function();
    };
}
