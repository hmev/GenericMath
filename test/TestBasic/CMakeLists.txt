set(EXEC_NAME TestBasic)

set( CMAKE_CXX_FLAGS "-std=c++11" )
#set( CMAKE_CXX_COMPILER "-Wdeprecated-declarations")
#set( CMAKE_WARN_DEPRECATED FALSE)
#add_definitions(-DGL_SILENCE_DEPRECATION)

include_directories(
    ${PROJECT_SOURCE_DIR}/source
    ${GTEST_INCLUDE_DIR}
)

set(SOURCE_LIST 
    main.cpp 
    Vector.cpp 
    Array.cpp 
    Matrix.cpp 
    Index.cpp 
    Complex.cpp 
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
  
add_executable(${EXEC_NAME} ${SOURCE_LIST})

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set_property(TARGET ${EXEC_NAME} PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
ELSE()
ENDIF()

target_link_libraries(${EXEC_NAME} ${GTEST_LIBRARY_DEBUG} ${CMAKE_THREAD_LIBS_INIT})
#target_link_libraries(${EXEC_NAME} pThread)