# cmake version
cmake_minimum_required(VERSION 2.6)

# project name option(C=C, CXX=C++)
project(mmdpipy CXX)

# Release option
set(CMAKE_CXX_FLAG_RELEASE "-O2 -fPIC")

# Debug option
# set(CMAKE_CXX_FLAG_DEBUG "-g")

# compile type
set(CMAKE_BUILD_TYPE Release)

# mmdpipy version
set(SERIAL "1.10.00")

# source
set(mmdpipy_src ${mmdpipy_src} mmdpipy.cpp )

# Include Directory
set(mmdpipy_inc_path
	/usr/local/include
	/usr/include
	/usr/local/include/mmdpi/
	/usr/include/bullet/
	/usr/include/bullet/BulletDynamics/
	/usr/include/bullet/BulletSoftBody/
	/usr/include/bullet/LinearMath/
	/usr/include/bullet/BulletCollision/
)

set(mmdpipy_lib_path
	/usr/local/lib/
	/usr/lib/
	/usr/local/lib/mmdpi/
)

set( mmdpipy_lib )

# OpenGL
find_package( PNG REQUIRED )
find_package( JPEG REQUIRED )
find_package( GLUT )
find_package( glut )
find_package( freeglut )
if( NOT GLUT_FOUND AND NOT glut_FOUND AND NOT freeglut_FOUND )
	add_definitions( -D_MMDPI_OPENGL_ES_DEFINES_ )
	add_definitions( -D_MMDPI_PRIJECTION_MATRIX_SELF_ )
endif()

# Bullet
if( bullet )
	add_definitions( -D_mmdpipy_USING_PHYSICS_ENGINE_ )
	include_directories( Bullet_INCLUDE_DIRS /usr/local/include/bullet )
	set( mmdpipy_lib ${mmdpipy_lib} BulletDynamics BulletCollision BulletSoftBody LinearMath )
endif()

# Outline
# It needs a lot of VRAM.
if( outline )
	add_definitions( -D_mmdpipy_OUTLINE_ )
endif()


find_package( GLUT )
find_package( glut )
find_package( freeglut )

#find_package( GLESv2 )
#find_package( EGL )
#find_package( bcm_host )	# Raspberry pi graphics driver

find_package( PNG REQUIRED )
find_package( ZLIB REQUIRED )
find_package( JPEG REQUIRED )

if( NOT WIN32 )
	set( mmdpipy_lib ${mmdpipy_lib}
		rt m
	)
endif()

set(mmdpipy_inc_path ${mmdpipy_inc_path}
	${PNG_INCLUDE_DIRS}
	${ZLIB_INCLUDE_DIRS}
	${JPEG_INCLUDE_DIR}
)

# Opengl Mode

# OpenGL ES
if( GLUT_FOUND OR glut_FOUND OR freeglut_FOUND )
	set( mmdpipy_lib ${mmdpipy_lib} GL GLU GLEW )

else()
	add_definitions( -D_mmdpipy_OPENGL_ES_DEFINES_ )
	add_definitions( -D_mmdpipy_PRIJECTION_MATRIX_SELF_ )
	if( pi )
		set( mmdpipy_lib_path ${mmdpipy_lib_path} /opt/vc/lib )
	endif()
	set( RASPGL_LIBRARIES GLESv2 EGL )
	if( pi )
		set( RASPGL_LIBRARIES ${RASPGL_LIBRARIES} bcm_host )
	endif()

endif()

if( x64 )
	add_definitions( -D_mmdpipy_AMD64BIT_ )
else()
	set( CMAKE_CXX_FLAG ${CMAKE_CXX_FLAG} -m32 )
endif()

# Raspberry Pi
set(mmdpipy_inc_path
	${mmdpipy_inc_path}
	/opt/vc/include/interface/vmcs_host/linux
	/opt/vc/include
	/opt/vc/include/interface/vcos/pthreads
)

set( mmdpipy_lib
	${mmdpipy_lib}

	${GLUT_LIBRARIES}
	${glut_LIBRARIES}
	${freeglut_LIBRARIES}
)

# boost-python
set( mmdpipy_lib ${mmdpipy_lib} python2.7 boost_python )
set( mmdpipy_lib_path ${mmdpipy_lib_path} /usr/lib/x86_64-linux-gnu )
set( mmdpipy_inc_path ${mmdpipy_inc_path} /usr/include/python2.7 /usr/include/x86_64-linux-gnu )

# link static library
link_directories( ${mmdpipy_lib_path} )
include_directories( ${mmdpipy_inc_path} )
add_library( mmdpipy SHARED ${mmdpipy_src} )

# rename
set_target_properties(mmdpipy PROPERTIES PREFIX "")
set_target_properties(mmdpipy PROPERTIES OUTPUT_NAME mmdpipy)

target_link_libraries( mmdpipy
	mmdpis
	${m_LIBRARIES} ${rt_LIBRARIES}
	${PNG_LIBRARIES} ${ZLIB_LIBRARIES} ${JPEG_LIBRARIES}
	${mmdpipy_lib} ${RASPGL_LIBRARIES}
)

# output .so
set_property(TARGET mmdpipy PROPERTY POSITION_INDEPENDENT_CODE ON)
install(TARGETS mmdpipy LIBRARY DESTINATION lib/mmdpi)

