#  include <iostream>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

//Data for shield
GLfloat shield[5][3] = { {4, 0, 0}, {4, 24, 0}, {-4, 24, 0}, {-4, 0, 0}};

//Color for rings
GLfloat colors[1][3] = {{0, 0, 1}};

//Color for right border
GLfloat white_colors[1][3] = {{0, 0, 0}};

//Color for left border
GLfloat black_colors[1][3] = {{1, 1, 1}};

//right border
GLfloat right_border[8][3] ={{0, 0, 0}, {4, 0, 0}, {4, 24, 0}, {0, 24, 0}, {0, 26, 0}, {6, 26, 0}, {6, -2, 0}, {0, -2, 0}};

//left border
GLfloat left_border[8][3] ={{0, 0, 0}, {-4, 0, 0}, {-4, 24, 0}, {0, 24, 0}, {0, 26, 0}, {-6, 26, 0}, {-6, -2, 0}, {0, -2, 0}};

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

//draw right border
void draw_left_border(void){
    glBegin(GL_POLYGON);
    for (int i = 0; i<8; i++)
        glVertex3fv(left_border[i]);
    glEnd();
}

void draw_ring(bool alternare_Border){
    for (int r = 0; r<360; r = r+45){
        glPushMatrix();
        glRotated(r, 0, 0, 1);
        glTranslated(0, 30, 0);
        glColor3fv(colors[0]);
        draw_shield();
        
        if (alternare_Border ==  false){
            
            glColor3fv(white_colors[0]);
            draw_right_border();
        
            glColor3fv(black_colors[0]);
            draw_left_border();
        }
        
        else{
            
            glColor3fv(black_colors[0]);
            draw_right_border();
            
            glColor3fv(white_colors[0]);
            draw_left_border();
        
        }
        
        glPopMatrix();
    }
}

void display(void){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bool alternate_Border;
    
    for (int i = 0; i < 4; i++){
        if (i%2 == 0)
            alternate_Border = false;
        else
            alternate_Border = true;
        glPushMatrix();
        
        //centre of each ring is 140 unit apart
        //each rings are 140-(30+28)*2=24 unit apart
        glTranslated((i-1)*210-i*70, 200, 0);
        draw_ring(alternate_Border);
        glPopMatrix();
        
    }
    
    for (int i = 0; i < 4; i++){
        if (i%2 != 0)
            alternate_Border = false;
        else
            alternate_Border = true;
        glPushMatrix();
        
        //y=200-140=60, so the center of each ring is still 140 unit apart
        glTranslated((i-1)*210-i*70, 60, 0);
        draw_ring(alternate_Border);
        glPopMatrix();
        
    }
    
    glFlush();
}

int main(int argc, char ** argv){
    
    glutInit(& argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 600);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Md_Mahedi_Rana");
    
    glClearColor(0.8,1.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-300, 300, -20, 280, 0, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glutDisplayFunc(display);
    
    glutMainLoop();
    
}
