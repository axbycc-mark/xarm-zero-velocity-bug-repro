#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

#include <xarm/wrapper/xarm_api.h>
#include <Eigen/Dense>

//============ CONFIGURATION ====================

const std::string xarm_ip = "192.168.1.208";

// ==============================================

// type aliases for eigen
namespace Eigen {
using Vector7f = Matrix<float, 7, 1>;
} // namespace Eigen

int main(int argc, char *argv[])
{
    std::cout << "Xarm connecting to " << xarm_ip << "\n";
    XArmAPI arm(xarm_ip, /*is_radian=*/true);

    std::cout << "Enabling motion\n";
    arm.motion_enable(true);

    std::cout << "Setting modes\n";
    constexpr int JOINT_VELOCITY_MODE = 4;
    std::cout << "Setting joint velocity" << "\n";
    arm.set_mode(JOINT_VELOCITY_MODE);
    std::cout << "Setting state" << "\n";
    arm.set_state(0);

    std::string userInput;
    while(true) {
	Eigen::Vector7f desired_vel = Eigen::Vector7f::Random() * 0.1;	
        std::cout << "Press enter to execute a short the random velocity command " << desired_vel.transpose() << "\n";
        std::getline(std::cin, userInput);

	{
	    const int result = arm.vc_set_joint_velocity(
		desired_vel.data(), /*is_sync=*/false, /*duration=*/0.1);
	    std::cout << "Result was " << result << "\n";

	}
	
	desired_vel.setZero();
	std::cout << "Press enter to execute a zero velocity command.\n";
        std::getline(std::cin, userInput);
	{
	    const int result = arm.vc_set_joint_velocity(
		desired_vel.data(), /*is_sync=*/false, /*duration=*/0.1);
	}
    };

    return 0;
}
