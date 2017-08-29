// temp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <functional>
#include <memory>


struct Node {
  char m_id;
  bool m_isWorld;
  std::unordered_map<char, std::unique_ptr<Node>> m_children;

  explicit Node(char id)
    : m_id(id)
    , m_isWorld(false)
    , m_children()
  {
  }

  Node(Node&& other) {
    m_id = other.m_id;
    m_isWorld = other.m_isWorld;
    m_children = std::move(other.m_children);
  }

  Node& operator=(Node&& other) {
    m_id = other.m_id;
    m_isWorld = other.m_isWorld;
    m_children = std::move(other.m_children);
    return *this;
  }

  Node(const Node& other) = delete;
  Node& operator=(const Node& other) = delete;
};

bool operator ==(const Node& lhs, const Node& rhs) { return   lhs.m_id == rhs.m_id; }
bool operator !=(const Node& lhs, const Node& rhs) { return   !(lhs == rhs); }

using namespace std;

void addWord(Node* root, const string& word) {
  Node * currentNode = root;
  for (char c : word) {
    auto insertionRes = currentNode->m_children.insert({ c, make_unique<Node>(c) });
    currentNode = insertionRes.first->second.get();
  }
  currentNode->m_isWorld = true;
}

void addChildWords(const Node* root, long& count) {
  if (root->m_isWorld) {
    ++count;
  }
  for (const auto& child : root->m_children) {
    addChildWords(child.second.get(), count);
  }
}
void findWordsCount(const Node* root, const string& word, int searchStart, long& count) {
  auto size = word.size();
  char contactLetter = word[searchStart];

  if (root->m_id != ' ' && root->m_id != contactLetter)
    return;

  if (searchStart == size - 1) { // Last world
    if (root->m_id == contactLetter)
      addChildWords(root, count);
    return;
  }

  const auto& children = root->m_children;
  ++searchStart;
  for (const auto& child : children) {
    findWordsCount(child.second.get(), word, searchStart, count);
  }
}

