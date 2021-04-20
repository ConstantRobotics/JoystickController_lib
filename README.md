***
![JOYSTIC](_static/jcontroller_logo_with_borders.png)
***
## 
## OVERVIEW
C++ library **JoystickController_lib** version **1.0** is designed to help developers work with joysticks. The library is cross-platform and uses the **SDL v2** library. The library is cross-platform and uses the **SDL v2** library. The library works only with HID compatible joysticks.
the library provides:
* Checking the availability of joysticks in the system.
* Initializing the selected joystick.
* Geting information about the joystick (name, number of axes and buttons, etc.).
* Getting the state of buttons, axis positions and more.

The library contains a description of just one class **JoystickController** with simple interface for easy use:
```c++
namespace joystick
{
    /**
     * @brief Class to work with joystick.
     */
    class JoystickController
    {
    public:

        JoystickController();

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
    };
}
```
***

## 
## LIBRARY INITIALIZATION
To initialize the library we use the method **Init()**. The method returns the number of available joysticks in the system. The method initializes the **SDL** library.
```c++
/**
 * @brief Method to init SDK library.
 * @return number of joystics.
 */
int Init();
```
***
## OPENING THE JOYSTICK
To open the joystick you need to call the **Open()** method. This method opens joystick according to joystick_ID (joystick number). The number of the joystick is its serial number. The number of joysticks in the system can be obtained using the method **Init()**.
```c++
/**
 * @brief Method to open joystick.
 * @param joystick_ID ID of joystic (from 0 to number-1).
 * @return true if joystic open.
 * @return false if joystick not open.
 */
 bool Open(int joystick_ID);
```
The joystick will close automatically when the program ends. In order to close the joystick independently you need to use the method **Close()**. When the **Open()** method is called again, the joystick will be closed and reopened (the same joystick or another joystick according to its joystick_ID).
***
## GETTING JOYSTICK INFORMATION
If the joystick is open (after calling the **Open()** method), you can get its name using the method **GetName()**, the number of available buttons on the joystick using the method **GetNumButtons()**, the number of available axes using the method **GetNumAxes()** and the number of available switches using the method **GetNumHats()**.
***
## GETTING THE STATE OF THE BUTTONS
To get the state of the button the method **GetButtonState()**. The button can be found either in the "pressed" state or in the "free" state. The method takes the ID of the button (from 0 to number_of_buttons - 1). If the button is pressed, the method returns **TRUE**. If the button is not pressed, the method returns **FALSE**. The method also takes the **reset_button** parameter. If **reset_button == true** the state of button inside the library will be switched to "free".
```c++
/**
 * @brief Get button state (pushed ot not pushed).
 * @param button_ID ID of button.
 * @param reset_button Flag to reset button state if you want.
 * @return true if the button pushed.
 * @return false if the button released.
 */
bool GetButtonState(int button_ID, bool reset_button = false);
```
***
## GETTING AXIS VALUE
To get the value of the axis the method **GetAxisValue()**. The method takes ID of axis as parameter and return current value of axis.
```c++
/**
 * @brief Get the Axis Value object
 * @param axis_ID ID of axis.
 * @return value of axis.
 */
int GetAxisValue(int axis_ID);
```
***
## GETTING SWITCH (HAT) VALUE
To get the value of the switch the method **GetHatValue()**. The method returns current hat value.
```c++
/**
 * @brief Get the Hut Value.
 * @return hut value ot -1 if joystick not open.
 */
int GetHatValue();
```
***
## SIMPLE EXAMPLE
The example application shows how to work with the library. The application receives the current values of the axes and buttons of the joystick and outputs them to the console.
```c++
#include <iostream>
#include <chrono>
#include <ctime>
#include <JoystickController.h>


// Entry point.
int main(void)
{
    // Create joystic controller object.
    joystick::JoystickController joystick_controller;

    // Init and get number of joysticks.
    int number_of_joysticks = joystick_controller.Init();

    // Check number of joysticks.
    if (number_of_joysticks <= 0)
    {
        std::cout << "No available joysticks. Exit..." << std::endl;
        return -1;
    }
    std::cout << "Number of joysticks: " << number_of_joysticks << std::endl << std::endl;

    // Dialog to enter joystick ID to open.
    int joystick_ID = 0;
    std::cout << "Enter joystick ID (from 0 to " << (number_of_joysticks - 1) << "): ";
    std::cin >> joystick_ID;

    // Open joystick.
    if (!joystick_controller.Open(joystick_ID))
    {
        std::cout << "Joystic not open. Exit..." << std::endl;
        return -1;
    }

    // Get joystick info.
    std::string joystick_name = joystick_controller.GetName();
    int num_buttons = joystick_controller.GetNumButtons();
    int num_axes = joystick_controller.GetNumAxes();
    int num_hats = joystick_controller.GetNumHats();

    // Show joystick info.
    std::cout << "Joystick open. Name: " <<
                 joystick_name << " Buttons: " <<
                 num_buttons << " Axes: " <<
                 num_axes << " Huts: " <<
                 num_hats << std::endl << std::endl;

    // Main loop.
    while (true)
    {
        // Prepare joystick info.
        std::string joystick_info = "Axes: ";
        for (int i = 0; i < num_axes; ++i)
            joystick_info = joystick_info + std::to_string(joystick_controller.GetAxisValue(i)) + ":";
        joystick_info = joystick_info + " hat value: " + std::to_string(joystick_controller.GetHatValue());
        joystick_info = joystick_info + " buttons: ";
        for (int i = 0; i < num_buttons; ++i)
            joystick_info = joystick_info + (joystick_controller.GetButtonState(i) ? "X " : "_ ");

        // Show joystic info.
        std::cout << joystick_info << std::endl;

        // Wait.
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 1;
}
```