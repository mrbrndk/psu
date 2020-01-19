#pragma comment(lib, "D:/Programs/OpenGL/glut32.lib")
#pragma comment(lib, "D:/Programs/OpenGL/glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <D:/Programs/OpenGL/glut.h>
#include <D:/Programs/OpenGL/glaux.h>
#include <cmath>
#include <iostream>

GLint width = 400;
GLint height = 400;

GLfloat coef = 0.0;

float x = 0.0, z = 0.0;
float lx = 0.0, lz = -1.0;
float angle = 0.0, deltaAngle = 0.0;
int xOrigin = -1;

AUX_RGBImageRec MyBitmap;
GLuint TexID;

GLfloat coord[11][2] = {
	{ -0.21,	0.67 },
	{ 0.21,		0.67 },
	{ 0.67,		-0.67 },
	{ 0.26,		-0.67 },
	{ 0.21,		-0.46 },
	{ -0.21,	-0.46 },
	{ -0.26,	-0.67 },
	{ -0.67,	-0.67 },
	{ 0.00,		0.32 },
	{ 0.14,		-0.21 },
	{ -0.14,	-0.21 }, };

GLfloat shift[11][2];

GLvoid renderScene(GLvoid);
GLvoid reshape(GLint w, GLint h);
GLvoid button(GLint button, GLint state, GLint x, GLint y);
GLvoid motion(GLint x, GLint y);
GLvoid animation(GLint value);

GLint main(GLint argc, GLbyte **argv)
{
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("������������ ������ �8");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderScene);
	glutMouseFunc(button);
	glutMotionFunc(motion);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, animation, 0);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//������������ � *.bmp �� �����
	glGenTextures(1, &TexID);//�������� �������������� ��� ��������
	AUX_RGBImageRec *pImage = auxDIBImageLoad(L"1.bmp");//�������� ����������� � ������

	void *BmpBits = pImage->data;

	glBindTexture(GL_TEXTURE_2D, TexID);//������ �������� ������� ��������
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pImage->sizeX, pImage->sizeY, GL_RGB,
		GL_UNSIGNED_BYTE, BmpBits);//�������� ������� ����������� � ������������� ��������

	//--���������� ��������� ���� �������� �� quadric-�������-------------//
	//--������� ���������� ��������---------------------------------------//
	//--������ ����������� �� ��������������� ���� s � t------------------//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//--�� ������������ ������������ ��� ������ ����� �� ��������---------//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//--��������� �������� � �������� �������-----------------------------//
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glutMainLoop();//�������� ����
	return 1;
}

GLvoid renderScene(GLvoid)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(x, 0.0, z,
		x + lx, 0.5, z + lz,
		0.0, 1.0, 0.0);

	glEnable(GL_TEXTURE_2D);
	glNormal3f(0.0, 0.0, 1.0);

	glBegin(GL_QUADS);
	for (int i = 0, j = 0; i < 8; i++)
	{
		j = (i + 1 < 8) ? i + 1 : 0;
		glTexCoord2f(1.0, 0.0);
		glVertex3f(shift[i][0], shift[i][1], 0.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(shift[j][0], shift[j][1], 0.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(shift[j][0], shift[j][1], 0.3);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(shift[i][0], shift[i][1], 0.3);
	}
	glEnd();

	glBegin(GL_QUADS);
	for (int i = 8, j = 8; i < 11; i++)
	{
		j = (i + 1 < 11) ? i + 1 : 8;
		glTexCoord2f(1.0, 0.0);
		glVertex3f(shift[i][0], shift[i][1], 0.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(shift[j][0], shift[j][1], 0.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(shift[j][0], shift[j][1], 0.3);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(shift[i][0], shift[i][1], 0.3);
	}
	glEnd();

	int seq[6][4] = {	{ 1, 2, 9, 9 },
						{ 1, 9, 11, 8 },
						{ 9, 2, 3, 10 },
						{ 8, 11, 6, 7 },
						{ 10, 3, 4, 5 },
						{ 11, 10, 5, 6 } };
						
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++)
	{
		glTexCoord2f(1.0, 0.0);
		glVertex3f(shift[seq[i][0] - 1][0], shift[seq[i][0] - 1][1], 0.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(shift[seq[i][1] - 1][0], shift[seq[i][1] - 1][1], 0.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(shift[seq[i][2] - 1][0], shift[seq[i][2] - 1][1], 0.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(shift[seq[i][3] - 1][0], shift[seq[i][3] - 1][1], 0.0);
	}
	glEnd();

	
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++)
	{
		glTexCoord2f(1.0, 0.0);
		glVertex3f(shift[seq[i][0] - 1][0], shift[seq[i][0] - 1][1], 0.3);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(shift[seq[i][1] - 1][0], shift[seq[i][1] - 1][1], 0.3);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(shift[seq[i][2] - 1][0], shift[seq[i][2] - 1][1], 0.3);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(shift[seq[i][3] - 1][0], shift[seq[i][3] - 1][1], 0.3);
	}
	glEnd();

	glutSwapBuffers();
	glFlush(); //�������� ��� ������� ������ � ������ OpenGL
}

GLvoid reshape(GLint w, GLint h)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLvoid button(GLint button, GLint state, GLint x, GLint y)
{
	// ������ ��� ������ ��������, ���� ������ ����� ������
	if (button == GLUT_LEFT_BUTTON)
	{
		//����� ������	��������
		if (state == GLUT_UP)
		{
			angle += deltaAngle;
			xOrigin = -1;
		}
		else
		{// state = GLUT_DOWN
			xOrigin	= x;
		}
	}
}

GLvoid motion(GLint x, GLint y)
{
	// ����� ����� ������ ������
	if (xOrigin >= 0)
	{
		// �������� deltaAngle
		deltaAngle = (x - xOrigin) * 0.01f;
		//  �������� ��������� ������
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
		//� �������� ��� ��� �����������
		glutPostRedisplay();
	}
}

GLvoid animation(GLint value)
{
	for (int i = 0; i < 11; i++)
	{
		shift[i][0] = coord[i][0] * sin(coef);
		shift[i][1] = coord[i][1] * sin(coef);
	}
	coef += 0.01;
	glutPostRedisplay();
	glutTimerFunc(20, animation, 0);
}