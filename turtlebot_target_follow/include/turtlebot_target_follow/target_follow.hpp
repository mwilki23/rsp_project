#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
//include <fiducial_msgs/FiducialTransforms.h>

class target_follow{

    private:

        ros::NodeHandle nh;
        ros::Subscriber sub_artf;
        ros::Publisher pub_wheelcmd;

    public:
        target_follow(ros::NodeHandle& nh);
        ~target_follow(){}

        //void callback_artf(const fiducial_msgs::FiducialTransforms& artf);
        void publish_wheelcmd();
};