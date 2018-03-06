package recipes;

import java.util.ArrayList;
import java.util.List;

public class Recipe
{
	private String name;
	private List<RecipeStep> steps = new ArrayList<RecipeStep>();
	
	public Recipe(String name)
	{
		if (name == null)
			throw new IllegalArgumentException();
		
		this.name = name;
	}

	public int getStepCount()
	{
		return steps.size();
	}

	public void addStep(RecipeStep input)
	{
		if (!steps.contains(input))
		{
			steps.add(input);
		}
		
	}


}
