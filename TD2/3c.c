#include<stdlib.h>
#include<stdio.h>

/* dans un premier temps on rajoute une longueur de lecture pour chaque processus
 *
 * struct proc {
 *
 * 	int p_waitlength;
 *
 * 	}
 *
 * 	*/

void wakeup(int length) {
	irq_disable();

	received_count += length;

	while (sleepq && length > 0) {
		struct proc * myproc = sleepq;
		sleepq = myproc -> p_next;
		myproc -> p_stat = STATUS_READY;
		myproc -> p_next = runq;
		int given = min(length, myproc -> p_waitlength);
		runq = myproc;
	}
	irq_enable();
}

void wait(int length) {
	while (length) {
		irq_disable();
		while(receive_count) {
			int consumed = min(received_count, length);
			received_count -= consumed;
			irq_enable();
			consume(consumed);
			length -= consumed;
		}
		current -> p_waitlength = length;
		current -> p_stat = STATUS_BLOCKED;
		current -> p_next = sleepq;
		sleepq = current;
		irq_enable();
		switch();
	}
}
