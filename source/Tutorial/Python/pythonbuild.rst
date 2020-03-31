Runnning example
=======================


To run the Python samples, you need to install the dmcam package corresponding to the Python version,
numpy, matplotlib, pygame, Pyqtgraph and other packages. The dmcam package is the driver package related to the SmartToF module device, which has been uploaded to the pypi website.

Install the packages needed to run the python samples
-----------------------------------------------------

#. Installation of dmcam library

	
	The dmcam package has been uploaded to the WHL package corresponding to each version of Python to the Pypi website since 1.60，to update and install the latest dmcam package, the installation command is as follows::
	   
	   pip install -U dmcam

	If you want to install the specified version of dmcam, you need to add the version number, for example, the installed version number is 1.57.7::

	   pip install dmcam==1.57.7

	The result of installing the dmcam package is as follows：

	.. image:: imageP/win_P1.jpg 

#. Installation of other libraries that the sample depends on
   
	Install numpy、matplotlib、pygame、PyQt5、pyqtgraph, can be installed by::

	 pip install -r requirement.txt

	.. note ::
	
	Installing PyQt5 in python2.7 or python3.4 environment may cause failure. You can install PyQt4 instead. 

After the Python related packages are installed, you can run the specified samples