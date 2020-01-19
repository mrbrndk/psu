#pragma comment(lib, "D:/Programs/OpenGL/glut32.lib")
#include <D:/Programs/OpenGL/glut.h>
#include <cmath>

#define M_PI 3.14159265358979323846

GLint width = 400;
GLint height = 400;

GLvoid renderScene(GLvoid); // функци€ дл€ перерисовки окна
GLvoid reshape(GLint w, GLint h);

GLint main(GLint argc, GLbyte **argv)
{
	glutInit(&argc, (char **)argv);  // инициализаци€
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(width, height);
	glutCreateWindow("Ћабораторна€ работа є6");
	glutDisplayFunc(renderScene); // регистраци€ обратных вызовов
	glutReshapeFunc(reshape);
	glutMainLoop();  // ќсновной цикл GLUT
	return 1;
}

GLvoid renderScene(GLvoid)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3ub(128, 128, 128);
	glBegin(GL_QUADS);
	glVertex2i(width / 2 - 100, height / 2 - 100);
	glVertex2i(width / 2 + 100, height / 2 - 100);
	glVertex2i(width / 2 + 100, height / 2 + 100);
	glVertex2i(width / 2 - 100, height / 2 + 100);
	glEnd();

	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	float x = width / 2;
	float y = height / 2 + 100;
	float r = 70.0;
	for (int i = 0; i < 360; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(360);
		float dx = r * cosf(angle);
		float dy = r * sinf(angle);
		glVertex2f(x + dx, y + dy);
	}
	glEnd();

	glColor3ub(0, 250, 154);
	glBegin(GL_LINE_LOOP);
	x = width / 2;
	y = height / 2 + 100;
	r = 70.0;
	for (int i = 0; i < 360; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(360);
		float dx = r * cosf(angle);
		float dy = r * sinf(angle);
		glVertex2f(x + dx, y + dy);
	}
	glEnd();

	glColor3ub(0, 250, 154);
	glBegin(GL_TRIANGLES);
	glVertex2i(width / 2, height / 2 + 70); //верхн€€ вершина
	glVertex2i(width / 2 - 75, height / 2 - 125); //лева€ вершина
	glVertex2i(width / 2 + 75, height / 2 - 120); //права€ вершина
	glEnd();

	glColor3ub(255, 255, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(width / 2, height / 2 + 70); //верхн€€ вершина
	glVertex2i(width / 2 - 75, height / 2 - 125); //лева€ вершина
	glVertex2i(width / 2 + 75, height / 2 - 120); //права€ вершина
	glEnd();

	glutSwapBuffers();
	glFlush(); //ќчистить все очереди команд и буферы OpenGL
}

GLvoid reshape(GLint w, GLint h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}