#include<stdlib.h>
#include<stdio.h>

/* Dans un premier temps on modifie la structure proc pour rajouter la connexion*/

struct proc {
	struct proc * p_next;
	int p_status;
	int waitlength;
	int p_waitconn;
}

struct conn {
	...
	int received_count;
	...
}

void wakeup(int length, struct conn * conn){
	irq_disable();

	received_count += length;

	while(sleepq && length > 0){
		/* On parcourt ici toute la liste de sleepq et on ne fait le wake up que sur les process qui attendent sur cette conn en particulier.
		 *
		 * On ne dépile donc pas forcément la tête de liste, il faudrait techniquement écrire un algo pour enlever un élément au milieu d'une liste simplement chainée mais c'est chiant pour pas grand chose
		 * */
	}

}


void wait(int length, struct conn * conn){
	while (length) {
		irq_disable();
		while(conn -> received_count){
			int consumed = min(received_count, length);
			received_count -= consumed;
			irq_enable();
			consume(consumed);
			length -= consumed;
		}
		current -> p_waitlength = length;
		current -> p_stat = STATUS_BLOCKED;
		current -> p_next = sleepq;
		current -> p_waitconn = conn;
		sleepq = current;
		irq_enable();
		switch();
	}
}



/* 3f */

struct conn {
	...
	int received_count;
	struct sleepq * sleepq;
	...
}

