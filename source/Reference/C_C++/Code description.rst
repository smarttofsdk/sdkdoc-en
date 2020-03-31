Parameters and filtering code examples
======================================

The module-related parameters and filtering function ID have been introduced in :ref:`doc_param` 
The following will explain how to set and get the module parameters and enable and disable the module filter function.
 
Module parameter setting and reading
++++++++++++++++++++++++++++++++++++

Below is an example of setting and reading the exposure time of the module:

* parameter setting::

	dmcam_param_item_t wparam;			
	uint16_t intg_time = 100;			//set first exposure time 
	memset(&wparam,0,sizeof(wparam));
	wparam.param_id = PARAM_INTG_TIME;	//Parameter setting is exposure time
	wparam.param_val_len = sizeof(intg_time);
	wparam.param_val.intg.intg_us = intg_time;
	assert(dmcam_param_batch_set(dev,&wparam,1));	//Call API for single parameter setting

	dmcam_param_item_t wparam;			
	uint16_t intg_hdrtime = 700;		//set second exposure time for setting HDR
	memset(&wparam,0,sizeof(wparam));
	wparam.param_id = PARAM_HDR_INTG_TIME;	//Parameter setting is HDR exposure time
	wparam.param_val_len = sizeof(intg_time);
	wparam.param_val.intg.intg_us = intg_hdrtime;
	assert(dmcam_param_batch_set(dev,&wparam,1));	//Call API for single parameter setting

.. tip::
    If the integration time of HDR is not set to 0, the module's HDR mode is turned on. In HDR mode, the second integration time must be set larger than the first integration time.

* parameter reading::

	dmcam_param_item_t rparam;
	memset(&rparam,0,sizeof(rparam));
	rparam.param_id = PARAM_INTG_TIME;	//Indicates that the parameter item to be read is the integration time
	assert(dmcam_param_batch_get(dev,&rparam,1));	//Call the API to get a single parameter	


For the setting and acquisition of other module parameters, refer to the setting and acquisition of the exposure time above.
	
Filter enable and disable
+++++++++++++++++++++++++

* Pixel calibration, used for correction of depth data after turning on::

	dmcam_filter_args_u witem;
	dmcam_filter_id_e filter_id = DMCAM_FILTER_ID_PIXEL_CALIB; //pixel calibration
	dmcam_filter_enable(dev,filter_id,&witem,sizeof(dmcam_filter_args_u));//enable pixel calibration
	dmcam_filter_disable(dev,DMCAM_FILTER_ID_PIXEL_CALIB); //disable pixel calibration
	
* Depth filtering, used to filter depth data when turned on::

	dmcam_filter_args_u witem;
	dmcam_filter_id_e filter_id = DMCAM_FILTER_ID_MEDIAN;	//depth filter item
	//witem.median_ksize = 3;	     //default value
	witem.depth_filter_mode = 0xf0;  //default value
	witem.depth_filter_strength = 1; //ranges 0~100
	dmcam_filter_enable(dev,filter_id,&witem,sizeof(dmcam_filter_args_u));//enable filter
	dmcam_filter_disable(dev,DMCAM_FILTER_ID_MEDIAN);//disable filter
	
* Amplitude filtering, filtering points with poor quality after turning on::

	dmcam_filter_args_u witem;
	dmcam_filter_id_e filter_id = DMCAM_FILTER_ID_AMP;	//amplitude filter item
	witem.min_amp = 30;	//Set the minimum amplitude filtering threshold
	dmcam_filter_enable(dev,filter_id,&witem,sizeof(dmcam_filter_args_u));//enable filter
	dmcam_filter_disable(dev,DMCAM_FILTER_ID_AMP);	//disable filter
	
* HDR mode，set two integration times to ensure that the same module will not overexpose when measuring different objects near and far::

	dmcam_filter_args_u witem;
	dmcam_filter_id_e filter_id = DMCAM_FILTER_ID_HDR;	//HDR mode
	witem.intg.intg_3d = 100;	         //HDR small exposure time in HDR mode
	witem.intg.intg_3dhdr = 700;         //HDR large exposure time in mode
	dmcam_filter_enable(dev,filter_id,&witem,sizeof(dmcam_filter_args_u)); //enable HDR

.. tip::
    Another way to turn on HDR mode is to directly set the exposure time of HDR to other than 0,
    As in the example of setting the integration above, both methods require the integration time of HDR to be set greater than the integration time of the other
	
	
	
* Automatic integration time, automatically adjust the exposure time according to the distance of the measured object after turning on::

	dmcam_filter_args_u witem;
	dmcam_filter_id_e filter_id = DMCAM_FILTER_ID_AUTO_INTG;	//Automatic exposure item
	witem.sat_ratio = 5;//Automatic exposure threshold value
	dmcam_filter_enable(dev,filter_id,&witem,sizeof(dmcam_filter_args_u));//enable
	dmcam_filter_disable(dev,DMCAM_FILTER_ID_AUTO_INTG);	//disable
	
* Multi-module interference cancellation, turn on to eliminate or reduce interference when multiple modules are turned on at the same time::

	dmcam_filter_args_u witem;
	dmcam_filter_id_e filter_id = DMCAM_FILTER_ID_SYNC_DELAY;	 //interference delay item
	witem.sync_delay = 0;	//0 means a random delay
	dmcam_filter_enable(dev,filter_id,&witem,sizeof(dmcam_filter_args_u));//enable
	dmcam_filter_disable(dev,DMCAM_FILTER_ID_SYNC_DELAY);	//enable

* Sports mode 0, frame format should be set to 2::

	dmcam_filter_args_u witem;
	dmcam_filter_id_e filter_id = DMCAM_FILTER_ID_SPORT_MODE;
	dmcam_param_item_t wparam;	
	uint32_t set_format = 2;	//set frame format to 2		
	memset(&wparam,0,sizeof(wparam));
	wparam.param_id = PARAM_FRAME_FORMAT;	//frame format item
	wparam.frame_format.format = set_format;
	wparam.param_val_len = sizeof(set_format);
	assert(dmcam_param_batch_set(dev,&wparam,1));
	witem.sport_mode = 0;	//set sport mode to 0
	dmcam_filter_enable(dev,filter_id,&witem,sizeof(dmcam_filter_args_u));//enable sport mode 0
	dmcam_filter_disable(dev,DMCAM_FILTER_ID_SPORT_MODE);//disable sport mode 0
	
* Sport mode 1, frame format should be set to 4::

	dmcam_filter_args_u witem;
	dmcam_filter_id_e filter_id = DMCAM_FILTER_ID_SPORT_MODE;
	dmcam_param_item_t wparam;	
	uint32_t set_format = 4;
	memset(&wparam,0,sizeof(wparam));
	wparam.param_id = PARAM_FRAME_FORMAT;
	wparam.frame_format.format = set_format;
	wparam.param_val_len = sizeof(set_format);
	assert(dmcam_param_batch_set(dev,&wparam,1));
	witem.sport_mode = 1;	
	dmcam_filter_enable(dev,filter_id,&witem,sizeof(dmcam_filter_args_u));//enable sport mode 1
	//After close sport mode 1 ,should set frame format back to 2
	set_format = 2;		
	wparam.frame_format.format = set_format;	
	wparam.param_id = PARAM_FRAME_FORMAT;	
	wparam.param_val_len = sizeof(set_format);
	assert(dmcam_param_batch_set(dev,&wparam,1));
	dmcam_filter_disable(dev,DMCAM_FILTER_ID_SPORT_MODE);