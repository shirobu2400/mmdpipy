#!/usr/bin/python
#-*-coding:utf-8-*-

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys

import mmdpipy

pmm = mmdpipy.mmdpipy()
RotationAxis = [0,0,0]

def IdentityMatrix():
	m = [0] * 16
	m[ 0] = 1
	m[ 5] = 1
	m[10] = 1
	m[15] = 1
	return m

def display():
	""" display """
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	glMatrixMode(GL_MODELVIEW)
	glLoadIdentity()
	##set camera
	gluLookAt(0.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
	##draw a teapot
	glColor3f(1.0, 0.0, 0.0)

	glPushMatrix()
	"""  /**** **** **** **** **** **** **** ****/  """

	glRotatef( RotationAxis[0], 1, 0, 0 );
	glRotatef( RotationAxis[1], 0, 1, 0 );

	glScalef( 0.1, 0.1, 0.1 );

	# ボーン名でもいじれる
	pmm.boneRotY( b"センター", 3.14 )
	pmm.bonePos( b"センター", 0, -8.0, +16.0 )

	pmm.draw()

	"""  /**** **** **** **** **** **** **** ****/  """
	glPopMatrix()

	#    glutSolidTeapot(1.0)  # solid
	# glFlush()  # enforce OpenGL command
	glutSwapBuffers()

def timer( value ):
	glutTimerFunc( 1000 / 30, timer, 0 );
	pmm.step01()
	glutPostRedisplay();

def reshape(width, height):
	"""callback function resize window"""
	glViewport(0, 0, width, height)
	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	gluPerspective(45.0, float(width)/float(height), 0.1, 100.0)

def argv_find(argv, option):
	for i in range(len(argv)):
		if argv[i] == option:
			if i + 1 < len(argv):
				return argv[i+1]
			return argv[i]
	return 0x00

def init(width, height):
	""" initialize """
	glClearColor(0.0, 0.0, 0.0, 1.0)
	glEnable(GL_DEPTH_TEST) # enable shading

	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	##set perspective
	gluPerspective(45.0, float(width)/float(height), 0.1, 100.0)

	model = argv_find(sys.argv, "-p")
	if model != 0x00 and not pmm.load(model):
		print( "model load error." )
		exit(0)
	motion = argv_find(sys.argv, "-v")
	if motion != 0x00 and not pmm.vmdload(motion):
		print( "motion load error." )
		exit(0)

def main():        	
	windw_width  = 300
	windw_height = 300

	glutInit(sys.argv)
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH)
	glutInitWindowSize(windw_width, windw_height)           # window size
	glutInitWindowPosition(100, 100)                        # window position
	glutCreateWindow(b"mmdpipy")                            # show window
	glutDisplayFunc(display)                                # draw callback function
	glutReshapeFunc(reshape)                                # resize callback function
	init(windw_width, windw_height)
	glutTimerFunc( 1000 / 60, timer, 0 );
	glutMainLoop()

if __name__ == '__main__':
	main()