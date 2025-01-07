import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

class Student implements Comparable<Student> {
    private String id;
    private String name;
    private String className;
    private String major;

    public Student(String id, String name, String className, String major) {
        this.id = id;
        this.name = name;
        this.className = className;
        this.major = major;
    }

    public String getStudentNumber() {
        return id;
    }

    public int compareTo(Student other) {
        return this.id.compareTo(other.id);
    }

    public String toString() {
        return "学号: " + id + ", 姓名: " + name + ", 班级: " + className + ", 专业: " + major;
    }
}

public class StudentList {
    public static void main(String[] args) {
        List<Student> students = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("请输入学生信息（学号 姓名 班级 专业），输入exit结束：");
            String input = scanner.nextLine();
            if (input.equals("exit")) {
                break;
            }

            String[] studentInfo = input.split(" ");
            if (studentInfo.length != 4) {
                System.out.println("输入格式错误，请重新输入。");
                continue;
            }

            String id = studentInfo[0];
            String name = studentInfo[1];
            String className = studentInfo[2];
            String major = studentInfo[3];

            Student student = new Student(id, name, className, major);
            students.add(student);
        }

        Collections.sort(students);

        System.out.println("按学号排序后的学生信息：");
        for (Student student : students) {
            System.out.println(student);
        }
    }
}
