package recipes;

public class Pair<T1, T2>
{
	private T1 first;
	private T2 second;
	
	public Pair(T1 first, T2 second)
	{
		if (first == null || second == null)
			throw new IllegalArgumentException();
		else
		{
			this.first = first;
			this.second = second;
		}
	}
	
	public void setFirst(T1 first)
	{
		this.first = first;
	}
	
	public void setSecond(T2 second)
	{
		this.second = second;
	}
	
	public T1 getFirst()
	{
		return first;
	}
	
	public T2 getSecond()
	{
		return second;
	}
	
	@Override
	public boolean equals(Object obj)
	{
		if (obj == null)
			return false;
		
		Pair<T1, T2> foo = (Pair<T1, T2>) obj;
		
		return this.first.equals(foo.first);
	}
}
