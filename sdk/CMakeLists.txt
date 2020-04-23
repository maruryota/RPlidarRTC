set(sdk_srcs src/rplidar_driver.cpp)
set(sdk_headers src/rplidar_driver_impl.h)

add_library(rplidar_sdk SHARED ${sdk_srcs}
  ${sdk_headers})


install(TARGETS rplidar_sdk 
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${INSTALL_PREFIX} COMPONENT component
    LIBRARY DESTINATION ${INSTALL_PREFIX} COMPONENT component
    ARCHIVE DESTINATION ${INSTALL_PREFIX} COMPONENT component)

