import java.util.List;
import java.util.ArrayList;
import java.util.function.Supplier;

@SuppressWarnings("unchecked")
public class PriorityQueueT<T extends Comparable<T>, L extends List<T>>  {
    private final BinaryHeap heap;
    private final Supplier<L> supplier;

    public PriorityQueueT(int n) {
        this(n, () -> (L) new ArrayList<T>());
    }
    
    public PriorityQueueT(int n, Supplier<L> supplier) {
        this.supplier = supplier;
        heap = new BinaryHeap(n);
    }

    public boolean isEmpty() { return heap.current_heap_size == 0; }

    public int getSize() { return heap.current_heap_size; }

    public T getMax() { return heap.getMin(); }


    public void push(T element) { heap.insertKey(element); }

    public T pop() { return delete(0); }

    public T delete(int index) { return heap.deleteElementOnIndex(index); }

    @Override
    public String toString() {
        return "PriorityQueue{" +
                "heap=" + heap +
                '}';
    }

    @SuppressWarnings("unchecked")
    private class BinaryHeap {
        private final L heapArray;
        private int current_heap_size;

        public BinaryHeap(int size) throws IllegalArgumentException {
            isValidSize(size);
            heapArray = supplier.get();
            current_heap_size = 0;
            System.out.println(heapArray.getClass().getName());
        }

        private void isValidSize(int size) {
            if (size <= 0)
                throw new IllegalArgumentException();
        }


        private void swap(int i, int j) {
            T temp = heapArray.get(i);
            heapArray.set(i, heapArray.get(j));
            heapArray.set(j, temp);
        }

        private int parent(int index) { return (index - 1) >> 1; }

        private int leftNode(int index) { return (index << 1) + 1; }

        private int rightNode(int index) { return (index << 1) + 2; }


        public void insertKey(T key) {
            int i = current_heap_size;
            heapArray.add(key);
            current_heap_size++;

            while (i != 0 && heapArray.get(i).compareTo(heapArray.get(parent(i))) < 0) {
                swap(i, parent(i));
                i = parent(i);
            }
        }

        private void increaseValueOnIndex(int index, T new_val) {
            heapArray.set(index, new_val);
            MinHeapify(index);
        }

        private void decreaseValueOnIndex(int index, T new_val) {
            heapArray.set(index, new_val);

            while (index != 0 && heapArray.get(index).compareTo(heapArray.get(parent(index))) < 0) {
                swap(index, parent(index));
                index = parent(index);
            }
        }

        public void changeValueOnAnIndex(int index, T new_val) {
            if (heapArray.get(index).equals(new_val)) {
                return;
            }
            if (heapArray.get(index).compareTo(new_val) < 0) {
                increaseValueOnIndex(index, new_val);
            } else {
                decreaseValueOnIndex(index, new_val);
            }
        }


        public T getMin() {
            return heapArray.get(0);
        }

        public T extractMin() {
            if (current_heap_size <= 0) {
                return null;
            }

            if (current_heap_size == 1) {
                current_heap_size--;
                return heapArray.get(0);
            }

            T root = heapArray.get(0);

            heapArray.set(0, heapArray.get(current_heap_size - 1));
            current_heap_size--;
            MinHeapify(0);

            return root;
        }

        public T deleteElementOnIndex(int index) {
            T el = heapArray.get(index);
            heapArray.remove(index);
            current_heap_size--;
            MinHeapify(0);
            return el;
        }

        // A recursive method to heapify a subtree
        // with the root at given index
        // This method assumes that the subtrees
        // are already heapified
        private void MinHeapify(int index) {
            int l = leftNode(index);
            int r = rightNode(index);

            int smallest = index;
            if (l < current_heap_size && heapArray.get(l).compareTo(heapArray.get(smallest)) < 0) {
                smallest = l;
            }
            if (r < current_heap_size && heapArray.get(r).compareTo(heapArray.get(smallest)) < 0) {
                smallest = r;
            }

            if (smallest != index) {
                swap(index, smallest);
                MinHeapify(smallest);
            }
        }

        @Override
        public String toString() {
            return heapArray.toString();
        }
    }
}
