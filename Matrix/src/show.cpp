//g++ show.cpp -o a.out -lglut -lGL -lGLU
#include "Linear.cpp"
#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

Matrix<float> origin, trans, rotat;
float pi = 2 * asin(1);

// coordinates of frame
float _array[3][7] = {
    {0.0, 0.1,  0.0, 0.09, 0.09, -0.01, 0.01},
    {0.0,  0.0, 0.1, -0.01, 0.01, 0.09, 0.09},
    {1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0}
};
float array[3][7] = {
    {0.0, 0.1,  0.0, 0.09, 0.09, -0.01, 0.01},
    {0.0,  0.0, 0.1, -0.01, 0.01, 0.09, 0.09},
    {1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0}
};
float (*frame)[7] = array;

// translation matrix
float matrix_trans[3][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}
};

// rotation matrix
float matrix_rotat[3][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 1.0}
};

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
}

void draw_axis(void) {
    // draw coordinate axis
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);  // x axis
	glVertex2f(-0.8, 0.0);
        glVertex2f(0.8, 0.0);
	glColor3f(1.0, 1.0, 1.0);  // y axis
	glVertex2f(0.0, 0.8);
        glVertex2f(0.0, -0.8);
	glEnd();

    // draw scale
    glBegin(GL_LINES);
    for (int i = -40; i <= 40; i++) {  // x axis
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(0.02*i, 0.0);
        glVertex2f(0.02*i, 0.006);
    }
	for (int i = -40; i <= 40; i++) {  // y axis
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(0.0, 0.02*i);
        glVertex2f(0.006, 0.02*i);
    }
    glEnd();
}

void draw_frame(void) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 7; j++)
            frame[i][j] /= frame[2][j];
    glShadeModel(GL_SMOOTH);
    glBegin (GL_LINES);  //draw frame
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(frame[0][0], frame[1][0]);
    glVertex2f(frame[0][1], frame[1][1]);

    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(frame[0][1], frame[1][1]);
    glVertex2f(frame[0][3], frame[1][3]);

    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(frame[0][1], frame[1][1]);
    glVertex2f(frame[0][4], frame[1][4]);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(frame[0][0], frame[1][0]);
    glVertex2f(frame[0][2], frame[1][2]);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(frame[0][2], frame[1][2]);
    glVertex2f(frame[0][5], frame[1][5]);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(frame[0][2], frame[1][2]);
    glVertex2f(frame[0][6], frame[1][6]);
    glEnd();
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    draw_axis();
    glLoadIdentity();
    draw_frame();
    glFlush ();
}

// translate the frame
void translate_frame(float x, float y) {
	matrix_trans[0][2] = x;
	matrix_trans[1][2] = y;
	trans.set((float**)matrix_trans, 3, 3);
	origin = trans * origin;
        for (int i = 0; i < 3; i++)
          	for (int j = 0; j < 7; j++)
            	frame[i][j] = origin.x[i][j];
}

// rotate the frame
void rotate_frame(float rad) {
	matrix_rotat[0][0] = cos(rad);
	matrix_rotat[0][1] = sin(rad);
	matrix_rotat[1][0] = -sin(rad);
	matrix_rotat[1][1] = cos(rad);
	rotat.set((float**)matrix_rotat, 3, 3);
    origin = rotat * origin;
        for (int i = 0; i < 3; i++)
          	for (int j = 0; j < 7; j++)
            	frame[i][j] = origin.x[i][j];
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'z':
        case 'Z':
        	origin.set((float**)_array, 3, 7);
                glClear (GL_COLOR_BUFFER_BIT);
				draw_axis();
                translate_frame(0.1, 0);
                glLoadIdentity();
                draw_frame();
                glFlush();
                translate_frame(0.1, 0);
                glLoadIdentity();
                draw_frame();
                glFlush();
                translate_frame(0.1, 0);
                glLoadIdentity();
                draw_frame();
                glFlush();
                break;
        case 'r':
        case 'R':
                origin.set((float**)_array, 3, 7);
                glClear (GL_COLOR_BUFFER_BIT);
				draw_axis();
                rotate_frame(pi/2);
                translate_frame(0, -0.1);
                glLoadIdentity();
                draw_frame();
                glFlush();
                translate_frame(0, -0.1);
                glLoadIdentity();
                draw_frame();
                glFlush();
                translate_frame(0, -0.1);
                glLoadIdentity();
                draw_frame();
                glFlush();
                break;
        case 'n':
        case 'N':
                origin.set((float**)_array, 3, 7);
                glClear (GL_COLOR_BUFFER_BIT);
		draw_axis();
                rotate_frame(pi/4);
                translate_frame(0.05*sqrt(2), 0.05*sqrt(2));
                glLoadIdentity();
                draw_frame();
                glFlush();
                translate_frame(-0.05*sqrt(2), -0.05*sqrt(2));
                rotate_frame(-pi/4);
                translate_frame(0.05*sqrt(2), 0.05*sqrt(2));
                translate_frame(0.1, 0);
                glLoadIdentity();
                draw_frame();
                glFlush();
                translate_frame(-0.1, 0);
                translate_frame(-0.05*sqrt(2), -0.05*sqrt(2));
                rotate_frame(-pi/4);
                translate_frame(0.05*sqrt(2), 0.05*sqrt(2));
                translate_frame(0.1, 0);
                translate_frame(0.05*sqrt(2), 0.05*sqrt(2));
                glLoadIdentity();
                draw_frame();
                glFlush();
                break;
        case 'd':
        case 'D':
                origin.set((float**)_array, 3, 7);
                glClear (GL_COLOR_BUFFER_BIT);
				draw_axis();
                rotate_frame(-pi/2);
                translate_frame(0, 0.1);
                glLoadIdentity();
                draw_frame();
                glFlush();
                translate_frame(0, 0.1);
                glLoadIdentity();
                draw_frame();
                glFlush();
                translate_frame(0, 0.1);
                glLoadIdentity();
                draw_frame();
                glFlush();
                break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
