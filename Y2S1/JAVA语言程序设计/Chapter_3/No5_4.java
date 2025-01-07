public class No5_4 {
    public static void main(String args[]){
        double sum = 0;
        long jc = 1;
        for (int i = 1; i <= 20; i++){
            jc *= i;
            sum += 1.0/jc;
        }
        System.out.println(sum);
    }    
}
