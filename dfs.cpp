#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
#include <iomanip>

using namespace std;

struct TreeNode {
    int value;
    vector<TreeNode*> children;
};

void dfs(TreeNode* node, int depth) {
    // Get the current time
    auto now = chrono::high_resolution_clock::now();
    auto now_s = chrono::time_point_cast<chrono::duration<double>>(now);
    double elapsed = now_s.time_since_epoch().count();

    // Print the node depth and timestamp
    #pragma omp critical
    {
        cout << fixed << setprecision(6);
        cout << "Node:" << node -> value <<  " at depth: " << depth << ", Time: " << elapsed << " seconds" << endl;
    }

    // Recursive case: internal node
    if (!node->children.empty()){
        for (int i = 0; i < node->children.size(); i++){
            #pragma omp task firstprivate(node, depth)
            {
                dfs(node->children[i], depth + 1);
            }
        }
    }
}

int main(){

    // Constructing Tree

    TreeNode* root = new TreeNode{1};
    TreeNode* child1 = new TreeNode{2};
    TreeNode* child2 = new TreeNode{3};

    root->children.push_back(child1);
    root->children.push_back(child2);

    TreeNode* grandchild1 = new TreeNode{4};
    TreeNode* grandchild2 = new TreeNode{5};
    TreeNode* grandchild3 = new TreeNode{6};

    child1->children.push_back(grandchild1);
    child2->children.push_back(grandchild2);
    child2->children.push_back(grandchild3);

    // Run DFS
    #pragma omp parallel
    {
        #pragma omp single
        {
            dfs(root, 0);
        }
    }

    return 0;
}

