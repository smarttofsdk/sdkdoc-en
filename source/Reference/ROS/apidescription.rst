ROS extension API description
=============================

dmcam_ros posted topics
++++++++++++++++++++++++

#. \/smarttof\/image_dist

    +------------------------+----------------------------------------------------------+
    |Command used            |  rosrun image_view image_view image:=/smarttof/image_dist|
    +========================+==========================================================+
    |Function description    |  Get depth data from topics posted by image_dist         |
    +------------------------+----------------------------------------------------------+

#. \/smarttof\/image_gray

    +----------------------+----------------------------------------------------------+
    |Command used          |  rosrun image_view image_view image:=/smarttof/image_gray|
    +======================+==========================================================+
    |Function description  | Get depth data from topics posted by image_gray          |
    +----------------------+----------------------------------------------------------+

#. \/smarttof\/camera_info

    +----------------------+-------------------------------------------------------------+
    |Command used          |  rosrun image_view image_view image:=/smarttof/camera_info  |
    +======================+=============================================================+
    |Function description  | Print camera information from topics posted by camera_info  |
    +----------------------+-------------------------------------------------------------+

#. \/smarttof\/pointcloud

    +----------------------+--------------------------------------------------------------------------+
    |Command used          |  rosrun image_view image_view image:=/smarttof/pointcloud                |
    +======================+==========================================================================+
    |Function description  | Display point cloud data from topics published via pointcloud from rviz  |
    +----------------------+--------------------------------------------------------------------------+

Services posted dmcam_ros
+++++++++++++++++++++++++

#. \/smarttof\/change_power  

    +----------------------+---------------------------------------------------------------+
    |Command used          |  rosservice call /smarttof/change_power "power_value:<value>" |
    +======================+===============================================================+
    |Function description  |  Modify the value of PARAM_ILLUM_POWER dynamically            |
    +----------------------+---------------------------------------------------------------+
    |function parameter    |  value defaults to 0                                          |
    +----------------------+---------------------------------------------------------------+

#. \/smarttof\/change_intg

    +----------------------+---------------------------------------------------------------+
    |Command used          |  rosservice call /smarttof/change_intg "intg_value:<value>"   |
    +======================+===============================================================+
    |Function description  |  Dynamically modify the value of PARAM_INTG_TIME,             |
    |         	           |  PARAM_INTG_TIME is the exposure time.                        |
    +----------------------+---------------------------------------------------------------+
    |Function parameter    |  The value of the exposure time ranges from 0 to 1500         |
    +----------------------+---------------------------------------------------------------+

#. \/smarttof\/change_mod_freq

    +----------------------+------------------------------------------------------------------------+
    |Command used          |  rosservice call /smarttof/ change_mod_freq "mod_freq_value:<value>"   |
    +======================+========================================================================+
    |Function description  |  Dynamically modify the value of PARAM_MOD_FREQ,                       |
    |         	           |  PARAM_MOD_FREQ is the modulation frequency.                           |
    +----------------------+------------------------------------------------------------------------+
    |Function parameter    |  The value is currently fixed at 12MHz                                 |
    +----------------------+------------------------------------------------------------------------+

#. \/smarttof\/change_frame_rate

    +----------------------+----------------------------------------------------------------------------+
    |Command used          |  rosservice call /smarttof/ change_frame_rate "frame_rate_value:<value>"   |
    +======================+============================================================================+
    |Function description  |  Dynamically modify the value of PARAM_FRAME_RATE,                         |
    |         	           |  PARAM_INTG_TIME is the exposure time.                                     |
    +----------------------+----------------------------------------------------------------------------+
    |Function parameter    |  PARAM_FRAME_RATE is the frame rate ranges from 1 to 30                    |
    +----------------------+----------------------------------------------------------------------------+
	
#. \/smarttof\/change_sync_delay

    +----------------------+--------------------------------------------------------------------------+
    |Command used          |  rosservice call /smarttof/ change_sync_delay "sync_delay_value:<value>" |
    +======================+==========================================================================+
    |Function description  |  Dynamically modify the value of PARAM_SYNC_DELAY,                       |
    |                      |  PARAM_SYNC_DELAY is the synchronization delay time.                     |
    +----------------------+--------------------------------------------------------------------------+
    |Function parameter    |  PARAM_FRAME_RATE is the frame rate ranges from 1 to 30                  |
    +----------------------+--------------------------------------------------------------------------+

#. \/smarttof\/change_filter

    +---------------------+--------------------------------------------------------------------------------+
    |Command used         |rosservice call /smarttof/change_filter  "filter_id: '<id>'filter_value:<value>"|
    +=====================+================================================================================+
    |Function description |  Turn on the filtering function of the specified id value in filter_id         |
    +---------------------+--------------------------------------------------------------------------------+
    |Function parameter   |  The id value in filter_id can be set to:                                      |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_LEN_CALIB //Lens calibration                                  |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_PIXEL_CALIB //Pixel calibration                               |
    |                     +--------------------------------------------------------------------------------+
    |                     | DMCAM_FILTER_ID_RESERVED //Not currently supported                             |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_AMP //amplitude filter                                        |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_AUTO_INTG //exposure time                                     |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_SYNC_DELAY //Not currently supported                          |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_TEMP_MONITOR //Not currently supported                        |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_HDR //HDR mode                                                |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_OFFSET //distance offset                                      |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_SPORT_MODE //sport mode                                       |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_SYS_CALIB //Not currently supported                           |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_AMBIENT_LIGHT_CALIB //Not currently supported                 |
    |                     +--------------------------------------------------------------------------------+
    |                     | Currently only the value of filter_value needs to be set in,                   |
    |                     | DMCAM_FILTER_ID_AMP, the range is 0-100                                        |
    |                     +--------------------------------------------------------------------------------+
    |                     |  The value of other filter_value can be 0 by default                           |
    +---------------------+--------------------------------------------------------------------------------+

	
#. \/smarttof\/disable_filter


    +---------------------+--------------------------------------------------------------------------------+
    |Command used         |  rosservice call /smarttof/disable_filter "filter_id: '<id>'"                  |
    +=====================+================================================================================+
    |Function description |  Turn off the filtering function of the specified id value in filter_id        |
    +---------------------+--------------------------------------------------------------------------------+
    |Function parameter   |  The id value in filter_id can be set to:                                      |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_LEN_CALIB //Lens calibration                                  |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_PIXEL_CALIB //Pixel calibration                               |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_RESERVED //Not currently supported                            |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_AMP //amplitude filter                                        |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_AUTO_INTG //exposure time                                     |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_SYNC_DELAY //Not currently supported                          |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_TEMP_MONITOR //Not currently supported                        |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_HDR //HDR mode                                                |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_OFFSET //distance offset                                      |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_SPORT_MODE //sport mode                                       |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_SYS_CALIB //Not currently supported                           |
    |                     +--------------------------------------------------------------------------------+
    |                     |  DMCAM_FILTER_ID_AMBIENT_LIGHT_CALIB //Not currently supported                 |
    +---------------------+--------------------------------------------------------------------------------+



