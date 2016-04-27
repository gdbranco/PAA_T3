#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define O 1
#define OMEGA 2
#define TETA 3

typedef struct _frac {
    int num;
    int denom;
}frac;
void get_polinomio(char* buffer, int expoente);
void show_prova(int a, int b, int fn, int p, int c,int OK);
void get_sprova(char* buffer, char *string_p);
void get_suposicao(char* buffer, int b, int p);
void get_fato(char* buffer, int a, int b, char* string_fn);
void get_fator(char* buffer, float fator);
void do_OMEGA(int OK,int b,char* string_p,char* string_fn);
void do_O(int OK,int b,char* string_p,char* string_fn);
int mdc(int a, int b);
frac to_frac(double x, int precision);

int mdc(int a, int b)
{
    if (a == 0) return b;
    if (b == 0) return a;

    if (a > b)
        return mdc(b, a % b);
    else
        return mdc(a, b % a);
}

frac to_frac(double x, int precision)
{
    int denom = 1;
    for (int i = 0; i < precision; i++) {
        denom *= 10;
    }

    int num = x * denom + 0.5; // hack: round if imprecise
    int mdciv = mdc(num, denom);

    frac f;
    f.num = num / mdciv;
    f.denom = denom / mdciv;

    return f;
}

void do_O(int OK,int b,char *string_p,char* string_fn)
{
  
}

void do_OMEGA(int OK,int b,char *string_p,char *string_fn)
{
  
}

void get_fato(char* buffer, int a, int b, char* string_fn)
{
  sprintf(buffer,"T(n) = %dT(n/%d) + %s",a,b,string_fn);
}

void get_suposicao(char* buffer, int b, int p)
{
  sprintf(buffer,"T(n/%d)<=c(n/%d)^%d",b,b,p);
}

void get_sprova(char* buffer, char *string_p)
{
  sprintf(buffer,"T(n)<=c%s",string_p);
}


void show_prova(int a, int b, int fn, int p, int c, int OK)
{
  char fato[21];
  char suposicao[18];
  char sprova[11];
  char string_fn[4];
  char string_p[4];
  char string_fator[10];
  float fator = (float)((1/pow(b,p))*a);
  get_polinomio(string_fn,fn);
  get_polinomio(string_p,p);
  get_fato(fato,a,b,string_fn);
  get_suposicao(suposicao,b,p);
  get_sprova(sprova,string_p);
  get_fator(string_fator,fator);
  printf("Fato : %s\n",fato);
  printf("Suposicao : %s\n",suposicao);
  printf("Preciso provar : %s\n",sprova);
  printf("%s\n",fato);
  printf("     <= %dc(n/%d)^%d + %s\n",a,b,p,string_fn);
  printf("     = %s%s + %s\n",string_fator,string_p,string_fn);
  printf("     = c%s - (%s%s - %s) <- desejado - residual\n",string_p,string_fator,string_p,string_fn);
  printf("     <= c%s <- desejado\n",string_p);
  switch(c)
  {
    case O:
      do_O(OK,b,string_p,string_fn);
      break;
    case OMEGA:
      do_OMEGA(OK,b,string_p,string_fn);
      break;
    case TETA:
      do_O(OK,b,string_p,string_fn);
      do_OMEGA(OK,b,string_p,string_fn);
      break;
    default:
      printf("undefined\n");
      break;
  }
}

void get_polinomio(char* buffer, int expoente)
{
  switch(expoente)
  {
    case 0:
      strcpy(buffer,"1");
      break;
    case 1:
      strcpy(buffer,"n");
      break;
    default:
      sprintf (buffer, "n^%d", expoente);
      break;
  }
}

void get_fator(char* buffer, float fator)
{
  frac _fator = to_frac(fator,10);
  switch(_fator.num)
  {
    case 1:
      if(_fator.denom==1)
      {
        strcpy(buffer,"c");
      }
      else
      {
      	sprintf(buffer, "(c/%d)",_fator.denom);
      }
      break;
    default:
      sprintf(buffer, "(c*%d/%d)",_fator.num,_fator.denom);
      break;
  }
}

int main(int argc, char *argv[])
{

  if(argc < 6)
  {
    printf("Usage: ./programa <a> <b> <fn> <p> <c>\n");
    return -1;
  }
  int a,b,p,fn,c,OK;
  /*C = 1 OMEGA, O, TETA*/
  //Inicializa dados
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  fn = atoi(argv[3]);
  p = atoi(argv[4]);
  if(strcmp("grandeo",argv[5])==0)
    c = O;
  else if(strcmp("grandeomega",argv[5])==0)
    c = OMEGA;
  else if(strcmp("teta",argv[5])==0)
    c = TETA;
  if( p==fn )
    OK = TETA; //TETA OK
  else if (p>=fn)
    OK = O; //O OK
  else
    OK = OMEGA; //OMEGA OK
  
  //Print inicial
  show_prova(a, b, fn, p, c, OK);
 
  return 0;
}
