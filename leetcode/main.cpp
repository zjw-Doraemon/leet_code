#include <iostream> 
#include <vector>
#include <iomanip>  // 引入iomanip库
#include <chrono>
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
    ~time_spend() {
        end = steady_clock::now();
        auto spend = end - start;
        auto spend_mill = duration_cast<microseconds>(spend);
        std::cout << "消耗时间  " << spend_mill.count() << " 微秒" << std::endl;

    }



};


// 二分查找 力扣 704 题
int search(std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;


    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            return mid;
        }

        if (target > nums[mid]) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }




    }

    return  -1;

}

// 移除元素 27 题
// 暴力方法 
int removeElement(std::vector<int>& nums, int val) {
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        count++;
        if (nums[i] == val) {
            for (int j = i; j < nums.size() - 1; j++) {
                nums[j] = nums[j + 1];

            }
            count--;
            i--; // 调整后 下标指向的值统一都向后移动了一位
            nums.pop_back();// 控制数组长度

        }


    }
    return count;

}
// 双指针法
int removeElement_1(std::vector<int>& nums, int val) {
    int j = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != val) {

            nums[j] = nums[i];
            j++;

        }
    }
    return j;


}


//有序数组的平方 977 题
// 双指针法
using namespace std;
vector<int> sortedSquares(vector<int>& nums) {
    int j = 0;
    int i = nums.size() - 1;

    std::vector<int> a(nums.size());
    int c = a.size() - 1;
    while (true) {
        if (i == j) {
            a[0] = nums[i] * nums[i];
            break;

        }
        if (nums[j] * nums[j] < nums[i] * nums[i]) {

            a[c] = nums[i] * nums[i];
            i--;
            c--;
            //print_vector(a);

        }
        else {

            a[c] = nums[j] * nums[j];
            j++;
            c--;
            //print_vector(a);

        }

    }
    return a;
}
// 长度最小的子数组 209
// 自己的方法
int minSubArrayLen_my(int target, vector<int>& nums) {
    int sum = 0;
    int less_long = nums.size() + 1;

    for (int i = 0; i < nums.size(); i++) {


        for (int j = i; j < nums.size(); j++) {
            sum = sum + nums[j];
            if (sum >= target) {
                int less_long_temp = j - i + 1;
                if (less_long_temp < less_long) {
                    less_long = less_long_temp;

                }
                break;

            }

        }
        sum = 0;
    }
    if (less_long == nums.size() + 1) {
        return 0;
    }
    return less_long;
}
// 滑动窗口
int minSubArrayLen(int target, vector<int>& nums) {
    int result = nums.size() + 1;
    int sum = 0;
    int start = 0;
    for (int j = 0; j < nums.size(); j++) {
        sum = nums[j] + sum;
        while (sum >= target) {
            int result_temp = j - start + 1;
            if (result > result_temp) {
                result = result_temp;

            }
            sum = sum - nums[start];
            start++;

        }

    }
    if (result == nums.size() + 1) {
        return 0;

    }
    return result;
}
//螺旋矩阵 59
vector<vector<int>> generateMatrix(int n) {
    int i = 1; // 填充数值
    int startx = 0, starty = 0;
    int mid = n / 2; //中间位置
    int offset = n; // 右边界

    vector<vector<int>>  result(n, vector<int>(n, 0));
    for (int a = 0; a < n / 2; a++) {
        // 第一行

        for (int j = starty; j < offset - 1; j++) {
            result[startx][j] = i;
            i++;
        }

        // 右边一列
        for (int j = startx; j < offset - 1; j++) {
            result[j][offset - 1] = i;
            i++;

        }

        // 下面一列 
        for (int j = offset - 1; j > starty; j--) {
            result[offset - 1][j] = i;
            i++;

        }

        // 左边一列 
        for (int j = offset - 1; j > startx; j--) {
            result[j][startx] = i;
            i++;
        }
        startx++;
        starty++;
        offset--;


    }
    if (n % 2 == 1) {
        result[mid][mid] = i;

    }
    return result;
}

// gpt 代码 
vector<vector<int>> generateMatrix_gpt(int n) {
    int i = 1; // 填充数值
    int left = 0, right = n - 1, top = 0, bottom = n - 1;

    vector<vector<int>> result(n, vector<int>(n, 0));

    while (left <= right && top <= bottom) {
        // 上边一行
        for (int j = left; j <= right; ++j) result[top][j] = i++;
        top++; // 向下收缩

        // 右边一列
        for (int j = top; j <= bottom; ++j) result[j][right] = i++;
        right--; // 向左收缩

        // 下边一行
        for (int j = right; j >= left; --j) result[bottom][j] = i++;
        bottom--; // 向上收缩

        // 左边一列
        for (int j = bottom; j >= top; --j) result[j][left] = i++;
        left++; // 向右收缩
    }

    return result;
}



void print_vector(std::vector<int> nums) {
    for (int i : nums) {
        std::cout << std::left << std::setw(3) << i << " ";  // 使用setw设置宽度
    }
    std::cout << std::endl;
}

// 二维数组遍历
void print_2_vector(std::vector<std::vector<int>> nums) {
    for (int i = 0; i < nums.size(); i++) {
        print_vector(nums[i]);
    }
}

// 58 卡码网 区间和
void km_58() {
    int count = 0;
    std::cin >> count;
    std::vector<int> array_temp(count, 0);
    //print_vector(array_temp);

    for (int i = 0; i < count; i++) {
        int temp = 0;
        std::cin >> temp;
        array_temp[i] = temp;
    }
    int left = 0, right = 0;
    while (std::cin >> left >> right) {

        int sum = 0;
        for (int i = left; i <= right; i++) {
            sum = sum + array_temp[i];
        }
        std::cout << sum << std::endl;
    }


}

// 移除链表元素 203
// 节点类
class ListNode {
public:
    int val;
    ListNode* next;

    ListNode(int e) :val(e), next(nullptr) {

    }
};
//循环添加节点
void create_list(ListNode* head) {
    int c = 0;
    while (std::cin >> c) {
        ListNode* cur = head;
        ListNode* temp = new ListNode(c);
        while (cur->next != nullptr) {
            cur = cur->next;

        }
        cur->next = temp;
        temp->next = nullptr;

    }
}
//遍历单链表
void print_ListNode(ListNode* head) {
    ListNode* temp = head;
    while (temp != nullptr) {
        std::cout << temp->val << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

ListNode* removeElements(ListNode* head, int val) {

    ListNode* virtual_head = new ListNode(0);
    virtual_head->next = head;
    ListNode* temp = head;
    ListNode* front = virtual_head;

    if (virtual_head->next == nullptr) {
        return head;
    }
    while (temp != nullptr) {

        if (temp->val == val) {
            front->next = temp->next;
            delete temp;
        }
        else {
            front = front->next;

        }

        temp = front->next;

    }
    ListNode* new_head = virtual_head->next;

    return new_head;

}
//设计链表 707
class node {
public:
    int val;
    node* next;
};
class MyLinkedList {
private:
    node* head;
    int length;
public:

    MyLinkedList() :head(new node()), length(0) {
        head->next = nullptr;


    }

    int get(int index) {
        if (index >= length || index < 0) {
            return -1;
        }

        node* temp = head;
        for (int i = 0; i < index + 1; i++) {
            temp = temp->next;

        }
        return temp->val;

    }

    void addAtHead(int val) {

        node* temp = new node();
        temp->val = val;
        temp->next = head->next;
        head->next = temp;
        length++;

    }

    void addAtTail(int val) {
        node* temp = head;
        node* cur = new node();
        cur->val = val;
        while (temp->next != nullptr) {
            temp = temp->next;

        }
        temp->next = cur;
        cur->next = nullptr;
        length++;
    }

    void addAtIndex(int index, int val) {
        if (index > length) {
            return;
        }
        if (index == length) {
            addAtTail(val);
            return;

        }
        node* cur = head;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        node* temp = new node();
        temp->val = val;
        temp->next = cur->next;
        cur->next = temp;
        length++;
    }

    void deleteAtIndex(int index) {
        if (index >= length || index < 0) {
            return;

        }
        node* cur = head;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        node* temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
        length--;
    }
    void print() {
        node* cur = head->next;
        while (cur != nullptr) {
            std::cout << cur->val << " ";
            cur = cur->next;
        }
        std::cout << std::endl;
    }
};

// 链表反转 206  借用203 定义的节点
ListNode* reverseList(ListNode* head) {
    if (head == nullptr) {
        return nullptr;

    }
    ListNode* left = head;
    ListNode* right = head->next;
    head->next = nullptr;
    while (right != nullptr) {
        ListNode* temp = right->next;
        right->next = left;
        left = right;
        right = temp;
    }

    return left;
}
// 俩俩交换链表中的节点 24
ListNode* swapPairs(ListNode* head) {
    if (head == nullptr) {
        return nullptr;

    }
    if (head->next == nullptr) {
        return head;
    }

    ListNode* left = head;
    ListNode* right = head->next;
    ListNode* new_List = head->next;
    while (right != nullptr) {

        ListNode* temp = right->next;
        if (temp == nullptr) {
            left->next = nullptr;
        }
        else {
            if (temp->next == nullptr) {
                left->next = temp;
            }
            else {
                left->next = temp->next;
            }

        }

        right->next = left;
        left = temp;
        if (temp != nullptr)
        {
            right = temp->next;
        }
        else {
            right = nullptr;
        }


    }
    return new_List;
}
// 递归
ListNode* swapPairs_1(ListNode* head) {

    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode* new_head = head->next;
    head->next = swapPairs_1(new_head->next);
    new_head->next = head;

    return new_head;
}
// 删除链表的倒数第n个节点 29
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (head == nullptr) {
        return head;
    }
    if (n <= 1 && head->next == nullptr) {
        return nullptr;
    }
    int fast = 0;
    int slow = 0;
    ListNode* virtual_head = new ListNode(0);
    virtual_head->next = head;
    ListNode* fast_ptr = virtual_head;
    ListNode* slow_ptr = virtual_head;
    while (fast_ptr->next != nullptr) {
        fast_ptr = fast_ptr->next;
        fast++;
        if (fast - slow > n) {
            slow_ptr = slow_ptr->next;


        }

    }
    ListNode* temp = slow_ptr->next;

    slow_ptr->next = slow_ptr->next->next;


    //std::cout << "Deleting node with value: " << (temp ? temp->val : -1) << std::endl;
    delete temp;

    return virtual_head->next;
}
// 面试题 链表 相交 02.07.
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    int length_a = 0, length_b = 0;
    int gap = 0;
    ListNode* ptr_a = headA, * ptr_b = headB;
    // 求a 的长度
    while (ptr_a != nullptr) {
        length_a++;
        ptr_a = ptr_a->next;


    }
    // 求b 的长度
    while (ptr_b != nullptr) {
        length_b++;
        ptr_b = ptr_b->next;

    }
    ptr_a = headA;
    ptr_b = headB;
    if (length_a >= length_b) {
        gap = length_a - length_b;
    }
    else
    {
        gap = length_b - length_a;
    }
    while (gap--) {
        if (length_a >= length_b) {
            ptr_b = ptr_b->next;
        }
        else {
            ptr_a = ptr_a->next;
        }
    }
    while (ptr_a != nullptr && ptr_b != nullptr) {
        if (ptr_a == ptr_b) {
            return ptr_a; // 找到交点
        }
        ptr_a = ptr_a->next;
        ptr_b = ptr_b->next;
    }
    return nullptr;

}
// 环形链表 ||  142
ListNode* detectCycle(ListNode* head) {

    if (head == nullptr || head->next == nullptr) {
        return nullptr;

    }
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* index_1 = head;
    while (true) {

        slow = slow->next;
        fast = fast->next->next;
        if (fast == nullptr || fast->next == nullptr) {
            return nullptr;
        }

        if (slow == fast) {
            break;
        }


    }
    ListNode* index_2 = fast;
    while (true) {

        if (index_1 == index_2) {
            return index_1;
        }
        //必须放下面  特殊情况是两个元素的循环链表不放下面会出错
        //输入：head = [1,2], pos = 0

        index_2 = index_2->next;
        index_1 = index_1->next;
    }


}



int main() {
    // 704
    /*{
        std::vector<int> test{ 1,3,5,7,9,11,13,15,17,19 };
        std::cout << search(test, 1);
    }*/
    // 27
    //// 暴力方法  
    //{
    //    time_spend time;
    //    std::vector<int> test_1{ 3,2,1,3 };
    //    print_vector(test_1);
    //    std::cout << removeElement(test_1, 3) << std::endl;
    //    print_vector(test_1);
    //    
    //}
    //// 双指针法
    //{
    //    
    //    time_spend time;
    //    std::vector<int> test_1{ 3,2,1,3 };
    //    print_vector(test_1);
    //    std::cout << removeElement_1(test_1, 3) << std::endl;
    //    print_vector(test_1);
    //}
    // 977
    /*{
        std::vector<int> sums{1};


        print_vector(sums);
        print_vector(sortedSquares(sums));

    }*/
    // 209
    /*{
        std::vector<int> test{ 2,3,1,2,4,3 };
        std::cout<<minSubArrayLen(7,test);

    }*/
    // 59
   /* {
        time_spend time;
        vector<vector<int>> test{ {1,2,3},{4,5,6},{7,8,9} };
        vector<vector<int>> test_1 = generateMatrix(9);
        print_2_vector(test_1);

    }*/
    // 58 km
    /*{
        time_spend spend;
        km_58();
    }*/
    // 203
    /*{
        ListNode head_(1);
        ListNode* head = &head_;
        create_list(head);
        print_ListNode(head);

        print_ListNode(removeElements(head, 3));

    }*/
    // 707
   /* {
        MyLinkedList List;
        int c = 0;
        while (std::cin >> c) {

            List.addAtTail(c);

        }
        List.print();
        List.addAtIndex(0,9);
        List.print();
        List.deleteAtIndex(0);
        List.print();


        std::cout << List.get(0) << std::endl;
    }*/
    // 链表反转 206
   /* {
        ListNode head_(1);
        ListNode* head = &head_;
        create_list(head);
        print_ListNode(head);
        ListNode* new_head = reverseList(head);

        print_ListNode(new_head);

    }*/
    //24
    {
        ListNode head_(1);
        ListNode* head = &head_;
        create_list(head);
        print_ListNode(head);
        time_spend T;
        print_ListNode(swapPairs(head));
    }
    // 29
    /*{
        ListNode head_(1);
        ListNode* head = &head_;
        create_list(head);
        print_ListNode(head);

        print_ListNode(removeNthFromEnd(head, 2));


    } */ // 有 bug  在  输入为 [1,2] 时 delete temp 会停住
    //02.07.
    /*{



    }*/


    //142
    {

    }
}