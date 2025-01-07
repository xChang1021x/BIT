public class No5_2 {
    public static void main(String args[]){
        long x = 1;
        long sum = 0;
        for (int i = 1; i <= 20; i++){
            x *= i;
            sum += x;
        }
        System.out.println(sum);
    }    
}
