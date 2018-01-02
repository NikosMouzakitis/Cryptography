#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>

#define BUF_SIZE 16
#define MTX "/mtx"
#define SHARED 1
#define MON1 "/mon1"
#define MON2 "/mon2"
#define COMPLETE "/cmp"
#define RUN "/run"

int m1,m2,c;
int fd[2];	// pipe
int counter1,counter2;	// counts messages coming from id1 and id2.
int valid_ids1[10] = {3,5,7,9,11,13,15,17,19,1};
int valid_ids2[10] = {4,6,8,10,12,14,16,18,0,2};

sem_t *mon1,*mon2,*complete;
pthread_mutex_t *mtx;
int *run_state;

void monitor2(int sig)
{
	int received_id;
	char buffer[BUF_SIZE];
	memset(buffer,0,BUF_SIZE);

	printf("-------------------\n");
	printf("Monitor2 runs\n");
	
	sem_wait(mon2);

	int n = read(fd[0],buffer,8);
	read(fd[0],&received_id,sizeof(int));
		
	if(received_id != valid_ids2[counter2 % 10]) {
		printf("INVALID RECEIVED_ID\n");
		*run_state = 0;	
	} else {
		printf("signal2: read %d bytes. %s\n",n,buffer);
		printf("received_id: %d\n",received_id);
	}
	counter2++;
	sem_post(complete);
}

void monitor1(int sig)
{
	int received_id;
	char buffer[BUF_SIZE];
	memset(buffer,0,BUF_SIZE);

	printf("-------------------\n");
	printf("Monitor1 runs\n");
	
	sem_wait(mon1);

	int n = read(fd[0],buffer,8);
	read(fd[0],&received_id,sizeof(int));

	if(received_id != valid_ids1[counter1 % 10] ) {
		printf("INVALID RECEIVED_ID.\n");
		*run_state = 0;	
	} else {
		printf("signal1: read %d bytes. %s\n",n,buffer);
		printf("received_id: %d\n",received_id);
	}
	counter1++;
	sem_post(complete);
}

int encrypt(int id)
{
	return (id+2)%20;
}

int main(int argc,char *argv[])
{
	int seg_mtx,seg_m1,seg_m2,seg_c;
	int mode = S_IRWXU | S_IRWXG;
	int seg_run;
	pid_t pid1,pid2;
	
	if(signal(SIGUSR1,monitor1) == SIG_ERR) {
		perror("Unable to create handler1\n");
		exit(-1);
	}

	if(signal(SIGUSR2,monitor2) == SIG_ERR) {
		perror("Unable to create handler2\n");
		exit(-1);
	}

	seg_m1 = shm_open(MON1,O_CREAT | O_TRUNC | O_RDWR,mode);
	seg_m2 = shm_open(MON2,O_CREAT | O_TRUNC | O_RDWR,mode);
	seg_c = shm_open(COMPLETE,O_CREAT | O_TRUNC | O_RDWR,mode);
	seg_run = shm_open(RUN,O_CREAT | O_TRUNC | O_RDWR,mode);


	if( (seg_m1 < 0) || (seg_m2 < 0) || (seg_c < 0) || (seg_run < 0)  ) {
		perror("/shm_open\n");
		exit(-1);
	}

	if(ftruncate(seg_m1,sizeof(sem_t)) == -1) {
		perror("/ftruncate\n");
		exit(-1);
	}
	
	if(ftruncate(seg_m2,sizeof(sem_t)) == -1) {
		perror("/ftruncate\n");
		exit(-1);
	}
	
	if(ftruncate(seg_c,sizeof(sem_t)) == -1) {
		perror("/ftruncate\n");
		exit(-1);
	}
	
	if(ftruncate(seg_run,sizeof(int)) == -1) {
		perror("/ftruncate\n");
		exit(-1);
	}

	mon1 = (sem_t *)mmap(NULL,sizeof(sem_t),PROT_READ | PROT_WRITE,MAP_SHARED,seg_m1,0);
	mon2 = (sem_t *)mmap(NULL,sizeof(sem_t),PROT_READ | PROT_WRITE,MAP_SHARED,seg_m2,0);
	complete = (sem_t *)mmap(NULL,sizeof(sem_t),PROT_READ | PROT_WRITE,MAP_SHARED,seg_c,0);
	run_state = (int *) mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE,MAP_SHARED,seg_run,0);

	if( (mon1 == MAP_FAILED) || (mon2 == MAP_FAILED) || (complete == MAP_FAILED) || (run_state == MAP_FAILED) ) {
		perror("/mmap failed\n");
		exit(-1);
	}

	*run_state = 1;
	sem_init(mon1,SHARED,0);
	sem_init(mon2,SHARED,0);
	sem_init(complete,SHARED,0);

	seg_mtx = shm_open(MTX,O_CREAT | O_TRUNC | O_RDWR,mode);

	if(seg_mtx < 0) {
		perror("/shm_open\n");
		exit(-1);
	}
	
	if(ftruncate(seg_mtx,sizeof(pthread_mutex_t)) == -1 ) {
		perror("/ftruncate\n");
		exit(-1);
	}
	
	mtx = (pthread_mutex_t *)mmap(NULL,sizeof(pthread_mutex_t),PROT_READ | PROT_WRITE,MAP_SHARED,seg_mtx,0);
	
	if( mtx == MAP_FAILED) {
		perror("/mmap failed\n");
		exit(-1);
	}

	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_setpshared(&attr,PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(mtx,&attr);

	if(pipe(fd) == -1) {
		perror("/pipe failed.\n");
		exit(-1);
	}

	pid1 = fork();
	
	if(pid1 == 0) { //child1
		
		int id = 1;
		int crypto;
		int parent = getppid();
		char *msg1 = "message1";
		char *sender_id;

		sender_id = (char *)malloc(sizeof(int));

		if(sender_id == NULL) {
			perror("/malloc failed\n");
			exit(-1);
		}

		close(fd[0]);
		crypto = id;
		sleep(2);

		printf("Operating:%d with id: %d\n",getpid(),id);

		while(*run_state) {

			pthread_mutex_lock(mtx);

			crypto = encrypt(crypto);
			strcpy(sender_id,&crypto);
			printf("Encrypted: %d to %d\n",id,crypto);
			fflush(stdout);
			write(fd[1],msg1,strlen(msg1));
			write(fd[1],sender_id,sizeof(int));

			sem_post(mon1);
			
			kill(parent,SIGUSR1);

			sem_wait(complete);

			pthread_mutex_unlock(mtx);

			sleep(1);

		}
		exit(0);
	} else if( pid1 > 0) {
		
		pid2 = fork();

		if(pid2 == 0) { // child 2

			int id = 2;
			int crypto;
			int parent = getppid();
			char *msg2 = "message2";
			char *sender_id;
			sender_id = (char *)malloc(sizeof(int));
		
			if(sender_id == NULL) {
				perror("malloc failed\n");
				exit(-1);
			}
			
			memset(sender_id,0,sizeof(int));

			crypto = id;
			close(fd[0]);
			sleep(2);
			
			printf("Operating:%d with id: %d\n",getpid(),id);

			while(*run_state) {
			
				pthread_mutex_lock(mtx);
				
				crypto = encrypt(crypto);
				printf("encypted: %d to %d\n",id,crypto);
				fflush(stdout);
				strcpy(sender_id,&crypto);	
				write(fd[1],msg2,strlen(msg2));
				write(fd[1],sender_id,sizeof(int));
				sem_post(mon2);
				kill(parent,SIGUSR2);
				sem_wait(complete);

				pthread_mutex_unlock(mtx);

				sleep(1);
			}
			exit(0);
		} else { // main

			close(fd[1]);

			printf("Monitor: %d\n",getpid());
			printf("monitoring: %d %d \n",pid1,pid2);

			while(*run_state) {


			}

			for(int i = 0; i < 2; i++) 
				wait(0);
		}
	}
	return 0;
}
