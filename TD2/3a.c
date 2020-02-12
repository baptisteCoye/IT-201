#include<stdio.h>
#include<stdlib.h>

void wakeup() {
	irq_disable();

	received_count++;

	while(sleepq){
		struct proc* myproc = sleepq;
		sleepq = myproc -> pnext;
		myproc -> p_stat = STATUS_READY;
		myproc -> p_next = runq;
		runq = myproc;
	}
	irq_enable();
}

void wait() {
	while(1){
		irq_disable();
		if (received_count) {
			/* On a bien reçu un paquet, on peut le traiter */
			received_count--;
			irq_enable();
			/* On peut maintenant le consume sans prendre de risque qu'un autre le prenne */
			consume();
			return;
		}
		current -> p_stat = STATUS_BLOCKED;
		current -> p_next = sleepq;
		sleepq = current;
		irq_enable();
		switch();
	}
}



