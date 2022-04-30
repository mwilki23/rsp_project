##launches camera
roslaunch raspicam_node camerav2_1280x960.launch

##compresses camera image to use for ar tag tracking
rosrun image_transport republish compressed in:=/raspicam_node/image raw out:=/raspicam_node/image/image_repub

##Launches Ar Tag Track
roslaunch aruco_detect aruco_detect.launch transport:=compressed verbose:=true

##Use rqt_gui to visualize
rosrun rqt_gui rqt_gui
