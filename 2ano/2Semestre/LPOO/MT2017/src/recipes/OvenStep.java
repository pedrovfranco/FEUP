package recipes;

import java.util.ArrayList;
import java.util.List;

public class OvenStep
{
	private String name;
	private String action;
	private int temperature;
	
	private List< Pair<SimpleIngredient, Float> > ingredients = new ArrayList< Pair<SimpleIngredient, Float> >(); 
	
	public OvenStep(String name, String action, int temperature)
	{
		this.name = name;
		this.action = action;
		this.temperature = temperature;
	}
	
	public void addIngredient(SimpleIngredient input, int quantity)
	{
		Pair<SimpleIngredient, Float> foo = new Pair<SimpleIngredient, Float>(input, (float) quantity);
		if (!ingredients.contains(foo))
		{
			ingredients.add(foo);
		}
	}
	
	public String getName()
	{
		return name;
	}
	
	public String getAction()
	{
		return action;
	}
	
	public int getTemperature()
	{
		return temperature;
	}
}
