import java.util.HashMap;
import java.util.Map;

public class test {

    // finds the subarray w largest sum of length k
    public static int findMaxSumSubarray(int[] arr, int k) {
        int maxValue = -100;
        int currentSum = 0;

        for (int i = 0; i < arr.length; i++) {
            currentSum += arr[i];
            if (i >= k - 1) {
                maxValue = Math.max(maxValue, currentSum);
                currentSum -= arr[i - (k - 1)];
            }
        }
        return maxValue;
    }

    // smallest subarray with sum >= target
    public static int dynamicSum(int[] arr, int target) {
        int minWindow = 100;
        int currentWindowSum = 0;
        int windowStart = 0;

        for (int windowEnd = 0; windowEnd < arr.length; windowEnd++) {
            currentWindowSum += arr[windowEnd];
            while (currentWindowSum >= target) {
                minWindow = Math.min(minWindow, windowEnd - windowStart + 1);
                currentWindowSum -= arr[windowStart];
                windowStart++;
            }
        }
        return minWindow;
    }

    public static double avgSubarrayK(int k, int[] nums) {
        double[] result = new double[nums.length - k + 1];
        int windowStart = 0;
        double windowSum = 0;
        for (int windowEnd = 0; windowEnd < nums.length; windowEnd++) {
            windowSum += nums[windowEnd];
            if (windowEnd > k - 1) {
                result[windowStart] = windowSum / k;
                windowSum -= nums[windowStart];
                windowStart++;
            }
        }
        return result;
    }

    /*
     * longest substring with k distinct characters
     * Input: String="araaci", K=2
     * Output: 4
     * Explanation: The longest substring with no more
     * than '2' distinct characters is "araa".
     * 
     * Input: String="cbbebi", K=3
     * Output: 5
     * Explanation: The longest substrings with no more
     * than '3' distinct characters are "cbbeb" & "bbebi".
     */

    public int longestSubstringWithKDistinctChars(String s, int k) {

        if (s == null || s.length() == 0 || k == 0)
            return 0;
        int windowStart = 0;
        int maxLen = 0;
        Map<Character, Integer> mp = new HashMap<>();

        // loop throough string, put characters in hashmap, if map size > k means we
        // have more than k unquique characters, move window to right by decreasing freq
        // of left most char, if freq = 0, remove the char
        for (int windowEnd = 0; windowEnd < s.length(); windowEnd++) {
            char right = s.charAt(windowEnd);
            mp.put(right, mp.getOrDefault(right, 0) + 1);

            while (mp.size() > k) {
                char left = s.charAt(windowStart);
                mp.put(left, mp.get(left) - 1);
                if (mp.get(left) == 0) {
                    mp.remove(left);
                }
                windowStart++;
            }
            maxLen = Math.max(maxLen, windowEnd - windowStart + 1);
        }
        return maxLen;
    }

    /*
     * fruits in basket
     * Given an array of characters where each character represents a fruit tree,
     * you are given two baskets and your goal is to put maximum number of fruits in
     * each basket. The only restriction is that each basket can have only one type
     * of fruit.
     * 
     * You can start with any tree, but once you have started you can’t skip a tree.
     * You will pick one fruit from each tree until you cannot, i.e., you will stop
     * when you have to pick from a third fruit type.
     * 
     * Write a function to return the maximum number of fruits in both the baskets.
     * 
     * Example 1:
     * 
     * Input: Fruit=['A', 'B', 'C', 'A', 'C']
     * Output: 3
     * Explanation: We can put 2 'C' in one basket and one 'A' in
     * the other from the subarray ['C', 'A', 'C']
     * Example 2:
     * 
     * Input: Fruit=['A', 'B', 'C', 'B', 'B', 'C']
     * Output: 5
     * Explanation: We can put 3 'B' in one basket and two 'C' in
     * the other basket.
     * This can be done if we start with the second letter:
     * ['B', 'C', 'B', 'B', 'C']
     * 
     */

    public static int fruitBasket(char[] arr) {
        int windowStart = 0;
        int maxFruit = 0;
        Map<Character, Integer> map = new HashMap<>();
        for (int windowEnd = 0; windowEnd < arr.length; windowEnd++) {
            char right = arr[windowEnd];
            map.put(right, map.getOrDefault(right, 0) + 1);

            while (map.size() > 2) {
                char left = arr[windowStart];
                map.put(left, map.get(left) - 1); // decrease freq of left char in window as we move to right
                if (map.get(left) == 0) {
                    map.remove(left);
                }
                windowStart++;
            }
            maxFruit = Math.max(maxFruit, windowEnd - windowStart + 1);
        }
        return maxFruit;
    }

    /*
     * Given a string, find the length of the longest substring which has no
     * repeating characters.
     * 
     * Example 1:
     * 
     * Input: String="aabccbb"
     * Output: 3
     * Explanation: The longest substring without any repeating
     * characters is "abc".
     * Example 2:
     * 
     * Input: String="abbbb"
     * Output: 2
     * Explanation: The longest substring without any repeating
     * characters is "ab".
     * Example 3:
     * 
     * Input: String="abccde"
     * Output: 3
     * Explanation: Longest substrings without any repeating
     * characters are "abc" & "cde".
     */

    public static int longestNoRepeat(String s) {
        Map<Character, Integer> map = new HashMap<>();
        int windowStart = 0;
        int maxLen = 0;
        for (int windowEnd = 0; windowEnd < s.length(); windowEnd++) {
            char right = s.charAt(windowEnd);
            if (map.containsKey(right)) {
                windowStart = Math.max(windowStart, map.get(right) + 1);
            }
            map.put(right, windowEnd);
            maxLen = Math.max(maxLen, windowEnd - windowStart + 1);
        }
        return maxLen;
    }

    /*
     * Problem:
     * 
     * You are given a string s and an integer k. You can choose any character of
     * the string and change it to any other uppercase English character. You can
     * perform this operation at most k times.
     * 
     * Return the length of the longest substring containing the same letter you can
     * get after performing the above operations.
     * 
     * Example 1:
     * 
     * Input: s = "ABAB", k = 2
     * Output: 4
     * Explanation: Replace the two 'A's with two 'B's or vice versa.
     * Example 2:
     * 
     * Input: s = "AABABBA", k = 1
     * Output: 4
     * Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
     * The substring "BBBB" has the longest repeating letters, which is 4.
     */

    public static int longestSame(String s, int k) {
        int[] cache = new int[26];
        int left = 0;
        int max = 0;
        int mostFreq = 0;
        for (int right = 0; right < s.length(); right++) {
            cache[s.charAt(right) - 'A']++;
            mostFreq = Math.max(mostFreq, cache[s.charAt(right) - 'A']); // calculates freq of repeated letter, thus the
                                                                         // letters to change will be the lenght - freq
            int letterToChange = (right - left + 1) - mostFreq;
            // if we have more letters to change than k, we remove the last letter and
            // increment left ptr
            if (letterToChange > k) {
                cache[s.charAt(left) - 'A']--;
                left++;
            }
            max = Math.max(max, right - left + 1);
        }
    }

    public static int longestOne(int arr[], int k) {
        int left = 0;
        int max = 0;
        int zeroCount = 0;
        for (int right = 0; right < arr.length; right++) {
            if (arr[right] == 0) {
                zeroCount++;
            }
            while (zeroCount > k) {
                if (arr[left] == 0) {
                    zeroCount--;
                }
                left++;
            }
            max = Math.max(max, right - left + 1);
        }
        return max;
    }

    /*
     * Given two strings s1 and s2, return true if s2 contains a permutation of s1,
     * or false otherwise.
     * 
     * In other words, return true if one of s1's permutations is the substring of
     * s2.
     * 
     * 
     * 
     * Example 1:
     * 
     * Input: s1 = "ab", s2 = "eidbaooo"
     * Output: true
     * Explanation: s2 contains one permutation of s1 ("ba").
     * Example 2:
     * 
     * Input: s1 = "ab", s2 = "eidboaoo"
     * Output: false
     * 
     */


     public static boolean isPerm(String s, String t){
        
     }


    public static void main(String[] args) {
        int[] input = new int[] { 4, 2, 2, 7, 8, 1, 2, 8, 10 };
        System.out.println(dynamicSum(input, 8));
    }

}
