#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 10;
static int stacks = 10;
GLfloat angle, fAspect;
GLfloat angulo_torus;

void Inicializa(void)
{
    GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0};//Cor
    GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};//Brilho
    GLfloat posicaoluz[4] = {0.0, 500.0, 0.0, 1.0};

    //capacidade brilho do material
    GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
    GLint especMaterial = 60;

    glClearColor(0,0,0,0);

    //variação de tonalidades
    glShadeModel(GL_SMOOTH);

    //define a refletância do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    //define a concentração do brilho
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    //ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    //define os parametros da luz de numero 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoluz);

    //habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    //habilita a luz de numero 0
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

}

void Desenha(void)
{
    int i, x = 0, y = 0.1, z = 1;;
    angulo_torus = 0.5;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glPushMatrix();
        glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    for(i=0; i<10; i++){

    }

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

    gluLookAt(0,0,10, 0,0,0, 0,1,0);
}

void Janela(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    if(h == 0)h = 1;

    fAspect = (GLfloat)w/(GLfloat)h;

    AreaVisualizacao();
}

void Teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Engrenagens");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(Janela);
    glutKeyboardFunc(Teclado);

    Inicializa();
    glutMainLoop();

    return 0;
}
