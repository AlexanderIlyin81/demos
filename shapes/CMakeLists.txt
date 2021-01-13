cmake_minimum_required( VERSION 3.0 )

set( CMAKE_PROJECT_NAME Shapes )

project( ${CMAKE_PROJECT_NAME} )

# Каталог для собранных программ и скриптов.
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin" )

set( CMAKE_BUILD_TYPE Release )
message( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )

if( MSVC )
	if (DEFINED CMAKE_C_FLAGS_RELEASE)
		string(REGEX REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
		string(REGEX REPLACE "/MD" "/MT" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
	endif (DEFINED CMAKE_C_FLAGS_RELEASE)
	if (DEFINED CMAKE_CXX_FLAGS_RELEASE)
		string(REGEX REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
		string(REGEX REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
	endif (DEFINED CMAKE_CXX_FLAGS_RELEASE)
endif()

find_package( Qt4 COMPONENTS QtCore QtGui REQUIRED )
   
include( ${QT_USE_FILE} )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

set( MOC_SOURCES
	src/MainWindow.h
)

set( UI_HEADERS
	src/UI/MainWindow.ui
)

#Create MOC files
qt4_wrap_cpp( MOCED_SOURCES
	${MOC_SOURCES}
)

#Create headers from .ui files
qt4_wrap_ui( UI_HEADERS 
	${UI_HEADERS}
)

add_executable( Shapes
	src/main.cpp
	src/MainWindow.h
	src/MainWindow.cpp
	src/model.h
	src/model.cpp
	${MOCED_SOURCES}
	${UI_HEADERS}
)

target_link_libraries( Shapes ${QT_LIBRARIES} )
