public class No5_1{
    public static void main(String args[]){
        char c='А';
        System.out.println("俄文字母表:");
        for (int i = (int)c; i < c + 32; i++){
            System.out.println((char)i + " ");
        }
    }
}