set(sdk_srcs src/rplidar_driver.cpp)
set(sdk_headers src/rplidar_driver_impl.h)
set(sdk_common src/sdkcommon.h)
set(thread src/hal/thread.cpp)

include_directories(src)
include_directories(include)
if(WIN32)
set(arch_srcs src/arch/win32/net_serial.cpp src/arch/win32/net_socket.cpp src/arch/win32/timer.cpp)
endif()
add_library(rplidar_sdk STATIC ${sdk_srcs}
  ${sdk_headers} ${arch_srcs} ${sdk_common} ${thread})


install(TARGETS rplidar_sdk 
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${INSTALL_PREFIX} COMPONENT component
    LIBRARY DESTINATION ${INSTALL_PREFIX} COMPONENT component
    ARCHIVE DESTINATION ${INSTALL_PREFIX} COMPONENT component)

