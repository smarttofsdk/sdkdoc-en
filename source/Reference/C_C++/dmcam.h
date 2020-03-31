/*****************************************************************//**
 *       @file  dmcam.h
 *      @brief  DM's camera device API
 *
 *  Detail Decsription starts here
 *
 *   @internal
 *     Project  $Project$
 *     Created  3/13/2017 
 *    Revision  $Id$
 *     Company  Data Miracle, Shanghai
 *   Copyright  (C) 2017 Data Miracle Intelligent Technologies
 *    
 *    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *    KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *    IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 *    PARTICULAR PURPOSE.
 *
 * *******************************************************************/

#ifndef DMCAM_H
#define DMCAM_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/*---------------------------------------------------------------------------*
 * lib init/uninit/cfg API section                                                                
 *---------------------------------------------------------------------------*/
/**
 * Init the DM camera layer. It should be called before any 
 * dmcam API is invoked.
 * 
 * @param log_fname [in] specified log file name of dmcam layer. 
 *                  if NULL, the default log
 *                  (dmcam_YYYYMMDD.log) is used.
 *                      
 */

__API void dmcam_init(const char *log_fname);

/**
* Uninit the DM camera layer.
*
*/
__API void dmcam_uninit(void);

/**
 * Set the logging configuration for dmcam layer.
 * 
 * @param console_level [in] specified dmcam_log_level_e, the 
 *                      console log whose log level bellow this
 *                      value will be suppressed.
 * @param file_level [in] specified dmcam_log_level_e, the 
 *                      file log whose log level bellow this
 *                      value will be suppressed.
 * @param usb_level [in] specified dmcam_log_level_e, the 
 *                      usb log whose log level bellow this
 *                      value will be suppressed.
 */

__API void dmcam_log_cfg(dmcam_log_level_e console_level, dmcam_log_level_e file_level, dmcam_log_level_e usb_level);


/** 
 * Setting where to save calibration data
 * 
 * @param path
 * 
 * @return __API void
 */
__API void dmcam_path_cfg(const char *path);


/** 
 * Getting calibration data path
 * 
 * 
 * @return _API char*
 */
__API char* dmcam_path_get(void);

/**
* covert specified error code into error string
*
* @param error_code
*
* @return const char*
*/
__API const char* dmcam_error_name(int error_code);


/*---------------------------------------------------------------------------*
 * device enumberation/open/close API section                                                                   
 *---------------------------------------------------------------------------*/
/**
 * list the dmcam device and fill into dmcam_dev_t array.
 * 
 * @param dev_list [out] device list array to be filled.
 * @param dev_list_num [in] capacity of device list 
 * 
 * @return int [out] number of dmcam device found
 */

__API int dmcam_dev_list(dmcam_dev_t *dev_list, int dev_list_num);

/**
* open specified dmcam device. if the device is not specified,
* it'll try to open the first dmcam device
*
* @param dev [in] specified dmcam device which is usally get
*            from dmcam_dev_list. if Null, the first dmcam
*            device will be opened.
*
* @return dmcam_dev_t* NULL = open device failed.
*/
__API dmcam_dev_t* dmcam_dev_open(dmcam_dev_t *dev);

/**
 * open specified dmcam device with specified fd. this is useful 
 * for android usb device. 
 * 
 * @param fd [in] specified fd
 * 
 * @return dmcam_dev_t*  return opened device. NULL = open 
 *         device failed.
 */
__API dmcam_dev_t* dmcam_dev_open_by_fd(int fd);

/**
 * open specified dmcam device with specified uri. 
 * 
 * @param uri_str [in] specified URI. Following URI are 
 *  supported:
 *    USB device URI:
 *      usb://bus:port or usb://bus:port:dev_addr
 *    Ethernet device URI:
 *      eth://hwid:token@ip or eth://hwid:token@ip
 *    FILE device URI:
 *      file://filename or filename
 * 
 * @return dmcam_dev_t* NULL = open device
 *         failed.
 */
__API dmcam_dev_t* dmcam_dev_open_by_uri(const char *uri_str);

/**
* Close specified dmcam device.
*
* @param dev
*/
__API void dmcam_dev_close(dmcam_dev_t *dev);

/**
 * get URI of specified device.
 * 
 * @param dev [in] specified device after dmcam_dev_open
 * @param uri_str [in] uri string buffer
 * @param uri_str_len [in] uri string buffer len
 * 
 * @return const char* [out] uri string. If null, get uri 
 *         failed.
 */

__API const char* dmcam_dev_get_uri(dmcam_dev_t *dev, char *uri_str, int uri_str_len);

/**
* Reset specified target on the dev
*
* @param dev [in] dmcam device handler
* @param target [in] reset taget defined in dmcam_dev_rst_e
*
* @return bool [out] true = reset ok.
*/
__API bool dmcam_dev_reset(dmcam_dev_t *dev, dmcam_dev_rst_e target);


/*---------------------------------------------------------------------------*
 * register/parameters RW API section                                                                     
 *---------------------------------------------------------------------------*/

/**
* Batch write registers of specified target on the device.
*
* @param dev [in] dmcam device handler
* @param target [in] specified target defined in
*               dmcam_dev_reg_e
* @param reg_base [in] base address of the registers
* @param reg_vals [in] register values to be written. All
*                 register value is denoted as UINT32
* @param reg_vals_len [in] count of values in reg_vals
*
* @return bool [out] true = write ok.
*/

__API bool dmcam_reg_batch_write(dmcam_dev_t *dev, dmcam_dev_reg_e target, uint32_t reg_base, const uint32_t *reg_vals, uint16_t reg_vals_len);

/**
* Batch read registers of specified target on the device.
*
* @param dev [in] dmcam device handler
* @param target [in] specified target defined in
*               dmcam_dev_reg_e
* @param reg_base [in] base address of the registers
* @param reg_vals [out] register values to be filled. All
*                 register value is denoted as UINT32
* @param reg_vals_len [in] count of values in reg_vals
*
* @return bool [out] true = read ok.
*/

__API bool dmcam_reg_batch_read(dmcam_dev_t *dev, dmcam_dev_reg_e target, uint32_t reg_base, uint32_t *reg_vals, uint16_t reg_vals_len);

/**
 * Batch write generic parameters to specified device.
 * 
 * @param dev [in] dmcam device handler
 * @param param_items [in] dmcam_param_item_t is used to denotes 
 *             generic parameter:
 *               * param_id[in]: defined in dmcam_dev_param_e to
 *                 identify the parameters.
 *               * param_vals[in]: denotes the generic value
 *                 (max = 16bytes)
 *               * param_vals_len[in]: denotes the length of
 *                 value.
 * @param item_cnt [in] count of params in param_items
 * 
 * @return bool [out] true = operation is ok.
 */

__API bool dmcam_param_batch_set(dmcam_dev_t *dev, const dmcam_param_item_t *param_items, int item_cnt);
/**
* Batch read generic parameters from specified device.
*
* @param dev [in] dmcam device handler
* @param param_items [in/out] dmcam_param_item_t is used to
*             denotes generic parameter:
*               * param_id[in]: defined in dmcam_dev_param_e to
*                 identify the parameters.
*               * param_vals[out]: denotes the generic value
*                 (max = 16bytes) filled by this function
*               * param_vals_len[out]: denotes the length of
*                 value filled by this function.
* @param item_cnt [in] count of params in param_items
*
* @return bool [out] true = operation is ok.
*/
__API bool dmcam_param_batch_get(dmcam_dev_t *dev, dmcam_param_item_t *param_items, int item_cnt);


/*---------------------------------------------------------------------------*
 * capture API section                                                                     
 *---------------------------------------------------------------------------*/

/**
 * Set specified capture configuration for specified device.
 * This api is available from v1.58 to replace @ref
 * dmcam_cap_set_frame_buffer
 * 
 * @param dev [in] specified dmcam device
 * @param cfg [in] specified capture configuration
 * 
 * @return bool [out] true = set OK.
 */

__API bool dmcam_cap_config_set(dmcam_dev_t *dev, const dmcam_cap_cfg_t *cfg);

/**
 * Get capture configuration of specified device
 * 
 * @param dev [in] specified dmcam device
 * @param cfg [out] capture configuration to be filled
 */
__API void dmcam_cap_config_get(dmcam_dev_t *dev, dmcam_cap_cfg_t *cfg);

/**
 * set frame buffer during capturing.
 * 
 * @param dev [in] dmcam device handler
 * @param frame_buf [in] framebuffer assigned by user. if null, 
 *                  the frame_buf will be alloced internally
 * @param frame_buf_size [in] frame buffer size, which will be 
 *                       rouned to frame size boundary.
 * 
 * @return bool [out] return true = set ok.
 */

API_DEPRECATED_FOR(dmcam_cap_config_set)
__API bool dmcam_cap_set_frame_buffer(dmcam_dev_t *dev, uint8_t *frame_buf, uint32_t frame_buf_size);


/**
* register frame ready callback function
*
* @param dev [in] dmcam device handler
* @param cb  [in] callback function in following format:
*     void (*dmcam_cap_frdy_f)(dmcam_dev_t*, dmcam_frame_t)
*
*/
__API void dmcam_cap_set_callback_on_frame_ready(dmcam_dev_t *dev, dmcam_cap_frdy_f cb);

/**
* register error callback function. It's invoked when some
* error occurs during the capturing process.
*
* @param dev [in] dmcam device handler
* @param cb [in] callback function in following format:
*     void (*dmcam_cap_err_f)(dmcam_dev_t*, int errno);
*/
__API void dmcam_cap_set_callback_on_error(dmcam_dev_t *dev, dmcam_cap_err_f cb);

/**
* Take a snapshot and fill frame data into specified frame. If
* the device is capturing, the snapshot will return the latest
* image{} or it'll auto start/snapshot/stop
*
* @param dev [in] dmcam device handler
* @param frame_data [out] frame data
* @param frame_dlen [in] frame buffersize should be large
*                   enough to containing one frame.
* @param frame [out] frame_t filled during snapshot. it can be
*              null
* @return bool return true = ok
*/
__API bool dmcam_cap_snapshot(dmcam_dev_t *dev, uint8_t *frame_data, uint32_t frame_dlen, dmcam_frame_t *frame);

/**
 * Check whether the device is in capturing state.
 * 
 * @param dev [in] dmcam device handler
 * 
 * @return bool [out] true = device in capturing state
 */
__API bool dmcam_cap_is_ongoing(dmcam_dev_t *dev);

/**
* start device capturing.
*
* @param dev [in] dmcam device handler
*
* @return bool return true = ok
*/

__API bool dmcam_cap_start(dmcam_dev_t *dev);

/**
* stop device capturing.
*
* @param dev [in] dmcam device handler
*
* @return bool return true = ok
*/

__API bool dmcam_cap_stop(dmcam_dev_t *dev);

/**
* Get specified number of frames into specified user buffer.
* This function may be blocking wait on the frame stream. if
* enough frames data are collected or any error happends, it'll
* returns.
* @param dev [in] dmcam device handler
* @param frame_num [in] number of frames to be captured.
* @param frame_data [out] frame data filled curing capturing.
* @param frame_dlen [in] frame_data buffer size in bytes.
* @param first_frame_info [out] first frame attributes. It can
*                         be NULL
*
* @return int [out] return the number for ready frames
*         collected. On error the errono is returned.
*        (errno < 0)
*/

__API int dmcam_cap_get_frames(dmcam_dev_t *dev, uint32_t frame_num, uint8_t *frame_data, uint32_t frame_dlen, dmcam_frame_t *first_frame_info);

/**
* get one frame into specified buffer. this function is
* non-blocking, if no frame is ready, it returns 0
*
* @param dev [in] dmcam device handler
* @param frame_data [out] frame data  to be filled, it can be
*                   NULL
* @param frame_info [out] frame attributes. It can be NULL
*
* @return int return 0 if not frame is ready, else return 1
*/
__API int dmcam_cap_get_frame(dmcam_dev_t *dev, uint8_t *frame_data, uint32_t frame_dlen, dmcam_frame_t *frame_info);

/**
* Firmware upgrade for different type target.
*
* @param dev[in]:dmcam device handler
* @param type[in]:firmware type
* @param version[in]:firmware version
* @param file_name[in]:firmware name
*
* @return int
*/
__API int dmcam_firmware_upgrade(dmcam_dev_t *dev, uint8_t type, uint16_t version, const char *file_name);

__API int dmcam_data_download(dmcam_dev_t *dev, char *name, uint8_t type, uint16_t version, uint32_t addr);
__API int dmcam_data_upload(dmcam_dev_t *dev, uint8_t type, const char *file_name);

/*---------------------------------------------------------------------------*
 * frame data get API section                                                                     
 *---------------------------------------------------------------------------*/
/** alias for dmcam_frame_get_dist_f32  */
__API int dmcam_frame_get_distance(dmcam_dev_t *dev, float *dst, int dst_len,
                                   uint8_t *src, int src_len, const dmcam_frame_info_t *finfo);

/**
 * convert to distance data to float32 from raw frame data. 
 * 
 * @param dev [in] specified dmcam device
 * @param dst [out] distance buffer. The unit of distance is in 
 *            meters (float32)
 * @param dst_len [in] distance buffer length in number of float
 * @param src [in] raw frame  data buffer
 * @param src_len [in] raw frame data length in byte
 * @param finfo [in] raw frame information 
 * 
 * @return int [out] return the number for distance points in 
 *         dst
 */

__API int dmcam_frame_get_dist_f32(dmcam_dev_t *dev, float *dst, int dst_len,
                                   uint8_t *src, int src_len, const dmcam_frame_info_t *finfo);

/**
 * convert to distance data in uint16 from raw frame data. 
 * 
 * @param dev [in] specified dmcam device
 * @param dst [out] distance buffer. The unit of distance is in 
 *            millimeter (uint16)
 * @param dst_len [in] distance buffer length in number of 
 *                uint16
 * @param src [in] raw frame data buffer
 * @param src_len [in] raw frame data length in byte
 * @param finfo [in] raw frame information 
 * 
 * @return int [out] return the number for distance points in 
 *         dst
 */

__API int dmcam_frame_get_dist_u16(dmcam_dev_t *dev, uint16_t *dst, int dst_len,
                                   uint8_t *src, int src_len, const dmcam_frame_info_t *finfo);

/** alias for dmcam_frame_get_gray_f32  */
__API int dmcam_frame_get_gray(dmcam_dev_t *dev, float *dst, int dst_len,
                               uint8_t *src, int src_len, const dmcam_frame_info_t *finfo);
/**
 * get gray data in float32 from raw frame data.
 * 
 * @param dev [in] specified dmcam device
 * @param dst [out] gray buffer. The gray value denotes the amplitude. 
 *            (float32 in [0, 2048.0) )
 * @param dst_len [in] distance buffer length in number of float
 * @param src [in] raw frame  data buffer
 * @param src_len [in] raw frame data length in byte
 * @param finfo [in] raw frame information 
 * 
 * @return int [out] return the number for gray points in 
 *         dst
 */

__API int dmcam_frame_get_gray_f32(dmcam_dev_t *dev, float *dst, int dst_len,
                                   uint8_t *src, int src_len, const dmcam_frame_info_t *finfo);

/**
 * get gray data in uint16_t from raw frame data.
 * 
 * @param dev [in] specified dmcam device
 * @param dst [out] gray buffer. The gray value denotes the amplitude. 
 *            (uint16_t in [0, 2048))
 * @param dst_len [in] distance buffer length in number of 
 *                uint16_t
 * @param src [in] raw frame  data buffer
 * @param src_len [in] raw frame data length in byte
 * @param finfo [in] raw frame information 
 * 
 * @return int [out] return the number for gray points in dst 
 */
__API int dmcam_frame_get_gray_u16(dmcam_dev_t *dev, uint16_t *dst, int dst_len,
                                   uint8_t *src, int src_len, const dmcam_frame_info_t *finfo);

/**
 * get point cloud data from distance data. The distance data is
 * usually calcuated using dmcam_frame_get_dist_f32. 
 * 
 * @param dev [in] specified dmcam device
 * @param pcl [out] point clound buffer. each 3 element consists
 *            a (x,y,z) point, output is in (w,h,3) demension.
 *            point in value (0,0,0) is invalid 
 * @param pcl_len [in] point cloud float element count
 * @param dist [in] distance image data buffer. The unit of 
 *             distance is meter (float)
 * @param dist_len [in] distance image data count (in 
 *                 sizeof(float))
 * @param img_w [in] distance image width in pixel
 * @param img_h [in] distance image height in pixel
 * @param p_cam_param [in] user specified camera lens parameter. 
 *                    if null, the internal camera parameter is
 *                    used.
 * 
 * @return int [out] return number of points in point cloud 
 *         buffer. Note: n points means 3*n floats. N should be
 *         img_w * img_h
 */
__API int dmcam_frame_get_pcl(dmcam_dev_t *dev, float *pcl, int pcl_len,
                              const float *dist, int dist_len, int img_w, int img_h, const dmcam_camera_para_t *p_cam_param);

/**
 * get point cloud data from distance data. The distance data is
 * usually calcuated using dmcam_frame_get_distance.
 * 
 * @param dev [in] specified dmcam device
 * @param pcl [out] point clound buffer. each 4 element consists
 *            a (x,y,z,d) point. (x,y,z) is coordinate, d is
 *            distance or pseudo-color. output is in (w,h,4)
 *            demension. point in value (0,0,0) is invalid 
 * @param pcl_len [in] point cloud float element count
 * @param dist [in] distance image data buffer. The unit of 
 *             distance is meter (float)
 * @param dist_len [in] distance image data count (in 
 *                 sizeof(float))
 * @param img_w [in] distance image width in pixel
 * @param img_h [in] distance image height in pixel 
 * @param pseudo_color [in] if true, d is pseudo uint32 rgb 
 *                     color value; if false, d is the distance
 *                     in meter 
 * @param p_cam_param [in] user specified camera lens parameter. 
 *                    if null, the internal camera parameter is
 *                    used.
 * 
 * @return int [out] return number of points in point cloud 
 *         buffer. Note: n points means 4*n floats. N should be
 *         img_w * img_h
 */
int dmcam_frame_get_pcl_xyzd(dmcam_dev_t *dev, float *pcl, int pcl_len,
                             const float *dist, int dist_len, int img_w, int img_h, bool pseudo_color, const dmcam_camera_para_t *p_cam_param);

/**
 *  Enable filter controller setting for raw data processing
 * 
 * @param dev [in] dmcam device handler
 * @param filter_id [in]:defined in dmcam_filter_id_e to
 *              identify the filter 
 * @param filter_arg [in] filter control args
 * @param reserved [in] reserved for future use. User should set 
 *                 to 0
 * @return int 0 = OK, otherwise failed.
 */
__API int dmcam_filter_enable(dmcam_dev_t *dev,  dmcam_filter_id_e filter_id, dmcam_filter_args_u *filter_arg, uint32_t reserved);

/**
 *  Disable filter controller setting for raw data processing
 * 
 * @param dev [in] dmcam device handler
 * @param filter_id [in] defined in dmcam_filter_id_e to 
 *              identify the filter 
 * 
 * @return int 0 = OK, otherwise failed.
 */
__API int dmcam_filter_disable(dmcam_dev_t *dev,  dmcam_filter_id_e filter_id);

/*---------------------------------------------------------------------------*
 * CMAP utils section                                                                       
 *---------------------------------------------------------------------------*/

/**
 * convert dist_f32 image (pixel in meter) to pesudo-RGB points 
 * with specified pixel format 
 * 
 * @param dst [out] pseudo-RGB point buffer
 * @param dst_len [in] point buffer size in bytes
 * @param src [in] float points buffer
 * @param src_len [in] count of float points
 * @param outfmt [in] pixel format of the pseudo-RGB 
 * @param min_val [in] minimum range of source point
 * @param max_val [in] max range of source point
 * 
 * @return int [out] the count of pseudo RGB points
 */
__API int dmcam_cmap_dist_f32_to_RGB(uint8_t *dst, int dst_len, const float *src, int src_len, dmcam_cmap_outfmt_e outfmt, float range_min_m, float range_max_m);

API_DEPRECATED_FOR(dmcam_cmap_dist_f32_to_RGB)
__API int dmcam_cmap_float(uint8_t *dst, int dst_len, const float *src, int src_len, dmcam_cmap_outfmt_e outfmt, float range_min_m, float range_max_m);

/**
 * convert dist_u16 image (pixel in milimeter) to pesudo-RGB 
 * points with specified pixel format 
 * 
 * @param dst [out] pseudo-RGB point buffer
 * @param dst_len [in] point buffer size in bytes
 * @param src [in] dist_u16 image buffer
 * @param src_len [in] count of u16 points
 * @param outfmt [in] pixel format of the pseudo-RGB 
 * @param min_val [in] minimum range of source point
 * @param max_val [in] max range of source point
 * 
 * @return int [out] the count of pseudo RGB points
 */
__API int dmcam_cmap_dist_u16_to_RGB(uint8_t *dst, int dst_len, const uint16_t *src, int src_len, dmcam_cmap_outfmt_e outfmt, uint16_t range_min_mm, uint16_t range_max_mm);
/**
 * convert gray_u16 image to IR image whose pixel is in [0~255] 
 * 
 * @param dst [out] IR image buffer
 * @param dst_len [in] IR image buffer size in bytes
 * @param src [in] gray_u16 image
 * @param src_len [in] count of u16 points in gray_u16 image
 * @param balance [in] [-1024, 1024] -> [darkest, brightest]
 * 
 * @return int [out] the count of IR image
 */
__API int dmcam_cmap_gray_u16_to_IR(uint8_t *dst, int dst_len, const uint16_t *src, int src_len, int balance);

/**
 * convert gray_f32 image to IR image whose pixel is in [0~255] 
 * 
 * @param dst [out] IR image buffer
 * @param dst_len [in] IR image buffer size in bytes
 * @param src [in] gray_f32 image
 * @param src_len [in] count of f32 points in gray_f32 image
 * @param balance [in] [-1024, 1024] -> [darkest, brightest]
 * 
 * @return int [out] the count of IR image
 */
__API int dmcam_cmap_gray_f32_to_IR(uint8_t *dst, int dst_len, const float *src, int src_len, int balance);
/*---------------------------------------------------------------------------*
 * File save/load API section                                                                         
 *---------------------------------------------------------------------------*/

/**
 * open specified file and get file descriptor for 
 * dmcam_frame_save_xxx apis. 
 * 
 * @param fname [in] specified filename
 * 
 * @return int [out] file descriptor. < 0 = failed
 */

__API int dmcam_file_open(const char *fname, const char *mode);


/**
 * close specified file descriptor 
 * 
 * @param fd [in] specified file descriptor
 */
__API void dmcam_file_close(int fd);


/**
 * save specified raw data (in uin16_t) with specified pixcel
 * width and height to file with specified saving format.
 * 
 * @param fd [in] specified file handler
 * @param save_fmt [in] file saving format defined in
 *                 dmcam_frame_save_fmt_t. only followin format
 *                 is supported:
 *              DMCAM_FRAME_SAVE_UINT32
 *              DMCAM_FRAME_SAVE_UINT16
 * @param raw [in] raw data
 * @param raw_len [in] number of raw data (in count of
 *                 uint16_t)
 * @param img_w [in] dist data pixel width
 * @param img_h [in] dist data pixel height
 * @param dcs_cnt [in] dist data dcs sub-frame count
 * @param raw_tag [in] any string. if want to used by replay, 
 *                specify (dmcam_t*)dev->product string here.
 * @return bool [out] true = save raw frame ok, false =
 *         fail
 */
__API bool dmcam_frame_save_raw(int fd, dmcam_frame_save_fmt_t save_fmt, const uint16_t *raw, int raw_len,
                                int img_w, int img_h, int dcs_cnt, const char *raw_tag);

/**
 * save specified distance data (in float32, unit: meter) with 
 * specified pixcel width and height to file with specified 
 * saving format. 
 * 
 * @param fd [in] specified file handler
 * @param save_fmt [in] file saving format defined in @ 
 *                 @ref dmcam_frame_save_fmt_t. only followin
 *                 format is supported:
 *              DMCAM_FRAME_SAVE_FLOAT32
 *              DMCAM_FRAME_SAVE_UINT32
 *              DMCAM_FRAME_SAVE_UINT16
 * @param dist [in] distance data (in float32, unit: meter)
 * @param dist_len [in] number of distance data (in count of 
 *                 float)
 * @param img_w [in] dist data pixel width
 * @param img_h [in] dist data pixel height
 * 
 * @return bool [out] true = save distance frame ok, false = 
 *         fail
 */
__API bool dmcam_frame_save_distance(int fd, dmcam_frame_save_fmt_t save_fmt, const float *dist, int dist_len, int img_w, int img_h);


/**
 * save specified gray data (in float32) with specified pixcel 
 * width and height to file with specified saving format. 
 * 
 * @param fd [in] specified file handler
 * @param save_fmt [in] file saving format defined in
 *                 @ref dmcam_frame_save_fmt_t. only followin
 *                 format is supported:
 *              DMCAM_FRAME_SAVE_UINT16
 *              DMCAM_FRAME_SAVE_UINT8
 * @param src [in] gray data (in float32)
 * @param src_len [in] number of distance data (in count of
 *                 float)
 * @param img_w [in] dist data pixel width
 * @param img_h [in] dist data pixel height
 * 
 * @return bool [out] true = save distance frame ok, false =
 *         fail
 */
__API bool dmcam_frame_save_gray(int fd, dmcam_frame_save_fmt_t save_fmt, const float *src, int src_len, int img_w, int img_h);

/*!
 * load one raw frame from specified file fd.
 * 
 * @param fd [in] specified data file fd. The fd related file is
 *           always saved by @ref dmcam_frame_save_raw api
 * @param dst [out] raw
 * @param dst_len [in] dst buffer length (in count of
 *                sizeof(uint16_t))
 * @param dst_w [out] raw frame pixel width
 * @param dst_h [out] raw frame pixel height
 * @param dst_dcsn [out] raw dcs cnt per frame
 * @param dst_tag [out] raw data tag string
 * @param tag_len [in] raw data tag buffer size
 * 
 * @return int [out] length of loaded raw data (in count of
 *         sizeof(uint16))
 */
__API int dmcam_frame_load_raw(int fd, uint16_t *dst, int dst_len, int *dst_w, int *dst_h,
                               int *dst_dcsn, char *dst_tag, int dst_tag_len);

/**
 * load one distance frame from specified file fd.
 * 
 * @param fd [in] specified data file fd. The fd related file is 
 *           always saved by @ref dmcam_frame_save_distance api
 * @param dst [out] distance in float (unit: meter)
 * @param dst_len [in] dst buffer length (in count of 
 *                sizeof(float))
 * @param dst_w [out] distance frame pixel width
 * @param dst_h [out] distance frame pixel height
 * 
 * @return int [out] length of loaded distance data (in count of
 *         sizeof(float))
 */

__API int dmcam_frame_load_distance(int fd, float *dst, int dst_len, int *dst_w, int *dst_h);


/**
 * load one gray frame from specified file fd.
 * 
 * @param fd [in] specified data file fd. The fd related file is 
 *           always saved by @ref dmcam_frame_save_gray api
 * @param dst [out] gray in float (unit: meter)
 * @param dst_len [in] dst buffer length (in count of 
 *                sizeof(float))
 * @param dst_w [out] gray frame pixel width
 * @param dst_h [out] gray frame pixel height
 * 
 * @return int [out] length of loaded gray data (in count of
 *         sizeof(float))
 */

__API int dmcam_frame_load_gray(int fd, float *dst, int dst_len, int *dst_w, int *dst_h);

#ifdef __cplusplus
}
#endif
#endif //DMCAM_H
