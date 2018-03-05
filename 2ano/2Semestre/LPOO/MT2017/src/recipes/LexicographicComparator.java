package recipes;

import java.util.Comparator;

public class LexicographicComparator implements Comparator<Pair<Ingredient, Float>> {
    
    public int compare(Pair<Ingredient, Float> a, Pair<Ingredient, Float> b) {
        return a.getFirst().getName().compareToIgnoreCase(b.getFirst().getName());
    }
}
