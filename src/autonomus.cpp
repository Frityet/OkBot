///
/// @author Amrit Bhogal on 2022-11-17
/// @brief
/// @version 1.0.0
///

#include "Robot.hpp"

#include "config.hpp"

static constexpr const auto FIELD_SIZE = 12_ft;

void Robot::autonomous()
{
    static const constexpr int RED_ID = 0, BLUE_ID = 1;
    struct pros::vision_signature red_vis = pros::Vision::signature_from_utility(RED_ID, 4901, 8395, 6648, -1857, -1143,
                                                                                 -1500, 1.900, 0),
        blue_vis = pros::Vision::signature_from_utility(BLUE_ID, -2931, 1, -1464, -1, 7817, 3908, 0.700, 0);

    _vision.set_signature(RED_ID, &red_vis);
    _vision.set_signature(BLUE_ID, &blue_vis);

    rev_launcher();
    drive(FIELD_SIZE / 2);
    turn(-120_deg);
}



extern "C" void autonomous()
{ Robot::INSTANCE->autonomous(); }
