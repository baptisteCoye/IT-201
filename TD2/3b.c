#include<stdlib.h>
#include<stdio.h>

void wakeup(int length) {
	irq_disable();

	received_count += length;

	while(sleepq) {
		struct proc * myproc = sleepq;
		sleepq = myproc -> pnext;
		myproc -> p_stat = STATUS_READY;
		myproc -> p_next = runq;
		runq = myproc;
	}
	irq_enable();
}

# ATTENTION : Vu qu'on relache les irq autour du consume() des nouveaux octets ont pu arriver

void wait(int length) {
	while(length) {
		irq_disable();
		/* On lit ce qu'on peut */
		if(receive_count) {
			int consumed = min(received_count, length);
			received_count -= consumed;
			irq_enable();
			consume(consumed);
			length -= consumed;
		}
		else {
			/* On a plus rien à lire il faut dormir */
			current -> p_stat = STATUS_BLOCKED;
			current -> p_next = sleepq;
			sleepq = current;
			irq_enable();
			switch();
		}
	}
}

