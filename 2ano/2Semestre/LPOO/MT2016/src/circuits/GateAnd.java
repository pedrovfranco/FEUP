package circuits;

public class GateAnd extends LogicGate
{
	public GateAnd(LogicVariable output, LogicVariable input1, LogicVariable input2) throws ColisionException, CycleException
	{
		super(output, input1, input2);
	}
	
	public String getSymbol()
	{
		return "AND";
	}
	
	public boolean calculate()
	{
		if (input1.gate != null)
		{
			input1.calculate();
		}
		if (input2.gate != null)
		{
			input2.calculate();
		}
		
		output.value = input1.value && input2.value;
		
		return output.value;
	}
}
