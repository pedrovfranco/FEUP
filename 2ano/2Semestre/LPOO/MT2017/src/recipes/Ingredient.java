package recipes;

public abstract class Ingredient implements Comparable<Ingredient>
{
	protected String name;
	
	public Ingredient(String name)
	{
		if (name == null)
			throw new IllegalArgumentException();
		else
			this.name = name;
	}
	
	public String getName()
	{
		return name;
	}
	
	@Override
	public boolean equals(Object obj)
	{
		if (obj != null)
		{
			Ingredient foo = (Ingredient) obj;
			return (this.name == foo.name);
		}
		
		return false;
	}

	@Override
	public String toString()
	{
		return name;
	}
	
	public int compareTo(Ingredient o)
	{
		if (o == null)
			return -1;
		else
		{
			Ingredient foo = (Ingredient) o;
			return this.getName().compareToIgnoreCase(foo.getName());
		}	
	}

}
