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
