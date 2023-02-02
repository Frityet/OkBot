///
/// @author Amrit Bhogal on 2023-01-31
/// @brief 
/// @version 1.0.0
///
#include "Robot.hpp"

#include "config.hpp"

class Robot *const Robot::INSTANCE = new class Robot();

Robot::Robot():
    _chassis(ChassisControllerBuilder()
                .withMotors (
                    { PORTS.left_motors[0], PORTS.left_motors[1], PORTS.left_motors[2] },
                    { PORTS.right_motors[0], PORTS.right_motors[1], PORTS.right_motors[2] }
                )
                .withDimensions(AbstractMotor::gearset::blue, {
                    { 2.75_in, 14_in },
                    imev5BlueTPR
                })
                .build()),
    _drive(_chassis->getModel()),
    _controller(),
    _intake(PORTS.intake),
    _launcher(PORTS.launcher),
    _pneumatics(PORTS.pneumatics),
    _vision(PORTS.vision)
{
    _intake.setBrakeMode(AbstractMotor::brakeMode::coast);
    _launcher.setBrakeMode(AbstractMotor::brakeMode::coast);
}

void Robot::rev_launcher(int16_t power, Time_t duration)
{
    _launcher.moveVoltage(power);
    pros::delay(duration);
}

void Robot::rev_intake(int16_t power, Time_t duration)
{
    _intake.moveVoltage(power);
    pros::delay(duration);
}

void Robot::set_pneumatics(int16_t val)
{ _pneumatics.set_value(val); }

void Robot::stop_launcher()
{ _launcher.moveVoltage(0); }

void Robot::stop_intake()
{ _intake.moveVoltage(0); }

void Robot::reset_pneumatics()
{ _pneumatics.set_value(0); }

void Robot::drive(QLength distance)
{ _chassis->moveDistance(distance); }

void Robot::turn(QAngle angle)
{ _chassis->turnAngle(angle); }

void Robot::shoot(int16_t power)
{
    rev_launcher(power);
    rev_intake(power);
    pros::delay(1_secs);
    stop_launcher();
    stop_intake();
}

struct pros::vision_object Robot::get_biggest_object()
{
    struct pros::vision_object biggest = {0};
    for (int i = 0; i < _vision.get_object_count(); i++) {
        struct pros::vision_object obj = _vision.get_by_size(i);
        if (obj.width * obj.height > biggest.width * biggest.height)
            biggest = obj;
    }
    return biggest;
}
