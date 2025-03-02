#if 1

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>



// 代码执行时间 类
using namespace std::chrono;
class time_spend {
private:
    steady_clock::time_point start;
    steady_clock::time_point end;

public:
    time_spend() {
        start = steady_clock::now();
    }

    void end_time() {
        end = steady_clock::now();
		auto spend = end - start;
		auto spend_mill = duration_cast<microseconds>(spend);
		std::cout << "消耗时间  " << spend_mill.count() << " 微秒" << std::endl;
    }
    ~time_spend() {
       /* end = steady_clock::now();
        auto spend = end - start;
        auto spend_mill = duration_cast<microseconds>(spend);
        std::cout << "消耗时间  " << spend_mill.count() << " 微秒" << std::endl;*/

    }



};


#endif
// 构造二叉树 节点定义  树的层序遍历
#if 1
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

};
// 层序遍历构造树
TreeNode* create (std::vector<int> nodes) {
    TreeNode* root = new TreeNode(nodes[0]);
    std::queue<TreeNode*> queue_tree;
    queue_tree.push(root);
    for (int i = 1; i < nodes.size(); i=i+2) {
        if (nodes[i] != NULL)
        {
            TreeNode* left = new TreeNode(nodes[i]);
            queue_tree.front()->left = left;
            queue_tree.push(left);
        }
        else
        {
            queue_tree.front()->left == nullptr;
        }
        if ( i+1 <= nodes.size()-1 && nodes[i + 1] != NULL)
        {
            TreeNode* right = new TreeNode(nodes[i + 1]);
            queue_tree.front()->right = right;
            queue_tree.push(right);
        }
        else {
            queue_tree.front()->right = nullptr;
        }
        
        

        queue_tree.pop();

    }
    return root;
}
// 层序遍历
void print_tree(TreeNode* root) {
    std::queue<TreeNode*> queue_tree;
    queue_tree.push(root);
    while (!queue_tree.empty()) {
        if (queue_tree.front() != nullptr) {
            std::cout << queue_tree.front()->val << " ";
            if (queue_tree.front()->left != nullptr || queue_tree.front()->right != nullptr  ) {
                queue_tree.push(queue_tree.front()->left);
                queue_tree.push(queue_tree.front()->right);
            }
            
        }
        else {
            std::cout << "null" << " ";
        }
        queue_tree.pop();
    }
    std::cout << std::endl;
}






#endif


// 删除二叉树中的节点
#if 0

#include <iostream>
#include <stack>
#include <vector>
#include <queue>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

};
// 插入节点
void insert(TreeNode*& root, int val) {
    if (root == nullptr) {
        root = new TreeNode(val);  // 如果树为空，直接创建根节点
        return;
    }

    TreeNode* tmp = root;
    while (tmp != nullptr) {
        // 查找插入位置
        if (val < tmp->val) {
            if (tmp->left == nullptr) {
                tmp->left = new TreeNode(val);  // 在左子树插入
                return;
            }
            tmp = tmp->left;
        }
        else if (val > tmp->val) {
            if (tmp->right == nullptr) {
                tmp->right = new TreeNode(val);  // 在右子树插入
                return;
            }
            tmp = tmp->right;
        }
        else {
            return;  // 如果值已存在，直接返回（避免重复插入）
        }
    }
}
// 构造二叉树 
void create(TreeNode*& root, int str[], int n) {
    root = nullptr;
    for (int i = 0; i < n; i++) {
        insert(root, str[i]);
    }
}
// 删除 二叉树中的节点
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root != nullptr&&root->left == nullptr && root->right == nullptr && root->val == key) {
        return nullptr;
    }
    TreeNode* tmp = root;
    TreeNode* tmp_is_left_child = nullptr;
    TreeNode* tmp_is_right_child = nullptr;
    while (tmp != nullptr && tmp->val != key) {
        if (tmp->val > key) {
            tmp_is_left_child = tmp;
            tmp_is_right_child = NULL;
            tmp = tmp->left;
        }
        else {
            tmp_is_right_child = tmp;
            tmp_is_left_child = NULL;
            tmp = tmp->right;
        }
    }
    // 没找到
    if (tmp == nullptr) {
        return root;
    }
    std::cout << "找到当前节点是" << tmp->val << std::endl;
    if (tmp->left == nullptr && tmp->right == nullptr) {
        if (tmp_is_left_child == nullptr && tmp_is_right_child != nullptr) {
            tmp_is_right_child->right = nullptr;
        }
        else if (tmp_is_left_child != nullptr && tmp_is_right_child == nullptr){
            tmp_is_left_child->left = nullptr;
        }
    }
    if (tmp->left != nullptr && tmp->right == nullptr) {
        if (tmp_is_left_child == nullptr && tmp_is_right_child != nullptr) {
            tmp_is_right_child->right = tmp->left;
        }
        else if (tmp_is_left_child != nullptr && tmp_is_right_child == nullptr) {
            tmp_is_left_child->left = tmp->left;
        }
        else {
            return root->left;
        }
    }
    if (tmp->right != nullptr && tmp->left == nullptr) {
        if (tmp_is_left_child == nullptr && tmp_is_right_child != nullptr) {
            tmp_is_right_child->right = tmp->right;
        }
        else if (tmp_is_left_child != nullptr && tmp_is_right_child == nullptr) {
            tmp_is_left_child->left = tmp->right;
        }
        else {
            return root -> right;
        }
    }
    if (tmp->left != nullptr && tmp->right != nullptr) {
        // 找到右子树的最小值
        std::vector<TreeNode*> result;
        TreeNode* tmp_inorder = nullptr;
        std::stack<TreeNode*> stack;
        stack.push(tmp->right);
        while (!stack.empty()) {
            if (stack.top() != nullptr) {
                TreeNode* p = stack.top();
                stack.pop();

                if (p->right != NULL) stack.push(p->right);

                stack.push(p);
                stack.push(nullptr);

                if (p->left != NULL) stack.push(p->left);
            }
            else {
                stack.pop();
                result.push_back(stack.top());
                stack.pop();
            }
        }
        tmp->val = result[0]->val;
        TreeNode* tmp_3 = tmp->right;
        
        if (tmp_3->left != nullptr) {
            while (tmp_3->left->left != nullptr) {
                tmp_3 = tmp_3->left;
            }


            tmp_3->left = result[0]->right;
        }
        else {
            tmp->right = tmp_3->right;
        }
       

    }
    return root;
}
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);
    std::cout << root->val << " ";
    inorderTraversal(root->right);
}
int main() {
    TreeNode* root = nullptr;
    create(root, new int[1]{ 0}, 1);
    inorderTraversal(root);
    std::cout << std::endl;
    deleteNode(root, 0);
    inorderTraversal(root);
    
}

#endif
// 判断是否是平衡二叉树
#if 0
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
class Solution {


public:
    
    int high_tree(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        

        int left = high_tree(root->left);
        if (left == -1) return -1;
        int right =  high_tree(root->right);
        if (right == -1) return -1;
        if (left - right > 1 || left - right < -1) {
            return -1;
        }
        return left > right ? left + 1 : right + 1;
        
    }


    bool isBalanced(TreeNode* root) {
        if (root == nullptr) {
            return true;

        }
        
        return high_tree(root)== -1 ? false:true;
        
        
        
        
    }
    
};
int main() {
    Solution s;
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->right->right = new TreeNode(3);  // 修改这里，让右边的子节点也指向3
    root->left->left->left = new TreeNode(4);  // 添加4节点到左边的3节点的左边
    root->right->right->right = new TreeNode(4);  // 添加4节点到右边的3节点的右边
	
	
	std::cout << s.isBalanced(root) << std::endl;
}   

#endif
// 二叉树的所有路径  自己写的
#if 0
#include <vector>
#include <iostream>
#include <string>
#include <stack>
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
using namespace std;
class Solution {

public:
    vector<string> result;
    string tmp;
    std::stack<int> size; // 回溯数值  最后一次添加的长度
    void binaryTreePaths_(TreeNode* root) {
        
        
        tmp = tmp + to_string(root->val) + "->";
        size .push( (to_string(root->val) + "->").size());  
        if (root->left == nullptr && root->right == nullptr) {
            result.push_back(tmp);
            return ;
            
            
        }
        if (root->left != nullptr) {
            binaryTreePaths_(root->left);
            tmp.resize(tmp.size() - size.top());
            size.pop();
        }
        if (root->right != nullptr) {
            binaryTreePaths_(root->right);
            tmp.resize(tmp.size() - size.top());
            size.pop();
        }
        

    }
    vector<string> binaryTreePaths(TreeNode* root) {
        
		if (root == nullptr) {
			return {};
		}
		binaryTreePaths_(root);
        for (string &c : result) {
            c.resize(c.size() - 2);
            
        }
        return result;
	}
};

int main() {
    Solution s;
    TreeNode* root = new TreeNode(37);
    root->left = new TreeNode(-34);
    root->right = new TreeNode(-48);
    root->left->right = new TreeNode(-100);
    root->right->left = new TreeNode(-100);
    root->right->right = new TreeNode(48);
    root->right->right->left = new TreeNode(-54);
    root->right->right->left->left = new TreeNode(-71);
    root->right->right->left->right = new TreeNode(-22);
    root->right->right->left->right->right = new TreeNode(8);

    
    for (auto i : s.binaryTreePaths(root)) {
        std::cout << i << std::endl;
    }
}

#endif
 
// 二叉树的所有路径 法二
#if 0
#endif

// 二叉树的所有路径 法三
#if 0
#include <vector>
#include <iostream>
#include <string>
#include <stack>
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
using namespace std;
class Solution {

public:
    vector<string> result;
    
    void binaryTreePaths_(TreeNode* root,string path) {



        path = path + to_string(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            
            result.push_back(path);
            return;


        }
        if (root->left != nullptr) {
            binaryTreePaths_(root->left,path+"->");
            
        }
        if (root->right != nullptr) {
            binaryTreePaths_(root->right,path+"->");
            
        }


    }
    vector<string> binaryTreePaths(TreeNode* root) {

        if (root == nullptr) {
            return {};
        }
        string path;
        binaryTreePaths_(root,path);

        return result;
    }
};

int main() {
    Solution s;
    TreeNode* root = new TreeNode(37);
    root->left = new TreeNode(-34);
    root->right = new TreeNode(-48);
    root->left->right = new TreeNode(-100);
    root->right->left = new TreeNode(-100);
    root->right->right = new TreeNode(48);
    root->right->right->left = new TreeNode(-54);
    root->right->right->left->left = new TreeNode(-71);
    root->right->right->left->right = new TreeNode(-22);
    root->right->right->left->right->right = new TreeNode(8);


    for (auto i : s.binaryTreePaths(root)) {
        std::cout << i << std::endl;
    }
}

#endif

// 相同的树
#if 0

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) {
            return true;
        }
        if (p == nullptr || q == nullptr) {
            return false;
        }
        if (p->val != q->val) 
        {
            return false;
        }
            
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        
        
    }
};
int main() {
    Solution a;
    TreeNode *root = create({1,NULL,2});
    TreeNode* root_1 = create({ 1,2 });
    print_tree(root);
    print_tree(root_1);
    std::cout<<a.isSameTree(root,root_1);
}



#endif

// 另一颗树的子树
#if 0


class Solution {
    bool tmp = false;
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) {
            return true;
        }
        if (p == nullptr || q == nullptr) {
            return false;
        }
        if (p->val != q->val)
        {
            return false;
        }

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);


    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        
        if (root == nullptr) {
            return false;
        }
        if (root->val ==  subRoot->val) {
            
            if (tmp == true) {
                return true;
            }
            tmp = isSameTree(root, subRoot);
            


        }

        isSubtree(root->left, subRoot);

        isSubtree(root->right,subRoot);
        return tmp ;
    }
};
int main()
{
    Solution c;
    TreeNode* a = create({ 1, NULL, 1, NULL, 1, NULL, 1, NULL, 1, NULL, 1, NULL, 1, NULL, 1, NULL, 1, NULL, 1, NULL, 1, 2 });
    TreeNode* b = create({ 1, NULL, 1, NULL, 1, NULL, 1, NULL, 1, NULL, 1, 2 });
    std::cout<< c.isSubtree(a,b);
}
#endif

// 二叉树的最大深度
#if 0
class Solution {
public:
    int result = 0;
    int length = 1;
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        result++;
        if (result > length)length = result;
        if (root->left) {
            maxDepth(root->left);
            
            result--;

        }
        if(root->right){
            maxDepth(root->right); 
            
            result--;
        }
        return length;

    } 
};
int main() {
    Solution a;
    TreeNode* root = create({1,2,3,4,5,6,7});

    print_tree(root);
    
    std::cout << a.maxDepth(root);
}


#endif

// 左叶子之和
#if 0 
class Solution {
public:
    int result = 0;
    int sumOfLeftLeaves(TreeNode* root) {
        if (root->left) {
            if(root->left->left == nullptr && root->left->right == nullptr)result = result + root->left->val;
            sumOfLeftLeaves(root->left);
        }
        if (root->right) {
            sumOfLeftLeaves(root->right);
        }
        return result;
    }
};




#endif

//513. 找树左下角的值
#if 0
class Solution {
public:
    int left_max = 0;
    int left_depth_max = 0;
    int findBottomLeftValue_(TreeNode* root , int depth) {
        if (root == nullptr) {
            return 0;
        }
        std::cout << "当前遍历的值是" << root->val << std::endl;
        depth++;
        // 自己的做法 复杂
        /*if ((root->right && root->right->left == nullptr && root->right->right == nullptr)
            || (root->left && root->left->left == nullptr && root->left->right == nullptr)) {
            if (depth + 1 > left_depth_max) {
                if (root->left) {
                    left_max = root->left->val;
                    left_depth_max = depth + 1;
                }
                else if(root->right) {
                    left_max = root->right->val;
                    left_depth_max = depth + 1;
                }
            }

        }*/
        if (root->left == NULL && root->right == NULL) {
            if (depth > left_depth_max) {
                left_depth_max = depth;
                left_max = root->val;
            }
            
        }

        findBottomLeftValue_(root->left, depth);
        findBottomLeftValue_(root->right, depth);

        return left_max;
    }
    int findBottomLeftValue(TreeNode* root) {
        if (root->left == nullptr && root->right == nullptr) {
            return root->val;
        }
        int depth = 0;
        return findBottomLeftValue_(root,depth);
    }
};
int main() {
    Solution a;
    TreeNode* root = create({ 3,1,5,9,2,4,6 });
    std::cout<<a.findBottomLeftValue(root);
}

#endif

// 112. 路径总和
#if 0

class Solution {
public:
    
    bool hasPathSum_(TreeNode* root, int targetSum,int tep) {
        if (root == nullptr) {
            return false;
        }
        tep = tep + root->val;
        if (root->left==nullptr && root->right ==nullptr && targetSum == tep) {
            return true;
        }
        
        
        return hasPathSum_(root->left, targetSum, tep) || hasPathSum_(root->right, targetSum, tep);
    }
    bool hasPathSum(TreeNode* root, int targetSum) {
        int tmp = 0;
        return hasPathSum_(root, targetSum ,tmp);
    }
};

int main() {
    Solution a;
    TreeNode* root = create({ 5, 4, 8, 11, NULL, 13, 4, 7, 2, NULL, NULL, NULL, 1 });
    std::cout << a.hasPathSum(root, 22);
}

#endif

// 113. 路径总和 II

#if 0
#define null NULL
using namespace std;
class Solution {
    vector<vector<int>> result;
    vector<int> tmp;
    int sum = 0;
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return {};
        }
        std::cout << "当前节点是" << root->val << std::endl;
        tmp.push_back(root->val);
        sum = sum + *(tmp.end()-1);
        //if (root->left == nullptr && root->right == nullptr  && [=]()-> int {
        //    int sum = 0;
        //    for (int c : tmp) {
        //        sum = c + sum;
        //    }
        //    return sum;
        //    }() == targetSum) {

        //    result.push_back(tmp);
        //}
        if (root->left == nullptr && root->right == nullptr && sum == targetSum) {
            result.push_back(tmp);
        }

        if (root->left) {
            pathSum(root->left, targetSum);
            sum = sum - *(tmp.end() - 1);
            tmp.pop_back();
            
        }
        if (root->right) {
            pathSum(root->right, targetSum);
            sum = sum - *(tmp.end() - 1);
            tmp.pop_back();
            
        }
        return result;
    }
};
int main() {
    Solution a;
    TreeNode* root = create({ 5,4,8,11,null,13,4,7,2,null,null,5,1 });
    std::vector<std::vector<int>> tmp;
    tmp = a.pathSum(root,22);
    for (std::vector<int> c : tmp) {
        for (int a : c) {
            std::cout << a << " ";
        }
        std::cout << std::endl;
    }
}

#endif

// 按序打印
#if 0
using namespace std;
class Foo {

public:
    mutex loc;
    condition_variable test;
    string order ;
    Foo() {

    }

    void first(function<void()> printFirst) {

        // printFirst() outputs "first". Do not change or remove this line.

        unique_lock<mutex> lk(loc);
        
        order = "second";
        printFirst();
        lk.unlock();
        test.notify_all();
    }

    void second(function<void()> printSecond) {

        // printSecond() outputs "second". Do not change or remove this line.
        unique_lock<mutex> lk(loc);
        test.wait(lk, [=] {return order == "second"; });
            
        order = "third";
        printSecond();
        lk.unlock();
        test.notify_all();
        
    }

    void third(function<void()> printThird) {

        // printThird() outputs "third". Do not change or remove this line.
        unique_lock<mutex> lk(loc);
        test.wait(lk, [=] {return order == "third"; });
        order = "first";
        printThird();
        lk.unlock();
        test.notify_all();
        
    }
};

void printFirst() {
    std::cout << "线程一 " << std::endl;
}
void printSecond() {
    std::cout << "线程二 " << std::endl;
}
void printthird() {
    std::cout << "线程三 " << std::endl;
}

int main() {
    Foo test;
    thread t1 (&Foo::first,&test,&printFirst);
    thread t2(&Foo::second, &test, &printSecond);
    thread t3(&Foo::third, &test, &printthird);
    
    t1.join();
    t2.join();
    t3.join();
}


#endif

// 哲学家问题
#if 0
using namespace std;
class DiningPhilosophers {
public:
    DiningPhilosophers() {

    }

    void wantsToEat(int philosopher,
        function<void()> pickLeftFork,
        function<void()> pickRightFork,
        function<void()> eat,
        function<void()> putLeftFork,
        function<void()> putRightFork) {

    }
};


#endif


//98. 所有可达路径
#if 0 
#include <iostream>
#include <vector>
#include <list>

// 图的存储 邻接矩阵 
class tu {
public:

    int node_num;
    std::vector<std::vector<int>> data;
    tu(int n):node_num (n), data(n, std::vector<int>(n, 0)){
        
    }
    void create( int c) {
        int a = 0, b = 0;
        for(int i = 0; i < c; i++){
            std::cin >> a >> b;
            data[a-1][b-1] = 1;
        }
    }
    
};
std::vector<int> tmp{1};
std::vector<std::vector<int>> result;
// 深度搜索可达路径
void research(tu a ,int n) {
    
    if (n == a.node_num - 1) {
        result.push_back(tmp);
        return;
    }
    
    for (int i = 0; i < a.node_num; i++) {
        if (a.data[n][i] == 1) {
            tmp.push_back(i+1);
            research(a,i);
            tmp.pop_back();
        }
    }
}
// 矩阵打印
void print_v(std::vector<std::vector<int>> a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            std::cout << a[i][j];
            if (j != a[i].size() - 1) {
                std::cout<< " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    int a = 0, b = 0;
    std::cin >> a >> b;
    tu test(a);
    test.create(b);
    //print_v(test.data);
    research(test,0);
    if (result.empty()) {
        std::cout << -1;
        return 0;
    }
    print_v(result);


    

}


#endif


#if 0
#include <iostream>
#include <vector>
#include <list>
// 邻接表
class graph {
public:
    int node_num;
    int side_num;
    std::vector<std::list<int>> data;
    graph(int n,int b) :node_num(n),side_num(b), data(n + 1, std::list<int>()) {
        
	}
    void create() {
        for (int i = 0; i < side_num; i++) {
            int a = 0, b = 0;
            std::cin >> a >> b;
            data[a].push_back(b);

        }

    }
    void print_group() {
        for (std::list<int> c : data) {
            
            for (std::list<int>::iterator i = c.begin(); i != c.end(); i++) {
                std::cout << *i ;
                if (i != --c.end()) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    std::vector<std::vector<int>> result;
    std::vector<int> tmp{1};
    // 深度搜索 可达路径
    void research( int a, int b) {
        if (a == b) {
            result.push_back(tmp);
            return;
        }
        for (std::list<int>::iterator i = data[a].begin(); i != data[a].end(); i++) {
            tmp.push_back(*i);
            research(*i, b);
            tmp.pop_back();
		}
        

    }
    

};

// 矩阵打印
void print_v(std::vector<std::vector<int>> a) {
    if (a.empty()) {
        std::cout << -1;
        
    }
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            std::cout << a[i][j];
            if (j != a[i].size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}




int main() {
    int a, b;
    std::cin>>a >> b;
    graph test(a,b);
    test.create();
    //test.print_group();
    test.research(1, a);
    print_v(test.result);

}
#endif

//797. 所有可能的路径
#if 0
using namespace std;
// 邻接矩阵
class Solution {
    vector<vector<int>> result;
    vector<int> tmp{0};
    int current = 0;
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        
        if (current == graph.size()-1) {
            result.push_back(tmp);
        }
        for (int i = 0; i < graph.size(); i++) {
            if (graph[current][i] == 1) {
                
                tmp.push_back(i);
                current = i;
                allPathsSourceTarget(graph);

                tmp.pop_back();
                current = tmp.back();
            }
        }
        return result;
    }
};

void printPaths(const vector<vector<int>>& paths) {
    for (const auto& path : paths) {
        cout << "[";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
}


int main() {
    // 构建一个示例图
    // 图的表示方法为邻接矩阵，其中1表示存在边，0表示不存在边
    vector<vector<int>> graph = {
        {0, 1, 1, 0}, // 从节点0可以到达节点1
        {0, 0, 0, 1}, // 从节点1可以到达节点2和3
        {0, 0, 0, 1}, // 从节点2可以到达节点3
        {0, 0, 0, 0}  // 节点3没有其他节点可以到达
    };

    Solution solution;
    vector<vector<int>> paths = solution.allPathsSourceTarget(graph);

    cout << "从源到目标的所有路径:" << endl;
    printPaths(paths);

    return 0;
}
#endif

//797. 所有可能的路径
#if 0
// 邻接表

using namespace std;

// 效率高代码 
class Solution_ {
public:
    vector<vector<int>> ans;
    vector<int> stk;
    int times = 0;

    void dfs(vector<vector<int>>& graph, int x, int n) {
        times++;
        if (x == n) {
            ans.push_back(stk);
            return;
        }
        for (auto& y : graph[x]) {
            stk.push_back(y);
            dfs(graph, y, n);
            stk.pop_back();
        }
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        stk.push_back(0);
        dfs(graph, 0, graph.size() - 1);
        return ans;
    }
};

// return  超大数组非常耗时  
 //你的原始代码
class Solution {

public:
    vector<vector<int>> result;
    vector<int> tmp{ 0 };
    int current = 0;

    int times = 0;
    void allPathsSourceTarget_(vector<vector<int>>& graph) {
        times++;
        if (current == graph.size() - 1) {
            result.push_back(tmp);
            return;
        }

        for (int c : graph[current]) {
            tmp.push_back(c);
            current = c;
            allPathsSourceTarget_(graph);
            tmp.pop_back();
            current = tmp.back();
        }
        
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
		allPathsSourceTarget_(graph);
		return result;
	}

};

// 辅助函数：打印路径
void printPaths(const vector<vector<int>>& paths) {
    cout << "找到的路径数量: " << paths.size() << endl;
    for (const auto& path : paths) {
        cout << "[";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
}

int main() {
    // 测试用例：graph = [[1,2], [3], [4], [4], []]
    // 正确路径应为 [0,1,3,4] 和 [0,2,4]
    vector<vector<int>> graph = {
    {4,14,3,12,5,2,8,1,10,6,13,7,11}, // 节点0的邻居
    {3,5,11,13,2,4,9,10,12,6},        // 节点1的邻居
    {4,5,10,6,7,13,14,12,11,3,8},     // 节点2的邻居
    {7,5,6,9,13,12,11,4,14},          // 节点3的邻居
    {6,8,13,12,7,10,5,9,14,11},       // 节点4的邻居
    {8,9,7,13,12,11,14,10,6},         // 节点5的邻居
    {8,10,14,11,13,7},                // 节点6的邻居
    {11,10,12,14,9,8},                // 节点7的邻居
    {11,10,13,12,9},                  // 节点8的邻居
    {12,13,11,10,14},                 // 节点9的邻居
    {14,11,13},                       // 节点10的邻居
    {13,14,12},                       // 节点11的邻居
    {14,13},                          // 节点12的邻居
    {14},                             // 节点13的邻居
    {}                                // 节点14的邻居
    };

    Solution_ solution;
    time_spend time;
    vector<vector<int>> paths = solution.allPathsSourceTarget(graph);
    time.end_time();
    std::cout<< solution.times << std::endl;

    Solution solution_;
    
    time_spend time_;
    vector<vector<int>> path = solution_.allPathsSourceTarget(graph);
    time_.end_time();
    std::cout << solution_.times << std::endl;
  
    //printPaths(paths);

    return 0;
}





#endif

// 卡玛网 99 leetcode 200

#if 0

// 广度优先搜索
using namespace std;

class Solution_ {
    
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                std::queue<int> tmp;
                if (grid[i][j] == '1') {
                    tmp.push(i);
                    tmp.push(j);
                    count++;
                }
                while (!tmp.empty()) {
                    int x = tmp.front();
                    tmp.pop();
                    int y = tmp.front();
                    tmp.pop();
                    grid[x][y] = 0;
                    if (x > 0 && grid[x - 1][y] == '1') {
                        tmp.push(x - 1);
                        tmp.push(y);
                        grid[x-1][y] = 0;
                    }
                    if (y < grid[i].size()-1 && grid[x][y + 1] == '1') {
                        tmp.push(x);
                        tmp.push(y + 1);
                        grid[x][y+1] = 0;
                    }
                    if (x < grid.size()-1 && grid[x+1][y] == '1') {
                        tmp.push(x+1);
                        tmp.push(y);
                        grid[x+1][y] = 0;
                    }
                    
                    
                    if (y > 0 && grid[x][y-1] == '1') {
                        tmp.push(x);
                        tmp.push(y-1);
                        grid[x][y-1] = 0;
                    }
                    
                }
                
            }


        }
        return count;
    }
};

// 访问过 数组 版本
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
        vector<std::pair<int, int>> dir
        {
            pair<int,int>(1,0),
            pair<int,int>(-1,0),
            pair<int,int>(0,-1),
            pair<int,int>(0,1)
        };
        int count = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                
                if (visited[i][j] == false && grid[i][j] == '1'  ) {
                    count++;
                    std::queue<pair<int, int>> tmp;
                    tmp.push(pair<int, int>(i, j));
                    visited[i][j] = true;
                    while (!tmp.empty()) {
                        for (int c = 0; c < 4; c++) {
                            int x = tmp.front().first + dir[c].first;
                            int y = tmp.front().second + dir[c].second;
                            
                            if (x<0||y<0||x>= grid.size()||y>= grid[0].size()) {
                                continue;
                            }
                            if (visited[x][y] == false &&
                                grid[x][y] == '1') {
                                tmp.push(pair<int, int>(x, y));
                                visited[x][y] = true;
                            }
                        }
                        tmp.pop();


                    }
                }

            }
        }
        return count;
    }
};



int main() {
    std::vector<std::vector<char>> a = {
    {'1', '1', '1', '1', '1'},
    {'1', '1', '0', '1', '0'},
    {'1', '0', '0', '0', '1'},
    {'0', '1', '0', '1', '0'}
    };
    Solution v;
    std::cout<<v.numIslands(a);
}

#endif



// 106. 从中序与后序遍历序列构造二叉树
#if 1
using namespace std;
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() == 1 && postorder.size() == 1) {
            int tem = postorder[postorder.size() - 1];
            TreeNode* root = new TreeNode(tem);
            return root;
        }
        int tem = postorder[postorder.size() - 1];
		TreeNode* root = new TreeNode(tem);
        std::vector<int>::iterator find_ = find( inorder.begin(), inorder.end(),tem);
		int find_index = find_ - inorder.begin();
        
		
        // 左子树最后一个元素下标
        int  left_index= find_index -1 ;
        // 右子树数量
        int right_num = inorder.end()  - find_ - 1;
        
        if (left_index >= 0) {
            //构造左子树
            vector<int> left_inorder(inorder.begin(), inorder.begin() + left_index + 1); //构造不包含最后一个元素 所以加一  不需要
            vector<int> left_postorder(postorder.begin(), postorder.begin() + left_index + 1);
            root->left = buildTree(left_inorder, left_postorder);
        }
		

        //构造右子树
        if (right_num == 0) {
            return root;
        }
        postorder.pop_back();
        vector<int> right_inorder(inorder.begin()+left_index+2,inorder.end());
        vector<int> right_postorder(postorder.begin()+left_index+1,postorder.end());
        root->right = buildTree(right_inorder,right_postorder);




        return root;
    }
};
int main() {
    Solution a;
    std::vector<int> tep1 = { 2,1 };
    std::vector<int> tep2 = { 2,1 };
   
    print_tree(a.buildTree(tep1, tep2));
}

#endif

