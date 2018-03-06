package circuits;

import java.util.ArrayList;
import java.util.List;

public class CombinatorialCircuit
{
	List<LogicVariable> variables = new ArrayList<LogicVariable>();
	
	public boolean addVariable(LogicVariable a)
	{
		if (a == null)
			return false;
		
		for (int i = 0; i < variables.size(); i++)
		{
			if (variables.get(i).equals(a))
				return false;
		}
		
		variables.add(a);
		return true;
	}
	
	public LogicVariable getVariableByName(String name)
	{
		int index = variables.indexOf(new LogicVariable(name));
		
		if (index == -1)
			return null;
		else
			return variables.get(index);
	}

}
