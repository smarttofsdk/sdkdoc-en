Compile and generate
======================

Windows platform
++++++++++++++++++++++

#. Copy the java package corresponding to the number of bits in the windows/java directory in the SDK and the corresponding libdmcam.dll in windows \ lib to the windows / samples / java directory

#. Run javac command to compile::

    javac –cp dmcam.jar .\com\smarttof\dmcam\sample\sampleBasic.java
    javac –cp dmcam.jar .\com\smarttof\dmcam\sample\sampleBasicUi.java

After compiling successfully, the corresponding class file is generated under windows/samples/java/com/smarttof/dmcam/sample.

Run java command in windows/samples/java directory::

	java –cp dmcam.jar com.smarttof.dmcam.sample.sampleBasic

Run java command in windows/samples/java directory::

	java –cp dmcam.jar com.smarttof.dmcam.sample.sampleBasicUi


linux platform
+++++++++++++++++++++++

#. Install openjdk-7-jdk for java extension under linux::

    sudo apt-get install openjdk-7-jdk
	
#. Copy the corresponding number of java packages in the linux/java directory in the SDK to the linux/samples/java directory.

#. Run javac command to compile::

    javac –cp .:dmcam.jar ./com/smarttof/dmcam/sample/sampleBasic.java
    javac –cp .:dmcam.jar ./com/smarttof/dmcam/sample/sampleBasicUi.java
	
	After compiling successfully, the corresponding class files are generated under linux/samples/java/com/smarttof/dmcam/sample.

	
Run java in the linux/samples/java directory. If some dynamic libraries are not found, you need to specify LD_LIBRARY_PATH::

	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd) java –cp .:dmcam.jar com.smarttof.dmcam.sample.sampleBasic

Run java in the linux/samples/java directory. If some dynamic libraries are not found, you need to specify LD_LIBRARY_PATH::

	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd) java –cp .:dmcam.jar com.smarttof.dmcam.sample.sampleBasicUi