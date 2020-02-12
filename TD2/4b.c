/* On creer une liste d'évènement attendu pour chaques processus */

struct events {

	struct event event;
	struct event * next_event;

}

void wait_any(struct events){

	while(events){
		if(events -> event.callback()){
			consume(events -> event);
			return;
		} /* Techniquement se ferait avec des IF sur chacun des élèments de la chaine mais plus compréhensible comme ça */
		else {
			/* On ajoute les maillons de chaînes pour sleepq */
			add_sleepq(events -> event);
			switch();
			/* Maintenant qu'on a switch on peut relacher les maillons */
			release_sleepq(events->event);
		}
	}
}

void wakeup(struct events){
	Parcours la sleepq
	add_runq()
	// !! On ne les supprime plus de la sleepq vu qu'ils seront enlever dans le wait après coup
}
			
/*

/!\ Impose de ne pas utiliser le même maillon pour la runq et les sleepq

*/

void waitAll(){
	wait1();
	wait2();
	...
}

/*
 *En général ça ne sert à rien en pratique car on préfère dormir et laisser le main 
 */
 

