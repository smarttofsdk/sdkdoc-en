dmcam python extension overview
===============================

Installation of python extension
++++++++++++++++++++++++++++++++


dmcam_ provides extensions based on the standard python wheel，the extension can be installed directly via pip and supports 36-bit and 64-bit environments for Windows and Linux，see `Pypi project homepage`_ .The installation command is::

	pip install -U dmcam

python API Description
++++++++++++++++++++++

The API in Python corresponds to the API defined in ** dmcam.h ** in the C library.

- The default package name in the python extension is: `dmcam`. Can be imported directly via `import`::

    import dmcam

- API name mapping(C->Python)： **dmcam_xxxxx(...) -> dmcam.xxxxx(...)** . For example `dmcam_dev_open` is mapped to `dmcam.dev_open`

     
- Structure mapping(C->Python): **dmcam_xxxxx -> dmcam.xxxx()** . Structure is mapped to a class in Python. For exaample, create `dmcam_frame_info_t` structure::

    finfo = dmcam.frame_info_t()

- `NULL` is mapped to `None`.For example ::
  
    dmcam.init(None) # dmcam_init(NULL)

- The following Python interfaces are different from the C APIs.
  
  `dmcam.dev_list()`
     The C interface is simplified in Python. You can get the device list directly in the following ways. Its return value is `dmcam.dev_t ()` ::
     devs = dmcam.dev_list()
     if devs is None:
        print(" No device found")
     else:
        print("found %d device" % len(devs))
        print(" Device URIs:")
        for i, d in enumerate(devs):
			print("[#%d]: %s" % (i, dmcam.dev_get_uri(d, 256)[0]))
  `dmcam.param_batch_set(dev, dict)`
   The C interface is simplified in Python, passing a `dict` directly, without having to construct a more complex `dmcam_param_item_t` structure and its length parameters. Use example like below ::
      wparams = {
          dmcam.PARAM_FRAME_RATE: dmcam.param_val_u(),
          dmcam.PARAM_INTG_TIME: dmcam.param_val_u(),}
	  
      wparams[dmcam.PARAM_FRAME_RATE].frame_rate.fps = 15
      wparams[dmcam.PARAM_INTG_TIME].intg.intg_us = 1000
      
      if not dmcam.param_batch_set(dev, wparams):
          print(" set parameter failed")
    
  `dmcam.param_batch_get(dev, list)`
   The C interface is simplified in Python. You can directly pass a list that needs to get parameters without having to construct a more complex `dmcam_param_item_t` structure and its length parameters. Use example like below ::

            # get intg from device
            param_vals = dmcam.param_batch_get(dev, [dmcam.PARAM_INTG_TIME])  # type: list[dmcam.param_val_u]
            param_intg_us = param_vals[0].intg.intg_us

  `dmcam.set_callback_on_frame_ready and dmcam.set_callback_on_error`
	Due to the differences between Python callback functions and C. Regarding the setting of callback functions in the acquisition process, currently, Python only supports setting two types of callbacks, `frame_ready` and `error`, through the above two interfaces. Setting of the callback function via `cap_cg_t` in `dmcam.cap_config_set (dev, cap_cfg_t)` is not supported. Use example like below ::
       def on_frame_rdy(dev, f):
           print("cap: idx=%d, num=%d" % (f.frame_fbpos, f.frame_count))
       def on_cap_err(dev, errnumber, errarg):
           print("caperr: %s" % dmcam.error_name(errnumber))

       cap_cfg = dmcam.cap_cfg_t()
       cap_cfg.cache_frames_cnt = 10  # frame buffer = 10 frames
       cap_cfg.on_frame_ready = None  # callback should be set by dmcam.cap_set_callback_on_frame_ready
       cap_cfg.on_cap_err = None      # callback should be set by dmcam.cap_set_callback_on_error
       cap_cfg.en_save_dist_u16 = False  # save dist into ONI file: which can be viewed in openni
       cap_cfg.en_save_gray_u16 = False  # save gray into ONI file: which can be viewed in openni
       cap_cfg.en_save_replay = False  # save raw into ONI file:  which can be simulated as DMCAM device
       cap_cfg.fname_replay = os.fsencode("replay_dist.oni")
       
       dmcam.cap_config_set(dev, cap_cfg)
       
       dmcam.cap_set_callback_on_frame_ready(dev, on_frame_rdy)
       dmcam.cap_set_callback_on_error(dev, on_cap_err)

  
The following table lists some common API interface comparisons：

.. list-table:: C and python interface comparison
	:widths: 60 60
	:header-rows: 1
	
	* - C library API
	  - python API
	* - dmcam_init
	  - dmcam.init
	* - dmcam_dev_list
	  - dmcam.dev_list	  
	* - dmcam_dev_open
	  - dmcam.dev_open
	* - dmcam_dev_close
	  - dmcam.dev_close	
	* - dmcam_cap_config_set
	  - dmcam.cap_config_set
	* - dmcam_cap_set_callback_on_error
	  - dmcam.cap_set_callback_on_error	  
	* - dmcam_param_batch_set
	  - dmcam.param_batch_set	  
	* - dmcam_cap_get_frames
	  - dmcam.cap_get_frames
	* - dmcam_frame_get_distance
	  - dmcam.frame_get_distance
	* - dmcam_frame_get_gray
	  - dmcam.frame_get_gray

.. _dmcam: https://pypi.org/project/dmcam/
.. _`Pypi project homepage`: https://pypi.org/project/dmcam/
