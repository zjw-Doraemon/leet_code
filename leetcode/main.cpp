#include <iostream> 
#include <vector>
#include <iomanip>  // ����iomanip��
#include <chrono>
#include <array>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>  // �����㷨�⣬��ʹ�� std::sort��
#include <stack>
#include <queue>
#include <string>
#include <map>
#include <algorithm>


// ����ִ��ʱ�� ��
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
        std::cout << "����ʱ��  " << spend_mill.count() << " ΢��" << std::endl;

    }



};


// ���ֲ��� ���� 704 ��
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

// �Ƴ�Ԫ�� 27 ��
// �������� 
int removeElement(std::vector<int>& nums, int val) {
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        count++;
        if (nums[i] == val) {
            for (int j = i; j < nums.size() - 1; j++) {
                nums[j] = nums[j + 1];

            }
            count--;
            i--; // ������ �±�ָ���ֵͳһ������ƶ���һλ
            nums.pop_back();// �������鳤��

        }


    }
    return count;

}
// ˫ָ�뷨
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


//���������ƽ�� 977 ��
// ˫ָ�뷨
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
// ������С�������� 209
// �Լ��ķ���
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
// ��������
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
//�������� 59
vector<vector<int>> generateMatrix(int n) {
    int i = 1; // �����ֵ
    int startx = 0, starty = 0;
    int mid = n / 2; //�м�λ��
    int offset = n; // �ұ߽�

    vector<vector<int>>  result(n, vector<int>(n, 0));
    for (int a = 0; a < n / 2; a++) {
        // ��һ��

        for (int j = starty; j < offset - 1; j++) {
            result[startx][j] = i;
            i++;
        }

        // �ұ�һ��
        for (int j = startx; j < offset - 1; j++) {
            result[j][offset - 1] = i;
            i++;

        }

        // ����һ�� 
        for (int j = offset - 1; j > starty; j--) {
            result[offset - 1][j] = i;
            i++;

        }

        // ���һ�� 
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

// gpt ���� 
vector<vector<int>> generateMatrix_gpt(int n) {
    int i = 1; // �����ֵ
    int left = 0, right = n - 1, top = 0, bottom = n - 1;

    vector<vector<int>> result(n, vector<int>(n, 0));

    while (left <= right && top <= bottom) {
        // �ϱ�һ��
        for (int j = left; j <= right; ++j) result[top][j] = i++;
        top++; // ��������

        // �ұ�һ��
        for (int j = top; j <= bottom; ++j) result[j][right] = i++;
        right--; // ��������

        // �±�һ��
        for (int j = right; j >= left; --j) result[bottom][j] = i++;
        bottom--; // ��������

        // ���һ��
        for (int j = bottom; j >= top; --j) result[j][left] = i++;
        left++; // ��������
    }

    return result;
}



void print_vector(std::vector<int> nums) {
    for (int i : nums) {
        std::cout << std::left << std::setw(3) << i << " ";  // ʹ��setw���ÿ��
    }
    std::cout << std::endl;
}

// ��ά�������
void print_2_vector(std::vector<std::vector<int>> nums) {
    for (int i = 0; i < nums.size(); i++) {
        print_vector(nums[i]);
    }
}

// 58 ������ �����
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

// �Ƴ�����Ԫ�� 203
// �ڵ���
class ListNode {
public:
    int val;
    ListNode* next;

    ListNode(int e) :val(e), next(nullptr) {

    }
};
//ѭ����ӽڵ�
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
//����������
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
//������� 707
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

// ����ת 206  ����203 ����Ľڵ�
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
// �������������еĽڵ� 24
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
// �ݹ�
ListNode* swapPairs_1(ListNode* head) {

    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode* new_head = head->next;
    head->next = swapPairs_1(new_head->next);
    new_head->next = head;

    return new_head;
}
// ɾ������ĵ�����n���ڵ� 29
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
// ������ ���� �ཻ 02.07.
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    int length_a = 0, length_b = 0;
    int gap = 0;
    ListNode* ptr_a = headA, * ptr_b = headB;
    // ��a �ĳ���
    while (ptr_a != nullptr) {
        length_a++;
        ptr_a = ptr_a->next;


    }
    // ��b �ĳ���
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
            return ptr_a; // �ҵ�����
        }
        ptr_a = ptr_a->next;
        ptr_b = ptr_b->next;
    }
    return nullptr;

}
// �������� ||  142
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
        //���������  �������������Ԫ�ص�ѭ����������������
        //���룺head = [1,2], pos = 0

        index_2 = index_2->next;
        index_1 = index_1->next;
    }


}
// ��Ч����ĸ��λ��
bool isAnagram(string s, string t) {
    if ( s.size()!=t.size()) {
        return false;
    }
    int tem[26]{0};
    std::cout << tem[3] << std::endl;
    for (char c : s) {
        tem[c - 'a']++;

    }
    for (char c : t) {
        tem[c - 'a']--;
    }
    for (int i = 0; i < 24; i++) {
        if (tem[i]!=0) {
            return false;
        }

    }
    return true;
}
// 349 ��������Ľ���

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    std::vector<int> result;
    std::unordered_set<int> set;
    for (int c : nums1 ) {
        set.insert(c);

    }
    for (int c : nums2) {
        if (set.find(c) != set.end() && find(result.begin(),result.end(),c) == result.end())
        {
            result.push_back(c);
        }
        

    }
    return result;
}
// ������ 202
bool isHappy(int n) {
    if (n <= 0) {
        return false;
    }
    std::unordered_set<int> tem;
    int count = 0;
    
    
    while (n != 1) {
        count++;
        int multiply_10 = 10;
        int copy_n = 0;
        
        while (n) {
            
            copy_n = copy_n + (n % multiply_10) * (n % multiply_10);
            n = n / 10;
            
        }
        
        n = copy_n;
        if (tem.find(n) != tem.end()) {
            std::cout << count << std::endl;
            return false;
            
        }
        tem.insert(copy_n);
        
    }
    std::cout << count << std::endl;
    return true;

}
// ����֮�� 1

vector<int> twoSum(vector<int>& nums, int target) {
    std::unordered_map<int, int> map;
    std::vector<int> result;
    
    for (int i = 0; i < nums.size(); i++) {


        if (map.find(target - nums[i]) != map.end() && map.find(target - nums[i])->second != i ){
            
            result.push_back(i);
            result.push_back(map[target - nums[i]]);
            return result;
        }
        else {
            map[nums[i]] = i;
        }

    }
    
}
// ������� �� 454 
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    std::unordered_map<int,int> sums_1_2;
    int result = 0;
    for (int i = 0; i < nums1.size(); i++) {
        for (int j = 0; j < nums1.size(); j++) {
            
                sums_1_2[nums1[i] + nums2[j]]++;
            
            
        }
        
    }
    // ���� map
    for (auto &c : sums_1_2) {
        std::cout << "[" << c.first <<"," << "  " << c.second << "]" << "   ";
    }
    std::cout << std::endl;
    for (int i = 0; i < nums1.size(); i++) {
        for (int j = 0; j < nums1.size(); j++) {
            if (sums_1_2.find(0 - (nums3[i]+nums4[j])) != sums_1_2.end() ){
                result = sums_1_2[0 - (nums3[i] + nums4[j])] + result;
            }

        }

    }
    return result;
}
// ����� 383
bool canConstruct(string ransomNote, string magazine) {
    int count[26]{0};
    for (char i : magazine) {
        count[i-'a']++;

    }
    for (char i : ransomNote) {
        if (count[i-'a'] > 0) {
            count[i - 'a']--;
        }
        else {
            return false;
        }
    }
    return true;
}
// ����֮�� 15
std::vector<std::vector<int>> threeSum(vector<int>& nums) {
    int i = 0;
    
    
    std::sort(nums.begin(),nums.end());
    std::vector<std::vector<int>> result{0};
    for (int q : nums) {
        std::cout << q << " ";

    }
    std::cout << std::endl;
    if (nums[0] > 0) {
        return { };
    }
    while(i < nums.size() && nums[i] <= 0) {
        // i ȥ�ز���
        if (i > 0 && nums[i] == nums[i - 1]) {
            i++;
            continue;
        }
        int left = i + 1;
        int right = nums.size() - 1;
        while (left < right) {
            if (left-1 != i && nums[left] == nums[left - 1]) {
                left++;
                continue;
            }
            if (right != nums.size() - 1 && nums[right] == nums[right + 1]) {
                
                right--;
                continue;
            }
            if (nums[i] + nums[left] + nums[right] == 0) {
                result.push_back({ nums[i] ,nums[left],nums[right] });
            }
            if (nums[i] + nums[left] + nums[right] > 0 ) {
                right--;
            }
            else {
                left++;
            }
        }
        i++;
    }
    return result;
}
// ����֮��  18
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    std::sort(nums.begin(),nums.end());
    for (int c : nums) {
        std::cout << c << " ";

    }
    std::cout << std::endl;
    vector<vector<int>> result;
    
    for (int i = 0; i <= static_cast<int>(nums.size()) - 4; i++) {
        
        
        if (i > 0 && nums[i] == nums[i-1]) {
            continue;
        }
        for (int j = i + 1; j <= nums.size() - 3; j++) {
            if (j-1 != i && nums[j] == nums[j-1]) {
                
                continue;
            }
            int left = j + 1;
            int right = nums.size() - 1;
            while (left < right) {
                if (left - 1 != j && nums[left] == nums[left-1]) {
                    left++;
                    continue;
                }
                if (right != nums.size() - 1 && nums[right] == nums[right + 1]) {
                    right--;
                    continue;
                }
             
                if (static_cast<int64_t>(nums[i]) + static_cast<int64_t>(nums[j]) +
                    static_cast<int64_t>(nums[left]) + static_cast<int64_t>(nums[right]) == static_cast<int64_t>(target)) {
                    result.push_back({ nums[i], nums[j], nums[left], nums[right] });
                    left++;
                    right--;
                    continue;
                }

                if (static_cast<int64_t>(nums[i]) + static_cast<int64_t>(nums[j]) +
                    static_cast<int64_t>(nums[left]) + static_cast<int64_t>(nums[right]) > static_cast<int64_t>(target)) {
                    right--;
                    continue;
                }

                if (static_cast<int64_t>(nums[i]) + static_cast<int64_t>(nums[j]) +
                    static_cast<int64_t>(nums[left]) + static_cast<int64_t>(nums[right]) < static_cast<int64_t>(target)) {
                    left++;
                    continue;
                }

            }
        }
    }
    return result;
}
// ��ת�ַ��� 344
void reverseString(vector<char>& s) {
    int left = 0, right = s.size() - 1;
    for (; left < right; left++, right--) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
    }
    
    
}
// ��ת�ַ��� 2
string reverseStr(string s, int k) {
    if (s.size() == 1) {
        return s;
    }
    int c = 0;
    int i = 0;
    
    for (; i < s.size(); i++) {
        c++;
        if (c == 2*k) {
            int left = i - (c -1), right = left + k ;
            std::reverse(s.begin() + left , s.begin()+right);
            c = 0;
        }
    }
    
    if (c < k) {
        int left = (i-1) - (c - 1);
        std::reverse(s.begin() + left, s.end());
    }
    if (c >= k ) {
        int left = (i -1) - (c - 1), right = left + k;
        std::reverse(s.begin() + left, s.begin() + right);
    }
    return s;
}
// �򵥵���� 
string reverseStr_(string s, int k) {
    for (int i = 0; i < s.size(); i += (2 * k)) {
        // 1. ÿ�� 2k ���ַ���ǰ k ���ַ����з�ת
        // 2. ʣ���ַ�С�� 2k �����ڻ���� k ������תǰ k ���ַ�
        if (i + k <= s.size()) {
            reverse(s.begin() + i, s.begin() + i + k);
        }
        else {
            // 3. ʣ���ַ����� k ������ʣ���ַ�ȫ����ת��
            reverse(s.begin() + i, s.end());
        }
    }
    return s;
}
// ������ 54
void replace(std::string &s) {
    std::unordered_set <char> a;
    for (int i = 0; i < 26; i ++) {
        a.insert(static_cast<char>('a' + i));
    }
    
    for (int i = 0; i < s.size(); i++) {
        if (a.find(s[i]) == a.end()) {
            s.erase(i,1);
            s.insert(i, "number");
            

        }
        
    }
}
void replace_1(string &s) {
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i]>='0' && s[i]<='9') {
            count++;
        }
    }
    int num = s.size();
    s.resize(s.size() + 5*count);
    int left = num - 1, right = s.size() - 1;
    string temp = string("rebmun");
    while (left >= 0) {
        if (s[left] >= '0' && s[left] <= '9') {
            for (char c : temp) {
                s[right] = c;
                right--;
                
                //std::cout << s << std::endl;
            }
            //std::cout << s << std::endl;
            left--;
        }
        else {
            s[right] = s[left];
            //std::cout << s << std::endl;
            left--;
            right--;
        }
    }

}
// ��ת�ַ����ĵ��� 151
// ������
string reverseWords_bao_li(string s) {
    string result = "";
    std::vector<string> split;
    string tmp;
    for (int i = 0; i < s.size(); i++) {

        if (s[i] == ' ' && i == 0 || s[i] == ' ' && s[i - 1] == ' ') {
            continue;
        }
        if (s[i] == ' ' && i != 0) {
            split.push_back(tmp);
            tmp = "";
            continue;
        }
        tmp.push_back(s[i]);
    }
    if (s.back() != ' '){
        split.push_back(tmp);
    }
    for (int i = split.size() - 1; i >= 0; i--) {
        result.append(split[i]);
        if (i != 0) {
            result.push_back(' ');
        }
    }
    return result;
}
// ˫ָ�뷨
string reverseWords(string s) {
    int slow = 0, fast = 0;
   
    // ȥ���ո�
    
    for (; fast < s.size()  ;  fast ++) {
        
        
        if (slow != 0 && fast != 0 && (s[fast] != ' ' && s[fast-1] == ' ')) {

            s[slow] = ' ';
            slow++;
            
        }
        if (s[fast] != ' ' ) {
            s[slow] = s[fast];
            slow++;
            
        }
        
        
    }
   // ԭ����
   //s.resize(slow);
    // ���ٸ��Ӷ�  ������ resize  ֻ��� �����ж�  
    int delete_ = 0;
    delete_ = s.size() - slow;
    for (int i = 0; i < delete_; i++) {
        s.pop_back();
    }
    // ��ת�����ַ���
    for (int left = 0, right = s.size() - 1; left < right; left++,right--) {
        char tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;

    }
    // ��ת ÿ��С�ַ���
    for (int left = 0, right = 0; right < s.size();right++) {
        if (right == s.size()-1 || s[right+1 ] == ' ') {
            for (int left_tmp = left, right_tmp = right; left_tmp < right_tmp; left_tmp++,right_tmp--) {
                char tmp = s[left_tmp];
                s[left_tmp] = s[right_tmp];
                s[right_tmp] = tmp;
            }
            left = right + 2;
        }
    }

    return s;
}
// ������ ����ת�ַ���
string right_rotation(string c, int n) {
    // �ֲ���ת 
    for (int left = 0, right = c.size() - 1 - n; left < right; left++,right--) {
        char tmp = c[left];
        c[left] = c[right];
        c[right] = tmp;
    }
    for (int left = c.size() - n, right = c.size()  - 1; left < right; left++, right--) {
        char tmp = c[left];
        c[left] = c[right];
        c[right] = tmp;
    }
    // ���巴ת
    for (int left = 0, right = c.size() - 1; left < right; left++, right--) {
        char tmp = c[left];
        c[left] = c[right];
        c[right] = tmp;
    }
    return c;
}
// �� ջģ����� 
class MyQueue {
public:
    std::stack<int> main_stack;
    std::stack<int> vice_stack;
    
    MyQueue() {
        
        
    }

    void push(int x) {
        main_stack.push(x);
        
    }

    int pop() {
        
        int result = 0 ;
        if (vice_stack.empty()) {
            while (!main_stack.empty()) {
                vice_stack.push(main_stack.top());
                main_stack.pop();
            }
            result = vice_stack.top();
            vice_stack.pop();

        }
        else {
            result = vice_stack.top();
            vice_stack.pop();
        }

        return result;
       
    }

    int peek() {
        int result = pop();
        vice_stack.push(result);
        return result;
    }

    bool empty() {
        return  vice_stack.empty() && main_stack.empty();
    }
};

// �ö���ģ��ջ
class MyStack {
public:
    std::queue<int> main;
    MyStack() {

    }

    void push(int x) {
        main.push(x);
    }

    int pop() {
        int size = main.size();
        for (int i = 0; i < size - 1; i++) {
            int tmp = main.front();
            main.pop();
            main.push(tmp);
        }
        int tmp = main.front();
        main.pop();
        return tmp;
        
    }

    int top() {
        int tmp = pop();
        main.push(tmp);
        return tmp;

    }

    bool empty() {
        return main.empty();
    }
};
// ��Ч������
bool isValid(string s) {
    if (s.empty()) {
        return false;
    }
    std::stack<char> tmp;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] =='(' || s[i] == '[' || s[i] == '{') {
            tmp.push(s[i]);
        }
        if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
            if (tmp.empty()) {
                return false;
            }
            if (tmp.top() == '{' && s[i] == '}'  || tmp.top() == '(' && s[i] == ')' || tmp.top() == '[' && s[i] == ']') {
                tmp.pop();
            }
            else {
                return false;
            }
                

        }
    }
    if (!tmp.empty()) {
        return false;
    }
    return true;
}
// ɾ���ַ����������ظ��������� 1047
string removeDuplicates(string s) {
    std::stack<int> result;
    std::string result_string;
    
    for (int i = 0; i < s.size(); i++) {
        
        if (!result.empty() && result.top() == s[i]) {
            result.pop();
        }
        else {
            result.push(s[i]);
        }
        

    }
    int tmp = result.size();
    for (int i = 0; i < tmp; i++) {
        result_string.insert(0,1,result.top());
        result.pop();
    }
    return result_string;
}
// �沨�����ʽ  ��׺���ʽ
int evalRPN(vector<string>& tokens) {
    std::stack<long long> result;
    
    for (string c : tokens) {
        if (c == "+" || c == "-" || c == "*" || c=="/") {
            long long temp_1 = result.top();
            result.pop();
            long long temp_2 = result.top();
            result.pop();
            if (c == "+") result.push(temp_2 + temp_1);
            if (c == "-") result.push(temp_2 - temp_1);
            if (c == "*") result.push(temp_2 * temp_1);
            if (c == "/") result.push(temp_2 / temp_1);
            
        }
        else {
            result.push(std::stoll(c));
        }
    }
    return result.top();
}
//  �������� 
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    std::deque<int> windows;
    vector<int> result;
    int j = 0;
    for (; j < k; j++) {
        while (!windows.empty() && nums[j] > windows.back()) { // �ɴ�
            windows.pop_back();
        }
        windows.push_back(nums[j]);

    }
    result.push_back(windows.front());
    for (int i = 0; j < nums.size(); j++, i++) {
        while (!windows.empty() && nums[j] > windows.back()) { // �ɴ�
            windows.pop_back();
        }
        windows.push_back(nums[j]);
        if (nums[i] == windows.front()) {
            windows.pop_front();
        }
        result.push_back(windows.front());

    }
    return result;
}

// ǰk����ƵԪ��
using namespace std;
class Solution_ {
    struct compare {



        bool operator()(std::pair<int, int> a, std::pair<int, int> b) {
            return a.second < b.second;
        }
    };
public:


    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> mp;
        vector<int> result;
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]]++;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, compare >pq;
        for (auto i : mp) {
            pq.push(i);
        }
        for (int i = 0; i < k; i++) {
            result.push_back(pq.top().first);
            pq.pop();
        }
        return result;
    }
};
// ������ 
// ����
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value):val(value) {

    }
};
// �ݹ�ǰ�����  ������� ������� �����
class Solution {

public:
    std::vector<int> result;
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        result.push_back(root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
        return result;
    
        
    }
};
//���� ǰ�����  ������� �������
vector<int> preorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::stack<TreeNode*> stack_tree;
    std::vector<int> result;
    stack_tree.push(root);
    while (!stack_tree.empty()) {
        TreeNode* tmp = stack_tree.top();
        result.push_back(tmp->val);
        stack_tree.pop();
        if (tmp->right!=nullptr  ) {
            stack_tree.push(tmp->right);
            
        }
        if (tmp->left != nullptr) {
            stack_tree.push(tmp->left);
        }
        



    }
    return result;
}

vector<int> inorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::stack<TreeNode*> stack_tree;
    std::vector<int> result;
    TreeNode* tmp = root;
    while ( tmp!=nullptr || !stack_tree.empty()) {
        if (tmp!=nullptr) {
            stack_tree.push(tmp);
            tmp = tmp->left;
        }
        else {
            tmp = stack_tree.top();
            stack_tree.pop();
            result.push_back(tmp->val);
            tmp = tmp->right;
        }
    }
    return result;
   
}
vector<int>  postorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::stack<TreeNode*> stack_tree;
    std::vector<int> result;
    stack_tree.push(root);
    while (!stack_tree.empty()) {
        TreeNode* tmp = stack_tree.top();
        result.push_back(tmp->val);
        stack_tree.pop();
       
        if (tmp->left != nullptr) {
            stack_tree.push(tmp->left);
        } 
        if (tmp->right != nullptr) {
            stack_tree.push(tmp->right);

        }
        std::reverse(result.begin(),result.end());




    }
    return result;
}
// ͳһ������  ǰ����� ������� �������


void printStack(std::stack<TreeNode*>& stack_TreeNode) {
    std::stack<TreeNode*> tempStack = stack_TreeNode; // ����ջ�Ա����
    std::cout << "Stack content: ";
    while (!tempStack.empty()) {
        TreeNode* node = tempStack.top();
        if (node) {
            std::cout << node->val << " ";
        }
        else {
            std::cout << "nullptr ";
        }
        tempStack.pop();
    }
    std::cout << std::endl;
}

std::vector<int> inorderTraversal_(TreeNode* root) {
    if (root == nullptr) return {};
    std::stack<TreeNode*> stack_TreeNode;
    std::vector<int> result;
    stack_TreeNode.push(root);

    while (!stack_TreeNode.empty()) {
        //printStack(stack_TreeNode); // ���ջ״̬
        TreeNode* tmp = stack_TreeNode.top();

        if (tmp != nullptr) {
            stack_TreeNode.pop();
            if (tmp->right != nullptr) {
                stack_TreeNode.push(tmp->right);
            }

            stack_TreeNode.push(tmp);
            stack_TreeNode.push(nullptr);

            if (tmp->left != nullptr) {
                stack_TreeNode.push(tmp->left);
            }

        }
       
        else{
            //printStack(stack_TreeNode); // ���ջ״̬
            stack_TreeNode.pop();
            //printStack(stack_TreeNode); // ���ջ״̬
            result.push_back(stack_TreeNode.top()->val);
            stack_TreeNode.pop();
        }
    }

    return result;
}
std::vector<int> preorderTraversal_(TreeNode* root) {
    if (root == nullptr) return {};
    std::stack<TreeNode*> stack_TreeNode;
    std::vector<int> result;
    stack_TreeNode.push(root);

    while (!stack_TreeNode.empty()) {
        //printStack(stack_TreeNode); // ���ջ״̬
        TreeNode* tmp = stack_TreeNode.top();

        if (tmp != nullptr) {
            stack_TreeNode.pop();
            
            if (tmp->right != nullptr) {
                stack_TreeNode.push(tmp->right);
            }

            

            if (tmp->left != nullptr) {
                stack_TreeNode.push(tmp->left);
            }
            stack_TreeNode.push(tmp);
            stack_TreeNode.push(nullptr);

        }

        else {
            //printStack(stack_TreeNode); // ���ջ״̬
            stack_TreeNode.pop();
            //printStack(stack_TreeNode); // ���ջ״̬
            result.push_back(stack_TreeNode.top()->val);
            stack_TreeNode.pop();
        }
    }

    return result;
}
std::vector<int>  postorderTraversal_(TreeNode* root) {
    if (root == nullptr) return {};
    std::stack<TreeNode*> stack_TreeNode;
    std::vector<int> result;
    stack_TreeNode.push(root);

    while (!stack_TreeNode.empty()) {
        //printStack(stack_TreeNode); // ���ջ״̬
        TreeNode* tmp = stack_TreeNode.top();

        if (tmp != nullptr) {
            stack_TreeNode.pop();
            stack_TreeNode.push(tmp);
            stack_TreeNode.push(nullptr);
            if (tmp->right != nullptr) {
                stack_TreeNode.push(tmp->right);
            }



            if (tmp->left != nullptr) {
                stack_TreeNode.push(tmp->left);
            }
            

        }

        else {
            //printStack(stack_TreeNode); // ���ջ״̬
            stack_TreeNode.pop();
            //printStack(stack_TreeNode); // ���ջ״̬
            result.push_back(stack_TreeNode.top()->val);
            stack_TreeNode.pop();
        }
    }

    return result;
}
// �������
void printQueue(const std::queue<TreeNode*>& q) {
    std::queue<TreeNode*> temp = q; // ���ƶ����Խ��й۲�
    std::cout << "��ǰ����״̬��";
    while (!temp.empty()) {
        std::cout << temp.front()->val << " "; // ����TreeNode��val��Ա
        temp.pop();
    }
    std::cout << std::endl;
}
vector<vector<int>> levelOrder(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::queue<TreeNode*> level;
    vector<vector<int>> result;   
    level.push(root);
    while (!level.empty()) {
        vector<int> tmp;
        //printQueue(level);
        int size = level.size();
       
        for (int i = 0; i < size; i++) {
            tmp.push_back(level.front()->val);
            if (level.front()->left != nullptr) {
                level.push(level.front()->left);
            }
            if (level.front()->right != nullptr) {
                level.push(level.front()->right);             
            }
            level.pop();           
        }       
        result.push_back(tmp);       
    }
    return result;
}
// �Ե����� ������� 107
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::queue<TreeNode*> level;
    vector<vector<int>> result;
    level.push(root);
    while (!level.empty()) {
        vector<int> tmp;
        //printQueue(level);
        int size = level.size();

        for (int i = 0; i < size; i++) {
            tmp.push_back(level.front()->val);
            if (level.front()->left != nullptr) {
                level.push(level.front()->left);
            }
            if (level.front()->right != nullptr) {
                level.push(level.front()->right);
            }
            level.pop();
        }
        result.push_back(tmp);
    }
    std::reverse(result.begin(),result.end());
    return result;
}
// �Ҳ���ͼ
vector<int> rightSideView(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::queue<TreeNode*> level;
    vector<vector<int>> result;
    vector<int> result_true;
    level.push(root);
    while (!level.empty()) {
        vector<int> tmp;
        //printQueue(level);
        int size = level.size();

        for (int i = 0; i < size; i++) {
            tmp.push_back(level.front()->val);
            if (level.front()->left != nullptr) {
                level.push(level.front()->left);
            }
            if (level.front()->right != nullptr) {
                level.push(level.front()->right);
            }
            level.pop();
        }
        result.push_back(tmp);
    }
    for (auto c : result) {
        result_true.push_back(*(c.end()-1));
    }
    return result_true;
}
// ÿһ�� ƽ��ֵ
vector<double> averageOfLevels(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::queue<TreeNode*> level;
    vector<vector<double>> result;
    vector<double> result_true;
    level.push(root);
    while (!level.empty()) {
        vector<double> tmp;
        //printQueue(level);
        int size = level.size();

        for (int i = 0; i < size; i++) {
            tmp.push_back(level.front()->val);
            if (level.front()->left != nullptr) {
                level.push(level.front()->left);
            }
            if (level.front()->right != nullptr) {
                level.push(level.front()->right);
            }
            level.pop();
        }
        result.push_back(tmp);
    }
    for (auto c : result) {
        double sum = 0;
        for (int i : c) {
            sum = sum + i;
        }
        result_true.push_back(static_cast<double>(sum)/ static_cast<double>(c.size()));
    }
    return result_true;
}
// n�����Ĳ������ 
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
vector<vector<int>> levelOrder(Node* root) {
    if (root == nullptr) {
        return {};
    }
    std::queue<Node*> level;
    vector<vector<int>> result;
    level.push(root);
    while (!level.empty()) {
        
        vector<int> tmp;
        //printQueue(level);
        int size = level.size();

        for (int i = 0; i < size; i++) {
            tmp.push_back(level.front()->val);
            if (!level.front()->children.empty()) {
                for (auto c :level.front()->children) {
                    level.push(c);
                }
            }
            
            level.pop();
        }
        result.push_back(tmp);
    }
    return result;
}
// ������ ÿһ�����ֵ
vector<int> largestValues(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::queue<TreeNode*> level;
    vector<vector<int>> result;
    vector<int> result_true;
    level.push(root);
    while (!level.empty()) {
        vector<int> tmp;
        //printQueue(level);
        int size = level.size();

        for (int i = 0; i < size; i++) {
            tmp.push_back(level.front()->val);
            if (level.front()->left != nullptr) {
                level.push(level.front()->left);
            }
            if (level.front()->right != nullptr) {
                level.push(level.front()->right);
            }
            level.pop();
        }
        result.push_back(tmp);
    }
    for (auto c : result) {
        
        int max = INT_MIN;
        for (int i : c) {
            if (i > max) {
                max = i;
            }
        }
        result_true.push_back(max);
        
    }
    return result_true;
}
//116. ���ÿ���ڵ����һ���Ҳ�ڵ�ָ��
namespace problem_116 {
    struct Node {
        int val;
        Node* left;
        Node* right;
        Node* next;
    };
    Node* connect(Node* root) {
        if (root == nullptr) {
            return {};
        }
        std::queue<Node*> level;
        vector<vector<Node*>> result;
        vector<int> result_true;
        level.push(root);
        while (!level.empty()) {
            vector<Node*> tmp;
            //printQueue(level);
            int size = level.size();

            for (int i = 0; i < size; i++) {
                tmp.push_back(level.front());
                if (level.front()->left != nullptr) {
                    level.push(level.front()->left);
                }
                if (level.front()->right != nullptr) {
                    level.push(level.front()->right);
                }
                level.pop();
            }
            result.push_back(tmp);
        }
        for (auto c : result) {
            Node* tmp = c[0];
            for (int i = 0; i < c.size() - 1; i++) {
                c[i]->next = c[i+1];

            }
        }
        return root;
    }
   
    
}
//����  104. ��������������
int maxDepth(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::queue<TreeNode*> level;
    vector<vector<int>> result;
    vector<int> result_true;
    level.push(root);
    while (!level.empty()) {
        vector<int> tmp;
        //printQueue(level);
        int size = level.size();

        for (int i = 0; i < size; i++) {
            tmp.push_back(level.front()->val);
            if (level.front()->left != nullptr) {
                level.push(level.front()->left);
            }
            if (level.front()->right != nullptr) {
                level.push(level.front()->right);
            }
            level.pop();
        }
        result.push_back(tmp);
    }
    return result.size();
}
// ��С���
int minDepth(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    std::queue<TreeNode*> level;
    vector<vector<TreeNode*>> result;
    int mix = 0;
    
    level.push(root);
    while (!level.empty()) {
        vector<TreeNode*> tmp;
        //printQueue(level);
        int size = level.size();

        for (int i = 0; i < size; i++) {
            tmp.push_back(level.front());
            if (level.front()->left != nullptr) {
                level.push(level.front()->left);
            }
            if (level.front()->right != nullptr) {
                level.push(level.front()->right);
            }
            level.pop();
        }
        result.push_back(tmp);
    }
    for  (auto c : result) {
        mix++;
        for (TreeNode* a : c) {
            if (a->left == NULL && a->right == NULL) {
                return mix;
            }
            
        }
        
    }
    

}


int main() {
    // 704
    /*{
        std::vector<int> test{ 1,3,5,7,9,11,13,15,17,19 };
        std::cout << search(test, 1);
    }*/
    // 27
    //// ��������  
    //{
    //    time_spend time;
    //    std::vector<int> test_1{ 3,2,1,3 };
    //    print_vector(test_1);
    //    std::cout << removeElement(test_1, 3) << std::endl;
    //    print_vector(test_1);
    //    
    //}
    //// ˫ָ�뷨
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
    // ����ת 206
   /* {
        ListNode head_(1);
        ListNode* head = &head_;
        create_list(head);
        print_ListNode(head);
        ListNode* new_head = reverseList(head);

        print_ListNode(new_head);

    }*/
    //24
    /*{
        ListNode head_(1);
        ListNode* head = &head_;
        create_list(head);
        print_ListNode(head);
        time_spend T;
        print_ListNode(swapPairs(head));
    }*/
    // 29
    /*{
        ListNode head_(1);
        ListNode* head = &head_;
        create_list(head);
        print_ListNode(head);

        print_ListNode(removeNthFromEnd(head, 2));


    } */ // �� bug  ��  ����Ϊ [1,2] ʱ delete temp ��ͣס
    //02.07.
    /*{



    }*/


    //242
    /*{
        string a = "alw";
        string b = "ert";
        std::cout << isAnagram(a, b) << std::endl;
    }*/
    // 349
   /* {
        std::vector<int> test_1{1,2,3,4,5,6};
        std::vector<int> test_2{ 1,2,6 ,9};
        intersection(test_1,test_2);

        for (int c: intersection(test_1, test_2)) {
            std::cout << c << "  ";

        }
        std::cout << std::endl;
    }*/
    // 202
    /*{
        std::cout << isHappy(44444444456) << std::endl;

    }*/
    // 1

    /*{
        std::vector<int> tmp{ 3,2,4 };
        std::vector<int> result;
        result = twoSum(tmp,6);
        for (int i = 0; i < result.size(); i++) {
            std::cout << result[i] << " ";
        }
        std::cout << std::endl;
    }*/
    // 454
    //{
    //    // ʾ������
    //    std::vector<int> nums1 = { 1, 2 };
    //    std::vector<int> nums2 = { -2, -1 };
    //    std::vector<int> nums3 = { -1, 2 };
    //    std::vector<int> nums4 = { 0, 2 };

    //    // ���� fourSumCount ��������ӡ���
    //    std::cout << "Result: " << fourSumCount(nums1, nums2, nums3, nums4) << std::endl;
    //}

    // 383
    /*{
        string test = "ab";
        string test_1 = "aba";
        std::cout<<canConstruct(test,test_1)<<std::endl;


    }*/
    // 15
    /*{
        vector<int>test{ -4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6 };

        vector<vector<int>> test_1{ {1,2,3,4,5},{1,2,3,4,2} };
        for (auto c :threeSum(test)) {
            for (int a : c) {
                std::cout  << a << " ";
            }
            std::cout << std::endl;
        }
    }*/


    // 18
    /*{
        vector<int>test{ 1000000000,1000000000,1000000000,1000000000 };
        for (auto c : fourSum(test,0)) {
            for (int a : c) {
                std::cout << a << " ";
            }
            std::cout << std::endl;
        }
    }*/
    // 344
   /* {
        vector<char> test{'a','d','e','w'};
        reverseString(test);
        for (char c : test) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }*/
    // 541 
   /* {
        string test = "abcdefg";

        for (char c : reverseStr(test, 3)) {
            std::cout << c << " ";
        }
        std::cout << std::endl;

    }*/
    // ������ 54 
    /*{
        string test = "a1b2c3";
        replace_1(test);
        std::cout << test;
    }*/
    //151 
    //{
    //    string test = " hello world";
    //    std::cout<<reverseWords(test);
    //}

    // �����ַ���
    /*{
        string test = "abcdefg";
        std::cout<<right_rotation(test,2);
    }*/
    // ��ջʵ�ֶ��� 232 
    //{
    //    // ���� MyQueue ����
    //    MyQueue test;

    //    // ִ�в��Բ���
    //    test.push(1);        // �� 1 ѹ�����
    //    test.push(2);        // �� 2 ѹ�����
    //    std::cout << "Peek: " << test.peek() << std::endl;  // ��� 1����ͷԪ��

    //    test.push(3);        // �� 3 ѹ�����
    //    std::cout << "Pop: " << test.pop() << std::endl;    // ��� 1����ͷԪ�س���

    //    std::cout << "Peek: " << test.peek() << std::endl;  // ��� 2����ͷԪ��

    //    test.push(4);        // �� 4 ѹ�����
    //    std::cout << "Pop: " << test.pop() << std::endl;    // ��� 2����ͷԪ�س���
    //    std::cout << "Pop: " << test.pop() << std::endl;    // ��� 3����ͷԪ�س���
    //    std::cout << "Pop: " << test.pop() << std::endl;    // ��� 4����ͷԪ�س���

    //    // ���Զ����Ƿ�Ϊ��
    //    std::cout << "Is queue empty? " << (test.empty() ? "Yes" : "No") << std::endl;  // ��� Yes������Ϊ��

    //    return 0;
    //}
    // ��Ч������ 20
   /* {
        std::string test = "(])";
        std::cout << isValid(test);
    }*/
    //1047 ɾ�����������ظ����ַ���
   /* {
        string test = "tabbc";
        std::cout<<removeDuplicates(test);
    }*/
    // 150 �沨�����ʽ
    /*{
        vector<string> test = { "4","13","5","/","+" };
        std::cout<<evalRPN(test);
    }*/
    // �������ı���
    /*{


        TreeNode* root = new TreeNode(1);
        root->right = new TreeNode(2);
        root->right->right = new TreeNode(3);
        root->right->right->right = new TreeNode(4);
        root->right->right->right->right = new TreeNode(5);
        root->right->right->right->right->right = new TreeNode(6);


        Solution solution;

        for (int c : preorderTraversal_(root)) {
            std::cout << c << " ";
        }

    }*/
    // �������
    /*{
        TreeNode* root = new TreeNode(3);
        root->left = new TreeNode(9);
        root->right = new TreeNode(20);
        root->right->left = new TreeNode(15);
        root->right->right = new TreeNode(7);


        for (auto c : levelOrder(root)) {
            for (int a : c) {
                std::cout << a << " ";
            }
            std::cout << endl;
        }
    }*/
    // ��С��� 
    // ����һ��������
    {
        TreeNode* root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->left = new TreeNode(4);

        // ���� minDepth ����
        int depth = minDepth(root);
        std::cout << "��С���: " << depth << std::endl; // Ӧ����� 2 (`1->3`)

        // �����ڴ�
        delete root->left->left;
        delete root->left;
        delete root->right;
        delete root;
    }



}