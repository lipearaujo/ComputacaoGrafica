#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define TAM_BLOCO 100
#define celula_visitada 1
#define celula_nao_visitada -1
bool Constroi_Pilha();
bool Destroi_Pilha();
bool Pilha_vazia();
bool Pilha_Push(int valor);
bool Pilha_Pop(int valor);
bool Pilha_Get(int valor);
FILE *carregar(char mapa[15][15]);
void AbreArquivo(char mapa[][15], char *nome_arquivo);

GLint slices = 20;
GLint stacks = 20;
GLfloat angle, fAspect;
int linha, coluna;
int vetor_tam[2];
char mapa[15][15];

typedef struct matriz_mapa{
    int linha;
    int coluna;
    int entrada;
    int saida;
}MATRIZ_MAPA;

typedef struct tipo_celula
{
    int valor_celula;
    tipo_celula *proxima_celula;
}TIPO_CELULA;

tipo_celula *Topo;

FILE *carregar(char mapa[15][15]){
    char nome_arquivo[10];

    printf("Insira o nome do arquivo que deseja abrir: ");
    scanf("%s", nome_arquivo);

    AbreArquivo(mapa, nome_arquivo);
}

void AbreArquivo(char mapa[15][15], char *nome_arquivo){
    int i,j;
    FILE *arquivo;

    arquivo = fopen(nome_arquivo,"r");

    if(arquivo == NULL){
        printf("ERRO");
        exit(0);
    }

    for(i=0; i<2; i++){
        fscanf(arquivo, "%d", &vetor_tam[i]);
    }
    printf("\n");

    linha = vetor_tam[0];
    coluna = vetor_tam[1];
    printf("Tamanho da Linha: %d\n",linha);
    printf("Tamanho da Coluna: %d\n",coluna);

    printf("\n");

    for(i=0;i<linha;i++){
        for(j=0;j<coluna;j++){

            fscanf( arquivo, "%d", &mapa[i][j]);
            printf("%d ", mapa[i][j]);
        }
        printf("\n");
    }

    fclose(arquivo);
}

bool Constroi_Pilha()
{
    Topo = NULL;
}

bool Destroi_Pilha()
{
    int aux;
    tipo_celula *temp;
    if(Pilha_vazia()){
        return false;
    }else{
        while(Pilha_Pop(Topo!=NULL)){
            temp = Topo;
            temp->proxima_celula = NULL;
            Topo = Topo->proxima_celula;

            free(temp);
        }
        return true;
    }
}

bool Pilha_vazia()
{
    if(Topo == NULL){
        return true;
    }else{
        return false;
    }
}

bool Pilha_Push(int valor)
{
    tipo_celula *nova_celula = (tipo_celula*)malloc(sizeof(tipo_celula));
    if(nova_celula == NULL){
        return false;
    }else{
        nova_celula->valor_celula = valor;
        nova_celula->proxima_celula = Topo;
        Topo = nova_celula;
        return true;
    }
}

bool Pilha_Pop(int valor)
{
    tipo_celula *temp;
    if(Pilha_vazia()){
        return false;
    }else{
        valor = Topo->valor_celula;
        temp = Topo;
        Topo = Topo->proxima_celula;

        temp->proxima_celula = NULL;

        free(temp);
        return true;
    }
}

bool Pilha_Get(int &valor)
{
    if(Pilha_vazia()){
        return false;
    }else{
        valor = Topo->valor_celula;
        return true;
    }
}

void Buscar_Saida()
{
    int vetor_entrada[2], vetor_saida[2];
    int i,j;

    printf("Informe a entrada do labirinto: \n");
    for(i=0; i<2; i++){
        scanf("%d", &vetor_entrada[i]);
    }

    printf("Informe a saida do labirinto: \n");
    for(j=0; j<2; j++){
        scanf("%d", &vetor_saida[j]);
    }

    printf("A entrada eh: %d,%d\n", vetor_entrada[0],vetor_entrada[1]);
    printf("A saida eh: %d,%d", vetor_saida[0], vetor_saida[1]);

}

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

void Desenha()
{
    int i,j,x,z;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*glPushMatrix();
        glTranslatef(400,5,100);
        glColor3f(0, 1.0, 0);
        glutSolidSphere(20, slices, stacks);
    glPopMatrix();*/

        for(i=0; i<15; i++){
            for(j=0; j<15; j++){
                if(mapa[i][j]){
                    x = i*TAM_BLOCO;
                    z = j*TAM_BLOCO;

                    glPushMatrix();
                        glColor3f(1, 1, 1);
                        glTranslatef(x, 5, z);
                        glutSolidCube(TAM_BLOCO);
                    glPopMatrix();
                }
            }
        }


    glutSwapBuffers();
}

void AreaVisualizacao()
{
    angle = 90;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle, fAspect, 0.1, 5000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //gluLookAt(100,25,100, 110,25,100, 0,1,0);
    gluLookAt(0,1700,10, 0,200,0, 0,1,0);//Mudar para angle = 90
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
    FILE* file = NULL;
    file = carregar(mapa);

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Labirinto 3D");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(Janela);
    glutKeyboardFunc(Teclado);

    Inicializa();
    Buscar_Saida();
    glutMainLoop();


    return 0;
}
