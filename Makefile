CXX		= g++
CXXFLAGS	= -Os -Wall
INCLUDE		= -I/usr/include/python2.7 -I/usr/include/python3.5 -I/usr/local/include/mmdpi
LIBFOLDER	= -L/usr/local/lib/mmdpi/
CXXFILE 	= mmdpipy.cpp
LIBFILE		= -lboost_python -lmmdpis -lBulletCollision -lBulletDynamics -lLinearMath -lBulletSoftBody -lGLEW -lglut -lGLU -lGL -lpng -ljpeg
PROGRAM		= mmdpipy.so

all: $(PROGRAM)

$(PROGRAM): $(CXXFILE)
	$(CXX) -fPIC $(CXXFILE) $(LIBFOLDER) $(LIBFILE) -shared -o $(PROGRAM) $(INCLUDE)

install: $(PROGRAM)
	rm /usr/local/lib/libmmdpis.so
	ln -s /usr/local/lib/mmdpi/libmmdpis.so /usr/local/lib/
	ldconfig

clean:
	\rm -rf *.o *.mod *.so
