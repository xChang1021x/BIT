package arraylist;

public class MyArrayList implements DynamicArray {
    private Object[] data;
    private int size;

    public MyArrayList() {
        data = new Object[10];
        size = 0;
    }

    public MyArrayList(int initialCapacity) {
        data = new Object[initialCapacity];
        size = 0;
    }

    public void add(Object element) {
        if (size == data.length) {
            ensureCapacity();
        }
        data[size] = element;
        size++;
    }

    public void add(int index, Object element) {
        if (index < 0 || index > size) {
            System.out.println("无效位置/超出范围");
            return;
        }
        if (size == data.length) {
            ensureCapacity();
        }
        for (int i = size; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = element;
        size++;
    }

    public Object get(int index) {
        if (index < 0 || index >= size) {
            System.out.println("无效位置/超出范围");
            return null;
        }
        return data[index];
    }

    public void remove(int index) {
        if (index < 0 || index >= size) {
            System.out.println("无效位置/超出范围");
            return;
        }

        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        data[size - 1] = null;
        size--;
    }

    public void set(int index, Object element) {
        if (index < 0 || index >= size) {
            System.out.println("无效位置/超出范围");
            return;
        }
        data[index] = element;
    }

    public int size() {
        return size;
    }

    public void printList(){
        System.out.print("List: ");
        for (int i = 0; i < size; i++){
            System.out.print(data[i] + " ");
        }
        System.out.println("");
    }

    private void ensureCapacity() {
        int newCapacity = data.length * 2;
        Object[] newData = new Object[newCapacity];
        System.arraycopy(data, 0, newData, 0, size);
        data = newData;
    }
}
