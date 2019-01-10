CXX		= g++
CXXFLAGS	= -fPIC
LDFLAGS 	= -O2 -shared 

INCLUDE_PATH	= -I/usr/local/include/mmdpi -I/usr/local/include/bullet -I/usr/include/bullet -I/usr/include/python2.7 -I/usr/include/python3.5
LIBRARY_PATH	= -L/usr/local/lib -L/usr/lib -L/usr/local/lib/mmdpi

LIBRARY_IMG	= -lpng -ljpeg
LIBMMDPI	= -lmmdpis

PHYSICLIB	= -lLinearMath -lBulletSoftBody -lBulletDynamics -lBulletCollision
BOOSTPY		= -lboost_python

CXXFILE 	= mmdpipy.cpp
OBJECTS		= $(CXXFILE:.cpp=.o)

PROGRAM		= mmdpipy.so

PILIB		= -lGLESv2 -lEGL -lbcm_host -L/opt/vc/lib
PIINC		= -I/opt/vc/include/interface/vmcs_host/linux \
		-I/opt/vc/include \
		-I/opt/vc/include/interface/vcos/pthreads
NPILIB		= -lGLEW -lglut -lGLU -lGL

OPTION		= -D_MMDPI_USING_PHYSICS_ENGINE_
LIBRATYS_PI	= $(LIBRARY_PATH) $(PHYSICLIB) $(PILIB) $(LIBRARY_IMG) $(LIBMMDPI)
LIBRATYS_NPI	= $(LIBRARY_PATH) $(PHYSICLIB) $(NPILIB) $(LIBRARY_IMG) $(LIBMMDPI)

all: $(PROGRAM)

$(PROGRAM): $(CXXFILE)
	$(CXX) $(CXXFLAGS) $(OPTION) -c $(CXXFILE) $(INCLUDE_PATH) -o $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBRATYS_NPI) $(BOOSTPY) -o $(PROGRAM)

pi: $(CXXFILE)
	$(CXX) $(CXXFLAGS) -D_MMDPI_OPENGL_ES_DEFINES_ $(OPTION) -c $(CXXFILE) $(PIINC) $(INCLUDE_PATH) -o $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBRATYS_PI) $(BOOSTPY) -o $(PROGRAM)

clean:
	\rm -rf *.o *.mod *.so
