### This is the README file to run the ar tracking on the turtlebot. Here we list the steps to run it:

1. Ensure the ROS_MASTER_URI and ROS_HOSTNAME are appropriately set on the turtlebot and main pc such that the ROS_MASTER_URI matches on both machines and the ROS_HOSTNAME matches the machines IP address

2. roscore on either turtlebot or you machine (depending on which has the MASTER_URI)

3. ssh to turtlebot and run:
	roslaunch turtlebot_target_follow turtlebot_bringup.launch

This will launch the raspicamera,  do the image transport needed for the ar tag processing node, and launch the turtlebot3_robot.bringup which starts all the motor drivers, gryo, etc on the turtlebot. 

4. On main computer run:
	roslaunch turtlebot_target_follow tartget_follow_start

This is start the aruco package which handles the ar tag transforms, the rqt_image_view so the user can see what the camera is seeing, and the target_follow_node which reads in the ar tag transform and sends appriopriate motor commands to the cmd_vel topic for the turtlebot to move.

To change the size of the ar tag to match that of your actual ar tag size change the fiducial_length rosparam via:
	roslaunch turtlebot_target_follow tartget_follow_start fiducial_length:= #number in meters



### To run ar tag vizualiation seperately

##launches camera
roslaunch raspicam_node camerav2_1280x960.launch

##compresses camera image to use for ar tag tracking
rosrun image_transport republish compressed in:=/raspicam_node/image raw out:=/raspicam_node/image/image_repub

##Launches Ar Tag Track
roslaunch aruco_detect aruco_detect.launch transport:=compressed verbose:=true

##Use rqt_gui to visualize
rosrun rqt_gui rqt_gui
