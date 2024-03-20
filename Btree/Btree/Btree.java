import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

/*
 * subtree(x) = (x) and its descendants 
 * depth(x) = # ancesotrs = # edged in path from (x) to root
 * height(x) = # edges in longest downward path from (x) = max depth in subtree(x) 
 * height of tree = max depth 
 */
public class Btree {
    public class Node {
        public int data;
        public Node left;
        public Node right;
        public Node parent;

        public Node(int data) {
            this.data = data;
        }
    }

    public Node root;

    public void addNode(int data, Node current) {
        if (root == null) {
            root = new Node(data);
        } else if (data < current.data) {
            if (current.left == null) {
                current.left = new Node(data);
                current.left.parent = current; 
            } else {
                addNode(data, current.left);
            }
        } else {
            if (current.right == null) {
                current.right = new Node(data);
                current.right.parent = current; 
            } else {
                addNode(data, current.right);
            }
        }
    }

    public int getData(int data, Node current) {
        if (current == null || current.data == data) {
            return current.data;
        } else if (data < current.data) {
            return getData(data, current.left);
        } else {
            return getData(data, current.right);
        }
    }

    public void preOrder(Node current) {
        if (current == null) {
            return; 
        } else {
            System.out.print(current.data + " ");
            preOrder(current.left);
            preOrder(current.right);
        }
    }

    public void inOrder(Node current){
        if (current == null){
            return; 
        }
        else {
            inOrder(current.left); 
            System.out.print(current.data + " ");
            inOrder(current.right); 
        }
    }

    public void postOrder(Node current){
        if (current == null){
            return;  
        }
        postOrder(current.left); 
        postOrder(current.right); 
        System.out.print(current.data + " "); 

    }

    public void nonRecInOrder(Node current){
        Stack <Node> stack = new Stack<>(); 
        while(current != null || !stack.isEmpty()){
            if (current != null){
                stack.push(current); 
                current = current.left; 
            } else {
                current = stack.pop(); 
                System.out.print(current.data + " ");
                current = current.right; 

            }
        }
    }

    public int minTree(Node current){
        while(current.left != null){
            current = current.left; 
        }
        return current.data; 
    }

    public int maxTree(Node current){
        while(current.right != null){
            current = current.right; 
        }
        return current.data; 
    }

    public int recMaxTree(Node current){
        if (current.right == null){
            return current.data; 
        }
        else return recMaxTree(current.right); 
    }

    public int recMinTree(Node current){
        if (current.left == null){
            return current.data; 
        }
        else return recMinTree(current.left); 
    }

    public int getSuccessor(Node current){
        if (current.right != null){
            return minTree(current.right);  
        }   else {
                Node temp = current.parent; 
                while(temp != null && temp.data < current.data){
                temp = temp.parent; 
            }
            return temp.data; 
        }
    }

    public void levelOrder(Node root) {
        if (root == null) {
            return;
        }
        Queue<Node> Q = new LinkedList<>();
        Q.add(root);
        while (!Q.isEmpty()) {
            Node current = Q.peek();
            System.out.print(current.data + " ");
            if (current.left != null) {
                Q.add(current.left);
            }
            if (current.right != null) {
                Q.add(current.right);
            }
            Q.poll();
        }
    }

    public int countLevels(Node root){
        if (root == null){
            return 0; 
        }
        int count = 0; 
        Queue<Node> Q = new LinkedList<>();
        Q.add(root); 
        while(!Q.isEmpty()){
            int nodeCount = Q.size(); 
            while (nodeCount > 0){
                Node current = Q.poll(); 
                if (current.left != null){
                    Q.add(current.left); 
                }
                if (current.right != null){
                    Q.add(current.right); 
                }
                --nodeCount; 
             }
        ++count;
        }
        return count; 
    }



 

    /*public int getPredecessor(Node current){
        if (current == root){ 
            return current.data; 
        }    
        if (current.left != null){
            return recMaxTree(current.left); 
         }  else if (return recMa
    }*/

    public static void main(String[] args) {
        Btree tree = new Btree();
        tree.addNode(5, tree.root);
        tree.addNode(3, tree.root);
        tree.addNode(7, tree.root);
        tree.addNode(2, tree.root);
        tree.addNode(4, tree.root);
        tree.addNode(6, tree.root);
        tree.addNode(8, tree.root);

        System.out.println("Preorder Traversal: ");
        tree.preOrder(tree.root);
        System.out.println("\nInorder Traversal: ");
        tree.inOrder(tree.root);
        System.out.println("\nPostorder Traversal: ");
        tree.postOrder(tree.root);

        System.out.println("\nNon-recursive Inorder Traversal: ");
        tree.nonRecInOrder(tree.root);

        System.out.println("\nLevel Order Traversal: ");
        tree.levelOrder(tree.root);

        System.out.println("\nMinimum Value: " + tree.recMinTree(tree.root));
        System.out.println("Maximum Value: " + tree.recMaxTree(tree.root));

        System.out.println("Successor of 3: " + tree.getSuccessor(tree.root.left));

        System.out.println("Number of levels in the tree: " + tree.countLevels(tree.root));
    }
}
