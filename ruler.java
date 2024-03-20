public class ruler {
    public static void drawRuler(int nInches, int majorLength){
        drawLine(majorLength, 0); 
        for(int i = 1; i <= nInches; i++){
            drawInterval(majorLength-1);
            drawLine(majorLength, i);
        }
    }

    public static void drawInterval(int centralLength){
        if (centralLength >= 1){
        drawInterval(centralLength - 1); 
        drawLine(centralLength); 
        drawInterval(centralLength - 1); 
        }
    }

    private static void drawLine(int length, int label){
        for(int i = 0; i < length; i++){
            System.out.print("-");

        }
        if (label >= 0){
            System.out.print(" " + label); 
        }
        System.out.print("\n"); 
    }

    private static void drawLine(int length){
        drawLine(length, -1); 
    }

    public static void main(String[] args){
        drawRuler(1, 4);
    }
}
