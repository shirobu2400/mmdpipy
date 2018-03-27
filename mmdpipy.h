
#define BOOST_PYTHON_STATIC_LIB
#include "mmdpi.h"
#include <boost/python.hpp>


class mmdpipy
{
private:
	mmdpi*		pm;

public:
	typedef struct
	{
		float m[ 16 ];
	} Mat4;
	Mat4	VpMatrix;

	bool load( const char* name );
	bool vmdload( const char* name );
	void draw( void );

	void set_bonerotX( const char* bone_name, float rotx );
	void set_bonerotY( const char* bone_name, float roty );
	void set_bonerotZ( const char* bone_name, float rotz );

	void set_bonepos( const char* bone_name, float x, float y, float z );
	void set_bone( const char* bone_name, const float* matrix );

	/*
	** 透視投影行列
	*/
	void perspectiveMatrix(float left, float right,
	                       float top, float bottom,
	                       float near, float far,
	                       Mat4 *matrix4);
	void set_projection_matrix( float width, float height );

	void step01( void );

	mmdpipy();
	~mmdpipy();
};
