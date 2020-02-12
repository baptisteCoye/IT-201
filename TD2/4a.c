


struct event {
	struct sleepq * sleepq;
	struct lock * lock;
	void * function_callback;
}

void wait() {
	lock();
	while(1){
		if(function_callback() == true){
			consume();
		}
		else{
			add_sleepq();
		}
	}
	unlock();
}

void wakeup() {
	lock();
	update();
	/* wakeup_sleepq permet de réveiller les processus en sommeil sur la sleepq*/
	wakeup_sleepq();
	unlock();
}



