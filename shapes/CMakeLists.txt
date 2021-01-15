cmake_minimum_required( VERSION 3.0 )

set( CMAKE_PROJECT_NAME Shapes )

project( ${CMAKE_PROJECT_NAME} )

set( CMAKE_AUTOUIC ON )
set( CMAKE_AUTOMOC ON )

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

if( VS2008 )
	add_definitions( -Dunique_ptr=auto_ptr -Dnullptr=NULL )
	find_package( Qt4 COMPONENTS QtCore QtGui REQUIRED )
	include( ${QT_USE_FILE} )
else()
	find_package( QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED )
	find_package( Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED )
	set( QT_LIBRARIES Qt${QT_VERSION_MAJOR}::Widgets )
endif()
   

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

add_executable( Shapes
	src/main.cpp
	src/MainWindow.h
	src/MainWindow.cpp
	src/model.h
	src/model.cpp
	src/MainWindow.ui
)

target_compile_definitions( Shapes PRIVATE
	-D_USE_MATH_DEFINES
)

target_link_libraries( Shapes ${QT_LIBRARIES} )
