#include<stdio.h>
#include<stdlib.h>

void wait() {

	//irq_disable();
/* Dans un premier temps on s'ajoute au début de la Sleep Queue */
	current -> p_next =sleepq;
	sleepq = current;
/* A partir de là on se note en sleep sur l'évènement */
	current -> p_stat = STATUS_BLOCKED;
/* Une fois qu'on sleep on peut laisser la main au autres processus */
	//irq_enable();
	switch();
}

void wakeup() {
/* On vérifie dans un premier temps l'état de notre Sleep Queue voir si il y a du travail a faire */
	//irq_disable();
	while(sleepq) {
		/* On prélève le premier élément de la Sleep Queue */
		struct proc * myproc = sleepq;
		/* On pense à redécaller la tête de la Sleep Queue */
		sleepq = myproc -> p_next;
		myproc -> p_next = NULL;
		/* On marque le processus comme actif */
		myproc -> p_stat = STATUS_READY;
		/* On s'ajoute sur la Run Queue */
		myproc -> p_next = runq;
		runq = myproc;
	}
	// sleepq = NULL;
	// irq_enable();
}


