
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.Iterator;

import node.Node;
import operation.Operation;

public class Buckets
{

	public static Node breadth(ArrayList<Node> currRow, int[] objective, Operation[] operations, String[] operationNames, int level)
	{
		ArrayList<Node> nextRow = new ArrayList<Node>();

		Node currNode = new Node();
		int[] operationHolder = new int[3];

		for (int i = 0; i < currRow.size(); i++)
		{
			for (int j = 0; j < operations.length; j++)
			{
				operationHolder = operations[j].operation(currRow.get(i).state);
				currNode = new Node(operationHolder[0], operationHolder[1], currRow.get(i).cost+operationHolder[2]);
				currNode.parent = currRow.get(i);
				currNode.operationName = operationNames[j];
				
				if (currNode.parent == null || !Arrays.equals(currNode.state, currNode.parent.state)) // Checks if the state is the same after the operation
				{
					if (currNode.parent.parent == null || !Arrays.equals(currNode.state, currNode.parent.parent.state)) // Checks if the state doesn't change from 2 levels above
					{
						nextRow.add(currNode);
					}
				}
				
				if (Arrays.equals(currNode.state, objective))
				{
					return currNode;
				}

			}
		}
		
		return breadth(nextRow, objective, operations, operationNames, level+1);
	}
	
	public static Node breadth2(HashSet<Node> tree, ArrayList<Node> currRow, int[] objective, Operation[] operations, String[] operationNames, int level)
	{
		Node currNode = new Node();
		Node nextNode = new Node();
		int[] operationHolder = new int[3];
				
		ArrayList<Node> nextRow = new ArrayList<Node>(); 

		for (int i = 0; i < currRow.size(); i++)
		{
			currNode = currRow.get(i);
			
			for (int j = 0; j < operations.length; j++)
			{
				operationHolder = operations[j].operation(currNode.state);
				nextNode = new Node(operationHolder[0], operationHolder[1], currNode.cost+operationHolder[2]);
				nextNode.parent = currNode;
				nextNode.operationName = operationNames[j];
				
				if (Arrays.equals(nextNode.state, objective))
				{
					return nextNode;
				}
				
				if (tree.add(nextNode))
				{
					nextRow.add(nextNode);
				}
			}
		}
		
		
		return breadth2(tree, nextRow, objective, operations, operationNames, level+1);
	}
	
	
	public static Node depth(Node currNode, int[] objective, Operation[] operations, String[] operationNames, int level, int limit)
	{
		int[] operationHolder = new int[3];
		Node newNode;
		
			for (int i = 0; i < operations.length; i++)
			{
				operationHolder = operations[i].operation(currNode.state);
				newNode = new Node(operationHolder[0], operationHolder[1], currNode.cost+operationHolder[2]);
				newNode.parent = currNode;
				newNode.operationName = operationNames[i];
				
				if (Arrays.equals(newNode.state, objective))
				{
					return newNode;
				}
				
				if (newNode.parent == null || !Arrays.equals(newNode.state, newNode.parent.state)) // Checks if the state is the same after the operation
				{
					if (newNode.parent.parent == null || !Arrays.equals(newNode.state, newNode.parent.parent.state)) // Checks if the state doesn't change from 2 levels above
					{
						if (level+1 <= limit)
						{
							Node nextCall = depth(newNode, objective, operations, operationNames, level+1, limit);
							
							if (nextCall != null)
								return nextCall;
						}
					}
				}

			}
		
			return null;
	}

	
	public static ArrayList<String> getPath(Node node, Operation[] operations, String[] operationNames)
	{
		ArrayList<String> path = new ArrayList<String>();
		
		while (node.parent != null) // Until reaches root node
		{
			path.add(node.operationName);
			
			node = node.parent;
		}
		
		String temp;
		for (int i = 0; i < path.size()/2; i++)
		{
			temp = path.get(i);
			path.set(i, path.get(path.size()-i-1));
			path.set(path.size()-i-1, temp);
		}

		return path;
	}

	public static void main(String[] args)
	{
		int capacityA = 4, capacityB = 3;

		Operation emptyA = (state) -> { int[] ret = {0, state[1], 1}; return ret;};
		Operation emptyB = (state) -> { int[] ret = {state[0], 0, 1}; return ret;};
		Operation fillA = (state) -> { int[] ret = {capacityA, state[1], 1}; return ret;};
		Operation fillB = (state) -> { int[] ret = {state[0], capacityB, 1}; return ret;};
		Operation pourAB = (state) -> { int[] ret = new int[3]; ret[2] = 1; if (state[0] + state[1] > capacityB) { ret[0] = state[0] - (capacityB - state[1]); ret[1] = capacityB;} else { ret[0] = 0; ret[1] = state[0] + state[1];} return ret;};
		Operation pourBA = (state) -> { int[] ret = new int[3]; ret[2] = 1; if (state[0] + state[1] > capacityA) { ret[0] = capacityA; ret[1] = state[1] - (capacityA - state[0]);} else { ret[0] = state[0] + state[1]; ret[1] = 0;} return ret;};
		
		Operation[] operations = {emptyA, emptyB, fillA, fillB, pourAB, pourBA};
		String[] operationNames = {"emptyA", "emptyB", "fillA", "fillB", "pourAB", "pourBA"};


		ArrayList<Node> root = new ArrayList<Node>();
		root.add(new Node(0,0,0));
		
		HashSet<Node> tree = new HashSet<Node>();
		tree.add(new Node(0,0,0));

		int[] objective = {2,0};

		long start = System.nanoTime();
		Node result = null;
		for (int i = 0; i < 50; i++)
		{
			tree = new HashSet<Node>();
			tree.add(new Node(0,0,0));
			result = breadth2(tree, root, objective, operations, operationNames, 0);
//			result = depth(new Node(0,0,0), objective, operations, operationNames, 0, 15);
		}
		

		
		ArrayList<String> path = getPath(result, operations, operationNames);
		
		for (int i = 0; i < path.size(); i++)
		{
			System.out.println(path.get(i));
		}
		
		double deltaTime = (System.nanoTime()-start);
		deltaTime /= 1000000;
				
		System.out.format("\nExecuted in %f seconds.", deltaTime);
	}
}