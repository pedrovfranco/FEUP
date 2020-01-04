// mutual exclusion  with busy-wait
//Ben-Ari 2010
bool wantP = false, wantQ = false;

active proctype P() {
do
	:: printf("Not critical P\n");
	   wantP = true;
	   do
	   :: 	!wantQ -> break
	   ::  else -> skip
	   od;
 	   printf("Critical P\n");
	   wantP = false
od
}

active proctype Q() {
do
	:: printf("Not critical Q\n");
	   wantQ = true;
	    do
	   :: 	!wantP -> break
	   ::  else -> skip
	   od;
 	   printf("Critical Q\n");
	   wantQ= false
od
}