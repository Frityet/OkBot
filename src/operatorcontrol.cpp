///
/// @author Amrit Bhogal on 2022-12-09
/// @brief 
/// @version 1.0.0
/// \brief

#include "Robot.hpp"

#include "Robot.hpp"

#include "config.hpp"

static std::pair<bool, bool *> toggle(bool *b)
{ return std::make_pair(*b = !*b, b); }

[[noreturn]] void Robot::operator_control()
{
    while (true) {
        _drive->tank(_controller.getAnalog(ControllerAnalog::leftY), _controller.getAnalog(ControllerAnalog::rightY));

        _intake.moveVoltage(_controller[CONTROLS.intake.in].isPressed() ? -12000
                                                                               : _controller[CONTROLS.intake.out].isPressed()
                                                                                    ? 12000
                                                                                    : 0);

        for (auto launcher_cfg : CONTROLS.launcher) {
            if (((int)launcher_cfg.button) == 0) continue;
            if (_controller[launcher_cfg.button].changed()) _flywheel_on = !_flywheel_on;
            _launcher.moveVoltage(_flywheel_on ? launcher_cfg.power : 0);
        }

        if (_controller[CONTROLS.blooper].isPressed())
            activate_blooper();

        if (_controller[CONTROLS.string_launcher].isPressed())
            activate_string_launcher();

        pros::delay(10);
    }
}

extern "C" [[noreturn]] void opcontrol()
{ Robot::INSTANCE->operator_control(); }
