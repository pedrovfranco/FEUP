// shared variables
//Ben-Ari
//MFES 2019-20
byte n;

proctype P(byte id; byte incr) {
       byte temp;
       temp = n + incr;
       n = temp;
       printf("P%d, n=%d\n", id, n)
}

init {
n = 0;
run P(1,10);
run P(2,15)
}