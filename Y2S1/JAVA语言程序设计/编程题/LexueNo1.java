import java.util.Scanner;
import java.lang.Math;

public class LexueNo1{
    public static void main(String args[]){
        int a, b, c;
        double ans1, ans2, rn, im;
        Scanner reader = new Scanner(System.in);
        a = reader.nextInt();
        b = reader.nextInt();
        c = reader.nextInt();

        if (b*b - 4*a*c > 0){
            ans1 = (- b + Math.sqrt(b*b - 4*a*c)) / (2 * a);
            ans2 = (- b - Math.sqrt(b*b - 4*a*c)) / (2 * a);
            String result = String.format ("%.6f", ans1);
            String result2 = String.format ("%.6f", ans2);
            System.out.println("x1 = " + result);
            System.out.println("x2 = " + result2);
        }
        else if (b*b - 4*a*c == 0){
            ans1 = - b / (2 * a);
            String result = String.format ("%.6f", ans1);
            System.out.println("x1 = " + result);
            System.out.println("x2 = " + result);
        }
        else{
            rn = - b / (2 * a);
            im = Math.sqrt(4*a*c - b*b) / (2 * a);
            String result = String.format ("%.6f", rn);
            String result2 = String.format ("%.6f", im);
            
            if (rn == 0){
                System.out.println("x1 = " + result2 + "i");
                System.out.println("x2 = -" + result2 + "i");
            }
            else{
                System.out.println("x1 =" + result + " + " + result2 + "i");
                System.out.println("x2 =" + result + " - " + result2 + "i");               
            }


        }
        reader.close();
    }
}