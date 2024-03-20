public class chapter2 {

    public static void insertionSort(int a[], int n) {
        for (int i = 1; i < n; i++) {
            int key = a[i];
            int j = i - 1;
            while (j >= 0 && a[j] > key) {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = key;
        }
    }

    public static void main(String[] args){
        int[] a = new int[6]; 
        a[0] = 2; 
        a[1] = 5; 
        a[2] = 10; 
        a[3] = 6; 
        a[4] = 3; 
        a[5] = 1; 

        insertionSort(a, 6); 

        for(int i = 0; i < 6; i++){
            System.out.print(a[i] + " "); 
        }
        System.out.println(); 

        reverseSort(a, 6); 

        for(int i = 0; i < 6; i++){
            System.out.print(a[i] + " "); 
        }
        
    }

    public static void reverseSort(int a[], int n){
        for(int i = 1; i < n; i++){
            int key = a[i]; 
            int j = i - 1; 
            while (j >= 0 && a[j] < key){
                a[j + 1] = a[j]; 
                j--; 
            }
            a[j + 1] = key; 
        }
    }

    public static void addBinary(int a[], int b[], int n) {
        int i = n - 1; 
        int carry = 0;
        int[] c = new int[n];
    
        while (i >= 0) {
            int sum = a[i] + b[i] + carry;
            
            if (sum == 0) {
                c[i] = 0;
                carry = 0;
            } else if (sum == 1) {
                c[i] = 1;
                carry = 0;
            } else if (sum == 2) {
                c[i] = 0;
                carry = 1;
            } else { 
                c[i] = 1;
                carry = 1;
    
            i--; 
        }
    }
}

    public static void merge(int A[], int l, int m, int r){
        int leftN = l - m + 1; 
        int rightN = r - m; 
        int[] L = new int[leftN]; 
        int[] R = new int[rightN]; 
        for(int i = 0; i < leftN; i++){
            A[i] = L[l + i]; 
        }
        for(int j = 0; j < rightN; j++){
            A[j] = R[m + 1 + j];
        }
        int i = 0; 
        int j = 0; 
        int k = m; 

        while(i < leftN && j < rightN){
            if (L[i] < R[j]){
                A[k] = L[i]; 
                ++i; 
            }
            else {
                A[k] = R[j]; 
                ++j; 
            }
            ++k; 
        }
   
        while(i < leftN){
            A[k] = L[i];
        }

        while(j < rightN){
            A[k] = R[j]; 
        }
    }

    public static void mergeSort(int a[], int l, int r){
        if (l >= r){
            return; 
        }
        int m = l + r / 2; 
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }

    public static int binarySearch(int a[], int start, int end, int target){
        if (end >= start) {
            int mid = start + (end - start) / 2; 
    
            if (a[mid] == target) {
                return mid; 
            }
            if (a[mid] > target) {
                return binarySearch(a, start, mid - 1, target);
            }
            return binarySearch(a, mid + 1, end, target);
        }
        return -1; 
    }
    

    

    
    
    
}
