package circuits;

public class GateNot extends LogicGate
{
	public GateNot(LogicVariable output, LogicVariable input1) throws ColisionException, CycleException
	{
		super(output, input1);
	}
	
	@Override
	public LogicVariable[] getInputs()
	{
		LogicVariable[] ret = {input1};
		return ret;
	}
	
	public String getSymbol()
	{
		return "NOT";
	}
	
	@Override
	public String getFormula()
	{
		return (this.getSymbol() + "(" + input1.getFormula() + ")");
	}
	
	public boolean calculate()
	{
		if (input1.gate != null)
		{
			input1.calculate();
		}
		
		output.value = !input1.value;
		
		return output.value;
	}
}
