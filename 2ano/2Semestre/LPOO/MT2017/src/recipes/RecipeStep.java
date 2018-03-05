package recipes;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class RecipeStep extends Ingredient
{
	protected String action;
	
	private List< Pair<Ingredient, Float> > ingredients = new ArrayList< Pair<Ingredient, Float> >();
	
	public RecipeStep(String name, String action)
	{
		super(name);
		
		if(action == null)
			throw new IllegalArgumentException();
		
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
		
		for (int i = 0;  i < ingredients.size(); i++)
		{
			if (ingredients.get(i).getFirst().getName().equals(input.getName()))
				return;
		}
		
		ingredients.add(foo);
	}
	
	public void addIngredient(Ingredient input, int quantity)
	{
		this.addIngredient(input, new Float(quantity));
	}
	
	public void addIngredient(RecipeStep input, float quantity)
	{
		addIngredient((Ingredient)input, quantity);
	}
	
	public void addIngredient(RecipeStep input, int quantity)
	{
		addIngredient((Ingredient)input, new Float(quantity));
	}
	
	public Float getQuantity(Ingredient input)
	{
		Float sum = new Float(0);
		
		for (int i = 0; i < ingredients.size(); i++)
		{
			if (ingredients.get(i).getFirst() instanceof RecipeStep)
			{
				Pair<RecipeStep, Float> foo = new Pair<RecipeStep, Float>((RecipeStep) ingredients.get(i).getFirst(), ingredients.get(i).getSecond());
				
				if (foo.getFirst().getName().equals(input.getName()))
				{
					if (foo.getFirst().getQuantity(input) > 0)
						sum += foo.getFirst().getQuantity(input) * foo.getSecond();
					else
						sum += foo.getSecond();
				}
				else
				{
					sum += foo.getFirst().getQuantity(input) * foo.getSecond();
				}
			}
			else
			{
				if (ingredients.get(i).getFirst().getName().equals(input.getName()))
					sum += ingredients.get(i).getSecond();
			}
		}
		
		return sum;
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
