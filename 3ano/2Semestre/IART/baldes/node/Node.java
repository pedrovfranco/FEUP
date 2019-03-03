package node;

import java.util.Arrays;

import operation.Operation;

public class Node
{
	public int[] state;
	public int cost;
	public int level;
	public Node parent = null;
	public String operationName = null;

	public Node()
	{
		this.state = new int[2];
		this.cost = 0;
	}

	public Node(int state1, int state2, int cost)
	{
		this.state = new int[2];
		this.state[0] = state1;
		this.state[1] = state2;

		this.cost = cost;
	}

	public Node(Node node)
	{
		this.state = new int[2];
		this.state[0] = node.state[0];
		this.state[1] = node.state[1];

		this.cost = node.cost;
	}

	@Override
	public String toString() {
		return "Node {state=" + Arrays.toString(state) + ", cost=" + cost + "}";
	}
	
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + Arrays.hashCode(state);
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
		Node other = (Node) obj;
		if (!Arrays.equals(state, other.state))
			return false;
		return true;
	}
}