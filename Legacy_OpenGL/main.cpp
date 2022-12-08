#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>

void renderScene(void);
void changeSize(int width, int height);
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);


void drawSnowMan();


float red = 1.0f;
float green = 0.0f;
float blue = 0.0f;
int mod;

struct Camera {
	float angle = 0.0f;
	
	// vector representing the camera's direction
	float lx = 0.0f;
	float lz = -1.0f;

	// xz position of the camera
	float x = 0.0f;
	float y = 1.0f;
	float z = 0.0f;
	
};

Camera camera;


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Legacy OpenGL");

	//register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// enter GLUT event processing cycle
	glutIdleFunc(renderScene);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);


	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

int KEY_W = 119;
int KEY_A = 97;
int KEY_S = 115;
int KEY_D = 100;

void processNormalKeys(unsigned char key, int x, int y) {

	
	
	
	

	
	
}
void processSpecialKeys(int key, int x, int y) {
	

	float speed = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		camera.angle -= 0.01f;
		camera.lx = sin(camera.angle);
		camera.lz = -cos(camera.angle);
		break;
	case GLUT_KEY_RIGHT:
		camera.angle += 0.01f;
		camera.lx = sin(camera.angle);
		camera.lz = -cos(camera.angle);
		break;
	case GLUT_KEY_UP:
		camera.x += camera.lx * speed;
		camera.z += camera.lz * speed;
		break;
	case GLUT_KEY_DOWN:
		camera.x -= camera.lx * speed;
		camera.z -= camera.lz * speed;
		break;
	}


}


void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// reset transformations
	glLoadIdentity();

	// Set the camera
	
	/*
	gluLookAt(0.0f, 0.0f, 10.0f, 
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
		*/
	
	gluLookAt(camera.x, camera.y, camera.z,
		camera.x + camera.lx, camera.y, camera.z + camera.lz,
		0.0f, 1.0f, 0.0f);
	
	
	// Draw ground
	
	glColor3f(0.9f, 0.9f, 0.9f);

	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	// Draw 36 SnowMen
	for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
				glTranslatef(i * 10.0, 0, j * 10.0);
				drawSnowMan();
			glPopMatrix();
		}
	

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


void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}