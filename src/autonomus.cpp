///
/// @author Amrit Bhogal on 2022-11-17
/// @brief
/// @version 1.0.0
///

#include "Robot.hpp"

#include "config.hpp"

#include <variant>

static constexpr const auto FIELD_SIZE = 12_ft;

template<typename T1, typename T2>
struct Either {
public:
    T1 t_1;
    T2 t_2;

    Either(const T1 &t1, const T2 &t2):
            t_1(t1),
            t_2(t2)
    {

    }

    operator T1()
    { return t_1; }

    operator T2()
    { return t_2; }
};

template<typename T>
class ReadOnlyProperty {
private:
    T _value;

public:
    ReadOnlyProperty(const T &v):
                    _value(v)
    { }

    operator const T &() const
    { return _value; }

    auto operator &() const -> Either<const T *, const ReadOnlyProperty<T> *>
    { return Either(&_value, this); }

    auto operator *() const -> Either<T, ReadOnlyProperty<T>>
    { return Either(_value, *this); }
};

template<typename TKey, typename TValue>
struct KeyValuePair {
public:
    ReadOnlyProperty<TKey> key;
    ReadOnlyProperty<TValue> value;

    KeyValuePair(const TKey &k, const TValue &v):
                    key(k),
                    value(v) {}



};

void Robot::autonomous()
{
    rev_launcher(12000, 2_secs);
    rev_intake(12000, 0.125_secs);

    _drive->left(-12000);
    pros::delay(0.125_secs);
    _drive->left(0);
    //pros::delay(1_secs);

    drive(20_cm, 150);

    turn(-8_deg);

    shoot(11000);

    while(true) pros::delay(1000_secs);
}


extern "C" void autonomous()
{ Robot::INSTANCE->autonomous(); }
