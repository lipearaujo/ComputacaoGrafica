#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>


void Janela(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(h==0)h = 1;
    if(w <= h){
        gluOrtho2D(-20.0, 20.0, -20.0*h/w, 20.0*h/w);
    }else{
        gluOrtho2D(-20.0*w/h, 20.0*w/h, -20.0, 20.0);
    }
}

void Casa()
{
    glBegin(GL_QUADS);
        glVertex2f(-6.0, -6.0);
        glVertex2f(-6.0, 6.0);
        glVertex2f(6.0, 6.0);
        glVertex2f(6.0, -6.0);
    glEnd();

}

void Telhado()
{
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0, 0.0);
        glVertex2f(6.0, 0.0);
        glVertex2f(0.0, 6.0);
    glEnd();

}

void Desenha_casa()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
        Casa();
        glColor3f(1.0, 1.0, 1.0);
        glScalef(0.3, 1.0, 0.0);
        Casa();
    glPopMatrix();

    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
        glTranslatef(0.0, 6.0, 0.0);
        Telhado();
        glColor3f(1.0, 0.0, 0.0);
        glRotatef(90, 0, 0, 1);
        Telhado();
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(6.0, -6.0, 0.0);
        glRotatef(180, 0, 1, 0);
        Telhado();
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(3.0, -3.0, 0.0);
        glScalef(0.5, 0.5, 0.0);
        Casa();
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(6.0, -6.0, 0.0);
        glScalef(2.0, 2.0, 0.0);
        glRotatef(180, 0, 0, 1);
        Telhado();
    glPopMatrix();


    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
        glTranslatef(12.0, 0.0, 0.0);
        glTranslatef(0.0, 3.0, 0.0);
        glScalef(1.0, 0.5, 0.0);
        Casa();
        glColor3f(1.0, 1.0, 1.0);
        glScalef(0.34, 1.0, 0.0);
        Casa();
    glPopMatrix();

    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
        glTranslatef(12.0, 0.0, 0.0);
        glTranslatef(0.0, -3.0, 0.0);
        glScalef(1.0, 0.5, 0.0);
        Casa();
    glPopMatrix();



    glFlush();

}

void Tecla(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
        case 'q':
            exit(0);
            break;
    }
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(320,150);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Casa");
    glutDisplayFunc(Desenha_casa);
    glutReshapeFunc(Janela);
    glutKeyboardFunc(Tecla);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutMainLoop();

    return 0;
}
