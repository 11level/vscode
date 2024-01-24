#include "main.h"
#include "lemlib/api.hpp"

pros::Motor left_front_motor(10, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor left_back_motor(20, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor right_front_motor(1, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor right_back_motor(11, pros::E_MOTOR_GEARSET_06, true);
//motor groups
pros::MotorGroup left_side_motors({left_front_motor, left_back_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_back_motor});

lemlib::Drivetrain_t drivetrain {
	&left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    15, // track width
    4.125, // wheel diameter
    257 // wheel rpm
};

/**

pros::ADIEncoder enc('A', 'B', true); // ports A and B, reversed
pros::Rotation rot(1, false); // port 1, not reversed


// uses "enc" as the encoder. 2.75" wheel diameter, 4.3" offset from tracking center, 36:84 gear ratio
lemlib::TrackingWheel center_tracking_wheel(&enc, 4.125, NULL, 36/84);

*/


// inertial sensor
pros::Imu inertial_sensor(8); // port 8



// odometry struct
lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};




// forward/backward PID
lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

// create the chassis
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);