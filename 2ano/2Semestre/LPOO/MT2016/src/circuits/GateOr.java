package circuits;

public class GateOr extends LogicGate
{
	public GateOr(LogicVariable output, LogicVariable input1, LogicVariable input2) throws ColisionException, CycleException
	{
		super(output, input1, input2);
	}
	
	public String getSymbol()
	{
		return "OR";
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
		
		output.value = input1.value || input2.value;
		
		return output.value;
	}
}
