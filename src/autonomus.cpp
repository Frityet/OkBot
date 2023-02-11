///
/// @author Amrit Bhogal on 2022-11-17
/// @brief
/// @version 1.0.0
///

#include "Robot.hpp"

#include "config.hpp"

static constexpr const auto FIELD_SIZE = 12_ft;

void Robot::autonomous()
{
    rev_launcher(12000, 2_secs);
    rev_intake(12000, 0.5_secs);

    _drive->left(-12000);
    pros::delay(1_secs);
    _drive->left(0);
    pros::delay(1_secs);

    drive(20_cm, 150);

    turn(-10_deg);

    shoot(11000);

    while(true) pros::delay(1000_secs);
}


extern "C" void autonomous()
{ Robot::INSTANCE->autonomous(); }
