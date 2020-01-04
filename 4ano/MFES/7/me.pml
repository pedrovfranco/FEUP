//Mutual exclusion wrong
//Ben-Ari 2008
//MFES 2019-20

bool wantP = false, wantQ = false;
int critical = 0;

active proctype P() {
do
	:: printf("No critical P\n");
	   wantP = true;
	   critical++;
 	   printf("Critical P\n");
	   assert(critical <= 1);
	   critical--;
	   wantP = false
od
}

active proctype Q() {
do
	:: printf("No critical Q\n");
	   wantQ = true;
	   critical++;
 	   printf("Critical Q\n");
	   assert(critical <= 1);
	   critical--;
	   wantQ= false
od
}