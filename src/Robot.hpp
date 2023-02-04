///
/// @author Amrit Bhogal on 2023-01-31
/// @brief 
/// @version 1.0.0
///
#pragma once

#include <memory>
#include <optional>

#include <okapi/api.hpp>

using namespace okapi;
using namespace okapi::literals;

using Time_t = uint32_t;


static constexpr int operator ""_secs(unsigned long long int secs)
{ return secs * 1000; }

static constexpr int operator ""_secs(long double secs)
{ return secs * 1000; }

static constexpr int operator ""_mils(unsigned long long int ms)
{ return ms; }

static constexpr int operator ""_mils(long double ms)
{ return ms; }

class Robot final {
    public:
        static class Robot *const INSTANCE;

        Robot();

    [[noreturn]] void operator_control(), autonomous(), roller_autonomous();

    void    rev_launcher(int16_t power = 8000, Time_t duration = 4_secs),
            rev_intake(int16_t power = 12000, Time_t duration = 0.5_secs),
            activate_blooper(), activate_string_launcher();

    void    stop_launcher(), stop_intake(), reset_blooper(), reset_string_launcher();

    void    drive(QLength distance, double velocity = 600),
            turn(QAngle angle),
            shoot(int16_t power = 12000);

    struct pros::vision_object get_biggest_object();

    private:
        std::shared_ptr<class ChassisController>_chassis;
        std::shared_ptr<class ChassisModel>     _drive;
        class Controller                        _controller;
        class Motor                             _intake, _launcher;
        class pros::ADIAnalogOut                _blooper, _string_launcher[2];
        class pros::Vision                      _vision;
};
