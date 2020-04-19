// -*- C++ -*-
/*!
 * @file  RPlidarRTCTest.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "RPlidarRTCTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rplidarrtc_spec[] =
  {
    "implementation_id", "RPlidarRTCTest",
    "type_name",         "RPlidarRTCTest",
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
    "conf.default.port_name", ""COM1"",
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
RPlidarRTCTest::RPlidarRTCTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_scan_dataOut("scan_data", m_scan_data)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RPlidarRTCTest::~RPlidarRTCTest()
{
}



RTC::ReturnCode_t RPlidarRTCTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("scan_data", m_scan_dataIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("port_name", m_port_name, ""COM1"");
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
RTC::ReturnCode_t RPlidarRTCTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RPlidarRTCTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RPlidarRTCTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RPlidarRTCTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RPlidarRTCTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RPlidarRTCTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RPlidarRTCTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RPlidarRTCTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RPlidarRTCTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RPlidarRTCTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RPlidarRTCTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RPlidarRTCTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(rplidarrtc_spec);
    manager->registerFactory(profile,
                             RTC::Create<RPlidarRTCTest>,
                             RTC::Delete<RPlidarRTCTest>);
  }
  
};


