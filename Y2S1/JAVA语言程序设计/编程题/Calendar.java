import java.time.DayOfWeek;
import java.time.LocalDate;
import java.util.Scanner;

public class Calendar {
    private int year;
    private int month;
    public Calendar(int year, int month) {
        this.year = year;
        this.month = month;
    }
    public void show() {
        LocalDate Now = LocalDate.now();
        int yearNow = Now.getYear();
        int monthNow = Now.getMonthValue();
        int dayNow = Now.getDayOfMonth();

        LocalDate date1 = LocalDate.of(year, month, 1);
        DayOfWeek val = date1.getDayOfWeek();
        int valday = val.getValue();

        System.out.println("    一   二   三   四   五   六   日");
        System.out.println(" -----------------------------------");
        for (int i = 0; i < (valday - 1); i++) {
            System.out.print("     ");
        }

        int count = 1;
        while (count <= date1.lengthOfMonth()) {
            if (year == yearNow && month == monthNow && count == dayNow)
                System.out.printf(" (%d)", count);
            else
                System.out.printf("%5d", count);
            count++;
            valday++;
            if (valday > 7) {
                valday -= 7;
                System.out.println("");
            }
        }
    }

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        System.out.println("请输入年份和月份");
        int year = reader.nextInt();
        int month = reader.nextInt();
        reader.close();

        Calendar calendar = new Calendar(year, month);
        calendar.show();
    }
}