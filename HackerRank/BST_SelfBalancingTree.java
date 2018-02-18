   /* Class node is defined as :
    class Node 
       int val;   //Value
       int ht;      //Height
       Node left;   //Left child
       Node right;   //Right child
   */

   static LinkedList<Node> insert1(Node root, int val) {
       Node node = root;
       LinkedList<Node> parents = new LinkedList<Node>();
       boolean heightIncreased = false;
       
       while(true) {
           parents.add(node);
           if(val < node.val) {
               if(node.left == null) {
                   Node nn = new Node();
                   nn.val = val;
                   nn.ht = 0;
                   node.left = nn;
                   if(node.right == null) {
                       heightIncreased = true;
                   }
                   break;
               }
               node = node.left;
           }
           else if(val > node.val) {
               if(node.right == null) {
                   Node nn = new Node();
                   nn.val = val;
                   nn.ht = 0;
                   node.right = nn;
                   if(node.left == null) {
                       heightIncreased = true;
                   }
                   break;
               }
               node = node.right;
           }
       }
       if(heightIncreased) {
           for (Node p : parents) { 
            ++p.ht;
           }
       }
       return parents;
   }

   static int balanceFactor(Node n) {
       int leftHeight = n.left != null ? n.left.ht + 1 : 0;
       int rightHeight = n.right != null ? n.right.ht + 1 : 0; 
       return leftHeight - rightHeight;
   }

   static void updateChild(Node n, Node oldChild, Node newChild) {
       if(n != null) {
           if(n.left == oldChild) {
                n.left = newChild;
           }
           else if(n.right == oldChild) {
                n.right = newChild;
           }
       }
   }

   static void updateHeight(Node n) {
       int lh = n.left  != null ? n.left.ht  : -1;
       int rh = n.right != null ? n.right.ht : -1;
       n.ht = Math.max(lh + 1, rh + 1);
       // System.out.printf("%d%n", n.ht);
   }

   static void rotateLeft(Node lhs, Node rhs, Node rhsParent) {
        if(rhs != null && lhs != null) {
            rhs.right = lhs.left;
            updateHeight(rhs);
            lhs.left = rhs;
            updateHeight(lhs);
            updateChild(rhsParent, rhs, lhs);
        }
   }

   static void rotateRight(Node lhs, Node rhs, Node rhsParent) {
       rhs.left = lhs.right;
       updateHeight(rhs);
       lhs.right = rhs;
       updateHeight(lhs);
       updateChild(rhsParent, rhs, lhs);
   }

   static Node balance(Node node, Node parent) {
       Node root = node;
       int bf = balanceFactor(node);
       if(bf > 1) { // left overbalance
           if(balanceFactor(node.left) == -1) { // left Right case
               rotateLeft(node.left.right, node.left, parent);
               rotateRight(node.left.right, node, parent);
               root = node.left.right;
           }
           else if(balanceFactor(node.left) == 1) { // left left case
               rotateRight(node.left, node, parent);
               root = node.left;
           }
       }
       else if(bf < -1) { // right overbalance
           if(balanceFactor(node.right) == 1) { // right left case
               rotateRight(node.right.left, node.right, parent);
               rotateLeft(node.right.left, node, parent);
               root = node.right.left;
           }
           else if(balanceFactor(node.right) == -1) { // right right case
               rotateLeft(node.right, node, parent);
               root = node.right;
           }
       }
       return root;
   }

   static Node insert(Node root,int val) {
       // System.out.printf("%d%n", root.ht);
       LinkedList<Node>parents = insert1(root, val);
        
       while(!parents.isEmpty()) {
          Node node = parents.removeLast(); // remove, get value
          // System.out.printf("%d%n", node.ht);
          updateHeight(node);
          // System.out.printf("%d%n", node.ht);
          Node parent = !parents.isEmpty() ? parents.getLast() : null;
          root = balance(node, parent);
       }
       return root;
    }
