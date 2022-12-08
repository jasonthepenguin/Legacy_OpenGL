#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void renderScene(void);
void changeSize(int width, int height);

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Legacy OpenGL");

	//register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}


void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glBegin(GL_TRIANGLES);
		glVertex3f(-2, -2, -5.0);
		glVertex3f(2, 0.0, -5.0);
		glVertex3f(0.0, 2, -5.0);
	glEnd();

	glutSwapBuffers();
}

void changeSize(int width, int height) {
	if (height == 0) {
		height = 1;
	}
	float ratio = 1.0 * width / height;

	// Use the projection matrix
	glMatrixMode(GL_PROJECTION);

	// Reset matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);

	// Set the correct perspective
	gluPerspective(45, ratio, 1, 1000);

	// Get back to the modelview
	glMatrixMode(GL_MODELVIEW);
}