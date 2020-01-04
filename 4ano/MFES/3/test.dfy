// Finds a value 'x' in a sorted array 'a', and returns its index,
// or -1 if not found. 


predicate isSorted(a: array<int>)
reads a
{
    forall i, j :: 0 <= i < j < a.Length ==> a[i] <= a[j]
}

predicate notIncludes(a: array<int>, x: int)
reads a
{
    forall i :: 0 <= i < a.Length ==> a[i] != x
}

method binarySearch(a: array<int>, x: int) returns (index: int)
requires isSorted(a) && a.Length > 0
ensures ((index == -1 && notIncludes(a, x)) || (0 <= index < a.Length && a[index] == x))
{
    var lastA := a;
    var low, high := 0, a.Length;
    while low < high
    decreases high-low
    invariant 0 <= low <= high <= a.Length
    invariant forall i :: 0 <= i < low || high <= i < a.Length ==> a[i] != x
    {
        var mid := low + (high - low) / 2;
        if 
        {
            case a[mid]  < x => low := mid + 1;
            case a[mid]  > x => high := mid;
            case a[mid] == x => return mid;
        }
    }

    return -1;
}

predicate sorted(a: array<int>, start: int , end: int)
requires 0 <= start <= end < a.Length
reads a
{
    forall i, j :: start <= i < j <= end ==> a[i] <= a[j]
}
method insertionSort(a: array<int>)
requires a.Length > 0
modifies a
ensures sorted(a, 0, a.Length-1)
{
    var i := 0;
    while i < a.Length 
    decreases a.Length-i
    invariant 0 <= i < a.Length
    invariant sorted(a, 0, i)
    {
        var j := i;
        while j > 0 && a[j-1] > a[j]
        decreases j
        invariant 0 <= j < a.Length
        invariant forall k :: j <= k <= i ==> a[k] >= a[j]
        {
            a[j-1], a[j] := a[j], a[j-1];
            j := j - 1;
        }
        i := i + 1;

        if (i == a.Length)
        {
            break;
        }
    }
}


method Main()
{
    // var a = new array;
    // a[0], a[1], a[2] := 1,2,3;

    // var foo := binarySearch(a, 4);

    print 0;
}