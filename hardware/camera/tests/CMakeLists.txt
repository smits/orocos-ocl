DEPENDENT_OPTION( BUILD_CAMERA_TEST "Build CameraComponents Test" OFF "BUILD_CAMERA;BUILD_TESTS" OFF)

IF ( BUILD_TESTS)

IF ( BUILD_CAMERA_TEST )

INCLUDE(${PROJ_SOURCE_DIR}/config/FindGthread.cmake)
INCLUDE(${PROJ_SOURCE_DIR}/config/FindGTK+-2.0.cmake)

IF(GTHREAD_FOUND AND GTK_FOUND)
    # This gathers all the .cpp files into the variable 'SRCS'
    FILE( GLOB SRCS [^.]*.cpp )

    # Add a test program
    GLOBAL_ADD_TEST( camera ${SRCS} )
    # Use  TARGET_LINK_LIBRARIES( report libs... ) to add library deps.
    PROGRAM_ADD_DEPS( camera orocos-taskbrowser orocos-camera)
  ELSE(GTHREAD_FOUND AND GTK_FOUND)
    MESSAGE(WARNING "Could not find needed libs for camera-test")
  ENDIF(GTHREAD_FOUND AND GTK_FOUND)
  
ENDIF ( BUILD_CAMERA_TEST )
ENDIF ( BUILD_TESTS)