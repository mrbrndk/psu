#pragma comment(lib, "D:/Programs/OpenGL/glut32.lib")
#include <D:/Programs/OpenGL/glut.h>
#include <cmath>
#include <iostream>

GLint fw = 50;
GLint fh = 50;
GLint size = 9;
GLint radius = 20;

GLint width = fw * size;
GLint height = fh * size;

GLvoid renderScene(GLvoid);
GLvoid reshape(GLint w, GLint h);
GLvoid createBall(GLint r, GLint x, GLint y);

GLint main(GLint argc, GLbyte **argv)
{
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //| GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("Курсовой проект");
	//glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
	glutMainLoop();//основной цикл
	return 1;
}

GLvoid renderScene(GLvoid)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3ub(128, 128, 128);
	glBegin(GL_QUADS);
	glVertex2i(width / 2 - 100, height / 2 - 100);
	glVertex2i(width / 2 + 100, height / 2 - 100);
	glVertex2i(width / 2 + 100, height / 2 + 100);
	glVertex2i(width / 2 - 100, height / 2 + 100);
	glEnd();

	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	for (int i = 0; i < size; i++)
	{
		glVertex2i(i * fw, 0);//вертикальный линии
		glVertex2i(i * fw, fh * size);

		glVertex2i(0, i * fh);//горизонтальные
		glVertex2i(fw * size, i * fh);
	}
	glEnd();

	glColor3ub(255, 0, 0);
	createBall(radius, 25, 25);

	glutSwapBuffers();
	glFlush(); //Очистить все очереди команд и буферы OpenGL
}

GLvoid reshape(GLint w, GLint h)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLvoid createBall(GLint r, GLint x, GLint y)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < 40; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(40);
		float dx = r * cosf(angle);
		float dy = r * sinf(angle);
		glVertex2f(x + dx, y + dy);
	}
	glEnd();
}