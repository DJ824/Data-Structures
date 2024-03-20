public class sll <E>{
    // node class 
    private static class Node<E>{ 
        private E element; 
        private Node<E> next; 
        public Node(E e, Node<E> n){    // constructor for a new node
            element = e; 
            next = n; 
        }

        public E getElement(){return element;}  // getter for element in node 
        public Node<E> getNext(){return next;}  // returns pointer to next node 
        public void setNext(Node<E> n) {next = n;}  // set pointer to next node 
    }
    // list class, data members include head and tail node, and size 
    private Node<E> head = null;  
    private Node<E> tail = null;  
    private int size = 0; 

    public sll() {}; // constructor for an empty list (only head/tail nodes)
    public int size() {return size;}
    public boolean isEmpty() {return size == 0;}
    // returns the first element of the list 
    public E first() {      
        if (isEmpty()) return null; 
        return head.getElement(); 
    }
    // returns last element in the list 
    public E last(){
        if (isEmpty()) return null; 
        return tail.getElement();
    }

    // insert a new node in the beginning of the list 
    public void addFirst(E e){
        head = new Node<>(e, head);
        if (size == 0)
            tail = head; 
        size++;  
    }

    public void addLast(E e){
        Node<E> newest = new Node<>(e, null); 
        if (isEmpty()) 
            head = newest; 
        else 
            tail.setNext(newest); 
            tail = newest; 
            size++; 
    }

    public E removeFirst(){
        if (isEmpty())
            return null; 
        E answer = head.getElement(); 
        head = head.next;
        size--; 
        if (size == 0) {tail = null;}
        return answer;  
    }

    public E removeLast(){
        if (isEmpty())
            return null; 
        E answer = tail.getElement(); 
        tail = null; 
        size--; 
        return answer; 
    }
 
    /* equality funtiont passes in an object and first ensures it is not a null type, then checks to ensure it is of the same class 
     * then casts the object into the sll class, and compare size and elements 
     */
    public boolean equals(Object o){
        if (o == null) return false; 
        if (getClass() != o.getClass()) return false; 
        sll<E> other = (sll) o; 
        if (size != other.size) return false; 
        Node<E> walkA = head; 
        Node<E> walkB = other.head; 
        while (walkA != null){
            if (!walkA.getElement().equals(walkB.getElement())) return false; 
            walkA = walkA.getNext(); 
            walkB = walkB.getNext(); 
        }
        return true; 
    }
    /* clone function first creates another object of type sll by safe casting, then ensures object to be cloned is not empty 
     * creates head pointer equal to base object, a walk node to iterate thru base object, and tail node equal to head  to link together cloned objects 
     * creates a new node and sets otherTail next node to newest and otherTail to newest to link next created node 
     */ 
    public sll<E> clone() throws CloneNotSupportedException{
        sll<E> other = (sll<E>) super.clone(); 
        if (size > 0){
            other.head = new Node<>(head.getElement(), null); 
            Node<E> walk = head.getNext();
            Node<E> connector = other.head; 
            while (walk != null){ 
                Node<E> newest = new Node<>(walk.getElement(), null); 
                connector.setNext(newest); 
                connector = newest;
                walk = walk.getNext(); 
            }
        }
        return other; 
    }


}
