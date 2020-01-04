method swap(a: int, b: int) returns (x: int , y: int)
ensures x==b && y==a
{
    x := b;
    y := a;
}

function method fib(n: nat) : nat
decreases n
{
    if (n < 2) then n else fib(n-1) + fib(n-2)
}


method fib2(n: nat) returns (value : nat)
{
    var i := 0;
    value := 0;
    var y := 1;
    while (i < n)
    {
        value, y := y, value + y;
        i := i + 1;
    }
}

method fib3(n: nat) returns (value: nat)
ensures value == fib(n)
{
    var i := 0;
    value := 0;
    var y := 1;

    while (i < n)
    decreases n-i
    invariant value == fib(i)
    invariant y == fib(i+1)
    invariant 0 <= i <= n
    {
        value, y := y, value + y;
        i := i + 1;
    }
}

function method fact(n: nat) : nat
decreases n
{
    if (n == 0) then 1 else n*fact(n-1)
}

method fact2(n: nat) returns (value: nat)
ensures value == fact(n)
{
    value := 1;
    var i := 0;

    while (i < n)
    decreases n-i
    invariant value == fact(i)
    invariant 0 <= i <= n
    {
        i := i + 1;
        value := value * i;
    }
}

method Main()
{
    var index := 8;
    var foo := fact2(index);
    var foo2 := fact(index); 
    
    assert foo == foo2;

    print foo;
}