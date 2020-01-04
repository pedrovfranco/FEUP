type T = int // for demo purposes, but could be another type
 
class {:autocontracts} Deque {
    // (Private) concrete state variables 
    const list: array<T>; // circular array, from list[start] (front) to list[(start+size-1) % list.Length] (back) 
    var start : nat; 
    var size : nat;

    // (Public) ghost variables used for specification purposes only
    ghost var elems: seq<T>;  // front at head, back at tail
    ghost const capacity: nat;

 
    constructor (capacity: nat)
    requires capacity > 0
    ensures this.capacity == capacity && |elems| == 0
    {
        list := new T[capacity];
        start := 0;
        size := 0;

        // Ghost statements
        elems := [];
        this.capacity := capacity;
    }

    predicate Valid()
    reads this
    {
        size <= list.Length &&
        capacity >= |elems| &&
        |elems| == size &&
        capacity == list.Length &&
        0 <= start < list.Length &&
        forall i :: 0 <= i < size ==> list[(start+i)%list.Length] == elems[i]
    }
 
    predicate method isEmpty() 
    {
        size == 0
    }
    
    predicate method isFull() 
    {
        size == list.Length
    }
 
    function method  front() : T 
    requires |elems| > 0 && capacity > 0
    {
        list[start]
    }
 
    function method /* {:verify false} */ back() : T 
    {
        list[(start + size - 1) % list.Length] 
    }
    
    method /* {:verify false}  */ push_back(x : T)
    requires !isFull()
    ensures elems == old(elems) + [x]
    {
        list[(start + size) % list.Length] := x;
        size := size + 1;

        // Ghost statements
        elems := elems + [x];
    }
 
    method {:verify false} pop_back()
    requires |elems| > 0
    {
        size := size - 1;

        // Ghost variables
        elems := elems[0..(|elems|-1)];
    }
 
    method {:verify false} push_front(x : T) 
    {
        if start > 0 {
            start := start - 1;
        }
        else {
            start := list.Length - 1;
        }
        list[start] := x;
        size := size + 1;
    }    
 
    method {:verify false} pop_front() 
    {
        if start + 1 < list.Length {
            start := start + 1;
        }
        else {
            start := 0;
        }
        size := size - 1;
    }


}
 
// A simple test scenario.
method testDeque()
{
    var q := new Deque(3);
    assert q.isEmpty();
    q.push_front(1);
    assert q.front() == 1;
    assert q.back() == 1;
    q.push_front(2);
    assert q.front() == 2;
    assert q.back() == 1;
    q.push_back(3);
    assert q.front() == 2;
    assert q.back() == 3;
    assert q.isFull();
    q.pop_back();
    assert q.front() == 2;
    assert q.back() == 1;
    q.pop_front();
    assert q.front() == 1;
    assert q.back() == 1;
    q.pop_front();
    assert q.isEmpty();

}


// method Main()
// {
//     var foo := [1,2,3];
//     print(foo);
//     print(foo[0..2]);
// }
