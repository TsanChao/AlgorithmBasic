//
// Created by mtk08120 on 2017/6/5.
//

#ifndef ALGORITHM_BST_H
#define ALGORITHM_BST_H

#include <stack>
#include <queue>
#include <cassert>

using namespace std;

class queque;

template <typename T>
class BST {
private:
    struct Node {
        T m_data;
        Node *m_left;
        Node *m_right;

        Node(T data) {
            m_data = data;
            m_left = m_right = nullptr;
        }
    };
    int count;
    Node *root;

    /*return root node of the tree*/
    Node * _insert_recursive(Node *node, T value) {

        if (nullptr == node) {
            count++;
            return new Node(value);
        }

        if (value == node->m_data)
            node->m_data = value;
        else if(value < node->m_data)
            node->m_left = _insert_recursive(node->m_left, value);
        else
            node->m_right = _insert_recursive(node->m_right, value);

        return node;
    }

    Node *_insert_non_recursive(Node *node, T value) {
        if (nullptr == node) {
            count++;
            return new Node(value);
        }

        Node *temp = node;
        while (1) {
            if (value == node->m_data)
                break;
            else if (value < node->m_data) {
                if (nullptr == node->m_left) {
                    node->m_left = new Node(value);
                    break;
                }
                else
                    node = node->m_left;
            } else {
                if (nullptr == node->m_right) {
                    node->m_right = new Node(value);
                    break;
                }
                else
                    node = node->m_right;
            }
        }

        return temp;
    }

    bool _contain(Node *node, T value) {
        if (nullptr == node)
            return false;
        if (value == node->m_data)
            return true;
        else if (value < node->m_data)
            return _contain(node->m_left, value);
        else
            return _contain(node->m_right, value);
    }

    T * _search(Node *node, T value) {
        if (nullptr == node)
            return nullptr;
        if (value == node->m_data)
            return &(node->m_data);
        else if (value < node->m_data)
            return _search(node->m_left, value);
        else
            return _search(node->m_right, value);
    }

    void _preOrder_recursive(Node *node) {
        if (nullptr == node)
            return;
        cout << node->m_data << " ";
        _preOrder_recursive(node->m_left);
        _preOrder_recursive(node->m_right);
    }

    void _preOrder_non_recursive(Node *node) {
        stack<Node *> s;
        Node *p = node;
        while (nullptr != p || !s.empty()) {
            while (nullptr != p) {
                cout << p->m_data << " ";
                s.push(p);
                p = p->m_left;
            }
            if(!s.empty()) {
                p = s.top();
                s.pop();
                p = p->m_right;
            }
        }
    }

    void _inOrder_recursive(Node *node) {
        if (nullptr == node)
            return;
        _inOrder_recursive(node->m_left);
        cout << node->m_data << " ";
        _inOrder_recursive(node->m_right);
    }

    void _inOrder_non_recursive(Node *node) {
        stack<Node *> s;
        Node *p = node;
        while (nullptr != p || !s.empty()) {
            while (nullptr != p) {
                s.push(p);
                p = p->m_left;
            }
            if (!s.empty()) {
                p = s.top();
                cout << p->m_data << " ";
                s.pop();
                p =p->m_right;
            }
        }
    }

    void _postOrder_recursive(Node *node) {
        if (nullptr == node)
            return;
        _postOrder_recursive(node->m_left);
        _postOrder_recursive(node->m_right);
        cout << node->m_data << " ";
    }

    void _postOrder_non_recursive(Node *node) {
        stack<Node *> s;
        Node *p = node;
        while (nullptr != p || !s.empty()) {
            while (nullptr != p) {
                s.push(p);
                p = p->m_left;
            }
            if (!s.empty()) {
                p = s.top();
                cout << p->m_data << " ";
                s.pop();
                p =p->m_right;
            }
        }
    }

    int _tHeight_recursive(Node *node) {
        if (nullptr == node)
            return 0;
        int lh = 0, rh = 0;
        if (nullptr != node->m_left)
            lh = _tHeight_recursive(node->m_left);
        if (nullptr != node->m_right)
            rh = _tHeight_recursive(node->m_right);
        return (lh > rh) ? (lh + 1) : (rh + 1);
    }

    int _tHeight_non_recursive(Node *node) {
        if (nullptr == node)
            return 0;
        vector<Node *> v;
        v.push_back(node);
        int cur = 0;
        int last = 0;
        int height = 0;
        while (cur < v.size()) {
            last = v.size();
            while (cur < last) {
                //cout << v[cur]->m_data << endl;
                if (v[cur]->m_left)
                    v.push_back(v[cur]->m_left);
                if (v[cur]->m_right)
                    v.push_back(v[cur]->m_right);
                cur++;
            }
            height++;
            //cout << endl;
        }
        return height;
    }

    void _levelOrder_u2d(Node *node) {
        if (nullptr == node)
            return;
        queue<Node *> q;
        q.push(node);
        while (!q.empty()) {
            Node *p = q.front();
            cout << p->m_data << " ";
            q.pop();
            if (p->m_left)
                q.push(p->m_left);
            if (p->m_right)
                q.push(p->m_right);
        }
    }

    void _levelOrder_u2d2(Node *node) {
        if (nullptr == node)
            return;
        vector<Node *> v;
        v.push_back(node);
        int cur = 0;
        int last = 0;
        int height = 0;
        while (cur < v.size()) {
            last = v.size();
            while (cur < last) {
                cout << v[cur]->m_data << " ";
                if (v[cur]->m_left)
                    v.push_back(v[cur]->m_left);
                if (v[cur]->m_right)
                    v.push_back(v[cur]->m_right);
                cur++;
            }
            height++;
            //cout << endl;
        }
    }

    void _levelOrder_u2d3(Node *node, int level, vector<vector<T>> &result) {
        if (nullptr == node)
            return;
        if (level > result.size()) {
            vector<T> v;
            result.push_back(v);
        }
        result[level - 1].push_back(node->m_data);
        _levelOrder_u2d3(node->m_left, level + 1, result);
        _levelOrder_u2d3(node->m_right, level + 1, result);
    }

public:
    BST();
    void insert_recursive(T value);
    void insert_non_recursive(T value);
    bool contain(T value);
    T* search(T value);
    void preOrder_recursive();
    void preOrder_non_recursive();
    void inOrder_recursive();
    void inOrder_non_recursive();
    void postOrder_recursive();
    int tHeight_recursive();
    int tHeight_non_recursive();
    void levelOrder_u2d();
    void levelOrder_u2d2();
    void levelOrder_u2d3();
};

template <typename T>
BST<T>::BST() {
    count = 0;
    root = nullptr;
}

template <typename T>
void BST<T>::insert_recursive(T value) {
    root = _insert_recursive(root, value);
}

template <typename T>
bool BST<T>::contain(T value) {
    return _contain(root, value);
}

template <typename T>
T * BST<T>::search(T value){
    return _search(root, value);
}

template <typename T>
void BST<T>::insert_non_recursive(T value) {
    root = _insert_non_recursive(root, value);
}

template <typename T>
void BST<T>::preOrder_recursive() {
    _preOrder_recursive(root);
}

template <typename T>
void BST<T>::preOrder_non_recursive() {
    _preOrder_non_recursive(root);
}

template <typename T>
void BST<T>::inOrder_recursive() {
    _inOrder_recursive(root);
}

template <typename T>
void BST<T>::inOrder_non_recursive() {
    _inOrder_non_recursive(root);
}

template <typename T>
void BST<T>::postOrder_recursive() {
    _postOrder_recursive(root);
}

template <typename T>
int BST<T>::tHeight_recursive(){
    _tHeight_recursive(root);
}

template <typename T>
int BST<T>::tHeight_non_recursive(){
    return _tHeight_non_recursive(root);
}

template <typename T>
void BST<T>::levelOrder_u2d(){
    _levelOrder_u2d(root);
}

template <typename T>
void BST<T>::levelOrder_u2d2(){
    _levelOrder_u2d2(root);
}

template <typename T>
void BST<T>::levelOrder_u2d3(){
    vector<vector<T>> result;
    _levelOrder_u2d3(root, 1, result);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
    }
}

#endif //ALGORITHM_BST_H
