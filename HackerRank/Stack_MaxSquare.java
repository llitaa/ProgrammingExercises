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
            // System.out.printf("Init node %d %d", height, index);
        }
    }
    
    //! Computes max rect square with node passed
    static long computeHeightSquare(int height, int startInd, int endInd) {
        long res = height * (endInd - startInd + 1);
        // System.out.printf("Update max: ht %d, sInd %d, eInd %d %n", height, startInd, endInd);
        return res;
    }
    
    static long updateMax(long currentMax, long value) {
        return Math.max(currentMax, value);
    }
        
    static long largestRectangle(int[] h) {
        //int[] h = {3,2,5,6,1,4,4};
        
        // Complete this function
        Stack<Node> stack = new Stack<Node>();
        long res = 0;
        for(int i=1; i<=h.length; ++i) {
            // System.out.println(i);
            int height = h[i-1];
            if(stack.isEmpty()) {
                stack.push(new Node(height, i));
                continue;
            }
            Node top = stack.peek();
            int prevHeight = top.height;
            // System.out.printf("height %d, prev height %d", height, prevHeight);
            
            if(height > prevHeight) {
                stack.push(new Node(height, i));
               // System.out.printf("Adding height %d, startInd %d", height, i);
            }
            else if(height < prevHeight){ // Height less then top
                // remove items from stack, compute max
                // System.out.printf("Height reduction %d%n", heightReduction);
                // System.out.printf("Height less: current %d previous %d%n", height, prevHeight);
                
                int size = 0;
                while(!stack.isEmpty()) {
                    Node currTop = stack.pop();
                    res =  updateMax(res, computeHeightSquare(currTop.height, currTop.index, i-1));
                    ++size;
                }
                if(height > 0) {
                    stack.push(new Node(height, i-size));
                }
            }
        }
        while(!stack.isEmpty()) {
            Node top = stack.pop();
            // System.out.printf("%d %d %d%n", top.height, top.index, h.length - 1);
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
