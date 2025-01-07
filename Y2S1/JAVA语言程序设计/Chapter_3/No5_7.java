public class No5_7 {
    public static void main(String args[]){
        int fac = 1, i = 1, sum = 0;
        while (true){
            sum += fac;
            if (sum > 9999){
                break;
            }
            i += 1;
            fac *= i;
        }
        System.out.println(i - 1);
    }
}
