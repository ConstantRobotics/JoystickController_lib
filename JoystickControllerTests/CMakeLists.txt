cmake_minimum_required(VERSION 3.13)



###############################################################################
## PROJECT
## name and version
###############################################################################
project(JoystickControllerTests LANGUAGES CXX)



###############################################################################
## CONFIGURATION
## project configuration
###############################################################################
#Tests
SET(${PARENT}_JOYSTICK_TEST_APPLICATION    ON CACHE BOOL "" FORCE)



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
###############################################################################
if (${PARENT}_JOYSTICK_TEST_APPLICATION)
    add_subdirectory(JoystickTestApplication)
endif()
