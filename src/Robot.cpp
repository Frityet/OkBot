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
    _blooper(PORTS.blooper),
    _string_launcher {
        pros::ADIDigitalOut(PORTS.string_launcher[0]),
        pros::ADIDigitalOut(PORTS.string_launcher[1])
    }
{
    _intake.setBrakeMode(AbstractMotor::brakeMode::coast);
    _launcher.setBrakeMode(AbstractMotor::brakeMode::coast);

    _blooper.set_value(false);
    _string_launcher[0].set_value(false);
    _string_launcher[1].set_value(false);
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

void Robot::activate_blooper()
{ std::puts("B"); _blooper.set_value(true); }

void Robot::reset_blooper()
{  _blooper.set_value(false); }

void Robot::activate_string_launcher()
{

    _string_launcher[0].set_value(true);
    _string_launcher[1].set_value(true);
}

void Robot::reset_string_launcher()
{
    _string_launcher[0].set_value(true);
    _string_launcher[1].set_value(true);
}

void Robot::stop_launcher()
{ _launcher.moveVoltage(0); }

void Robot::stop_intake()
{ _intake.moveVoltage(0); pros::delay(1_secs); }


void Robot::drive(QLength distance, double velocity)
{
    _chassis->setMaxVelocity(velocity);
    _chassis->moveDistance(distance);
}

void Robot::turn(QAngle angle)
{ _chassis->turnAngle(angle); }

void Robot::shoot(int16_t power)
{
    stop_intake();
    pros::delay(0.25_secs);
    rev_intake(-power, 0.25_secs);
    stop_intake();
    pros::delay(0.25_secs);
    rev_intake(-power, 0.25_secs);
    stop_intake();
    pros::delay(0.25_secs);
    rev_intake(-power, 0.25_secs);
    stop_intake();
}
