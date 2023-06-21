#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLfloat angle, fAspect;
GLint stacks = 40;
GLint slices = 40;


void Desenha()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(10, slices, stacks);

    glPushMatrix();
        glTranslatef(0.0, 15.0, 0.0);
        glutSolidSphere(5, slices, stacks);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(2.0, 17.0, 0.0);
        glutSolidSphere(0.5, slices, stacks);

        glTranslatef(-4.0, 0.0, 0.0);
        glutSolidSphere(0.5, slices, stacks);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0, 0.3, 0.0);
        glTranslatef(0.0, 15.0, 0.0);
        glutSolidCone(0.5, 5 ,slices, stacks);
    glPopMatrix();


    glutSwapBuffers();
}

void AreaVisualizacao()
{
    angle = 45;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle, fAspect, 0.1, 200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,80, 0,0,0, 0,1,0);
}

void Janela(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    if(h == 0)h = 1;

    fAspect = (GLfloat)w/(GLfloat)h;

    AreaVisualizacao();
}

static void Teclado(unsigned char key, int x, int y)
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
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Boneco de Neve");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(Janela);
    glutKeyboardFunc(Teclado);

    glutMainLoop();

    glClearColor(0,0,0,0);

    return 0;
}
