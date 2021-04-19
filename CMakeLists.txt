cmake_minimum_required(VERSION 3.13)



###############################################################################
## PROJECT
## name and version
###############################################################################
project(UniversalDemoApplications LANGUAGES CXX)



###############################################################################
## CONFIGURATION
## project configuration
###############################################################################
SET(${PARENT}_JOYSTICK_CONTROLLER               ON CACHE BOOL  "" FORCE)
SET(${PARENT}_JOYSTICK_CONTROLLER_TESTS         OFF CACHE BOOL  "" FORCE)



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
###############################################################################
# 3rdparty
add_subdirectory(3rdparty)

if (${PARENT}_JOYSTICK_CONTROLLER)
    add_subdirectory(JoystickController)
endif()

if (${PARENT}_JOYSTICK_CONTROLLER_TESTS)
    add_subdirectory(JoystickControllerTests)
endif()
