ROS depth map display
=======================

#. Open ROS environment::

	roscore&
	
#. Enter the folder where ros is located to initialize the environment variables::

	source ./devel/setup.bash
	
#. Run the launch file::

	roslaunch dmcam_ros start.launch
	
#. Show depth map command::

	rosrun image_view image_view image:=/smarttof/image_dist

   The depth image is shown below：

   .. image:: imageR/lin_R2.jpg 