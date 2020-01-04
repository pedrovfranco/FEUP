//Mutual Exclusion with  deadlock
//Ben-Ari 2010
//MFES 2019-20
bool wantP = false, wantQ = false;

active proctype P() {
do
	:: printf("Not critical P\n");
	   wantP = true;
	   !wantQ;
 	   printf("Critical P\n");
	   wantP = false
od
}

active proctype Q() {
do
	:: printf("Not critical Q\n");
	   wantQ = true;
	   !wantP;
 	   printf("Critical Q\n");
	   wantQ= false
od
}