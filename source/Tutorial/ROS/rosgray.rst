ROS grayscale display
=======================

#. Open ROS environment::

	roscore&
	
#. Enter the folder where ros package is located to initialize the environment variables::

	source ./devel/setup.bash
	
#. Run the launch file::

	roslaunch dmcam_ros start.launch
	
#. Show grayscale command::

	rosrun image_view image_view image:=/smarttof/image_gray

	The grayscale image is shown below：

   .. image:: imageR/lin_R3.jpg 