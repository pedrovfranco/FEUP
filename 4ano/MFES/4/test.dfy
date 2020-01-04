type T = int // to allow doing new T[capacity], but can be other type 
 
class Stack
{
    const elems: array<T>; // immutable (pointer)
    var size : nat; // used size

    var cap : nat; // capacity
 
    constructor (capacity: nat)
    requires capacity > 0
    ensures Valid() && size == 0 && cap == capacity == elems.Length
    {
        cap := capacity;
        elems := new T[capacity];
        size := 0; 
    }
 
    predicate method /**/ isEmpty()
    reads this
    {
        size == 0
    }
 
    predicate method /**/ isFull()
    reads this
    {
        size == cap
    }
 
    method /**/ push(x : T)
    modifies this, elems
    requires size < elems.Length
    ensures old(size) == size - 1 && old(elems[..size-2]) + [x] == elems[..size-1]
    {
        elems[size] := x;
        size := size + 1;
    }
 
    function method /**/ top(): T
    reads elems, this
    requires size > 0 && Valid()
    {
        elems[size-1]
    }
    
    method /**/ pop()
    modifies this
    {
        if (size > 0)
        {
            size := size-1;
        }
    }

    predicate Valid()
    reads this
    {
        size <= cap == elems.Length
    }
}

predicate arrayEquals(a: array<int>, ia: nat, ja: nat, b: array<int>, ib: nat, jb: nat)
requires 0 <= ia <= ja < a.Length && 0 <= ib <= jb < b.Length
reads a, b
{
    // if (ja - ia != jb - ib) then
    // {
    //     false
    // }
    // else
    // {
    //     if (ja - ia == 0) then
    //         true
    //     else
    //         forall i, j :: ia <= i <= ja && ib <= j <= jb ==> a[i] == b[j]
    // }

    !((ja - ia == jb - ib) ==> !(ja - ia == 0 ||  forall i, j :: ia <= i <= ja && ib <= j <= jb ==> a[i] == b[j]))
}

// A simple test case.
method /**/ Main()
{
    var s := new Stack(3);
    assert s.isEmpty();
    s.push(1);
    s.push(2);
    s.push(3);
    assert s.top() == 3;
    assert s.isFull();
    s.pop();
    assert s.top() == 2;
    print "top = ", s.top(), " \n";
}
