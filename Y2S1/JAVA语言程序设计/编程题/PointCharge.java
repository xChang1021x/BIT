import java.util.Scanner;
import java.lang.Math;

public class PointCharge {
    public final static double K = 9 * Math.pow(10, 9);
    private double q;
    private double x, y;
    

    public double calPotential(){
        return K * q / Math.sqrt(x*x + y*y);
    }

    public static void main(String[] args){
        Scanner reader = new Scanner(System.in);
        PointCharge point = new PointCharge();
        point.q = reader.nextDouble();
        point.x = reader.nextDouble();
        point.y = reader.nextDouble();
        reader.close();

        System.out.println(point.calPotential());
    }    
}
