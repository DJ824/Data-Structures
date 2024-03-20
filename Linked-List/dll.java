public class dll<E>{
    private static class Node<E>{
        private E element; 
        private Node<E> prev; 
        private Node<E> next; 
        public Node(E e, Node<E> p, Node<E> n){
            element = e; 
            prev = p;
            next = n; 
        }
        
        public E getElement() {return element;}
        public Node<E> getNext() {return next;}
        public Node<E> getPrev() {return prev;}
        public void setPrev(Node<E> p) {prev = p;}
        public void setNext(Node<E> n) {next = n;}

    }

    private Node<E> header; 
    private Node<E> trailer; 
    private int size = 0; 
    public dll(){
        header = new Node<>(null,null,null); 
        trailer = new Node<>(null, header, null); 
        header.setNext(trailer); 
    }
    
    public int size() {return size;}
    public boolean isEmpty() {return size == 0;}

    public E first(){
        if (isEmpty()) {return null;}
        return header.getNext().getElement(); 
    }
    
    public E last() {
        if (isEmpty()) return null; 
        return trailer.getPrev().getElement();
    }

    public void addFirst(E e){
        addBetween(e, header, header.getNext()); 
    }

    public void addLast(E e){
        addBetween(e, trailer.getPrev(), trailer); 
    }

    private void addBetween(E e, Node<E> first, Node<E> second){
        Node<E> newOne = new Node<> (e, first, second); 
        first.setNext((newOne));
        second.setPrev(newOne);
    }
    
    private E remove(Node<E> node){ 
        Node<E> prev = node.getPrev(); 
        Node<E> next = node.getNext(); 
        prev.setNext(next); 
        next.setPrev(prev); 
        size--; 
        return node.getElement();
    }

    public void reverse(){
        Node<E> current = header;
        Node<E> next; 
        Node<E> prev = null;  
        while (current != null){
            current.prev = prev; 
            prev.next = current; 
            prev = current; 
            current = current.getNext(); 


        } 
        prev = header; 
    }
}