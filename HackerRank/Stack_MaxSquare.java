import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    static class Node {
        int height;
        int index; // Index it was introduced
        Node (int ht, int ind) {
            height = ht;
            index = ind;
        }
    }
    
    //! Computes max rect square with node passed
    static long computeHeightSquare(int height, int startInd, int endInd) {
        long res = height * (endInd - startInd + 1);
        return res;
    }
    
    static long updateMax(long currentMax, long value) {
        return Math.max(currentMax, value);
    }
        
    static long largestRectangle(int[] h) {
        // Complete this function
        int stackSize = 0;
        Stack<Node> stack = new Stack<Node>();
        long res = 0;
        for(int i=1; i<=h.length; ++i) {
            // System.out.println(i);
            int height = h[i-1];
            int prevHeight = stackSize == 0 ? -1 : stack.peek().height;
            int itemInd = i;
            if(height < prevHeight) { 
                int lastInd = stackSize;
                while(stackSize != 0) { // found bigger item
                    Node currTop = stack.peek();
                    if(currTop.height > height) {
                        res =  updateMax(res, computeHeightSquare(currTop.height, currTop.index, i-1));
                        itemInd = currTop.index;
                        stack.pop();
                        --stackSize;
                    }
                    else {
                        break;
                    }  
                }
            }
            prevHeight = stackSize == 0 ? -1 : stack.peek().height;
            if(height > prevHeight) {
                ++stackSize;
                stack.push(new Node(height, itemInd));
            }
        }
        while(!stack.isEmpty()) {
            Node top = stack.pop();
            res = updateMax(res, computeHeightSquare(top.height, top.index, h.length));
        }
        return res;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] h = new int[n];
        for(int h_i = 0; h_i < n; h_i++){
            h[h_i] = in.nextInt();
        }
        long result = largestRectangle(h);
        System.out.println(result);
        in.close();
    }
}