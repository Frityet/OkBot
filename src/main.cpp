extern "C" {
    void    autonomous(void),
            initialize(void),
            disabled(void),
            competition_initialize(void),
            opcontrol(void);
}

#include "Robot.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void competition_initialize() {}

void disabled(){}
