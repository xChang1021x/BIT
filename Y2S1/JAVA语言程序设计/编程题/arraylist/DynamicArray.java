package arraylist;

public interface DynamicArray {
    void add(Object element);
    void add(int index, Object element);
    Object get(int index);
    void remove(int index);
    void set(int index, Object element);
    int size();
    void printList();
}
