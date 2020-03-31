dmcam Java extension overview
=============================

The Java extension provided by dmcam makes it easy for developers based on Java to perform rapid secondary development based on SmartToF_ cameras. 
This document mainly describes the installation of Java extensions and the associations and differences between Java API and C API.


Java extension installation
+++++++++++++++++++++++++++

* Window 

  * Supported systems： 

    - Windows 7/8/10 32bit/64bit 
    - JDK >= 1.8

  * Java extended dynamic library includes：

    - dmcam.jar: Java extended dynamic library for importing Java projects.
    - dmcam_java.dll: Java dmcam extended suitable library configuration
    - libdmcam.dll: dmcam core lib

  * Installation method
  
    - Add the above dll to the PATH or copy it to the executable file directory.
    - Java project references `dmcam.jar`

* Linux

  * Supported systems：

    - Linux 64bit (Ubuntu 14.04/16.04 tested)
    - Open JDK >= 7

  * Java extended dynamic library includes：
  
    - dmcam.jar: Java extended dynamic library for importing Java projects.
    - libdmcam_java.so: Java dmcam extended suitable library configuration
    - libdmcam.so: dmcam core lib  
  
  * Installation method
  
    - Setting `LD_LIBRAYR_PATH` contains the above **so/dll** folder, or put the dynamic library in the system library directory, such as： `/usr/local/lib/`
  
Java API description
++++++++++++++++++++++


The module API in Java corresponds to the API defined in ** dmcam.h ** in the C library.。

- The default namespace for Java extensions is: `com.smarttof.dmcam`. Can be imported via `import`:

  .. code-block:: Java
    
        import com.smarttof.dmcam.*;

        public class sampleBasic{
	    public static void main(String[] args) {
            dmcamDevArray devs = new dmcamDevArray(16);
		    int cnt = dmcam.dev_list(devs.cast(), 16);
        }

- API name mapping(C->Java)： **dmcam_xxxxx(...) -> dmcam.xxxxx(...)** .For example `dmcam_dev_open` is mapped to `dmcam.dev_open`

     
- Structure mapping(C->Java): **dmcam_xxxxx -> xxxx()** 。 . Structure is mapped to a class in Java. For example, create a `dmcam_frame_info_t` structure as follows:

  .. code-block:: Java

      finfo = new frame_info_t()

  .. caution::

      `dmcam.init(null)` is automatically called when the Java extension is loaded，`dmcam.uninit()` will be called automatically when released. So it is not necessary to use  `dmcam.init()` and `dmcam.uninit()` in the program.

- Accessing member variables of a structure： **obj.field -> obj.getField()/setField**. Member variable access needs to be performed by the get / set method corresponding to the member variable name. For example：

  .. code-block:: Java

     cap_cfg_t cfg = new cap_cfg_t(); 
     cfg.setCache_frames_cnt(10);  // cfg.cache_frame_cnt = 10
     cfg.setOn_error(null);        // cfg.on_error = NULL
     /* ... */

- `NULL` is mapped to `null`, for example:
  
  .. code-block:: Java

      dmcam.dev_open(null) // dmcam_dev_open(NULL)

- The following are some differences between calling API in Java and C, need to pay attention.
  
  `dmcam.dev_list()`
    In Java, the device list is obtained as follows. The return value is the number of ready devices. Use example like below:

    .. code-block:: Java

            dmcamDevArray devs = new dmcamDevArray(16);
            int cnt = dmcam.dev_list(devs.cast(), 16);

            System.out.printf("found {0} device\n", cnt);
    
  `dmcam.param_batch_set()`
   Setting parameters in Java is a bit more complicated than C, and you need to construct a param_item_t instance. The specific usage example is as follows::

   .. code-block:: Java

      int pwr_percent = 100;
      param_item_t wparam = new param_item_t();
      dmcamParamArray wparams = new dmcamParamArray(1);
      wparam.setParam_id(dev_param_e.PARAM_ILLUM_POWER);
      wparam.getParam_val().getIllum_power().setPercent((short) pwr_percent);
      wparams.setitem(0, wparam);
      if (!dmcam.param_batch_set(dev, wparams.cast(), 1)) {
	    System.out.printf(" set illu_power to %d %% failed\n", pwr_percent);}

  `dmcam.param_batch_get(dev, list)`
    Setting parameters in Java is a bit more complicated than C, and you need to construct a param_item_t instance. The specific usage example is as follows::

    .. code-block:: Java

            param_item_t r_fps = new param_item_t();
            r_fps.setParam_id(dev_param_e.PARAM_FRAME_RATE);
            param_item_t r_intg = new param_item_t();
            r_intg.setParam_id(dev_param_e.PARAM_INTG_TIME);
           
            dmcamParamArray rparams = new dmcamParamArray(2);
            rparams.setitem(0, r_fps);
            rparams.setitem(1, r_intg);

            if (dmcam.param_batch_get(dev, rparams.cast(), 2)) {
                System.out.printf("fps = %d, intg = %d", 
                (int)rparams.getitem(0).getParam_val().getFrame_rate().getFps(),
                (int)rparams.getitem(1).getParam_val().getIntg().getIntg_us());}

  `dmcam.set_callback_on_frame_ready and dmcam.set_callback_on_error`
   Java extensions do not support callback functions. When capturing, you can refer to the following settings:：

   .. code-block :: Java

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
