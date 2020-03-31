Use of ROS rviz tool
=====================

rviz is a graphical tool that comes with ros, which can conveniently perform graphical operations on the ros program. The overall interface is shown in the figure below:

	.. image:: imageR/lin_Rv1.jpg 
	
The interface is mainly divided into a display setting area on the left, a large display area in the middle, and a viewing angle setting area on the right.
At the top are several tools related to navigation. The bottom is the display of some data related to ros status.

rviz preparation before use
+++++++++++++++++++++++++++

#. Open ROS environment::

	Roscore&
	
#. Enter the folder where ros package is located to initialize the environment variables::

	source ./devel/setup.bash

#. Run the launch file::

	roslaunch dmcam_ros start.launch
	
rviz display depth image
++++++++++++++++++++++++	

#. Open a terminal and run rviz::

	rviz
	
#. Select **add**, select **Image** under **image_dist** in the **By topic**, and finally confirm the addition, as shown in the figure below:：

	.. image:: imageR/lin_Rv2.jpg 
	
#. The display effect is shown in the following figure:

	.. image:: imageR/lin_Rv3.jpg 
	

rviz display pointcloud image
++++++++++++++++++++++++++++++	

#. Open a terminal and run rviz::

	rviz
	
#. Select add, select **PointCloud2** under *pointcloud* in *byTopic*, and finally confirm the addition.

	.. image:: imageR/lin_Rv4.jpg
	
#. In the *displays* area in the upper left corner of rviz, modify the value of the *FixedFrame* variable under *GlobalOptions* to *dmcam_ros*. The point cloud is displayed as shown below.

	.. image:: imageR/lin_Rv5.jpg