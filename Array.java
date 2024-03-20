public class Array{ 
    public class gameEntry{
        private String name; 
        private int score; 

        public gameEntry(String n, int s){
            name = n;
            score = s; 
        }

        public String getName(){return name;}
        public int getScore(){return score;}
        public String toString(){
            return "(" + name + "," + score + ")"; 
        }
    }

    public class ScoreBoard{
        private int numEntries = 0; 
        private gameEntry[] board;
        
        public ScoreBoard(int capacity){
            board = new gameEntry[capacity]; 
        }

        public void add(gameEntry x){
            int newScore = x.getScore(); 
            if (numEntries < board.length || newScore > board[numEntries - 1].getScore()){
                if (numEntries < board.length){
                    numEntries++; 
                }
                int j = numEntries - 1; 
                while (j > 0 && board[j-1].getScore()< newScore){
                    board[j] = board[j-1]; 
                    j--; 
                }
                board[j] = x; 
            }
        }

        public gameEntry remove(int x) throws IndexOutOfBoundsException{
            if (x < 0 || x >= numEntries)
                throw new IndexOutOfBoundsException("invalid index: " + i);
            gameEntry temp = board[x]; 
            for(int i = x; i < numEntries - 1; i++){
                board[i] = board[i + 1]; 
            }
            board[numEntries - 1] = null; 
            numEntries--; 
            return temp; 
        }

        public static void insertionSort(char[] data){
            int n = data.length; 
            for(int i = 1; i < n; i++){
                char cur = data[i]; 
                int j = i; 
                while(j > 0 && data[j-1] > cur){
                    data[j] = data[j-1]; 
                    j--; 
                }
                data[j] = cur; 
            }
        }

    }


        

}