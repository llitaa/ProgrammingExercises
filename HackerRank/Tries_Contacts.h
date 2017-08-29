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
  long m_childenWordsCount;
  std::unordered_map<char, std::unique_ptr<Node>> m_children;

  explicit Node(char id)
    : m_id(id)
    , m_isWorld(false)
    , m_children()
    , m_childenWordsCount(0)
  {
  }

  Node(Node&& other) {
    m_id = other.m_id;
    m_isWorld = other.m_isWorld;
    m_childenWordsCount = other.m_childenWordsCount;
    m_children = std::move(other.m_children);
  }

  Node& operator=(Node&& other) {
    m_id = other.m_id;
    m_isWorld = other.m_isWorld;
    m_childenWordsCount = other.m_childenWordsCount;
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
    ++currentNode->m_childenWordsCount;
    auto insertionRes = currentNode->m_children.insert(make_pair(c, make_unique<Node>(Node(c))));
    currentNode = insertionRes.first->second.get();
  }
  currentNode->m_isWorld = true;
  ++currentNode->m_childenWordsCount;
}

void addChildWords(const Node* root, long& count) {
  if (root->m_isWorld) {
    ++count;
  }
  for (const auto& child : root->m_children) {
    addChildWords(child.second.get(), count);
  }
}
bool findWordsCount(const Node* root, const string& word, unsigned searchStart, long& count) {
  auto size = word.size();
  char contactLetter = word[searchStart];

  if (root->m_id != contactLetter || searchStart >= size)
    return false;

  if (searchStart == size - 1) { // Last world
    if (root->m_id == contactLetter) {
      count += root->m_childenWordsCount;
      return true;
    } 
  }

  const auto& children = root->m_children;
  ++searchStart;
  for (const auto& child : children) {
    if (findWordsCount(child.second.get(), word, searchStart, count))
      break;
  }
  return false;
}

