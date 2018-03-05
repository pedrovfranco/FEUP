package recipes;

import java.util.ArrayList;
import java.util.List;

public class OvenStep extends RecipeStep
{
	private int temperature;
	
	private List< Pair<SimpleIngredient, Float> > ingredients = new ArrayList< Pair<SimpleIngredient, Float> >(); 
	
	public OvenStep(String name, String action, int temperature)
	{
		super(name, action);

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
		return super.name;
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
