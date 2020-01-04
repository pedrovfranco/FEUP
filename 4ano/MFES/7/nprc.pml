//processes with shared variables
//check  which are  the maximun and minimun value
//Ben-Ari
//MFES 2019-20
int n = 0;

proctype P() {
       int temp, i = 1;     
       do 
          :: i > 10 -> break
	  :: else ->
          temp = n + 1;
       	  n = temp
	  i =  i + 1
	od
}

init {
atomic{run P();
run P()
}


(_nr_pr == 1) ->
printf("value %d\n", n);

}
