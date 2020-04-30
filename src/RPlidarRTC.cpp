// -*- C++ -*-
/*!
 * @file  RPlidarRTC.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "RPlidarRTC.h"
#include "rplidar.h"

using namespace rp::standalone::rplidar;

// Module specification
// <rtc-template block="module_spec">
static const char* rplidarrtc_spec[] =
  {
    "implementation_id", "RPlidarRTC",
    "type_name",         "RPlidarRTC",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "maruryota",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.port_name", "COM1",
    "conf.default.baudrate", "115200",
    "conf.default.debug", "0",
    "conf.default.encoding", "2",
    "conf.default.geometry_x", "0",
    "conf.default.geometry_y", "0",
    "conf.default.geometry_z", "0",

    // Widget
    "conf.__widget__.port_name", "text",
    "conf.__widget__.baudrate", "text",
    "conf.__widget__.debug", "text",
    "conf.__widget__.encoding", "text",
    "conf.__widget__.geometry_x", "text",
    "conf.__widget__.geometry_y", "text",
    "conf.__widget__.geometry_z", "text",
    // Constraints

    "conf.__type__.port_name", "string",
    "conf.__type__.baudrate", "int",
    "conf.__type__.debug", "int",
    "conf.__type__.encoding", "int",
    "conf.__type__.geometry_x", "double",
    "conf.__type__.geometry_y", "double",
    "conf.__type__.geometry_z", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RPlidarRTC::RPlidarRTC(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_scan_dataOut("scan_data", m_scan_data)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RPlidarRTC::~RPlidarRTC()
{
}



RTC::ReturnCode_t RPlidarRTC::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("scan_data", m_scan_dataOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("port_name", m_port_name, "COM1");
  bindParameter("baudrate", m_baudrate, "115200");
  bindParameter("debug", m_debug, "0");
  bindParameter("encoding", m_encoding, "2");
  bindParameter("geometry_x", m_geometry_x, "0");
  bindParameter("geometry_y", m_geometry_y, "0");
  bindParameter("geometry_z", m_geometry_z, "0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RPlidarRTC::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RPlidarRTC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RPlidarRTC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

RTC::ReturnCode_t RPlidarRTC::onActivated(RTC::UniqueId ec_id)
{
  drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);

  if (!drv) {
	  fprintf(stderr, "insufficent memory, exit\n");
	  exit();
  }
  const char * opt_com_path = NULL;
  _u32         opt_com_baudrate = 115200;
  u_result     op_result;

  rplidar_response_device_health_t healthinfo;
  rplidar_response_device_info_t devinfo;
  do {
	  // try to connect
	  if (IS_FAIL(drv->connect(opt_com_path, opt_com_baudrate))) {
		  fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n"
			  , opt_com_path);
		  break;
	  }

	  // retrieving the device info
	  ////////////////////////////////////////
	  op_result = drv->getDeviceInfo(devinfo);

	  if (IS_FAIL(op_result)) {
		  if (op_result == RESULT_OPERATION_TIMEOUT) {
			  // you can check the detailed failure reason
			  fprintf(stderr, "Error, operation time out.\n");
		  }
		  else {
			  fprintf(stderr, "Error, unexpected error, code: %x\n", op_result);
			  // other unexpected result
		  }
		  break;
	  }

	  // print out the device serial number, firmware and hardware version number..
	  printf("RPLIDAR S/N: ");
	  for (int pos = 0; pos < 16; ++pos) {
		  printf("%02X", devinfo.serialnum[pos]);
	  }

	  printf("\n",
		  "Version: ", RPLIDAR_SDK_VERSION, "\n",
		  "Firmware Ver: %d.%02d\n",
		  "Hardware Rev: %d\n"
		  , devinfo.firmware_version >> 8
		  , devinfo.firmware_version & 0xFF
		  , (int)devinfo.hardware_version);


	  // check the device health
	  ////////////////////////////////////////
	  op_result = drv->getHealth(healthinfo);
	  if (IS_OK(op_result)) { // the macro IS_OK is the preperred way to judge whether the operation is succeed.
		  printf("RPLidar health status : ");
		  switch (healthinfo.status) {
		  case RPLIDAR_STATUS_OK:
			  printf("OK.");
			  break;
		  case RPLIDAR_STATUS_WARNING:
			  printf("Warning.");
			  break;
		  case RPLIDAR_STATUS_ERROR:
			  printf("Error.");
			  break;
		  }
		  printf(" (errorcode: %d)\n", healthinfo.error_code);

	  }
	  else {
		  fprintf(stderr, "Error, cannot retrieve the lidar health code: %x\n", op_result);
		  break;
	  }


	  if (healthinfo.status == RPLIDAR_STATUS_ERROR) {
		  fprintf(stderr, "Error, rplidar internal error detected. Please reboot the device to retry.\n");
		  // enable the following code if you want rplidar to be reboot by software
		  // drv->reset();
		  break;
	  }

  } while (0);

  drv->startMotor();

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RPlidarRTC::onDeactivated(RTC::UniqueId ec_id)
{

	drv->stop();
	drv->stopMotor();

	RPlidarDriver::DisposeDriver(drv);

  return RTC::RTC_OK;
}

u_result capture_and_display(RPlidarDriver * drv, RTC::RangeData data)
{
	u_result ans;

	rplidar_response_measurement_node_t nodes[8192];
	size_t   count = _countof(nodes);

	printf("waiting for data...\n");

	// fetech extactly one 0-360 degrees' scan
	ans = drv->grabScanData(nodes, count);
	if (IS_OK(ans) || ans == RESULT_OPERATION_TIMEOUT) {
		drv->ascendScanData(nodes, count);

		int key = getchar();
		for (int pos = 0; pos < (int)count; ++pos) {
			printf("%s theta: %03.2f Dist: %08.2f \n",
				(nodes[pos].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT) ? "S " : "  ",
				(nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f,
				nodes[pos].distance_q2 / 4.0f);
		}
	}
	else {
		printf("error code: %x\n", ans);
	}

	return ans;
}


RTC::ReturnCode_t RPlidarRTC::onExecute(RTC::UniqueId ec_id)
{
	// take only one 360 deg scan and display the result as a histogram
	////////////////////////////////////////////////////////////////////////////////
	if (IS_FAIL(drv->startScan(0, 1))) // you can force rplidar to perform scan operation regardless whether the motor is rotating
	{
		fprintf(stderr, "Error, cannot start the scan operation.\n");

	}

	/*if (IS_FAIL(capture_and_display(drv))) {
		fprintf(stderr, "Error, cannot grab scan data.\n");

	}*/

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RPlidarRTC::onAborting(RTC::UniqueId ec_id)
{
	drv->stop();
	drv->stopMotor();

	RPlidarDriver::DisposeDriver(drv);

  return RTC::RTC_OK;
}



RTC::ReturnCode_t RPlidarRTC::onError(RTC::UniqueId ec_id)
{
	drv->stop();
	drv->stopMotor();

	RPlidarDriver::DisposeDriver(drv);

  return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t RPlidarRTC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RPlidarRTC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RPlidarRTC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RPlidarRTCInit(RTC::Manager* manager)
  {
    coil::Properties profile(rplidarrtc_spec);
    manager->registerFactory(profile,
                             RTC::Create<RPlidarRTC>,
                             RTC::Delete<RPlidarRTC>);
  }
  
};


