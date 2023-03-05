///
/// @author Amrit Bhogal on 2023-03-01
/// @brief
/// @version 1.0.0
///


#include "lemlib/chassis/chassis.hpp"
#include <pros/motors.hpp>
#include <lemlib/api.hpp>

//inches

static constexpr auto operator ""_in(long double x)
{ return x; }

static constexpr auto operator ""_in(unsigned long long x)
{ return x; }



extern "C" void autonomous()
{
    puts("Autonomus");
    auto chassis = lemlib::Chassis (
        lemlib::Drivetrain_t {
            leftMotors: new pros::MotorGroup({ 4, 2, 12 }), rightMotors: new pros::MotorGroup({ -3, -5, -11 }),
            trackWidth: 14.0_in, wheelDiameter: 2.75_in,
            rpm: 360
        },
        lemlib::ChassisController_t {
            kP: 10, kD: 30,
            smallError: 1, smallErrorTimeout: 100,
            largeError: 3, largeErrorTimeout: 500,
            slew: 5
        },
        lemlib::ChassisController_t {
            kP: 2, kD: 10,
            smallError: 1, smallErrorTimeout: 100,
            largeError: 3, largeErrorTimeout: 500,
            slew: 5
        },
        lemlib::OdomSensors_t {
            imu: new pros::Imu(13),
        }
    );
    chassis.calibrate();
    chassis.setPose({ 0, 0, 0 });

    chassis.setPose(50.2, 100.333, 87);
    pros::delay(1000);
}
