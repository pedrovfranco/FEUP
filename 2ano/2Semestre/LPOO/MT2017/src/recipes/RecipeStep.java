package recipes;

import java.util.TreeSet;

public class RecipeStep extends Ingredient
{
	protected String action;
	
	private TreeSet< Pair<Ingredient, Float> > ingredients = new TreeSet< Pair<Ingredient, Float> >(new PairComparator());
	
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
	
	public boolean addIngredient(Ingredient input, float quantity)
	{
		return ingredients.add(new Pair<Ingredient, Float>(input, quantity));
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
		
		for (Pair<Ingredient, Float> it : ingredients)
		{
			if (it.getFirst() instanceof RecipeStep)
			{
				Pair<RecipeStep, Float> foo = new Pair<RecipeStep, Float>((RecipeStep) it.getFirst(), it.getSecond());
				
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
				if (it.getFirst().getName().equals(input.getName()))
					sum += it.getSecond();
			}
		}
		
		return sum;
	}
	
	public int getIngredientCount()
	{
		return ingredients.size();
	}
	
	public TreeSet< Pair<Ingredient, Float> > getIngredients()
	{
		return ingredients;
	}
	
	@Override
	public String toString()
	{		
		String res = "to make " + name + ", " + action + " ";
		
		for (Pair<Ingredient, Float> it : ingredients)
		{
			res += it.getSecond() + " " + it.getFirst().getName();
			
			if (it != ingredients.last()) //If not last one
				res += ", ";
		}
		
		return res;
	}
}
