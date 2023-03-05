///
/// @author Amrit Bhogal on 2022-11-17
/// @brief
/// @version 1.0.0
///

#include "Robot.hpp"

#include "config.hpp"
#include "pros/rtos.hpp"


void Robot::autonomous()
{
    std::puts("Started autonomous");


    rev_launcher(-12000, 0);
    rev_intake(12000, 0);
    drive(FIELD_SIZE / 3 - 40_cm, 300);
    std::puts("Done driving");
    turn(17_deg);
	shoot(11000);

    turn(-65_deg);
    rev_intake(12000, 0);
    drive(1_m, 600);

    turn(80_deg);
	shoot(11500);
    stop_launcher();
    rev_intake(12000, 0_secs);
    turn(-75_deg);
    drive(-(FIELD_SIZE / 4) - 10_in, 600);
    pros::delay(0.5_secs);
    stop_intake();

    //Now we need to move back a bit by only moving the right side of the robot
    _drive->right(-100);
    pros::delay(0.5_secs);
    _drive->right(0);
    rev_intake(12000, 0.125_secs);
    pros::delay(0.5_secs);
    stop_intake();


    while (true) pros::delay(1000000000_secs);
}

void Robot::autonomous_v2()
{
    rev_launcher(-12000, 0);
    //First, we need to hit the rollder to the right by only moving the left side of the robot
    _drive->right(-80);
    pros::delay(0.33_secs);
    _drive->right(-30);
    pros::delay(0.5_secs);
    _drive->right(-10);
    rev_intake(12000, 0);
    pros::delay(0.5_secs);
    _drive->right(0);
    stop_intake();    //rev_intake(12000, 1_secs);

    turn(10_deg), drive(26_cm, 300);
    std::puts("Done driving");

    turn(5_deg);
    shoot(11050);

    turn(-65_deg);
    rev_intake(12000, 0);
    drive(1_m, 600);

    turn(80_deg);
	shoot(11500);
    stop_launcher();
    rev_intake(12000, 0_secs);
    turn(-75_deg);
    drive(-(FIELD_SIZE / 4) - 10_in, 600);
    pros::delay(0.5_secs);
    stop_intake();

    while (true) pros::delay(1000000000_secs) ;
}

extern "C" void autonomous()
{ Robot::INSTANCE->autonomous_v2(); }
