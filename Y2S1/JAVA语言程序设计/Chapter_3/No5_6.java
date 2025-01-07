import java.util.Scanner;

public class No5_6 {
    public static void main(String args[]){
        Scanner reader = new Scanner(System.in);
        int a, b;
        int min;
        int Lcm = 1, Hcf = 1;
        a = reader.nextInt();
        b = reader.nextInt();
        if (a >= b){
            min = b;
        }
        else{
            min = a;
        }

        for (int i = min; i >= 1; i++){
            if (a % i == 0 && b % i == 0){
                Hcf = i;
                break;
            }
        }

        for (int i = min; i <= a * b; i++){
            if (i % a == 0 && i % b == 0){
                Lcm = i;
                break;
            }
        }
        System.out.println("最大公约数：" + Hcf);
        System.out.println("最小公倍数：" + Lcm);
        reader.close();
    }    
}
