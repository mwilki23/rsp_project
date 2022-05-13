# RSP Final Project: Turtlebot Follow the Leader
Kapi Ketan Mehta (kmehta4), Michael Wilkinson (mwilki23), Brian Woronowicz (bworono1)
------------------------------------------------
Repo for Spring 2022 RSP Course Project.

__Installation__
------------------------------------------------
To install the package, clone the repository into a catkin workspace. This package requires that the physical turtlebot has the standard turlebot3 and raspicam packages installed on it.

__Deliverables__
------------------------------------------------
For this project, we produced the code necessary to have a turtlebot use its raspicam to detect and follow a fiducial marker (AR tag), both in real life and in gazebo. To do so we have created the following packages (descriptions in Package Description section):

__Camera Related__
- turtlebot_camera_bringup

__Hardware Related__
- turtlebot_target_follow

__Simulation Related__
- turtlebot3_project_bringup
- turtlebot_description
- turtlebot_aruco_driver


__Package Descriptions__
------------------------------------------------
__turtlebot_camera_bringup__  
This package contains launch files to start the raspicam on the turtlebot and launch aruco AR tag detection (using aruco_detect package) on the main pc.

__turtlebot_target_follow__  
This package contains the hpp and cpp code for the turtlebot target following. It is the main package of the project.  
	
It parses the /fiducial_transforms (transformation from the raspicam on the turtlebot to detected fiducial markers) rostopic to obtain the AR tag transformation and publishes wheel velocity commands for both physical and simulated turtlebots to the apprioprate /cmd_vel rostopics based on the AR tag transformation.   
	
The package minimizes the angle and maintans a distance of ~1 meter between the turtlebot and the detected fiducial transform. If the robot loses the fiducial marker it will rotate in place with a directionality derived from the horizontal offset it last detected the transform. If fiducial transform gets too close to the camera (< 0.8 meters from the camera) the turtlebot will reverse in order to maintain ~1 meter distance.  
	
	
__turtle_Project_simulation (Directory)__

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;__turtlebot_description__

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This package contains files required for 3D model descriptions for the turtlebots and AR tag.  
	
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;__turtlebot3_project_bringup__

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This package contains launch files required to spawn a follower turtlebot and AR tag leader Turtlebot in gazebo.  
	
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;__turtlebot_aruco_driver__

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This package contains launch file to run the aruco AR tag detection purely in simulation.  
	

__Running the project__
------------------------------------------------

__Running the tracker on the physical Turtlebot__
1. Ensure the ROS_MASTER_URI and ROS_HOSTNAME are appropriately set on the turtlebot and main pc such that the ROS_MASTER_URI matches on both machines and the ROS_HOSTNAME matches the machines IP address

2. Run the following commands in your main pc's terminal:  
```echo 'export LDS_MODEL=LDS-01' >> ~/.bashrc```
	
```echo "export TURTLEBOT3_MODEL=burger" >> ~/.bashrc```

If your model is the 'waffle' model, replace 'burger' in the line above with 'waffle'.
	
4. In workspace, run:

The following instructions assume that a catkin workspace has been created at `$WORKSPACE` and the source path is present at `$WORKSPACE/src`

```catkin build turtlebot_target_follow```  
	
```
source $WORKSPACE/devel/setup.bash

# Replace $WORKSPACE with the appropriate worksapce path
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

To do a gazebo simulation-only version of the target tracking where the turtlebot follows a teleoperated turtlebot with an AR tag, run:
	
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
