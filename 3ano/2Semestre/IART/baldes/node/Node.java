package node;

import java.util.Arrays;

import operation.Operation;

public class Node
{
	public int[] state;
	public int cost;
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
}