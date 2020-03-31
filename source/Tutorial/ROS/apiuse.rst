Filter setting under ROS
=========================

Use of filtering functions
+++++++++++++++++++++++++++

#. Enable a filter function，for example DMCAM_FILTER_ID_AUTO_INTG::

	rosservice call /smarttof/change_filter "filter_id:
	'DMCAM_FILTER_ID_AUTO_INTG'
	filter_value: 0"
	
#. Disable a filter function，如DMCAM_FILTER_ID_AUTO_INTG::

	rosservice call /smarttof/disable_filter "filter_id:
	'DMCAM_FILTER_ID_AUTO_INTG'"
	
For detailed introduction of ROS API, please go to ROS extension chapter.




