OpenNI2 extension introduction
==============================

n order to support the framework in OpenNI2 to implement the call to the Smart module, the corresponding driver library samrttof.dll is provided in the SDK,
This driver follows the definition of OpenNI2 in OniDriverAPI.h, which mainly includes DriverService, DriverBase, DeviceBase, StreamBase
In these several categories, the driver source code for smarttof.dll is released in the SDK.

SmartToF module settings
++++++++++++++++++++++++

All related parameter settings and use of filtering functions in SmartToF are performed through the setProperty function in the smarttofStream class, according to setProperty
set the corresponding propertyId.

The following table lists the property ID of the property:

.. list-table::
	:widths: auto
	:header-rows: 1
	
	* - function ID
	  - Description
	* - PROPERTY_ID_PARAM_SET
	  - Module parameter setting IDID
	* - PROPERTY_ID_PARAM_GET
	  - Module parameter acquisition ID
	* - PROPERTY_ID_FILTER_LEN_CALIB_ENABLE
	  - Lens filter enable
	* - PROPERTY_ID_FILTER_LEN_CALIB_DISABLE
	  - Lens filter disable
	* - PROPERTY_ID_FILTER_PIXEL_CALIB_ENABLE
	  - Pixel filtering enabled
	* - PROPERTY_ID_FILTER_PIXEL_CALIB_DISABLE
	  - Pixel filtering disabled
	* - PROPERTY_ID_FILTER_AMP_CALIB_ENABLE
	  - Amplitude filtering enabled
	* - PROPERTY_ID_FILTER_AMP_CALIB_DISABLE
	  - Amplitude filtering disabled
	* - PROPERTY_ID_FILTER_AUTO_INTG_ENABLE
	  - Auto exposure enabled
	* - PROPERTY_ID_FILTER_AUTO_INTG_DISABLE
	  - Auto exposure disabled
	* - PROPERTY_ID_FILTER_TEMP_MONITOR_ENABLE
	  - Temperature monitoring enabled
	* - PROPERTY_ID_FILTER_TEMP_MONITOR_DISABLE
	  - Temperature monitoring disabled
	* - PROPERTY_ID_FILTER_HDR_ENABLE
	  - HDR function enable
	* - PROPERTY_ID_FILTER_HDR_DISABLE
	  - HDR function disable

Sample code for module setup under OpenNI2
------------------------------------------


In OpenNI2, you can set the property ID in the above list to the SmartToF module through setProperty.
For specific setting code examples, please refer to the setting of integration time code below.::

    dmcam_param_item_t wparam;	//setting integration time
    wparam.param_id = PARAM_INTG_TIME;
    wparam.param_val.intg.intg_us = intg;
    wparam.param_val_len = sizeof(wparam.param_val.intg.intg_us);
    depth.setProperty(PROPERTY_ID_PARAM_SET, (void *)&wparam, sizeof(wparam));

The code to get the module settings is as follows::

    dmcam_param_item_t rparam;	//getting framerate
    rparam.param_id = PARAM_FRAME_RATE;
    rparam.param_val_len = sizeof(rparam.param_val.frame_rate.fps);
    depth.getProperty(PROPERTY_ID_PARAM_GET, &rparam);
    printf("frame rate:%d fps\n", rparam.param_val.frame_rate.fps);

    
