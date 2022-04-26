roslaunch raspicam_node camerav2_1280x960.launch

rosrun image_transport republish compressed in:=/raspicam_node/image raw out:=/raspicam_node/image/image_repub

roslaunch aruco_detect aruco_detect.launch transport:=compressed verbose:=true

Use rqt_gui to visualize
