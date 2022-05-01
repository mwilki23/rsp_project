#include <turtlebot_target_follow/target_follow.hpp>

int main(int argc, char** argv){
    ros::init(argc, argv, "target_follow");
    ros::NodeHandle nh;

    target_follow target_follower(nh);
    ros::spin();
    return 0;
}