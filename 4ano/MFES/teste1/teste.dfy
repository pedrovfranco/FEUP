// method A(y: int, x: int ) returns (z: int)
// requires y > 0
// ensures z > x
// {
//     z:= x-y;
// }

// method B() returns (b: int)
// requires a == 0
// ensures a == 3*b
// {
//     var a:= 0;
//     a:=a+b;
//     b := b/3;
// }


method B()
{
    {
        var a:int, b: int; a:= 0; a:=a+b; b := b/3; assert a == 3*b;
    }
}

method A()
{
    {
        var x:int, y: int, z: int; assume y > 0; z:= x-y; assert z > x;
    }
}

method test()
{
}

method Main()
{
    test();
}
