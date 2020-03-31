Parameter setting and filter setting in python
===============================================

Here we will introduce the setting and reading of parameters in python.

Parameter setting and filter setting
++++++++++++++++++++++++++++++++++++

* Set one parameter，such as setting the frame format::

	wparams_fmt = {dmcam.PARAM_FRAME_FORMAT: dmcam.param_val_u()}
	wparams_fmt[dmcam.PARAM_FRAME_FORMAT].frame_format.format = 2
	if not dmcam.param_batch_set(dev, wparams_fmt):
		log.error(" frame format failed")
		
* Get one parameter，Eg.Read integration time::

	param_val = dmcam.param_batch_get(dev, [dmcam.PARAM_INTG_TIME])
	param_intg_us = param_val.intg.intg_us
	
Filter enable and disable
+++++++++++++++++++++++++

* Pixel calibration for depth data correction ::

	drnu_param = dmcam.filter_args_u()
	drnu_param.case_idx = 0  #  12MHz calibaration
	dmcam.filter_enable(dev, dmcam.DMCAM_FILTER_ID_PIXEL_CALIB, drnu_param, 0)	#enable pixel calibration
	
	dmcam.filter_disable(dev, dmcam.DMCAM_FILTER_ID_PIXEL_CALIB)	#disable pixel calibration
	
* Depth filtering for depth data filtering::

	filter_param = dmcam.filter_args_u()
	filter_param.median_ksize = 3	
	dmcam.filter_enable(dev, dmcam.DMCAM_FILTER_ID_MEDIAN, filter_param, sys.getsizeof(filter_param))	#enable depth filter
	
	dmcam.filter_disable(dev, dmcam.DMCAM_FILTER_ID_MEDIAN)	#disable depth filter
	
* Amplitude filtering for filtering poor quality points::
	
	amp_min_val = dmcam.filter_args_u()
	amp_min_val.min_amp = 30	#Set threshold for minimum amplitude filtering
	dmcam.filter_enable(dev, dmcam.DMCAM_FILTER_ID_AMP, amp_min_val, sys.getsizeof(amp_min_val))    #enable amplitude filter
	
	dmcam.filter_enable(dev, dmcam.DMCAM_FILTER_ID_AMP)		#disable amplitude filter
	
* Automatic integration time, open the module to automatically adjust the exposure time according to the measured object::

	intg_auto_arg = dmcam.filter_args_u()
	intg_auto_arg.sat_ration = 5	#Value of the auto exposure setting
	dmcam.filter_enable(dev, dmcam.DMCAM_FILTER_ID_AUTO_INTG, intg_auto_arg, sys.getsizeof(intg_auto_arg))  #Turn on automatic exposure
	
	dmcam.filter_disable(dev,DMCAM_FILTER_ID_AUTO_INTG)		#Turn off automatic exposure
	
* sport mode 0，set frame format to 2(Only for TC-E series)::
	
	dmfilter = dmcam.filter_args_u()
	
	wparams_fmt = {dmcam.PARAM_FRAME_FORMAT: dmcam.param_val_u()}
	wparams_fmt[dmcam.PARAM_FRAME_FORMAT].frame_format.format = 2	#set frame format value 2
	dmcam.param_batch_set(dev, wparams_fmt)		#set frame format
	
	dmfilter.sport_mode = 0		#set sport mode value to 0
	dmcam.filter_enable(dev, dmcam.DMCAM_FILTER_ID_SPORT_MODE, dmfilter, 0)		#open sport mode 0
	
	dmcam.filter_disable(dev, dmcam.DMCAM_FILTER_ID_SPORT_MODE)		#close sport mode 0
	
* sport mode 1，set frame format to 2(Only for TC-E series)::

	dmfilter = dmcam.filter_args_u()
	
	wparams_fmt = {dmcam.PARAM_FRAME_FORMAT: dmcam.param_val_u()}
	wparams_fmt[dmcam.PARAM_FRAME_FORMAT].frame_format.format = 4 #set frame format value to 4
	dmcam.param_batch_set(dev, wparams_fmt)  #set frame format
	
	dmfilter.sport_mode = 1		#set sport mode value 1
	dmcam.filter_enable(dev, dmcam.DMCAM_FILTER_ID_SPORT_MODE, dmfilter, 1) 	#open sport mode 1
	
	#when close sport mode 1，please switch frame format to 2
	wparams_fmt = {dmcam.PARAM_FRAME_FORMAT: dmcam.param_val_u()}
	wparams_fmt[dmcam.PARAM_FRAME_FORMAT].frame_format.format = 2 #set frame format to 2
	dmcam.param_batch_set(dev, wparams_fmt)  #set frame format
	
	dmcam.filter_disable(dev, dmcam.DMCAM_FILTER_ID_SPORT_MODE)		#close sport mode 1
	
	
	
	
	
	
	
	
	
	
	
	
	

	
