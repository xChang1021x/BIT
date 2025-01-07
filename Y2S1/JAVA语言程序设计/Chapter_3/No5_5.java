public class No5_5 {
    public static void main(String args[]){
        int sum = 0;
        for (int i = 2; i < 1000; i++){
            sum = 0;
            for (int j = 1; j < i; j++){
                if (i % j == 0){
                    sum += j;
                }
            }
            if (sum == i){
                System.out.println(i);
            }
        }
    }    
}
