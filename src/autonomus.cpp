///
/// @author Amrit Bhogal on 2022-11-17
/// @brief
/// @version 1.0.0
///

#include "Robot.hpp"

#include "config.hpp"

static constexpr const auto FIELD_SIZE = 12_ft;

class Boolean {
private:
    const bool *const _value;

public:
    Boolean(bool value) : _value(new bool(value)) {}
    ~Boolean() { delete _value; }

    operator bool() const { return *_value; }
    operator const bool *() const { return _value; }

    bool operator!() const { return !*_value; }

    bool operator==(const Boolean &other) const { return *_value == *other._value; }
    bool operator!=(const Boolean &other) const { return *_value != *other._value; }

    bool operator==(const bool &other) const { return *_value == other; }
    bool operator!=(const bool &other) const { return *_value != other; }

    bool operator==(const bool *other) const { return *_value == *other; }
    bool operator!=(const bool *other) const { return *_value != *other; }

    bool operator==(const Boolean *other) const { return *_value == *other->_value; }
    bool operator!=(const Boolean *other) const { return *_value != *other->_value; }
};

static void vision_check(class Robot *robot, int red_id, int blue_id)
{
    std::printf("Vision check\n");
    struct pros::vision_object obj = robot->get_biggest_object();
    while (obj.signature != blue_id) {
        std::printf("Looking for blue\n");
        robot->turn(50_deg);
        obj = robot->get_biggest_object();
    }


    std::printf("Found object: %s\n", obj.signature == red_id ? "red" : "blue");
    std::printf("Middle: %d\n", obj.x_middle_coord);

    while (obj.x_middle_coord > SETTINGS.vision_epsilon.maximum or obj.x_middle_coord < SETTINGS.vision_epsilon.minimum) {
        std::printf("Turning\n");
        robot->turn(obj.x_middle_coord < SETTINGS.vision_epsilon.maximum ? 7.5_deg : -7.5_deg);
        obj = robot->get_biggest_object();
        std::printf("mid: %d\n", obj.x_middle_coord);
    }
    printf("Shooting with %d, offset: %d\n", robot->get_biggest_object().signature, robot->get_biggest_object().x_middle_coord);
    robot->shoot(11500);

}

void Robot::autonomous()
{
    std::printf("Started autonomous\n");
    static const constexpr int RED_ID = 0, BLUE_ID = 1;
    struct pros::vision_signature red_vis = pros::Vision::signature_from_utility(RED_ID,
                                                                                 4901, 8395,6648,
                                                                                 -1857, -1143,-1500,
                                                                                 1.900, 0),
                                  blue_vis = pros::Vision::signature_from_utility(BLUE_ID,
                                                                                  -2931,1, -1464,
                                                                                  -1,7817, 3908,
                                                                                  0.700, 0);

    _vision.set_zero_point(pros::E_VISION_ZERO_CENTER);
    _vision.set_signature(RED_ID, &red_vis);
    _vision.set_signature(BLUE_ID, &blue_vis);
    rev_launcher(12000, 1_secs);
    rev_intake(12000, 0.25_secs);
    drive(FIELD_SIZE / 3 - 40_cm, 300);
    turn(20_deg);
    vision_check(this, RED_ID, BLUE_ID);

    turn(-(45_deg + 10_deg));

    rev_intake(12000, 0_secs);
    drive(1_m, 300);
    stop_intake();

    turn(75_deg);

    vision_check(this, RED_ID, BLUE_ID);
    stop_launcher();

    turn(-(45_deg + 20_deg + 10_deg));
    drive(-(FIELD_SIZE / 3) - 10_in, 600);

    rev_intake(12000, 0.25_secs);

    while (true) pros::delay(100);
}

extern "C" void autonomous()
{ Robot::INSTANCE->autonomous(); }
