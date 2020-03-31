ROS pointcloud display
=======================

*cloud_viewer* is a simple example of using smarttof ros to display pointcloud data,
this sample simply implements how to get pointcloud data from the pointcloud topic published by smarttof ros and display it

#. Open ROS environment::

	roscore&
	
#. Enter the folder where ros package is located to initialize the environment variables::

	source ./devel/setup.sh
	
#. Run the launch file::

	roslaunch cloud_viewer start.launch

#. Display pointcloud image

	.. image:: imageR/lin_R4.jpg 
	
#. Use the wheel in the middle of the mouse and the left mouse button to adjust the point cloud to display the image. The final effect is shown in the figure.

	.. image:: imageR/lin_R5.jpg 