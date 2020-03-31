dmcam C# extension overview
===========================

The C# extension provided by dmcam makes it easy for developers based on .net C# to perform rapid secondary development based on SmartToF_ cameras. 
This document mainly describes the installation of C# extensions and the associations and differences between C# API and C API.

C# extension installation
++++++++++++++++++++++++++


* Window

  * Supported systems： 

    - Windows 7/8/10 32bit/64bit 
    - .Net framework >= 3.5 

  * C# extended dynamic library includes：
  
    - dmcam_csharp.dll: C# extended dynamic library for importing C# projects
    - dmcam_csharp_adapter.dll:C# dmcam extended suitable library configuration
    - libdmcam.dll: dmcam core lib
  
  * Installation method
  
    - Add the above dll to the PATH or copy it to the executable file directory.
    - C# project references `dmcam_csharp.dll`

* Linux
  
  * Supported systems：

    - Linux 64bit (Ubuntu 14.04/16.04 tested)
    - Mono

  * C# extended dynamic library includes
  
    - dmcam_csharp.dll: C# extended dynamic library for importing C# projects.
    - dmcam_csharp_adapter.so: C# dmcam extended suitable library configuration
    - libdmcam.so: dmcam core lib  
  
  * Installation method
  
    - Setting `LD_LIBRAYR_PATH` contains the above **so/dll** folder, or put the dynamic library in the system library directory, such as： `/usr/local/lib/`
  
C# API description
++++++++++++++++++++++


The module API in C# corresponds to the API defined in ** dmcam.h ** in the C library.

- The default namespace for C# extensions is: `com.smarttof` . Can be imported via `using`:

    .. code-block:: C#
    
        using com.smarttof;
        namespace sampleBasic {
        public class sampleBasic{
            public static void Main(string[] argv) {
                dmcam.init(null);
                /* ... */
                dmcam.uninit();
        }

- API name mapping(C->C#)： **dmcam_xxxxx(...) -> dmcam.xxxxx(...)** .For example `dmcam_dev_open` is mapped to`dmcam.dev_open`

     
- Structure mapping(C->C#): **dmcam_xxxxx -> xxxx()** . Structure is mapped to a class in C#, For example, create a `dmcam_frame_info_t` structure as follows:

    .. code-block:: C#

      finfo = new frame_info_t()

- `NULL` is mapped to `null`, For example:
  
    .. code-block:: C#

      dmcam.init(null) // dmcam_init(NULL)

- There are differences between the following C# interfaces and C APIs, you need to pay attention:
  
  `dmcam.dev_list()`
    In C#, the device list is obtained as follows. The return value is the number of ready devices. Use example like below:

    .. code-block:: C#

            dmcamDevArray devs = new dmcamDevArray(16);
            int cnt = dmcam.dev_list(devs.cast(), 16);

            Console.Write("found {0} device\n", cnt);
    
  `dmcam.param_batch_set()`
   Setting parameters in C# is a bit more complicated than C, and you need to construct a param_item_t instance. The specific usage example is as follows:

   .. code-block:: C#

            param_item_t p_fps = new param_item_t();
            p_fps.param_id = dev_param_e.PARAM_FRAME_RATE;
            p_fps.param_val.frame_rate.fps = 15;

            param_item_t p_intg = new param_item_t();
            p_intg.param_id = dev_param_e.PARAM_INTG_TIME;
            p_intg.param_val.intg.intg_us = 1000;
           
            dmcamParamArray wparams = new dmcamParamArray(2);
            wparams.setitem(0, p_fps);
            wparams.setitem(1, p_intg);

            if (!dmcam.param_batch_set(dev, wparams.cast(), 2)) {
                Console.WriteLine(" set param failed\n");
            } 
            

  `dmcam.param_batch_get(dev, list)`
       Setting parameters in C# is a bit more complicated than C, and you need to construct a **param_item_t** instance. The specific usage example is as follows.
	   
    .. code-block :: C#

            param_item_t r_fps = new param_item_t();
            r_fps.param_id = dev_param_e.PARAM_FRAME_RATE;
            param_item_t r_intg = new param_item_t();
            r_intg.param_id = dev_param_e.PARAM_INTG_TIME;
           
            dmcamParamArray rparams = new dmcamParamArray(2);
            rparams.setitem(0, r_fps);
            rparams.setitem(1, r_intg);

            if (!dmcam.param_batch_get(dev, rparams.cast(), 2)) {
                Console.WriteLine(" get param failed\n");
            } else {
                Console.WriteLine("fps = {0}, intg = {1}", 
                        (int)rparams.getitem(0).param_val.frame_rate.fps,
                        (int)rparams.getitem(1).param_val.intg.intg_us);
            }

  `dmcam.set_callback_on_frame_ready and dmcam.set_callback_on_error`
  
	C# extensions do not support callback functions. When capturing, you can refer to the following settings:

   .. code-block:: C#

            cap_cfg_t cfg = new cap_cfg_t();
            cfg.cache_frames_cnt = 10;
            cfg.on_error= null;
            cfg.on_frame_ready= null;
            cfg.en_save_replay= 0;
            cfg.en_save_dist_u16= 0;
            cfg.en_save_gray_u16= 0;
            cfg.fname_replay= null;

            dmcam.cap_config_set(dev, cfg);

  
.. _`Pypi project homepage`: https://pypi.org/project/dmcam/
.. _SmartToF: http://www.smarttof.com
