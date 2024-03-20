public class recursion {
    public int maxArray(int a[], int n, int target, int max){
        if (target == n){
            return max; 
        }
        int temp = a[target]; 
        if (temp > max)
            max = temp; 
        return maxArray(a, n, target + 1, max); 
    }
    
}
