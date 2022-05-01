#include <turtlebot_target_follow/target_follow.hpp>

target_follow::target_follow(ros::NodeHandle& nh): nh(nh),rate(10){
    sub_artf = nh.subscribe("/fiducial_transforms",10,&target_follow::callback_artf, this);
    pub_wheelcmd = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
}

void target_follow::callback_artf(const fiducial_msgs::FiducialTransform& artf){
    //std::cout<<"test"<<std::endl;
    x_dist = artf.transform.translation.x; //forward-backward
    z_dist = artf.transform.translation.z; //left-right
    //y distance is up in the air so not relevant
    //double z_rot = artf.transform.translation.x;
    geometry_msgs::Twist wheelcmd;
    if (x_dist > 1.0){
        wheelcmd.linear.x = 0.1;
    }
    else{
        wheelcmd.linear.x = 0.0;
    }

    //wheelcmd.angular.z = 0.01;
    pub_wheelcmd.publish(wheelcmd);
}

