/*Enunciado: Escreva um programa que realiza tratamento de sinais POSIX. 
O programa deve:
  - Contar quantas vezes o usuário envia o sinal SIGINT (Ctrl-C) para o processo em
execução.
  - Quando o sinal receber um SIGTSTP (Ctl-Z), ele deve imprimir o número de sinais
SIGINT que ele recebeu.
  -Depois de ter recebido 10 SIGINT’s, o programa deve “convidar” o usuário a sair
(“Really exit (Y/n)?”).
   - Se o usuário não responder em 5 seg., o programa finaliza
   - Se responder ‘Y’ manda um sinal de termino a ele próprio.
   - Se responder ‘n’ reinicia contagem*/
   
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int count = 0;

void SIGINT_count()
{
  count = count + 1;
}

void SIGTSTP_count()
{
  printf("contagem: %d", count);
}

void SIGALRM_kill()
{
  kill(getpid(), SIGKILL);
}

int main(void)
{
  signal(SIGINT, SIGINT_count);
  signal(SIGTSTP, SIGTSTP_count);
  signal(SIGALRM, SIGALRM_kill);

  char resp;

  for (;;)
  {
    pid_t pid = getpid();
    printf("pid=%ld\n", (long)pid);
    sleep(1);
    alarm(5);
    if (count == 10)
    {
      printf("Really exit(Y/n)?");
      scanf("%c", &resp);

      if (resp == 'Y')
      {
        kill(getpid(), SIGKILL);
      }
      else if (resp == 'n')
      {
        count = 0;
        alarm(0);
      }
    }
  }
}

// #include <signal.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int count = 0;

// void SIGINT_count()
// {
//   count = count + 1;
//   char resp;

//   if (count == 10)
//   {
//     printf("Really exit(Y/n)?");
//     scanf("%c", &resp);
//     alarm(5);

//     if (resp == 'Y')
//     {
//       kill(getpid(), SIGKILL);
//     }
//     else if (resp == 'n')
//     {
//       count = 0;
//       alarm(0);
//     }
//   }
// }

// void SIGTSTP_count()
// {
//   printf("contagem: %d", count);
// }

// int main(void)
// {
//   signal(SIGINT, SIGINT_count);
//   signal(SIGTSTP, SIGTSTP_count);
//   signal(SIGALRM, SIGKILL);

//   for (;;)
//   {
//     pid_t pid = getpid();
//     printf("pid=%ld\n", (long)pid);
//     sleep(1);
//   }
// }