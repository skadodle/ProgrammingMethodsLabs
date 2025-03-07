import java.util.*;

public class Test {
    public static void main(String[] args) {
        PriorityQueue<Integer> pq = new PriorityQueue<>(6, Collections.reverseOrder());
        pq.add(50);
        pq.add(200);
        pq.add(10);
        pq.add(300);
        pq.add(250);
        System.out.println(pq);
    }
}
