import java.io.*;
import java.util.*;

public class BinarySearch {

    static int binarySearch(int[] a, int x, int left, int right) {
        int middle = (left + right)/2;
        int returnValue = -1;
        
        if( x > a[right] || x < a[left])
        	return returnValue;
        
        if(a[middle] == x)
        	return middle;
        //write your code here

        if(a[middle] > x){
        	returnValue = binarySearch(a,x,left,middle);
        
        }
        
        if(a[middle] < x){
        	returnValue =binarySearch(a,x,middle + 1,right);
        	
        }
        return returnValue;
    }

//    static int linearSearch(int[] a, int x) {
//        for (int i = 0; i < a.length; i++) {
//            if (a[i] == x) return i;
//        }
//        return -1;
//    }

    public static void main(String[] args) {
        FastScanner scanner = new FastScanner(System.in);
        int n = scanner.nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = scanner.nextInt();
        }
        int m = scanner.nextInt();
        int[] b = new int[m];
        for (int i = 0; i < m; i++) {
          b[i] = scanner.nextInt();
        }
        for (int i = 0; i < m; i++) {
            //replace with the call to binarySearch when implemented
            System.out.print(binarySearch(a, b[i],0,a.length - 1)+" ");
        }
    }
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner(InputStream stream) {
            try {
                br = new BufferedReader(new InputStreamReader(stream));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}
