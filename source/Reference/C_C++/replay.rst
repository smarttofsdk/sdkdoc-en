Video save and replay instructions
==================================

In the algorithm evaluation of the module, one of the main preparations before the evaluation is the acquisition of video files. 
In SmartToFViewer, we have introduced how to obtain it through SmartToFViewer.
Record and play, here introduces how to record and read video files through the program, as well as the main introduction to the API

Settings for video files
++++++++++++++++++++++++


Whether to save the video file and what kind of data the video file saves are mainly set in the program ``dmcam_cap_cfg_t`` structure, the specific code is as follows

.. code-block:: C

    /* set capture config */
   dmcam_cap_cfg_t cap_cfg = {
    .cache_frames_cnt = FRAME_BUF_FCNT, /* FRAME_BUF_FCNT frames can be cached in frame buffer*/
    .on_error = NULL,      /* No error callback */
    .on_frame_ready = NULL, /* No frame ready callback*/
    .en_save_replay = false, /* false save raw data stream to replay file */
    .en_save_dist_u16 = false, /* disable save dist stream into replay file */
    .en_save_gray_u16 = false, /* disable save gray stream into replay file*/
    .fname_replay = NULL, /* replay filename */
   };

Among the above structure parameters, the parameters related to the video file are ``en_save_replay`` ``en_save_dist_u16`` ``en_save_gray_u16`` ,
，the specific descriptions of these parameters are as follows：

- Support SmartToF SDK standard playback
  
  If you only need to support SmartToF SDK standard playback, just set the above ``en_save_replay`` to ``true`` and the other two to ``false``
  
- OpenNI-compatible playback (such as NiViewer)
 
  Support playback of OpenNI tools, such as NiViewer playback.In this case, you need to set ``en_save_replay`` to ``false``, ``en_save_dist_u16`` and ``en_save_gray_u16``.
  Set to ``true`` or any one of the settings ``true``, if both are set to enable, it means to store the depth map and grayscale map, and one of them is enabled to enable ``en_save_dist_u16`` as the depth map,
  Enabling ``en_save_gray_u16`` means that the saved image is grayscale.

Reading of video files
+++++++++++++++++++++++


SmartToF video file "xxx.oni" can be simulated as a standard DMCAM device and can be opened by the ``dmcam_dev_open_by_uri`` function,
If the file name is "test.oni", the code to read the file name is as follows.

.. code-block:: C

	dev = dmcam_dev_open_by_uri("test.oni") 	//or file://test.oni

.. caution::

	The main differences between analog dmcam devices and real dmcam devices are as follows:

	- When simulating equipment, all processing based on the original DCS data in the SDK can be adjusted and superimposed, such as: depth filtering, minimum amplitude filtering, pixel calibration, lens calibration, etc.

	- When simulating a device, adjusting related parameters of the DCS raw data is not effective in simulating the device, such as exposure time, HDR function, etc.
