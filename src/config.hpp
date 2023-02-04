///
/// @author Amrit Bhogal on 2022-12-09
/// @brief
/// @version 1.0.0
///
#pragma once

#include "okapi/api.hpp"

using namespace okapi;
using namespace okapi::literals;

/*<=>*/

static const constexpr struct {
    int8_t  left_motors[3], right_motors[3],
            intake, launcher, vision, blooper, string_launcher[2];
} PORTS = {
    .left_motors = {-4, -2, -12 },
    .right_motors = {3, 5, 11  },
    .intake = -10,
    .launcher = -9,
    .vision = 14,
    .blooper = 'A',
    .string_launcher = { 'B', 'C' }
};

static const constexpr struct {
    struct {
        ControllerDigital in, out;
    } intake;
    struct {
        ControllerDigital button;
        int16_t power;
    } launcher[3];
    ControllerDigital blooper, string_launcher;
} CONTROLS = {
    .intake = {
        .in = ControllerDigital::R2,
        .out = ControllerDigital::R1
    },
    .launcher = {
        {
            .button = ControllerDigital::L1,
            .power = 12000
        },
    },
    .blooper = ControllerDigital::A,
    .string_launcher = ControllerDigital::B
};

template<typename T>
struct Range {
    T minimum = 0, maximum = 0;
};

template<typename T>
using Range_t = Range<T>;

static const constexpr struct {
    Range_t<int32_t> vision_epsilon;
} SETTINGS = {
    .vision_epsilon = { -75, 75 }
};
