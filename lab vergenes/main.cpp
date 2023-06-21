//Labirinto - Computação Gráfica
//Mateus Almeida de Vergennes

#include<iostream>
#include <gl/glut.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

int cx=2,cy=0,cz=1;
int tx=-10,ty=0,tz=-40;
int a=75;
int cn;

GLfloat angle, fAspect;



int mapa[15][15];

void Inicializa (void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    angle=35;
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle,fAspect,0.1,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(0,80,200, 0,0,0, 0,0,0);
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}


void Cubo(){
    glPushMatrix();
    glColor3f(1.0,1,0.25);
    glTranslatef(cx,cy,cz);
    glutSolidCube(0.4);
}

void parede(){
    glutWireCube(1);
}
void parede_comeco_final(){
    glutSolidCube(1);
}


void chao(){
    int i,j;
    glPushMatrix();
    for(i=0;i<15;i++){
        for(j=0;j<15;j++){
            if(mapa[i][j]==1){
                glColor3f(0.25,0.75,1);
                glTranslatef(1,0,0);
                parede();
            }
            if(mapa[i][j]==2){
                glColor3f(0.0,1.0,1.0);
                glTranslatef(1,0,0);
                parede_comeco_final();
            }
            if(mapa[i][j]==3){
                glColor3f(0.4,0.4,1.0);
                glTranslatef(1,0,0);
                parede_comeco_final();
            }
            if(mapa[i][j]==0){
                glTranslatef(1,0,0);
            }

        }
        glTranslatef(-15,0,1);
    }
    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(tx,ty,tz);
    glRotatef(a,1,1,0);
    chao();
    Cubo();

    glutSwapBuffers();
}

void Init(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 1.0f, 0.1f, 1000);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1,0.1,0.1,1);
}

static void teclas(unsigned char key, int x, int y){//controle do braco
    switch (key){
        //Controle Transladacao Camera
        case 'j':
            tx--;
        break;
        case 'k':
            ty--;
        break;
        case 'l':
            tz--;
        break;
        case 'u':
            tx++;
        break;
        case 'i':
            ty++;
        break;
        case 'o':
            tz++;
        break;
        //Controle Angulacao Camera
        case 'h':
            a--;
        break;
        case 'y':
            a++;
        break;

        //Frente e Trás
        case 'w':
            cz-=1;

        break;
        case 's':
            cz+=1;
        break;
        //Esquerda e Direita
        case 'a':
            cx-=1;
        break;
        case 'd':
            cx+=1;
        break;
        //Cima e Baixo
        case 'q':
            cy+=1;
        break;
        case 'z':
             cy-=1;
        break;
        case 27 :
        case 'e':
            exit(0);
        break;
    }
    glutPostRedisplay();
}



// Programa Principal
int main(int argc, char **argv)
{
    int m,n;
    FILE *arquivo;

    arquivo= fopen("mapa_labirinto.txt", "r");
    for(m=0;m<15;m++){
        for(n=0;n<15;n++){
            fscanf(arquivo,"%d ", &mapa[m][n]);
        }
    }
    printf("INSTRUCOES:\n");
    printf("o programa aceita arquivos mapa com o nome 'mapa_labirinto' no formato .txt com dimensoes de matriz 15x15 separando cada termo por um espacamento ou ENTER\n" );
    printf("CONTROLES:\n");
    printf("------peca---------------\n");
    printf("w-peca se move para FRENTE\n");
    printf("s-peca se move para TRAS\n");
    printf("a-peca se move para ESQUERDA\n");
    printf("d-peca se move para DIREITA\n");
    printf("q-peca se move para cima\n");
    printf("z-peca se move para baixo\n");
    printf("------mapa---------------\n");
    printf("transladacao:\n");
    printf("j-translada no sentido negativo de X\n");
    printf("k-translada no sentido negativo de Y\n");
    printf("l-translada no sentido negativo de Z\n");
    printf("u-translada no sentido positivo de X\n");
    printf("i-translada no sentido positivo de Y\n");
    printf("o-translada no sentido positivo de Z\n");
    printf("angulo:\n");
    printf("h-diminui o angulo\n");
    printf("y-aumenta o angulo\n");
    printf("botao esquerdo mouse-zoom in\n");
    printf("botao direito mouse-zoom out\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800,600);
    glutCreateWindow("Labirinto");
    glutDisplayFunc(display);
    glutKeyboardFunc(teclas);
    Init();
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
    Inicializa();
    glutMainLoop();
}
