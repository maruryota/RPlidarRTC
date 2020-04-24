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
  RPlidarDriver * drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
  
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
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RPlidarRTC::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RPlidarRTC::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RPlidarRTC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RPlidarRTC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

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


