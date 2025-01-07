import java.util.Scanner;

import arraylist.DynamicArray;
import arraylist.MyArrayList;
import arraylist.MyLinkedList;

public class ArrayList {
    public static void PrintMenu(){
        System.out.println("1. 在列表最后位置添加数据（输入格式：1 数据）");
        System.out.println("2. 在第i个位置上添加数据（输入格式：2 位置 数据）");
        System.out.println("3. 获取第i个位置上的数据（输入格式：3 位置）");
        System.out.println("4. 删除第i个位置上的数据（输入格式：4 位置）");
        System.out.println("5. 修改第i个位置上的数据（输入格式：5 位置 数据）");
        System.out.println("0. 退出程序");
    }
    public static void main(String[] args) {
        MyArrayList myList = new MyArrayList();
        MyLinkedList myLinkList = new MyLinkedList();
        
        Scanner reader = new Scanner(System.in);
        System.out.print("请输入初始化列表的大小：");
        int initialSize;
        while (true){
            while (!reader.hasNextInt()){
                System.out.println("请输入整数！");
                System.out.print("请输入初始化列表的大小：");
                reader.next();
            }
            initialSize = reader.nextInt();   
            if (initialSize < 0){
                System.out.println("初始化大小不能小于0！");
                System.out.print("请输入初始化列表的大小：");
                continue;
            }
            break;
        }
        myList = new MyArrayList(initialSize);
        control controller = new control();
        PrintMenu();
        while (reader.hasNext()){
            if (!reader.hasNextInt()){
                System.out.println("请输入正确的模式序号！");
                reader.next();
                continue;
            }
            int mode = reader.nextInt();

            if (mode == 1){
                Object x = reader.next();
                controller.Mode_1(myList, x);
                controller.Mode_1(myLinkList, x);
            }
            else if (mode == 2){
                int x = reader.nextInt();
                Object y = reader.next();
                controller.Mode_2(myList, x, y);
                controller.Mode_2(myLinkList, x, y);
            }
            else if (mode == 3){
                int x = reader.nextInt();
                controller.Mode_3(myList, x);
                controller.Mode_3(myLinkList, x);
            }
            else if (mode == 4){
                int x = reader.nextInt();
                controller.Mode_4(myList, x);
                controller.Mode_4(myLinkList, x);
            }
            else if (mode == 5){
                int x = reader.nextInt();
                Object y = reader.next();
                controller.Mode_5(myList, x, y);
                controller.Mode_5(myLinkList, x, y);
            }
            else if (mode == 0){
                break;
            }
            else{
                System.out.println("请输入正确的模式序号！");
                continue;
            }
        }
        reader.close();
    }
}

class control {
    public void Mode_1(DynamicArray myList, Object x){
        myList.add(x);
        myList.printList();    
    }    

    public void Mode_2(DynamicArray myList, int x, Object y){
        myList.add(x, y);
        myList.printList();   
    }    

    public void Mode_3(DynamicArray myList, int x){
        System.out.println(myList.get(x));
        System.out.println("");
    }    

    public void Mode_4(DynamicArray myList, int x){
        myList.remove(x);
        myList.printList();
    }    

    public void Mode_5(DynamicArray myList, int x, Object y){
        myList.set(x, y);
        myList.printList();   
    }    
}