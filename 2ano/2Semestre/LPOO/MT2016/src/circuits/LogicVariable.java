package circuits;

public class LogicVariable
{
	private String name;
	protected boolean value;
	protected LogicGate gate;
	
	public LogicVariable(String name, boolean value)
	{
		if (name == null)
			throw new IllegalArgumentException();
		
		this.name = name;
		this.value = value;
	}
	
	public LogicVariable(String name)
	{
		if (name == null)
			throw new IllegalArgumentException();
		
		this.name = name;
		this.value = false;
	}
	
	public String getName()
	{
		return name;
	}
	
	public boolean getValue()
	{
		if (gate != null)
			return gate.calculate();
		else
			return value;
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
	
	public void setValue(boolean value)
	{
		this.value = value;
	}
	
	public boolean equals(Object o)
	{
		if (o == null || !(o instanceof LogicVariable))
			return false;
		else
		{
			LogicVariable foo = (LogicVariable) o;
			return (this.name.equals(foo.getName()));
		}
	}
	
	public LogicGate getCalculatedBy()
	{
		return gate;
	}
	
	public String getFormula()
	{
		if (gate == null)
			return name;
		else
			return gate.getFormula();
	}
	
	public boolean calculate()
	{
		if (gate != null)
			value = gate.calculate();
		return value; 
	}
}
