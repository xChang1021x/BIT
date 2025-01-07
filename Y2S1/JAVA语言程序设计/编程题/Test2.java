import java.util.*;

public class Test2 {
    public static void main(String args[]){
        Scanner reader = new Scanner(System.in);
        double sum = 0;
        int m = 0;
        while (reader.hasNextDouble()){
            double x = reader.nextDouble();
            assert x >= 0 && x < 100 : "输入的成绩非法";
            m = m + 1;
            sum = sum + x;
            System.out.printf("%d 个数的和为 %f\n", m, sum);
        }
        
    }
}
