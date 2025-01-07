public class No5_3 {
    public static void main(String args[]){
        int sum = 0;
        int sushu = 0;
        for (int i = 2; i < 100; i++){
            sushu = i;
            for (int j = 2; j < i; j++){
                if (sushu % j == 0){
                    sushu = 0;
                    break;
                }
            }
            sum += sushu;
        }
        System.out.println(sum);
    }
}
