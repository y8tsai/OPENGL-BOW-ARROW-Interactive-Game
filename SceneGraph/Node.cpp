#include "Node.h"
#include "Globals.h"
#include "Window.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void Node::drawBoundingSphere(vec3 C)
{
	mat4 transSphere;
	transSphere = transSphere.translate( center + C);
	glPushMatrix();
	glMultMatrixf( transSphere.ptr() );
	glColor3f(1.0, 1.0, 1.0);
	glutWireSphere(radius, 10, 10);  //render a unit sphere
	glPopMatrix();
}

//bool Node::culling(vec3 Center, float Radius)
//{
//
//	center = Globals::camera.getInverseMatrix() * center;
//	//naming conventions n = near , f = far, t = top, b= bottom, l = left, r= right , c = center 
//
//	float Hnear = 2 * tan(Window::viewAngle * 3.141592 / 360) * Window::nearDist;
//	float Wnear = Hnear * (Window::width / Window::height);
//	//Code Taken From Lighthouse3D tutorial about culling
//
//	float Hfar = 2 * tan(Window::viewAngle * 3.141592 / 360) * Window::farDist;
//	float Wfar = Hfar * (Window::width / Window::height);
//
//	Vector3 p = Globals::camera.e;
//	Vector3 d = (Globals::camera.d - Globals::camera.e).normalize();
//	Vector3 up = Globals::camera.up.normalize();
//	Vector3 right = up.cross(d).normalize();
//
//	//farplane center point
//	Vector3 fc = p + d * Window::farDist;
//
//	//computer 4 corners of the far plane
//	Vector3 ftl = fc + (up * (Hfar/2) ) - (right * (Wfar/2) );
//	Vector3 ftr = fc + (up * (Hfar / 2)) + (right * (Wfar / 2));
//	Vector3	fbl = fc - (up * (Hfar / 2)) - (right * (Wfar / 2));
//	Vector3	fbr = fc - (up * (Hfar / 2)) + (right * (Wfar / 2));
//
//	//nearplane center point
//	Vector3 nc = p + d * Window::nearDist;
//
//	//compute 4 corners of the near plane
//	Vector3	ntl = nc + (up * (Hnear / 2)) - (right * (Wnear / 2));
//	Vector3	ntr = nc + (up * (Hnear / 2)) + (right *(Wnear / 2));
//	Vector3	nbl = nc - (up * (Hnear / 2)) - (right * (Wnear / 2));
//	Vector3	nbr = nc - (up * (Hnear / 2)) + (right * (Wnear / 2));
//
//	//for near and far planes we can use d and -d respective for normals and nc and fc for point
//
//	//for the other 4 planes, we'll use point ntl for left and top, point nbr for right and bottom
//
//	//calc bottom normal (pointing inwards)
//	Vector3 first = fbr - nbr;
//	Vector3 second = nbl - nbr;
//	Vector3 bottomNormal = first.cross(second).normalize();
//
//	//calc right normal (pointing inwards)
//	second = ntr - nbr; 
//	Vector3 rightNormal = second.cross(first).normalize();
//
//	//calc top normal (pointing inwards)
//	first = ntl - ntr;
//	second = ftr - ntr;
//	Vector3 topNormal = first.cross(second).normalize();
//
//	//calc left normal (pointing inwards)
//	first = nbl - ntl;
//	second = ftl - ntl;
//	Vector3 leftNormal = first.cross(second).normalize();
//
//	Vector3 nearNormal = d;
//	Vector3 farNormal = d.scale(-1);
//
//	if ((Center - nc).dot(nearNormal) < Radius )
//		return true;
//
//	if ((Center - fc).dot(farNormal) < Radius)
//		return true;
//	
//	if ((Center - ntl).dot(leftNormal) < Radius)
//		return true;
//
//	if ((Center - ntl).dot(topNormal) < Radius)
//		return true;
//	
//	if ((Center - ntr).dot(leftNormal) < Radius)
//		return true;
//
//	if ((Center - nbr).dot(bottomNormal) < Radius)
//		return true;
//
//	return false;
//}

void Node::setMatrix(mat4)
{
	//do nothing
}


mat4 Node::getMatrix()
{
	mat4 newMatrix;
	return newMatrix;
}