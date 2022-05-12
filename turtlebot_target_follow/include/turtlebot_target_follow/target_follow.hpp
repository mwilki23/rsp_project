#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <fiducial_msgs/FiducialTransformArray.h>
#include <fiducial_msgs/FiducialTransform.h>

class target_follow{

    private:

        ros::NodeHandle nh;
        ros::Subscriber sub_artf;
        ros::Publisher pub_wheelcmd;
        ros::Publisher sim_pub_wheelcmd;
        ros::Rate rate;

	geometry_msgs::Twist wheelcmd;

	//fiducial_msgs::FiducialTransformArray empty_tf;

        double x_dist; 
        double z_dist; 
	double x_quat; 
        double y_quat; 
        double z_quat; 
        double w_quat; 
	
	double x_rot;
	double y_rot;
	double z_rot;

	double motion_dir;
        double forward_vel;
        double reverse_vel;
        double spin_vel;	

    public:
        target_follow(ros::NodeHandle& nh);
        ~target_follow(){}

        void callback_artf(const fiducial_msgs::FiducialTransformArray& artf);
};
