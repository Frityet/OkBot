///
/// @author Amrit Bhogal on 2023-01-31
/// @brief
/// @version 1.0.0
///
#pragma once

#include <memory>
#include <optional>


using Time_t = uint32_t;

#define private public
#   include <pros/adi.hpp>
#undef private

#include <okapi/api.hpp>

using namespace okapi::literals;

using okapi::QLength;
using okapi::QSpeed;
using okapi::QAngle;


static constexpr int operator ""_secs(unsigned long long int secs)
{ return secs * 1000; }

static constexpr int operator ""_secs(long double secs)
{ return secs * 1000; }

static constexpr int operator ""_mils(unsigned long long int ms)
{ return ms; }

static constexpr int operator ""_mils(long double ms)
{ return ms; }

static constexpr const auto FIELD_SIZE = 12_ft;

class Robot final {
    public:
        static class Robot *const INSTANCE;

        Robot();

    [[noreturn]] void operator_control(), autonomous(), roller_autonomous(), autonomous_v2(), autonomous_skills();

    void    rev_launcher(int16_t power = 8000, Time_t duration = 4_secs),
            rev_intake(int16_t power = 12000, Time_t duration = 0.5_secs),
            toggle_blooper(), activate_string_launcher();

    void    stop_launcher(), stop_intake(), reset_blooper(), reset_string_launcher();

    void    drive(QLength distance, double velocity = 600),
            turn(QAngle angle),
            shoot(int16_t power = 12000, Time_t duration = 0.25_secs);

    private:
        std::shared_ptr<class okapi::OdomChassisController> _chassis;
        std::shared_ptr<class okapi::ChassisModel>          _drive;
        class okapi::IMU                                    _imu;
        class okapi::Controller                             _controller;
        class okapi::Motor                                  _intake, _launcher;
        class pros::ADIDigitalOut                           _blooper, _string_launcher[2];
};
