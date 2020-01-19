#pragma comment(lib, "D:/Programs/OpenGL/glut32.lib")
#include <D:/Programs/OpenGL/glut.h>
#include <cmath>

GLint width = 400;
GLint height = 400;

GLfloat shift[11][2] = {
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

GLvoid renderScene(GLvoid);
GLvoid reshape(GLint w, GLint h);

GLint main(GLint argc, GLbyte **argv)
{
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("Лабораторная работа №7");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
	glutMainLoop();//основной цикл
	return 1;
}

GLvoid renderScene(GLvoid)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glRotatef(-25.0, 1.0, 0.0, 0.0);
	glRotatef(-25.0, 0.0, 1.0, 0.0);

	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	for (int i = 0, j = 0; i < 8; i++)
	{
		j = (i + 1 < 8) ? i + 1 : 0;
		glVertex3f(shift[i][0], shift[i][1], 0.0);
		glVertex3f(shift[j][0], shift[j][1], 0.0);
		glVertex3f(shift[j][0], shift[j][1], 0.3);
		glVertex3f(shift[i][0], shift[i][1], 0.3);
	}
	glEnd();

	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	for (int i = 8, j = 8; i < 11; i++)
	{
		j = (i + 1 < 11) ? i + 1 : 8;
		glVertex3f(shift[i][0], shift[i][1], 0.0);
		glVertex3f(shift[j][0], shift[j][1], 0.0);
		glVertex3f(shift[j][0], shift[j][1], 0.3);
		glVertex3f(shift[i][0], shift[i][1], 0.3);
	}
	glEnd();

	int seq[18] = { 4, 3, 5, 2, 10, 2, 9, 2, 9, 1, 11, 8, 11, 7, 11, 6, 10, 5 };
	glColor3ub(255, 0, 0);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < 18; i++) glVertex3f(shift[seq[i]-1][0], shift[seq[i]-1][1], 0.0);
	glEnd();

	glColor3ub(255, 0, 0);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < 18; i++) glVertex3f(shift[seq[i] - 1][0], shift[seq[i] - 1][1], 0.3);
	glEnd();

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 8; i++) glVertex3f(shift[i][0], shift[i][1], 0.0);
	glEnd();

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 8; i < 11; i++) glVertex3f(shift[i][0], shift[i][1], 0.0);
	glEnd();

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 8; i++) glVertex3f(shift[i][0], shift[i][1], 0.3);
	glEnd();

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 8; i < 11; i++) glVertex3f(shift[i][0], shift[i][1], 0.3);
	glEnd();

	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	for (int i = 0; i < 11; i++)
	{
		glVertex3f(shift[i][0], shift[i][1], 0.0);
		glVertex3f(shift[i][0], shift[i][1], 0.3);
	}
	glEnd();

	glutSwapBuffers();
	glFlush(); //Очистить все очереди команд и буферы OpenGL
}

GLvoid reshape(GLint w, GLint h)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}