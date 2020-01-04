//concurrent processes
//Ben-Ari
//MFES 2019-20
byte n = 0;
active proctype P() {
       n = 1;
       printf("P, n=%d\n",n);
}

active proctype Q() {
      n = 2;
       printf("Q, n=%d\n",n);
}