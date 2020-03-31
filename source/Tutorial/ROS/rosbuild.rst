Environment setup using modules in ROS environment
===================================================

Install ros under Ubuntu
++++++++++++++++++++++++++++

The process of installing ros under ubuntu is as follows：

#. Open a command line terminal, enter the ros folder in the SDK, and run the following command::

	sudo chmod 755 install_ros.sh
	./install_ros.sh
	
#. The installation selection version prompt appears as shown in the figure below. Manually enter the version name and press Enter to start the installation. Indigo is recommended for Ubuntu 14.04, and Kinetic is recommended for Ubuntu 16.04.

	.. image:: imageR/lin_R1.jpg 

ROS environment configuration
++++++++++++++++++++++++++++++++++

The environment variables of the installed version need to be initialized before each use of the ROS system，
Take Kinetic as an example， Kinetic is installed in the /opt/ros/kinetic/ by default.
The environment variable configuration file location is /opt/ros/kinetic/setup.bash. You need to initialize the ros environment before each use. 
The command is as follows::

	source /opt/ros/kinetic/setup.bash
	
In order to simplify the process of configuring environment variables, you can choose to place the configuration of environment variables in the **~/.bashrc file**，
This way, every time you open a new terminal, the ROS environment variables will be automatically configured.::

	echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
	
SmartToF ros package compilation
+++++++++++++++++++++++++++++++++

#. Enter the directory where ros is located, and use the **ls** command to view the files in the directory as follows::

	install_ros.sh  Makefile  src
	
#. Use catkin_make(The steps used by catkin_make are implemented in the Makefile, you can also use the make command to compile)::

	source /opt/ros/kinetic/setup.bash(This step is required without initializing the environment in bashrc)
	catkin_make
	
#. After the compilation is complete, the *devel* and *build* directories will be generated. Use the **ls** command to view the generated files::

	build  devel  install_ros.sh  Makefile  src
	
#. Initialize environment variables in **devel** folder::

	source devel/setup.bash 