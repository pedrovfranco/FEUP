package recipes;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class RecipeStep extends Ingredient
{
	private String name;
	private String action;
	
	private List< Pair<Ingredient, Float> > ingredients = new ArrayList< Pair<Ingredient, Float> >();
	
	public RecipeStep(String name, String action)
	{
		super(name);;
		
		this.name = name;
		this.action = action;
	}
	
	public String getName()
	{
		return name;
	}
	
	public String getAction()
	{
		return action;
	}
	
	public void addIngredient(Ingredient input, float quantity)
	{
		Pair<Ingredient, Float> foo = new Pair<Ingredient, Float>(input, quantity);
		if (!ingredients.contains(foo))
		{
			ingredients.add(foo);
		}
			
	}
	
	public void addIngredient(Ingredient input, int quantity)
	{
		Pair<Ingredient, Float> foo = new Pair<Ingredient, Float>(input, (float)quantity);
		if (!ingredients.contains(foo))
		{
			ingredients.add(foo);
		}
			
	}
	
	public void addIngredient(RecipeStep input, int quantity)
	{
		Pair<RecipeStep, Float> foo = new Pair<RecipeStep, Float>(input, (float)quantity);
		if (!ingredients.contains(foo))
		{
			ingredients.add(foo);
		}
	}
	
	public Float getQuantity(Ingredient input)
	{
		for (int i = 0; i < ingredients.size(); i++)
		{
			if (ingredients.get(i).getFirst() instanceof RecipeStep)
			{
				return ingredients.get(i).getSecond();
			}
				
		}
		
		return 0F;
	}
	
	public int getIngredientCount()
	{
		return ingredients.size();
	}
	
	public List< Pair<Ingredient, Float> > getIngredients()
	{
		return ingredients;
	}
	
	@Override
	public String toString()
	{
		Collections.sort(ingredients, new LexicographicComparator());
		
		String res = "to make " + name + ", " + action + " ";
		
		for (int i = 0; i < ingredients.size(); i++)
		{
			res += ingredients.get(i).getSecond() + " " + ingredients.get(i).getFirst().getName();
			
			if (i != ingredients.size()-1) //If not last one
				res += ", ";
		}
		
		return res;
	}
}
