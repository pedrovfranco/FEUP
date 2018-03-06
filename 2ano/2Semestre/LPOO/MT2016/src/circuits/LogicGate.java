package circuits;

public abstract class LogicGate
{
	protected LogicVariable output;
	protected LogicVariable input1;
	protected LogicVariable input2;
	
	public LogicGate(LogicVariable output, LogicVariable input1, LogicVariable input2) throws ColisionException, CycleException
	{
		if (output == null || input1 == null || input2 == null)
		{
			throw new IllegalArgumentException();
		}
		
		if (output.gate != null)
			throw new ColisionException();
		
		if (input1.gate != null)
		{
			LogicVariable[] foo = input1.gate.getInputs();
			for (int i = 0; i < foo.length; i++)
			{
				if (foo[i].equals(output))
					throw new CycleException();
			}
		}
		
		if (input2.gate != null)
		{
			LogicVariable[] foo = input2.gate.getInputs();
			for (int i = 0; i < foo.length; i++)
			{
				if (foo[i].equals(output))
					throw new CycleException();
			}
		}
			
		this.output = output;
		this.input1 = input1;
		this.input2 = input2;
		
		this.output.gate = this;
	}
	
	public LogicGate(LogicVariable output, LogicVariable input1) throws ColisionException, CycleException
	{
		if (output == null || input1 == null)
		{
			throw new IllegalArgumentException();
		}
		
		if (output.gate != null)
			throw new ColisionException();
		
		if (input1.gate != null)
		{
			LogicVariable[] foo = input1.gate.getInputs();
			for (int i = 0; i < foo.length; i++)
			{
				if (foo[i].equals(output))
					throw new CycleException();
			}
		}
		
		this.output = output;
		this.input1 = input1;
		
		this.output.gate = this;
	}
	
	public LogicVariable getOutput()
	{
		return output;
	}
	
	public LogicVariable[] getInputs()
	{
		LogicVariable[] ret = {input1, input2};
		return ret;
	}
	
	public abstract String getSymbol();
	
	public String getFormula()
	{
		return (this.getSymbol() + "(" + input1.getFormula() + "," + input2.getFormula() + ")");
	}
	
	public abstract boolean calculate();

}
