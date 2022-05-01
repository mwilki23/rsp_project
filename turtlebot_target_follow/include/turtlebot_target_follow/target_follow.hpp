#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <fiducial_msgs/FiducialTransform.h>

class target_follow{

    private:

        ros::NodeHandle nh;
        ros::Subscriber sub_artf;
        ros::Publisher pub_wheelcmd;
        ros::Rate rate;

        double x_dist; 
        double z_dist; 

    public:
        target_follow(ros::NodeHandle& nh);
        ~target_follow(){}

        void callback_artf(const fiducial_msgs::FiducialTransform& artf);
};