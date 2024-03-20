package slidingWindow;

import java.util.List;
import java.util.Map;
import java.util.LinkedList;
import java.util.HashMap;

public class solution {
    public List<Integer> slidingWindowTemplate(String s, String t) {
        // init a collection or int value to save the result according to the question
        List<Integer> result = new LinkedList<>();
        if (t.length() > s.length()) {
            return result;
        }
        // create hashmap to store freq of characters
        Map<Character, Integer> map = new HashMap<>();
        for (char c : t.toCharArray()) {
            // incement the index denoted by character by 1, getorDefault will return the
            // value mapped with specified key (c), returns 0 if there is no value mapped
            // with key, then increment the value for every occurance of
            // specific key c
            map.put(c, map.getOrDefault(c, 0) + 1);
        }
        // maintain counter to check whetcher s matches target string
        int counter = map.size();
        // 2 pointers, begin = left of window, end = right of window
        int begin = 0, end = 0;

        int len = Integer.MAX_VALUE;

        while (end < s.length()) {
            char c = s.charAt(end);
            if (map.containsKey(c)) {
                map.put(c, map.get(c) - 1);
                if (map.get(c) == 0) {
                    counter--;
                }
            }
            end++;

            while (counter == 0) {
                char tempc = s.charAt(begin);
                if (map.containsKey(tempc)) {
                    map.put(tempc, map.get(tempc) + 1);
                    if (map.get(tempc) > 0) {
                        counter++;
                    }

                }
                begin++;
            }
        }
        return result;

    }
}
