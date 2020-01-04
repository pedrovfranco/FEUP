// mutual exclusion with semaphore
// Ben-Ari 2010
// MFES 2019-20
#define mutex (critical >2)

byte y = 1;
int critical = 0;

active [2] proctype P() {
do
	:: printf("Not critical %d\n",_pid); 
	    atomic{
	     y > 0 -> y--;
	     }
	     critical++;
 	     printf("Critical %d\n",_pid);
	     critical--;
	     y++
od
}

ltl P1 { [] mutex }
