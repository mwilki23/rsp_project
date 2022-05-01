#include <turtlebot_target_follow/target_follow.hpp>

target_follow::target_follow(ros::NodeHandle& nh): nh(nh){
    //sub_artf = nh.subscribe("/fiducial_transforms",10,&target_follow::callback_artf, this);
    pub_wheelcmd = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
}

//void callback_artf(const fiducial_msgs::FiducialTransforms& artf){}

void target_follow::publish_wheelcmd(){
    geometry_msgs::Twist wheelcmd;
    wheelcmd.linear.x = 0.01;
    wheelcmd.angular.z = 0.01;
    pub_wheelcmd.publish(wheelcmd);
}

