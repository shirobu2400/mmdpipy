
#define BOOST_PYTHON_STATIC_LIB
#include "mmdpi.h"
#include "mmdpipy.h"
#include <boost/python.hpp>


bool mmdpipy::load( const char* name )
{
	if( pm->load( name ) )
		return false;
	return true;
}
bool mmdpipy::vmdload( const char* name )
{
	if( pm->vmd_load( name ) )
		return false;
	return true;
}
void mmdpipy::draw( void )
{
	if( pm )
		pm->draw();
}

void mmdpipy::set_bonerotX( const char* bone_name, float rotx )
{
	mmdpiMatrix	matrix;
	matrix.rotation( 1, 0, 0, rotx );
	if( pm )
		pm->set_bone_matrix( bone_name, matrix );
}

void mmdpipy::set_bonerotY( const char* bone_name, float roty )
{
	mmdpiMatrix	matrix;
	matrix.rotation( 0, 1, 0, roty );
	if( pm )
		pm->set_bone_matrix( bone_name, matrix );
}

void mmdpipy::set_bonerotZ( const char* bone_name, float rotz )
{
	mmdpiMatrix	matrix;
	matrix.rotation( 0, 0, 1, rotz );
	if( pm )
		pm->set_bone_matrix( bone_name, matrix );
}

void mmdpipy::set_bonepos( const char* bone_name, float x, float y, float z )
{
	mmdpiMatrix	matrix;
	matrix.transelation( x, y, z );
	if( pm )
		pm->set_bone_matrix( bone_name, matrix );
}

void mmdpipy::set_bone( const char* bone_name, const float* matrix )
{
	mmdpiMatrix	m;

	m._11 = matrix[ 0];
	m._12 = matrix[ 1];
	m._13 = matrix[ 2];
	m._14 = matrix[ 3];

	m._21 = matrix[ 4];
	m._22 = matrix[ 5];
	m._23 = matrix[ 6];
	m._24 = matrix[ 7];

	m._31 = matrix[ 8];
	m._32 = matrix[ 9];
	m._33 = matrix[10];
	m._34 = matrix[11];

	m._41 = matrix[12];
	m._42 = matrix[13];
	m._43 = matrix[14];
	m._44 = matrix[15];

	if( pm )
		pm->set_bone_matrix( bone_name, m );
}

/*
** 透視投影行列
*/
void mmdpipy::perspectiveMatrix(float left, float right,
			float top, float bottom,
			float near, float far,
			Mat4 *matrix4)
{
	float dx = right - left;
	float dy = bottom - top;
	float dz = far - near;

	GLfloat* matrix = matrix4->m;

	matrix[ 0] =  2.0f * near / dx;
	matrix[ 5] =  2.0f * near / dy;
	matrix[ 8] =  (right + left) / dx;
	matrix[ 9] =  (top + bottom) / dy;
	matrix[10] = -(far + near) / dz;
	matrix[11] = -1.0f;
	matrix[14] = -2.0f * far * near / dz;
	matrix[ 1] = matrix[ 2] = matrix[ 3] = matrix[ 4] =
	matrix[ 6] = matrix[ 7] = matrix[12] = matrix[13] = matrix[15] = 0.0f;
}

void mmdpipy::set_projection_matrix( float width, float height )
{
	float	aspect = ( float )width / ( float )height;
	float	dw = 0.5f * aspect;
	float	dh = 0.5f;
	perspectiveMatrix( -dw, +dw, -dh, +dh, 1, 160, &VpMatrix );
	pm->set_projection_matrix( VpMatrix.m );
}

void mmdpipy::step01( void )
{
	if( pm->get_vmd( 0 ) )
		( *pm->get_vmd( 0 ) ) += 1.0;
}

mmdpipy::mmdpipy()
{
	pm = new mmdpi();
}
mmdpipy::~mmdpipy()
{
	delete pm;
}


BOOST_PYTHON_MODULE( mmdpipy )
{
	boost::python::class_<mmdpipy>( "mmdpipy", boost::python::init<>() )
	.def( "load", &mmdpipy::load )
	.def( "vmdload", &mmdpipy::vmdload )
	.def( "draw", &mmdpipy::draw )
	.def( "setBone", &mmdpipy::set_bone )
	.def( "bonePos", &mmdpipy::set_bonepos )
	.def( "boneRotX", &mmdpipy::set_bonerotX )
	.def( "boneRotY", &mmdpipy::set_bonerotY )
	.def( "boneRotZ", &mmdpipy::set_bonerotZ )
	.def( "setProjectionMatrix", &mmdpipy::set_projection_matrix )
	.def( "step01", &mmdpipy::step01 )
	// .def( "set_fps", &mmdpipy::set_fps )
	;
}