import java.time.DayOfWeek;
import java.time.LocalDate;
import java.util.Scanner;

public class CalendarPlus {
    private int year;
    private int month;
    public CalendarPlus(int year, int month) {
        this.year = year;
        this.month = month;
    }
    public void preMonth(){
        if (month > 1){
            month--;            
        }
        else{
            month = 12;
            year--;
        }
    }
    public void nextMonth(){
        if (month < 12){
            month++;            
        }
        else{
            month = 1;
            year++;
        }
    }
    public void preYear(){
        year--;
    }
    public void nextYear(){
        year++;
    }
    public void show() {
        LocalDate Now = LocalDate.now();
        int yearNow = Now.getYear();
        int monthNow = Now.getMonthValue();
        int dayNow = Now.getDayOfMonth();

        LocalDate date1 = LocalDate.of(year, month, 1);
        DayOfWeek val = date1.getDayOfWeek();
        int valday = val.getValue();

        System.out.println("    一   二   三   四   五   六   日       月份：" + month + "  年份：" + year);
        System.out.println(" -----------------------------------");
        for (int i = 0; i < (valday - 1); i++) {
            System.out.print("     ");
        }

        int count = 1;
        while (count <= date1.lengthOfMonth()) {
            if (year == yearNow && month == monthNow && count == dayNow)
                System.out.printf("  *%d", count);
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
    public static int VerifyYear(){
        Scanner reader = new Scanner(System.in);
        int year = 2023;
        do{
            while(!reader.hasNextInt()){
                System.out.println("请输入有效年份！(请输入整数)"); 
                System.out.print("请输入年份: ");
                reader.nextLine();
            }
            year = reader.nextInt();
            if (year < 1600){
                System.out.println("请输入有效年份！(1600年或以后)"); 
                System.out.print("请输入年份: ");
            }
        } while(year < 1600);
        return year;
    }
    public static int VerifyMonth(){
        Scanner reader = new Scanner(System.in);
        int month = 1;
        do{
            while(!reader.hasNextInt()){
                System.out.println("请输入有效月份！(请输入整数)"); 
                System.out.print("请输入月份: ");
                reader.nextLine();
            }
            month = reader.nextInt();
            if (month < 1 || month > 12){
                System.out.println("请输入有效月份！(1-12)");
                System.out.print("请输入月份: "); 
            }
        } while(month < 1 || month > 12);
        return month;
    }
    public static void Mode2(CalendarPlus calendar){    
        System.out.println("输入<显示上个月的日历，输入>显示下个月的日历，输入x退出");
        Scanner reader = new Scanner(System.in);
        String x = reader.next();
        do{
            if (x.equals("<")){
                calendar.preMonth();
                calendar.show();
                System.out.println("");
            }
            else if (x.equals(">")){
                calendar.nextMonth();
                calendar.show();
                System.out.println("");
            }
            else if (x.equals("x")){
                break;
            }
            else{
                System.out.println("错误的输入！");
            }
            System.out.println("输入<显示上个月的日历，输入>显示下个月的日历，输入x退出");
            x = reader.next();
            
        } while (!x.equals("x"));
    }
    public static void Mode3(CalendarPlus calendar){
        while (true){
            System.out.println("输入<显示上个月的日历，输入>显示下个月的日历，输入x退出");
            Scanner reader = new Scanner(System.in);
            String x = reader.next();
            if (x.equals("<")){
                calendar.year--;
                calendar.month = 1;
                for (int i = 0; i < 12; i++){
                    calendar.show();
                    System.out.println("");
                    calendar.month++;
                }
                calendar.month = 1;
                System.out.println("");
            }
            else if (x.equals(">")){
                calendar.year++;
                calendar.month = 1;
                for (int i = 0; i < 12; i++){
                    calendar.show();
                    System.out.println("");
                    calendar.month++;
                }
                calendar.month = 1;
                System.out.println("");
            }
            else if (x.equals("x")){
                break;
            }
            else{
                System.out.println("错误的输入！");
            }
        }
    }
    public static CalendarPlus CreateNewCalander(){
        int year, month;
        System.out.print("请输入年份: ");
        year = VerifyYear();
        System.out.print("请输入月份: "); 
        month = VerifyMonth();
        CalendarPlus calendar = new CalendarPlus(year, month);
        return calendar;
    }
    public static void PrintMenu(){
        System.out.println("请输入日历模式：");
        System.out.println("1. 输入年、月，显示指定日历页");
        System.out.println("2. 对当前月份日历页进行操作");
        System.out.println("3. 显示当前年份所有日历页并操作");
        System.out.println("4. 退出程序");        
    }
    public static void main(String[] args) {
        CalendarPlus NowCalendar = new CalendarPlus(LocalDate.now().getYear(), LocalDate.now().getMonthValue());
        System.out.println("当前月份日历表：");
        NowCalendar.show();
        System.out.println("");
        System.out.println("");
        PrintMenu();
        CalendarPlus calendar = NowCalendar;
        Scanner reader = new Scanner(System.in);
        while (reader.hasNext()){
            if (!reader.hasNextInt()){
                System.out.println("请输入正确的模式序号！");
                reader.next();
                continue;
            }
            int mode = reader.nextInt();
            
            if (mode == 1){
                calendar = CreateNewCalander();
                calendar.show();
                System.out.println("");
                PrintMenu();
            }
            else if (mode == 2){
                System.out.println("当前月份日历页：");
                calendar.show();
                System.out.println("");
                Mode2(calendar);
                PrintMenu();
            }
            else if (mode == 3){
                calendar.month = 1;
                System.out.println("当前年份日历页：");
                for (int i = 0; i < 12; i++){
                    calendar.show();
                    System.out.println("");
                    calendar.month++;
                }
                Mode3(calendar);
                PrintMenu();
            }
            else if (mode == 4){
                break;
            }
            else{
                System.out.println("请输入正确的模式序号！");
            }
        }
        reader.close();
    }
}
