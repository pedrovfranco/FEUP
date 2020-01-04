// Vending Machine with Counting
//MFES-2019/20
active proctype P() {
int max = 10, nsoda = 10, nbeer = 10;
do :: true ->// inserting a coin
	    printf("beers %d and sodas %d\n",nbeer,nsoda);
      	     if :: nsoda > 0 -> nsoda = nsoda - 1
	     :: nbeer > 0 -> nbeer = nbeer - 1
	     :: nsoda == nbeer == 0 -> skip
	     fi
   :: true ->
      //filling the machine
       atomic{nsoda = max; nbeer = max}	     
od	     
}