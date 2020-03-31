Building the sample
=====================

Generate vs progect under windows
+++++++++++++++++++++++++++++++++

* Generate vs progect under windows

#. create *vsbuild* folder under *windows/samples/c* 

#. using command line tools or using *mingw* under msys2,enter vsbuild and using cmake command to generate VS project，detail command like follows::

    cd vsbuild
	
    cmake .. -G "Visual Studio 12 2013"  //according to your VS version

The generated VS project is shown below
	
	.. image:: imageC/win_C1.jpg
	
#. Open dmcam_c_sample.sln, compile to generate C excutable program.

 VS project and version show as table 3-1：

	.. list-table:: Table3-1 VS version
		:widths: 60 40
		:header-rows: 1
		
		* - Version
		  - Number
		* - Visual Studio 2005
		  - 8
		* - Visual Studio 2008
		  - 9
		* - Visual Studio 2010
		  - 10
		* - Visual Studio 2012
		  - 11
		* - Visual Studio 2013
		  - 12	  
		* - Visual Studio 2015
		  - 14
		* - Visual Studio 2017
		  - 15
  
After successfully generating the VS project, use VS to open the project and generate the solution. The following figure shows the sample_capture_frames program after generating the solution
	.. image:: imageC/win_C2.jpg
	
* Generate excutable program under windows

#. Create *build* folder under *windows\samples\c*

#. Enter *build* folder and generate excutable file via *cmake*，detail's command are as follows::

    cd build
	
    cmake .. -G "MSYS Makefiles"
	
    make -j
	
#. Run excutable via double click it

* Run in linux

#. Copy libdmcam.so to */usr/lib*

#. Open terminal，install cmake::

    sudo apt-get install cmake

#. Create *build* folder under *linux/sample/c*，and run the following commands::

    cd build
    cmake .. -G "Unix Makefiles"
    make -j

After generating the executable file, the executable file shown in the following figure is displayed under the build folder:	
	.. image:: imageC/win_C3.jpg
	
Run the excutable program

C++ Sample process
---------------------

C++ Samples please refer to C Samples.























