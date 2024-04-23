#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

const int max_nodes = 1000;
int visited[max_nodes];
int n_threads;

struct TreeNode
{
    int value;
    vector<TreeNode *> children;
};

void bfs(TreeNode *root)
{

    queue<TreeNode *> q;
    q.push(root);
    visited[root->value] = 1;

    while (!q.empty())
    {
        int currentSize = q.size();

#pragma omp parallel num_threads(n_threads)
        {
#pragma omp for
            for (int i = 0; i < currentSize; i++)
            {
                TreeNode *node;
#pragma omp critical
                {
                    node = q.front();
                    q.pop();
                }

                vector<TreeNode *>::iterator it;
                for (it = node->children.begin(); it != node->children.end(); ++it)
                {
                    TreeNode *child = *it;
                    if (!visited[child->value])
                    {
#pragma omp critical
                        {
                            visited[child->value] = 1;
                            q.push(child);
                        }
                    }
                }
            }
        }
    }
}

int main()
{

    // construct Tree

    TreeNode *root = new TreeNode{0};
    int numnodes = 15;
    for (int i = 1; i < numnodes; i++)
    {
        TreeNode *child = new TreeNode{i};
        root->children.push_back(child);
        for (int j = 0; j < i; j++)
        {
            TreeNode *grandchild = new TreeNode{j};
            child->children.push_back(grandchild);
        }
    }

    // initialize OpenMP
    n_threads = omp_get_max_threads();

    // Run BFS
    bfs(root);

    // print visited nodes
    for (int i = 0; i < numnodes; i++)
    {
        if (visited[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}

