#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

	int
	main()
{
	pid_t pid;
	char nome[5] = "MARIA";
	int status = 0;

	fprintf(stdout, "proc-%c  getppid:%ld  getpid:%ld\n Acaba de ser criado\n \n", nome[0], (long)getppid(), (long)pid);
	pid = fork();
	if (pid == 0)
	{
		fprintf(stdout, "proc-%c  getppid:%ld getpids:%ld\n Acaba de ser criado\n", nome[1], (long)getppid(), (long)pid);

		pid = fork();
		if (pid == 0)
		{

			fprintf(stdout, "proc-%c  getppid:%ld  getpid:%ld\n Acaba de ser criado\n", nome[3], (long)getppid(), (long)pid);
			fprintf(stdout, "proc-%c  getppid:%ld  getpid:%ld\n morreu\n", nome[3], (long)getppid(), (long)pid);
			exit(0);
		}
		waitpid(pid, &status, 0);
		fprintf(stdout, "proc-%c  getppid:%ld getpids:%ld\n morreu\n", nome[1], (long)getppid(), (long)pid);
		exit(0);
	}
	waitpid(pid, &status, 0);
	pid = fork();
	if (pid == 0)
	{
		fprintf(stdout, "proc-%c  getppid:%ld  getpid:%ld\n Acaba de ser criado\n", nome[2], (long)getppid(), (long)pid);
		fprintf(stdout, "proc-%c  getppid:%ld  getpid:%ld\n morreu\n", nome[2], (long)getppid(), (long)pid);
		exit(0);
	}
	waitpid(pid, &status, 0);
	fprintf(stdout, "proc-%c  getppid:%ld  getpid:%ld\n morreu\n \n", nome[0], (long)getppid(), (long)pid);
	exit(0);

	return 0;
}
