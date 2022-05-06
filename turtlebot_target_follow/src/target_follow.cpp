#include <turtlebot_target_follow/target_follow.hpp>

target_follow::target_follow(ros::NodeHandle& nh): nh(nh),rate(10){
    sub_artf = nh.subscribe("/fiducial_transforms",10,&target_follow::callback_artf, this);
    pub_wheelcmd = nh.advertise<geometry_msgs::Twist>("cmd_vel",10);
}

void target_follow::callback_artf(const fiducial_msgs::FiducialTransformArray& artf){
   // std::cout<<"test"<<std::endl;
    if(artf.transforms.empty()){

	std::cout<<"No Fiducials to be found!"<<std::endl;
    
    }else{

        // Note: +z is coming out of raspicam's lens
	//
	//           [o]--------> +x
        //           /|
	//          / |
	//         /  |
        //        /   |
	//       /    |
	// +z-> L     V <- +y


	x_dist = artf.transforms[0].transform.translation.x; //forward-backward
	z_dist = artf.transforms[0].transform.translation.z; //left-right
	//y distance is up in the air so not relevant

	
  	x_quat = artf.transforms[0].transform.rotation.x; 
        y_quat = artf.transforms[0].transform.rotation.y;
        z_quat = artf.transforms[0].transform.rotation.z;
        w_quat = artf.transforms[0].transform.rotation.w;

	bot_to_fid_yaw = asin(2*w_quat*y_quat - 2*z_quat*x_quat); // found this on wikipedia

	std::cout<<"bot_to_fid_yaw = " << bot_to_fid_yaw <<std::endl;


	geometry_msgs::Twist wheelcmd;
	if (z_dist > 1.0){
		//wheelcmd.angular.z = 0.1;
		std::cout << "z_dist > 1" << std::endl;
	}else{
		//wheelcmd.angular.z = -0.1;
		std::cout << "z_dist < 1" << std::endl;
	}

    }
    //pub_wheelcmd.publish(wheelcmd);
}

