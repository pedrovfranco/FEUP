//several processes with shared variables
//Ben-Ari
//MFES 2019-20
byte n = 0;
active [2] proctype P() {
       byte temp;
       temp = n+1;
       n = temp;
       printf("P%d, n=%d\n",_pid,n)
}
