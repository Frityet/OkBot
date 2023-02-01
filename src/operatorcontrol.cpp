///
/// @author Amrit Bhogal on 2022-12-09
/// @brief 
/// @version 1.0.0
/// \brief

#include "Robot.hpp"

#include "Robot.hpp"

#include "config.hpp"

[[noreturn]] void Robot::operator_control()
{
    while (true) {
        _drive->arcade(_controller.getAnalog(ControllerAnalog::leftY), _controller.getAnalog(ControllerAnalog::rightX));

        _intake.moveVoltage(_controller[CONTROLS.intake.in].isPressed() ? -12000
                                                                        : _controller[CONTROLS.intake.out].isPressed() ? 12000 : 0);

        for (auto launcher_cfg : CONTROLS.launcher) {
            if (((int)launcher_cfg.button) == 0) continue;
            _launcher.moveVoltage(_controller[launcher_cfg.button].isPressed() ? launcher_cfg.power : 0);
        }

        _pneumatics.set_value(_controller[CONTROLS.pneumatics].isPressed());

        pros::delay(10);
    }
}

extern "C" [[noreturn]] void opcontrol()
{ Robot::INSTANCE->operator_control(); }
