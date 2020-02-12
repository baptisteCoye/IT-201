

struct semaphore {
	struct lock lock;
	int count;
	struct proc * proc
}

void sem_init(struct semaphore){
	semaphore -> lock = STATUS_READY;
	semaphore -> count = 0;
	semaphore -> proc = NULL;
}

void sem_wait(struct semaphore, struct proc * proc){
	semaphore -> lock = STATUS_BLOCKED;
	if (semaphore -> count > 0){
		semaphore -> count--;
		return;
	}
	else {
		proc -> p_next = semaphore -> proc;
		semaphore -> proc = proc;
		semaphore -> lock = STATUS_READY;
		switch();
		sem_wait(semaphore, proc);
	}
}


void sem_post(struct semaphore){
	semaphore -> lock = STATUS_BLOCKED;
	if(proc = NULL) {
		semaphore -> count++;
		semaphore -> lock = STATUS_READY;
	}
	else{
		current = pop(semaphore -> proc);
		wakeup(current);
		sempahore -> lock = STATUS_READY;
	}
}


/* Techniquement le wake et wait ne change pas par rapport à la 3a à part que le recv_count devient le count de la sémaphore */


/* 5c */

/* Une variable de condition n'est rien de plus qu'une file d'attente 
 *
 * cond_signal -> réveil le 1er de la file
 *
 * cond_broadcast -> réveil tout le monde
 *
 * cond_wait -> endort à la fin de la liste
 *
 * CF man pthread_cond_wait()
 *
 *
 *
 * Similaire à une semaphore car :
 *
 * condition -> "compteur > 0"
 *
 * le compteur est modifié dès qu'on prend le verrou
 *
 * sem_wait fait cond_wait si compteur == 0 compteur--
 *
 * semp_post fait compteur++ puis cond_signal
 *
 * /
