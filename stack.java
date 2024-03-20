public class stack<E> {  
   private E[][] data; 
   private int blueT;
   private int redT;  
   private int capacity; 

  public stack(int capacity){
    this.capacity = capacity; 
    this.data = new E[capacity][2]; 
    this.blueT = -1;
    this.redT = -1;  
  }


   public int size() { return (redT + blueT + 2); }

   public boolean isEmpty(){
    return (redT == -1 && blueT == -1); 
   }

   public void redPush(E e){
    data[++redT][0] = e;
   }

   public void bluePush(E e){
    data[++blueT][1] = e;
   }

   public E redPop(){
     E ans = data[redT][0]; 
     data[redT][0] = null; 
     --redT; 
     return ans; 
   }

   public E bluePop(){
    E ans = data[blueT][1]; 
    data[blueT][1] = null; 
    --blueT; 
    return ans; 
   }







}
