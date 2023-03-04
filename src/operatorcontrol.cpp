///
/// @author Amrit Bhogal on 2022-12-09
/// @brief
/// @version 1.0.0
/// \brief

#include "Robot.hpp"

#include "config.hpp"

[[noreturn]] void Robot::operator_control()
{
    while (true) {
        _drive->tank(_controller.getAnalog(ControllerAnalog::leftY), _controller.getAnalog(ControllerAnalog::rightY));

        _intake.moveVoltage(_controller[CONTROLS.intake.in].isPressed() ? -12000
                                                                            : _controller[CONTROLS.intake.out].isPressed()
                                                                        ? 12000
                                                                            : 0);

        for (auto launcher_cfg : CONTROLS.launcher) {
            static int16_t voltage = 0;
            if (((int)launcher_cfg.button) == 0) continue;

            if (_controller[launcher_cfg.button].changed()) voltage = launcher_cfg.power;

            _controller.setText(2, 0, "Voltage: " + std::to_string(voltage));

            _launcher.moveVoltage(voltage);
        }

        if (_controller[CONTROLS.blooper].isPressed())
            toggle_blooper();

        if (_controller[CONTROLS.string_launcher].isPressed())
            activate_string_launcher();

        pros::delay(10);
    }
}

extern "C" [[noreturn]] void opcontrol()
{ Robot::INSTANCE->operator_control(); }
