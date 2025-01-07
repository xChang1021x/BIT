import java.util.Scanner;

public class LexueNo2 {
    public static void main(String args[]){
        Scanner reader = new Scanner(System.in);
        String x = reader.nextLine();
        String num = x.substring(2, x.length());
        char o = x.charAt(0);
        int height = Integer.parseInt(num);

        for (int i = 0; i < height; i++){
            for (int j = height - 1 - i; j > 0; j--){
                System.out.print(" ");
            }
            System.out.print(o);
            for (int j = 0; j < 2*i - 1; j++){
                System.out.print(" ");
            }
            if (i != 0){
                System.out.print(o);
            }
            System.out.println("");
            o++;
            if (o > 'Z' && o < 'a' || o > 'z'){
                o -= 26;
            }
        }
        o -= 2;
        for (int i = height - 1; i > 0; i--){
            for (int j = height; j > i; j--){
                System.out.print(" ");
            }
            System.out.print(o);
            for (int j = 0; j < 2*i - 3; j++){
                System.out.print(" ");
            }
            if (i != 1){
                System.out.print(o);
            }
            System.out.println("");
            o--;
            if (o < 'a' && o > 'Z' || o < 'A'){
                o += 26;
            }
        }
        reader.close();
    }
}
