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
void show_prova(int a, int b, int fn, int p, int c);
void get_sprova(char* buffer, char *string_p, char *relacao);
void get_suposicao(char* buffer, int b, int p, char *relacao);
void get_fato(char* buffer, int a, int b, char* string_fn);
void get_fator(frac *_fator,char* buffer, float fator);
void do_OMEGA(int a, int b, int fn, int p, int c);
void do_O(int a, int b, int fn, int p, int c);
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

void do_O(int a, int b, int fn, int p, int c)
{
  char fato[21];
  char suposicao[18];
  char sprova[11];
  char string_fn[4];
  char string_p[4];
  char string_residual[100];
  char relacao[3] = "<=";
  float fator = (float)(a/pow(b,p));
  get_polinomio(string_fn,fn);
  get_polinomio(string_p,p);
  get_fato(fato,a,b,string_fn);
  get_suposicao(suposicao,b,p,relacao);
  get_sprova(sprova,string_p,relacao);
  printf("Fato : %s\n",fato);
  printf("Suposicao : %s\n",suposicao);
  printf("Preciso provar : %s\n",sprova);
  printf("%s\n",fato);
  printf("     %s %dc(n/%d)^%d + %s\n",relacao,a,b,p,string_fn);
  if(fator==1)
  {
    printf("     = c%s + %s\n",string_p,string_fn);
  	sprintf(string_residual,"(- %s)",string_fn);
  	printf("     = c%s - %s <- desejado - residual\n",string_p,string_residual);
    printf("     %s c%s para nenhuma escolha com c > 0\n",relacao,string_p);
    printf("-----Nao foi possivel completar a prova!\n");
  }
  else
  {
    printf("     = %.2f*c%s + %s\n",fator,string_p,string_fn);
  	sprintf(string_residual,"(%.2f*c%s - %s)",1-fator,string_p,string_fn);
  	printf("     = c%s - %s <- desejado - residual\n",string_p,string_residual);
  	if(fator > 1)
  	{
  		printf("     %s c%s para nenhuma escolha com c > 0!\n",relacao,string_p);
    	printf("-----Nao foi possivel completar a prova!\n");
  	}
  	else
  	{
		if(p>=fn)
		{
		  printf("     %s c%s <- desejado\n",relacao,string_p);
	  	  printf("Quando (%s) >= 0, por exemplo,\n",string_residual);
	  	  printf("se c >= %.2f e n >= 2\n",1/(1-fator));
		}
		else
		{
  		  printf("     %s c%s para nenhuma escolha com c > 0!\n",relacao,string_p);
	  	  printf("-----Nao foi possivel completar a prova!\n");
		}
	}
  }
}

void do_OMEGA(int a, int b, int fn, int p, int c)
{
  char fato[21];
  char suposicao[18];
  char sprova[11];
  char string_fn[4];
  char string_p[4];
  char string_residual[100];
  char relacao[3] = ">=";
  float fator = (float)(a/pow(b,p));
  get_polinomio(string_fn,fn);
  get_polinomio(string_p,p);
  get_fato(fato,a,b,string_fn);
  get_suposicao(suposicao,b,p,relacao);
  get_sprova(sprova,string_p,relacao);
  printf("Fato : %s\n",fato);
  printf("Suposicao : %s\n",suposicao);
  printf("Preciso provar : %s\n",sprova);
  printf("%s\n",fato);
  printf("     %s %dc(n/%d)^%d + %s\n",relacao,a,b,p,string_fn);
  if(fator==1)
  {
    printf("     = c%s + %s\n",string_p,string_fn);
    sprintf(string_residual,"%s",string_fn);
  	printf("     = c%s + %s <- desejado + residual\n",string_p,string_residual);
    printf("     %s c%s <- desejado\n",relacao,string_p);
    printf("Quando (%s) >= 0, por exemplo,\n", string_fn);
    printf("se n >= 1\n");
  }
  else
  {
    printf("     = %.2f*c%s + %s\n",fator,string_p,string_fn);
    sprintf(string_residual,"(%.2f*c%s + %s)",fator-1,string_p,string_fn);
  	printf("     = c%s + %s <- desejado + residual\n",string_p,string_residual);
  	if(fator > 1)
  	{
  		printf("     %s c%s <- desejado\n",relacao,string_p);
	    printf("Quando (%s) >= 0, por exemplo,\n", string_residual);
	    printf("se c >= 1 e n>=1\n");
  	}
  	else
  	{
		if(p>=fn)
		{
		  printf("     %s c%s para nenhuma escolha com c > 0!\n",relacao,string_p);
	  	  printf("-----Nao foi possivel completar a prova!\n");
		}
		else
		{
  		  printf("     %s c%s <- desejado\n",relacao,string_p);
	  	  printf("Quando (%s) >= 0, por exemplo,\n",string_residual);
	  	  printf("se c >= %.2f e n >= 2\n",1/(1-fator));
		}
	}
  }
}

void get_fato(char* buffer, int a, int b, char* string_fn)
{
  sprintf(buffer,"T(n) = %dT(n/%d) + %s",a,b,string_fn);
}

void get_suposicao(char* buffer, int b, int p,char *relacao)
{
  sprintf(buffer,"T(n/%d)%sc(n/%d)^%d",b,relacao,b,p);
}

void get_sprova(char* buffer, char *string_p,char *relacao)
{
  sprintf(buffer,"T(n)%sc%s",string_p,relacao);
}


void show_prova(int a, int b, int fn, int p, int c)
{
  switch(c)
  {
    case O:
      do_O(a,b,fn,p,c);
      break;
    case OMEGA:
      do_OMEGA(a,b,fn,p,c);
      break;
    case TETA:
      do_O(a,b,fn,p,c);
      do_OMEGA(a,b,fn,p,c);
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

void get_fator(frac *_fator,char* buffer, float fator)
{
  *_fator = to_frac(fator,10);
  switch(_fator->num)
  {
    case 1:
      if(_fator->denom==1)
      {
        strcpy(buffer,"c");
      }
      else
      {
      	sprintf(buffer, "(c/%d)",_fator->denom);
      }
      break;
    default:
      sprintf(buffer, "(c*%d/%d)",_fator->num,_fator->denom);
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
  int a,b,p,fn,c;
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
  
  //Print inicial
  show_prova(a, b, fn, p, c);
 
  return 0;
}
