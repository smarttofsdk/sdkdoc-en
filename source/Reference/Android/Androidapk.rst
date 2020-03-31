dmcam Android extension overview
================================

Android extension provided by dmcam can facilitate Android developers' rapid secondary development based on SmartToF_ camera, 
This document mainly describes the use of Android extensions and their associations and differences with the C API.

Android extension installation
++++++++++++++++++++++++++++++

* Supported systems：

  - Android 4.4.2
  
* Android extended dynamic libraries include (ARM V5 and ARM V7 architecture)

  - libdmcam.so: dmcam core lib
  - libdmcam_java.so: Java dmcam extension adapter library
  - dmcam_android.jar: android extended dynamic library, can be imported into Android projects
  - libusb1.0.so: usb device driver library
  
* Installation method

  - Add all the above libraries(.so) to libs under Android project
  - Add `dmcam.jar` under Android project
  
Android API description
++++++++++++++++++++++++

Android app development is based on the Java language, so the main API description in Android and Java are basically the same, 
and they all correspond to the APIs defined in ** dmcam.h ** in the C library.

- The default namespace expanded in Android is: `com.smarttof.dmcam` . Can be imported via `import`：

  .. code-block:: Java
  
		import com.smarttof.dmcam.*;
		
		public boolean devSetFrameRate(dev_t dev, int fps){
			if (dev == null)
				return false;
			
			param_item_t wparam = new param_item_t();
			dmcamParamArray wparams = new dmcamParamArray(1);
			
			wparam.setParam_id(dev_param_e.PARAM_FRAME_RATE);
			wparam.getParam_val().getFrame_rate().setFps(fps);
		
			wparams.setitem(0, wparam);
			logUI("DMCAM",
					String.format("set fps = %d\n", wparams.getitem(0)
							.getParam_val().getFrame_rate().getFps()));
			if (!dmcam.param_batch_set(dev, wparams.cast(), 1)) {
				logUI("DMCAM", String.format(" set fps to %d failed\n", fps));
				return false;
			}
			return true;
		}
		
- The calling API in Android is basically the same as the calling API in Java，the mapping relationship is as follows: **dmcam_xxxxx(...) -> dmcam.xxxxx(...)** .
  For example `dmcam_dev_close` be mapped to `dmcam.dev_close`
  
- Structure mapping： **dmcam_xxxxx -> xxxxx()** . Structure is mapped to a class in java. For example, create a `dmcam_param_item_t` structure as follows:
 
  .. code-block:: Java
  
	  wparam = new param_item_t();
	  
  .. caution::
  
      The API called when opening the device in Android is `dmcam.dev_open_by_fd`, not `dmcam.dev_open` in other environments.

- Accessing member variables of a structure： **obj.field -> obj.getField()/setField** . Member variable access needs to be performed by the get / set method corresponding to the member variable name. For example:

  .. code-block:: Java

     cap_cfg_t cfg = new cap_cfg_t(); 
     cfg.setCache_frames_cnt(10);  // cfg.cache_frame_cnt = 10
     cfg.setOn_error(null);        // cfg.on_error = NULL
     /* ... */

- `NULL` is mapped to `null` , for example:
  
  .. code-block:: Java

      cfg.setOn_error(null);

- The following are some differences between calling API in Android and C, need to pay attention.

  `dmcam.dev_open_by_fd()`
	
	To open the device under Android, you need to call the API dmcam.dev_open_by_fd () designed for Android. The specific usage example is as follows：
	
   .. code-block:: Java
   
	   UsbDeviceConnection connection = usbManager.openDevice(usbDevice);
	   fd = connection.getFileDescriptor();
	   dev = dmcam.dev_open_by_fd(fd);
	   
  `dmcam.param_batch_set()`
	Need to construct param_item_t instance, the specific example is as follows:
	
   .. code-block:: Java
   
      param_item_t wparam = new param_item_t();
	  dmcamParamArray wparams = new dmcamParamArray(1);
	  
	  wparam.setParam_id(dev_param_e.PARAM_INTG_TIME);
	  wparam.getParam_val().getIntg().setIntg_us(expoUs);
	  
	  wparams.setitem(0, wparam);
	  if (!dmcam.param_batch_set(dev, wparams.cast(), 1)) {
			logUI("DMCAM",
					String.format(" set exposure to %d us failed\n", expoUs));
			return false;
	  }
	  
  `dmcam.param_batch_get()`
	To obtain parameters, you also need to construct an instance. The specific example is as follows:
	
   .. code-block:: Java
   
	  param_item_t r_fps = new param_item_t();
	  r_fps.setParam_id(dev_param_e.PARAM_FRAME_RATE);
	  
	  dmcamParamArray rparam = new dmcamParamArray(1);
	  rparam.setitem(0,r_fps);
	  
	  if (dmcam.param_batch_get(dev, rparam.cast(), 1)) {
		logUI("DMCAM",
				String.format(" get frame_rate %d fps\n",  (int)rparam.getitem(0).getParam_val().getFrame_rate().getFps()));
	  }
	  
  `dmcam.set_callback_on_frame_ready and dmcam.set_callback_on_error`
   Callback functions are not supported in Android extensions. When capture data, you can refer to the following settings:

   .. code-block:: Java

        cap_cfg_t cfg = new cap_cfg_t();
        cfg.setCache_frames_cnt(10);
        cfg.setOn_error(null);
        cfg.setOn_frame_ready(null);
        cfg.setEn_save_replay((short)0);
        cfg.setEn_save_dist_u16((short)0);
        cfg.setEn_save_gray_u16((short)0);
        cfg.setFname_replay(null);

        dmcam.cap_config_set(dev, cfg);	  

.. _SmartToF: http://www.smarttof.com






















