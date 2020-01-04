//use of  assert for the correction of sequential programs
//Ben-Ari
//MFES 2019-20
active proctype P() {
int a  = 7, b = 5, max;
if
:: a >= b -> max = a
:: b >= a  -> max = b
fi;
printf("max %d\n", max);
assert (a>=b -> max ==a : max ==b);

}

// init {P()}
