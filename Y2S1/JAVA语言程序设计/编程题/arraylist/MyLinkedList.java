package arraylist;

public class MyLinkedList implements DynamicArray {
    private Node head;
    private Node tail;
    private int size;

    public MyLinkedList() {
        head = null;
        tail = null;
        size = 0;
    }

    private class Node {
        Object data;
        Node next;

        Node(Object data) {
            this.data = data;
            this.next = null;
        }
    }

    public void add(Object element) {
        Node newNode = new Node(element);
        if (size == 0) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail.next = newNode;
            tail = newNode;
        }
        size++;
    }

    public void add(int index, Object element) {
        if (index < 0 || index > size) {
            System.out.println("无效位置/超出范围");
            return;
        }

        Node newNode = new Node(element);
        if (index == 0) {
            newNode.next = head;
            head = newNode;
        } 
        else {
            Node current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current.next;
            }
            newNode.next = current.next;
            current.next = newNode;
        }
        size++;
    }

    public Object get(int index) {
        if (index < 0 || index >= size) {
            System.out.println("无效位置/超出范围");
            return null;
        }

        Node current = head;
        for (int i = 0; i < index; i++) {
            current = current.next;
        }
        return current.data;
    }

    public void remove(int index) {
        if (index < 0 || index >= size) {
            System.out.println("无效位置/超出范围");
            return;
        }

        if (index == 0) {
            head = head.next;
        } else {
            Node current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current.next;
            }
            current.next = current.next.next;
        }
        size--;
    }

    public void set(int index, Object element) {
        if (index < 0 || index >= size) {
            System.out.println("无效位置/超出范围");
            return;
        }

        Node current = head;
        for (int i = 0; i < index; i++) {
            current = current.next;
        }
        current.data = element;
    }

    public int size() {
        return size;
    }

    public void printList() {
        Node current = head;
        System.out.print("List: ");
        while (current != null) {
            System.out.print(current.data + " ");
            current = current.next;
        }
        System.out.println();
        System.out.println();
    }
}
