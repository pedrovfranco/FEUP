package building;

import java.util.HashSet;
import java.util.Set;

public class Building extends Facility
{
	private String name;
	private int minFloor;
	private int maxFloor;
	private int capacity;
	
	private Set<Room> rooms = new HashSet<Room>();
	
	public Building(String name, int minFloor, int maxFloor) throws IllegalArgumentException
	{
		if (name == null)
			throw new IllegalArgumentException();
		
		if (maxFloor < minFloor)
			throw new IllegalArgumentException();
		
		this.name = name;
		this.minFloor = minFloor;
		this.maxFloor = maxFloor;
		this.capacity = 0;
	}

	public String getName()
	{
		return name;
	}
	
	public int getMinFloor()
	{
		return minFloor;
	}
	
	public int getMaxFloor()
	{
		return maxFloor;
	}

	public String toString()
	{
		return ("Building(" + name + ")");
	}
	
	public int getCapacity()
	{
		return capacity;
	}
	
	public void setCapacity(int capacity)
	{
		this.capacity = capacity;
	}
	
	public void addRoom(Room input) throws DuplicateRoomException
	{
		if (!rooms.add(input))
			throw new DuplicateRoomException();
		else
			capacity += input.getCapacity();
	}
	
	public boolean canEnter(User input)
	{
		for (Room room : rooms)
		{
			if (room.canEnter(input))
				return true;
		}
		return false;
	}
}
