#  include <iostream>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

//Data for shield
GLfloat shield[5][3] = { {4, 0, 0}, {4, 20, 0}, {-4, 20, 0}, {-4, 0, 0}};

//Color for rings
GLfloat colors[1][3] = {{0, 0, 1}};

//Color for right border
GLfloat right_colors[1][3] = {{0, 0, 0}};

//Color for left border
GLfloat left_colors[1][3] = {{1, 1, 1}};

//right border
GLfloat right_border[8][3] ={{0, 0, 0}, {4, 0, 0}, {4, 20, 0}, {0, 20, 0}, {0, 22, 0}, {6, 22, 0}, {6, -2, 0}, {0, -2, 0}};



//draw shield using the current modelview matrix
void draw_shield(void){
    glBegin(GL_POLYGON);
        for (int i = 0; i<4; i++)
            glVertex3fv(shield[i]);
    glEnd();
}

//draw right border
void draw_right_border(void){
    glBegin(GL_POLYGON);
    for (int i = 0; i<8; i++)
        glVertex3fv(right_border[i]);
    glEnd();
}

void draw_ring(void){
    for (int r = 0; r<360; r = r+45){
        glPushMatrix();
        glRotated(r, 0, 0, 1);
        glTranslated(0, 30, 0);
        glColor3fv(colors[0]);
        draw_shield();
        glColor3fv(right_colors[0]);
        draw_right_border();
        glPopMatrix();
    }
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < 4; i++){
        glPushMatrix();
        glTranslated((i-1)*210-i*70, 200, -i*5);
        //glScaled(i+1, i+1, i+1);
        draw_ring();
        glPopMatrix();
    }
    for (int i = 0; i < 4; i++){
        glColor3fv(colors[i]);
        glPushMatrix();
        glTranslated((i-1)*210-i*70, 0, -i*5);
        //glScaled(i+1, i+1, i+1);
        draw_ring();
        glPopMatrix();
    }
    glFlush();
}

int main(int argc, char ** argv){
    
    glutInit(& argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("CTM stack");
    
    glClearColor(0.8,1.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
    
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-300, 300, -300, 300, 0, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    glutDisplayFunc(display);
    
    glutMainLoop();
    
}
