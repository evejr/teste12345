/*Controle de Alunos*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define T_STR 100

typedef char string[T_STR];

struct disciplina{
  int codigo;
  float media;
  struct disciplina *prox;
};

struct noh{
  unsigned int matricula;
  string nome;
  struct disciplina *disciplinas;
  struct noh *esquerda, *direita;
};

typedef struct noh noh;
typedef struct disciplina disciplina;

noh* cria_noh(string nome, unsigned int matricula);
disciplina* cria_disciplina(int codigo);
void inserir_noh(noh **arvore, noh *novo);
noh* localizarNoh(noh *arvore, unsigned int matricula);
void insere_disciplina(noh *arvore, disciplina *nova);
void mostrar_disciplinas(noh *arvore);
void inserir_nota(disciplina *disciplina, float nota);
disciplina *localizarDisciplina(noh *noh, int codigo_disc);
int menu();

int main(){
  disciplina *aux2;
  noh *arvore = NULL, *aux;
  string nome;
  unsigned int  matricula = 0;
  int codigo, opc;
  float nota;

  do{
    switch(menu()){

      case 1: printf("Insira nome aluno: ");
              fflush(stdin);
              gets(nome);
              printf("Insira matricula do aluno: ");
              scanf("%d", &matricula);
              inserir_noh(&arvore, cria_noh(nome, matricula));
            break;
      case 2: printf("Digite matricula: ");
              scanf("%d", &matricula);
              aux = localizarNoh(arvore, matricula);
              if(!aux){
                printf("Aluno nao encontrado!!\n\n");
                printf("Deseja cadastrar aluno? <(1)Sim, (0)Nao>\n ");
                scanf("%d", &opc);
                if(opc){
                  printf("Insira nome aluno: ");
                  fflush(stdin);
                  gets(nome);
                  printf("Insira matricula do aluno: ");
                  scanf("%d", &matricula);
                  inserir_noh(&arvore, cria_noh(nome, matricula));
                }else
                  break;
              }
              else{
                  do{
                    printf("Insira codigo da disciplina: ");
                    scanf("%d", &codigo);
                    insere_disciplina(aux, cria_disciplina(codigo));
                    printf("Continuar cadastrando?\n<(1)SIM - (0)NAO>\n");
                    scanf("%d", &opc);
                  }while(opc);
              }
            break;
      case 3: printf("Digite a matricula do aluno: ");
              scanf("%d", &matricula);
              aux = localizarNoh(arvore, matricula);
              if(aux)
                mostrar_disciplinas(aux);
              else
                printf("Não encontrado\n");
            break;
      case 4: printf("Digite Matricula do aluno? ");
              scanf("%d", &matricula);
              aux = localizarNoh(arvore, matricula);
              if(aux){
                printf("Digite codigo da disciplina: ");
                scanf("%d", &codigo);
                aux2 = localizarDisciplina(aux, codigo);
                if(aux2){
                  printf("Digite nota do aluno: ");
                  scanf("%.2f", &nota);
                  inserir_nota(aux2, nota);
                }else
                  printf("Matricula nao encontrada!!!\n\n");
              }else
                printf("Aluno nao encontrado!!\n\n");
            break;
      case 0: exit(0);

    }

  }while(1);
  return 0;
}

int menu(){
  int opc;
  printf("1.Inserir Aluno\n");
  printf("2.Inserir Disciplina\n");
  printf("3.Mostrar Disciplinas de Aluno\n");
  printf("4.Inserir nota\n");
  printf("0. Sair\n");
  printf("?: ");
  scanf("%d", &opc);
  return opc;
}

noh* cria_noh(string nome, unsigned int matricula){
  noh* novo = (noh*) malloc(sizeof(noh));
  novo->matricula = matricula;
  novo->esquerda = NULL;
  novo->direita = NULL;
  novo->disciplinas = NULL;
  strcpy(novo->nome, nome);

  return novo;
}

disciplina* cria_disciplina(int codigo){
  disciplina *nova = (disciplina*) malloc(sizeof(disciplina));
  nova->codigo = codigo;
  nova->prox = NULL;
  nova->media = 0;
}

void inserir_noh(noh **arvore, noh *novo){

  if(!*arvore)
    *arvore = novo;
  else if(novo->matricula > (*arvore)->matricula)
    inserir_noh(&(*arvore)->direita, novo);
  else if(novo->matricula < (*arvore)->matricula)
    inserir_noh(&(*arvore)->esquerda, novo);

}

noh* localizarNoh(noh *arvore, unsigned int matricula){
  if(arvore){
    if(matricula > arvore->matricula)
      return localizarNoh(arvore->direita, matricula);
    else if(matricula < arvore->matricula)
      return localizarNoh(arvore->esquerda, matricula);
  }
  return arvore;
}

void insere_disciplina(noh *arvore, disciplina *nova){
  nova->prox = arvore->disciplinas;
  arvore->disciplinas = nova;
}

void mostrar_disciplinas(noh *arvore){

  printf("Aluno: %s\n", arvore->nome);
  int i = 1;
  while(arvore->disciplinas){
    printf("%d - %d\n", i++, arvore->disciplinas->codigo);
    arvore->disciplinas = arvore->disciplinas->prox;
  }
}

disciplina *localizarDisciplina(noh *noh, int codigo_disc){

  while(noh->disciplinas){
    if(noh->disciplinas->codigo == codigo_disc)
      return noh->disciplinas;
    noh->disciplinas = noh->disciplinas->prox;
  }
  return NULL;
}

void inserir_nota(disciplina *disciplina, float nota){
  disciplina->media = nota;
}
