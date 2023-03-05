// Copyright (C) 2023 Amrit Bhogal
//
// This file is part of OkBot-old.
//
// OkBot-old is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OkBot-old is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with OkBot-old.  If not, see <http://www.gnu.org/licenses/>.

#include "Robot.hpp"

// #define pragma(...) _Pragma(#__VA_ARGS__)
// #define if      if (
// #define then    )
// #define while   while (
// #define loop      )
// #define do   {
// #define end     }
// #define function auto
// #define repeat  do
// #define until(...)   } while (__VA_ARGS__)


[[noreturn]] void Robot::autonomous_skills()
{
    //Used throughout the autonomous
    rev_launcher(-9400, 0);
    rev_intake(9000, 0);

    //When we shoot we are close to the goal, so the blooper must be up
    toggle_blooper();

    //Drive backwards to the roller, because the intake is already running, it rolls
    drive(-2.5_cm, 75);
    drive(15_cm, 100);

    //Rotate to the other roller, we are going to also suck up another disc on the way
    turn(-45_deg);
    drive(40_cm, 150);

    //Turn around to roll roller
    turn(120_deg);
    drive(-30_cm, 100);
    pros::delay(0.1_secs);

    //Turn and move towards the goal
    drive(25_cm, 100);
    turn(-85_deg);
    drive(110_cm, 200);

    //Realign, and shoot
    turn(10_deg);
    drive(30_cm, 100);
    shoot(10250, 0);

    //Turn towards the discs on the side of the goal-guard
    turn(65_deg);
    rev_intake(9000, 0);
    rev_launcher(-10000, 0);

    //Drive towards the discs, and shoot
    drive(125_cm, 100);
    turn(-125_deg);
    stop_intake(); //Can't intake 4 discs
    drive(20_cm, 100);
    shoot(10250, 0);

    //Suck up the discs
    turn(35_deg);
    rev_intake(12000, 0.5_secs);

    drive(85_cm, 100);

    //Turn and shoot
    turn(-90_deg);
    shoot(10250, 0);

    rev_intake(12000, 0);
    //Drive to the other roller, and once in position, call the function again
    turn(10_deg);
    drive(-150_cm, 150);
    drive(25_cm, 100);
    turn(-90_deg);
    drive(-10_cm, 100);
    drive(25_cm, 100);


    while (true) {
        pros::delay(10000);
    }
}
