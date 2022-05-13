# RSP Final Project: Turtlebot Follow the Leader
Kapi Ketan Mehta, Michael Wilkinson, Brian Woronowicz
------------------------------------------------
Repo for Spring 2022 RSP Course Project.
For this project, we produced the code necessary to have a turtlebot use its raspicam to detect and follow a fiducial marker (AR tag), both in real life and in gazebo. 

__Installation__
To install the package, clone the repository into a catkin workspace.

__Package Descriptions__
------------------------------------------------
__turtlebot_target_follow__  
This package contains the hpp and cpp code for the turtlebot target following. It is the main package of the project.  
	
It parses the /fiducial_transforms (transformation from the raspicam on the turtlebot to detected fiducial markers) rostopic and publishes /cmd_vel (wheel velocity commands for the turtlebot) for both physical and simulated turtlebots.   
	
The package minimizes the angle between the turtlebot and the detected fiducial transform. If the robot loses the fiducial marker from the left side of the camera, it makes the robot rotate left. If the robot loses the fiducial marker from the right side of the camera, it makes the robot rotate right. Also, if the fiducial transform gets too close to the camera (< 0.7 meters from the camera), then it makes the turtlebot back up.  
	
	
*__turtle_Project_simulation__

	*__turtlebot_description__  

This package contains files required for 3D model descriptions for the turtlebots and AR tag.  
	
	*__turtlebot3_project_bringup__  

This package contains launch files required to spawn a follower turtlebot and AR tag leader Turtlebot in gazebo.  
	
	*__turtlebot_aruco_driver__  

This package contains launch file to run the aruco AR tag detection purely in simulation.  
	

__turtlebot_camera_bringup__  

This package contains launch files to start the raspicam on the turtlebot and launch aruco AR tag detection




__Running the project__
------------------------------------------------

__Running the tracker on the physical Turtlebot__
1. Ensure the ROS_MASTER_URI and ROS_HOSTNAME are appropriately set on the turtlebot and main pc such that the ROS_MASTER_URI matches on both machines and the ROS_HOSTNAME matches the machines IP address

2. Run the following commands in your main pc's terminal:  
```echo 'export LDS_MODEL=LDS-01' >> ~/.bashrc```
	
```echo "export TURTLEBOT3_MODEL=burger" >> ~/.bashrc```
	
4. In workspace, run:  
The following instructions assume that a catkin workspace has been created at '$WORKSPACE' and the source path os at `$WORKSPACE/src`
```catkin build turtlebot_target_follow```  
	
```
source $WORKSPACE/devel/setup.bash

# Replace $WORKSAPCE with the appropriate worksapce path
```

5.  Run roscore on either turtlebot or your machine (depending on which has the MASTER_URI)

6. ssh to turtlebot and run:  
	
```roslaunch turtlebot_target_follow turtlebot_bringup.launch```

This will launch the raspicamera, do the image transport needed for the ar tag processing node, and launch the turtlebot3_robot.bringup which starts all the motor drivers, gryo, etc on the turtlebot. 

7. On main computer run:  
	
```roslaunch turtlebot_target_follow target_follow_start.launch```

This starts the aruco package which handles the ar tag transforms, gazebo client with a simulated turtlebot mimicing the real one, and the target_follow_node which reads in the ar tag transform and sends appriopriate motor commands to the cmd_vel topic for the turtlebot and mimic to move.

To change the size of the ar tag to match that of your actual ar tag size change the fiducial_length rosparam via:  
	
```roslaunch turtlebot_target_follow tartget_follow_start fiducial_length:= #tag side length in meters```
  
__Usage with Gazebo Simulation Only__
-----------------------------------------------

There are launch files which allows to run the simulation only version of the task with gazebo.
	
```roslaunch turtlebot_target_follow follower_simulation.launch```

__Miscellaneous__
-----------------------------------------------

__To run ar tag vizualiation seperately__
	
__Launch camera__  
	
```roslaunch raspicam_node camerav2_1280x960.launch```

__Image transpost converts the images into suitable compressed format to use for ar tag tracking__
	
```rosrun image_transport republish compressed in:=/raspicam_node/image raw out:=/raspicam_node/image/image_repub```

__Launches Ar Tag Track__
	
```roslaunch aruco_detect aruco_detect.launch transport:=compressed verbose:=true```

__Use rqt_gui to visualize__
	
```rosrun rqt_gui rqt_gui```
