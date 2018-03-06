package building;

public class User
{
	private String name;
	
	public User(String name) throws IllegalArgumentException
	{
		if (name == null)
			throw new IllegalArgumentException();
		
		this.name = name;
	}
	
	public String getName()
	{
		return name;
	}
	
	@Override
	public boolean equals(Object obj)
	{
		if (obj == null)
			return false;
		
		if (!(obj instanceof User))
			return false;
		
		User foo = (User) obj;
		
		return name.equals(foo.getName());
	}
}
