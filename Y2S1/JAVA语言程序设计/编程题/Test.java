import java.util.Scanner;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

public class Test{
    public static void main(String args[]){
        Scanner scanner = new Scanner(System.in);
        int year1, month1, day1, year2, month2, day2;
        year1 = scanner.nextInt();
        month1 = scanner.nextInt();
        day1 = scanner.nextInt();
        year2 = scanner.nextInt();
        month2 = scanner.nextInt();
        day2 = scanner.nextInt();
        LocalDate Date1 = LocalDate.of(year1, month1, day1);
        LocalDate Date2 = LocalDate.of(year2, month2, day2);
        System.out.println(Date1.until(Date2, ChronoUnit.DAYS));
        scanner.close();
    }
}


