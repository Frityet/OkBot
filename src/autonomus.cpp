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
    std::puts("Started autonomous");
    drive(-5_cm, 0.2_secs);
    drive(5_cm, 0.2_secs);

    rev_launcher(12000, 0.5_secs);
    rev_intake(12000, 0.25_secs);
    drive(FIELD_SIZE / 3 - 40_cm, 150);
    std::puts("Done driving");
    turn(17_deg);
	shoot(11000);

    turn(-20_deg);
    turn(-45_deg);
    rev_intake(12000, 0.25_secs);
    drive(1_m, 150);

    turn(85_deg);
	shoot(11500);
    stop_launcher();
    rev_intake(12000, 0_secs);
    turn(-75_deg);
    drive(-(FIELD_SIZE / 3) - 10_in - 0.5_m, 600);
    pros::delay(0.5_secs);
    stop_intake();

    while (true) pros::delay(100);
}


extern "C" void autonomous()
{ Robot::INSTANCE->autonomous(); }
