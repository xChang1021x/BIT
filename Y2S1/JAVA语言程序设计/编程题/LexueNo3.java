import java.util.Scanner;

public class LexueNo3 {
    public static void main(String args[]){
        Scanner reader = new Scanner(System.in);
        String[] Dictionary = new String[8];
        String temp;
        for (int i = 0; i < 5; i++){
            Dictionary[i] = reader.nextLine();
        }
        for (int i = 0; i < 4; i++){
            for (int j = i + 1; j < 5; j++){
                if (Dictionary[i].compareTo(Dictionary[j]) <= 0){
                    temp = Dictionary[i];
                    Dictionary[i] = Dictionary[j];
                    Dictionary[j] = temp;
                }
            }
        }
        for (int i = 0; i < 5; i++){
            System.out.println(Dictionary[i]);
        }
        reader.close();
    }
}
// char byte boolean short int long float double