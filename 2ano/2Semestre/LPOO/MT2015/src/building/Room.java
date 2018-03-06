package building;

import java.util.HashSet;
import java.util.Set;

public class Room extends Facility
{
	private Building building;
	private String number;
	private int floor;
	private int capacity;
	
	Set<User> users = new HashSet<User>();

	public Room(Building building, String number, int floor) throws IllegalArgumentException, DuplicateRoomException
	{
		if (building == null || number == null)
			throw new IllegalArgumentException();
		
		if (floor < building.getMinFloor() || floor > building.getMaxFloor()) // Check if floor is within building floor range
			throw new IllegalArgumentException();
		
		this.building = building;
		this.number = number;
		this.floor = floor;
		
		building.addRoom(this);
	}
	
	public Room(Building building, String number, int floor, int capacity) throws IllegalArgumentException, DuplicateRoomException
	{
		if (building == null || number == null)
			throw new IllegalArgumentException();
		
		if (floor < building.getMinFloor() || floor > building.getMaxFloor()) // Check if floor is within building floor range
			throw new IllegalArgumentException();
		
		this.building = building;
		this.number = number;
		this.floor = floor;
		this.capacity = capacity;
				
		building.addRoom(this);
	}

	public Building getBuilding()
	{
		return building;
	}
	
	public String getNumber()
	{
		return number;
	}
	
	public int getFloor()
	{
		return floor;
	}
	
	public String getName()
	{
		return building.getName() + number;
	}
	
	public String toString()
	{
		return ("Room(" + building.getName() + "," + number + ")");
	}
	
	public int getCapacity()
	{
		return capacity;
	}
	
	public void authorize(User input)
	{
		users.add(input);
	}
	
	public boolean canEnter(User input)
	{
		return users.contains(input);
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((building == null) ? 0 : building.hashCode());
		result = prime * result + capacity;
		result = prime * result + floor;
		result = prime * result + ((number == null) ? 0 : number.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Room other = (Room) obj;
		if (building == null)
		{
			if (other.building != null)
				return false;
		} else if (!building.equals(other.building))
			return false;
		if (capacity != other.capacity)
			return false;
		if (floor != other.floor)
			return false;
		if (number == null)
		{
			if (other.number != null)
				return false;
		} else if (!number.equals(other.number))
			return false;
		return true;
	}

}
