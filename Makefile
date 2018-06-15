CXX		= g++
CXXFLAGS	= -Os -Wall
INCLUDE		= -I/usr/include/python2.7 -I/usr/include/python3.5 -I/usr/local/include/mmdpi
LIBFOLDER	= -L/usr/local/lib/mmdpi/
CXXFILE 	= mmdpipy.cpp
LIBFILE		= -lboost_python -lmmdpis -lBulletCollision -lBulletDynamics -lLinearMath -lBulletSoftBody -lGLEW -lglut -lGLU -lGL -lpng -ljpeg
PROGRAM		= mmdpipy.so

PILIB		= -lGLESv2 -lEGL -lbcm_host -L/opt/vc/lib
PIINC		= -I/opt/vc/include/interface/vmcs_host/linux \
		-I/opt/vc/include \
		-I/opt/vc/include/interface/vcos/pthreads

all: $(PROGRAM)

$(PROGRAM): $(CXXFILE)
	$(CXX) -fPIC $(CXXFILE) $(LIBFOLDER) $(LIBFILE) -shared -o $(PROGRAM) $(INCLUDE)

pi: $(CXXFILE)
	$(CXX) -fPIC -D_MMDPI_OPENGL_ES_DEFINES_ $(CXXFILE) $(LIBFOLDER) $(PILIB) $(LIBFILE) -shared -o $(PROGRAM) $(INCLUDE) $(PIINC)

install: $(PROGRAM)
	ldconfig

clean:
	\rm -rf *.o *.mod *.so
