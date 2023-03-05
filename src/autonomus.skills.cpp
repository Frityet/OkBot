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

void Robot::autonomous_skills()
{
    rev_launcher(-9500, 0);
    rev_intake(12000, 0);
    toggle_blooper();
    drive(-2.5_cm, 75);
    drive(15_cm, 100);
    turn(-45_deg);
    drive(40_cm, 150);
    turn(120_deg);
    drive(-30_cm, 50);
    pros::delay(0.1_secs);
    drive(25_cm, 100);
    turn(-85_deg);

    drive(125_cm, 150);
    turn(20_deg);
    drive(40_cm, 100);

    shoot(10000);

    turn(75_deg);
    rev_launcher(-10000, 0);
    drive(75_cm);
    turn(-100_deg);
    shoot(10000);

    while (true) pros::delay(1000000000_secs) ;
}
