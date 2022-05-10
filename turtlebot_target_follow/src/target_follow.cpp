#include <turtlebot_target_follow/target_follow.hpp>
#include <math.h>  

target_follow::target_follow(ros::NodeHandle& nh): nh(nh),rate(10){
    sub_artf = nh.subscribe("/fiducial_transforms",10,&target_follow::callback_artf, this);
    pub_wheelcmd = nh.advertise<geometry_msgs::Twist>("cmd_vel",10);
}

void target_follow::callback_artf(const fiducial_msgs::FiducialTransformArray& artf){
   std::cout << std::setprecision(2) << std::fixed;
    if(artf.transforms.empty()){
	std::cout<<"No Fiducials to be found!"<<std::endl;
	wheelcmd.linear.x =  0.0;
	
	double sgn_latshift = abs(x_dist)/(x_dist + 0.0001); //get lateral shift direction btwn bot and tag and no divide by zero error
	//double sgn_rotshift = abs(y_rot)/(y_rot + 0.0001); //get lateral shift direction btwn bot and tag and no divide by zero error
	wheelcmd.angular.z = -1.0*sgn_latshift*0.10; //rotates slowly to search for tag

    
    }
   else{


	x_dist = artf.transforms[0].transform.translation.x; //forward-backward
	z_dist = artf.transforms[0].transform.translation.z; //left-right
	//y distance is up in the air so not relevant
	std::cout<<"[x_dist z_dist] = "<< x_dist << " " << z_dist << std::endl;
	
  	x_quat = artf.transforms[0].transform.rotation.x; 
        y_quat = artf.transforms[0].transform.rotation.y;
        z_quat = artf.transforms[0].transform.rotation.z;
        w_quat = artf.transforms[0].transform.rotation.w;

	// found this on wikipedia
	x_rot = atan2((2*(w_quat*x_quat + y_quat*z_quat)),(1-2*(x_quat*x_quat + y_quat*y_quat)));
	
	double siny = 2*(w_quat*y_quat - z_quat*x_quat);
 	if (abs(siny)>=1){y_rot = copysign(M_PI/2, siny);}
	else{y_rot = asin(siny);}
	
	z_rot = atan2((2*(w_quat*z_quat + x_quat*y_quat)),(1-2*(y_quat*y_quat + z_quat*z_quat)));
	
	
	std::cout<<"[x_rot y_rot z_rot] = "<< x_rot << " " << y_rot << " " << z_rot << std::endl;


	if (abs(y_rot) > 0.08) {
		if(abs(x_dist)/abs(z_dist) < 0.4){wheelcmd.angular.z = -0.3*y_rot;}
		else { wheelcmd.angular.z = 0.0;}
	}
	else{ wheelcmd.angular.z = 0.0;}
	if (z_dist > 1.0){
		wheelcmd.linear.x = 0.1;
		std::cout << "artag_dist > 1m" << std::endl;
	}else{
		wheelcmd.linear.x = 0.0;
		std::cout << "artag_dist < 1m" << std::endl;
	}

    }
    pub_wheelcmd.publish(wheelcmd);
}

