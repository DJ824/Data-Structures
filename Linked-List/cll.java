public class cll<E>{
        // node class 
        private static class Node<E>{ 
            private E element; 
            private Node<E> next; 
            public Node(E e, Node<E> n){    // constructor for a new node
                element = e; 
                next = n; 
            }
    
            public E getElement() {return element;}  // getter for element in node 
            public Node<E> getNext() {return next;}  // returns pointer to next node 
            public void setNext(Node<E> n) {next = n;}  // set pointer to next node 
        }

    private Node<E> tail = null; 
    private int size = 0; 
    public cll() {} 
    public int size() {return size;}
    public boolean isEmpty() {return size == 0;}
    public E first(){
        if (isEmpty()) {return null;}
        return tail.getNext().getElement(); 
    }
    public E last() {
        if (isEmpty()) {return null;} 
        return tail.getElement(); 
    }

    public void rotate(){
        if (!isEmpty()) 
            tail = tail.getNext(); 
    }

    public void addFirst(E e){
        if (isEmpty()){
            tail = new Node<>(e,null); 
            tail.setNext(tail); // if the list is empty, set the new node as tail and link to itself 
        }
        Node<E> newest = new Node<>(e,tail.getNext());
        tail.setNext(newest);
        ++size; 
    }

    public void addLast(E e){
        addFirst(e); 
        tail = tail.getNext(); 
    }

    public E removeFirst(){
        if (isEmpty()) {return null;}
        Node<E> head = tail.getNext();
        if (head == tail){
            tail = null;
        } 
        else tail.setNext(head.getNext());
        --size; 
        return head.getElement();
    }

}   `