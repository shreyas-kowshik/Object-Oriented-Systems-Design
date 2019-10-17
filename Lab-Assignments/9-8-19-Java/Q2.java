class Node { 
	int key, height; 
	Node left, right; 

	Node(int d) { 
		key = d; 
		height = 1; 
	} 
} 

class Q2 { 

	Node root; 
     static int COUNT = 5;
     
	int height(Node N) { 
		if (N == null) 
			return 0; 

		return N.height; 
	} 

	int max(int a, int b) { 
		return (a > b) ? a : b; 
	} 

	Node rightRotate(Node y) { 
		Node x = y.left; 
		Node T2 = x.right; 

		x.right = y; 
		y.left = T2; 
 
		y.height = max(height(y.left), height(y.right)) + 1; 
		x.height = max(height(x.left), height(x.right)) + 1; 

		return x; 
	} 

	Node leftRotate(Node x) { 
		Node y = x.right; 
		Node T2 = y.left; 

		y.left = x; 
		x.right = T2; 

		x.height = max(height(x.left), height(x.right)) + 1; 
		y.height = max(height(y.left), height(y.right)) + 1; 

		return y; 
	} 

	int get_balance(Node N) { 
		if (N == null) 
			return 0; 

		return height(N.left) - height(N.right); 
	} 

	Node insert(Node node, int key) { 
		if (node == null) 
			return (new Node(key)); 

          // Insert the element at it's appropriate position
		if (key <= node.key) 
			node.left = insert(node.left, key); 
		else if (key > node.key) 
			node.right = insert(node.right, key); 

          // node represents the parent pointer to the new node just after the new node is inserted
		node.height = 1 + max(height(node.left),height(node.right));

          // check the balance for the current node
		int balance = get_balance(node); 
          
		// Left Left Case
		if (balance > 1 && key < node.left.key) // left subtree is longer and the node has come from the left child of the current node's left child
			return rightRotate(node); // right rotate about current node

		// Right Right Case 
		if (balance < -1 && key > node.right.key) // if right subtree is longer
			return leftRotate(node); // left rotate about current node

		// Left Right Case 
		if (balance > 1 && key > node.left.key) { 
			node.left = leftRotate(node.left); 
			return rightRotate(node); 
		} 

		// Right Left Case 
		if (balance < -1 && key < node.right.key) { 
			node.right = rightRotate(node.right); 
			return leftRotate(node); 
		} 

		return node; 
	} 
     
     static void tree_print(Node root, int space)  
     {  
          if (root == null)  
               return;  
          space += COUNT;  
          tree_print(root.right, space);  
  
          System.out.print("\n");  
          for (int i = COUNT; i < space; i++)  
               System.out.print(" ");  
          System.out.print(root.key + "\n");  
  
          tree_print(root.left, space);  
     }  

	void inOrder(Node node) { 
	     if(node == null) return;
	     inOrder(node.left); 
		System.out.print(node.key + " ");
		inOrder(node.right);  
	} 
     
	public static void main(String[] args) { 
		Q2 tree = new Q2(); 
          
		tree.root = tree.insert(tree.root, 10); 
		tree.root = tree.insert(tree.root, 20);
		tree.root = tree.insert(tree.root, 30); 
		tree.root = tree.insert(tree.root, 40); 
		tree.root = tree.insert(tree.root, 50); 
		tree.root = tree.insert(tree.root, 25); 
          
		System.out.println("In-order traversal" + 
						" of constructed tree is : "); 
		tree.inOrder(tree.root); 
		
		tree_print(tree.root,0);
	} 
} 

