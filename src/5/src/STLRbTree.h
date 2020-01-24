#ifndef INC_5_STLRBTREE_H
#define INC_5_STLRBTREE_H

#include <utility>
//按照自己的意愿修改过的STL红黑树实现

template<typename T>
void swap(T &a,T &b) noexcept
{
  T temp = std::move(a);
  a = std::move(b);
  b = std::move(temp);
}

enum RbTreeColor { red = false, black = true };

struct RbTreeNode
{
    typedef RbTreeNode* basePtr;
    typedef const RbTreeNode* constBasePtr;

    RbTreeColor	color;
    basePtr		parent;
    basePtr		left;
    basePtr		right;

    static basePtr
    minimum(basePtr x) noexcept
    {
      while (x->left != nullptr) x = x->left;
      return x;
    }

    static constBasePtr
    minimum(constBasePtr x) noexcept
    {
      while (x->left != nullptr) x = x->left;
      return x;
    }

    static basePtr
    maximum(basePtr x) noexcept
    {
      while (x->right != nullptr) x = x->right;
      return x;
    }

    static constBasePtr
    maximum(constBasePtr x) noexcept
    {
      while (x->right != nullptr) x = x->right;
      return x;
    }
};

static RbTreeNode*
localRbTreeIncrement(RbTreeNode* x) noexcept
{
  if (x->right != nullptr)
  {
    x = x->right;
    while (x->left != nullptr)
      x = x->left;
  }
  else
  {
    RbTreeNode* y = x->parent;
    while (x == y->right)
    {
      x = y;
      y = y->parent;
    }
    if (x->right != y)
      x = y;
  }
  return x;
}

RbTreeNode*
RbTreeIncrement(RbTreeNode* x) noexcept
{
  return localRbTreeIncrement(x);
}

const RbTreeNode*
RbTreeIncrement(const RbTreeNode* x) noexcept
{
  return localRbTreeIncrement(const_cast<RbTreeNode*>(x));
}

static RbTreeNode*
localRbTreeDecrement(RbTreeNode* x) noexcept
{
  if (x->color == red
      && x->parent->parent == x)
    x = x->right;
  else if (x->left != nullptr)
  {
    RbTreeNode* y = x->left;
    while (y->right != nullptr)
      y = y->right;
    x = y;
  }
  else
  {
    RbTreeNode* y = x->parent;
    while (x == y->left)
    {
      x = y;
      y = y->parent;
    }
    x = y;
  }
  return x;
}

RbTreeNode*
RbTreeDecrement(RbTreeNode* x) noexcept
{
  return localRbTreeDecrement(x);
}

const RbTreeNode*
RbTreeDecrement(const RbTreeNode* x) noexcept
{
  return localRbTreeDecrement(const_cast<RbTreeNode*>(x));
}

static void
localRbTreeRotateLeft(RbTreeNode* const x,
                      RbTreeNode*& root)
{
  RbTreeNode* const y = x->right;

  x->right = y->left;
  if (y->left !=nullptr)
    y->left->parent = x;
  y->parent = x->parent;

  if (x == root)
    root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

void
RbTreeRotateLeft(RbTreeNode* const x,
                 RbTreeNode*& root)
{ localRbTreeRotateLeft (x, root); }

static void
localRbTreeRotateRight(RbTreeNode* const x,
                       RbTreeNode*& root)
{
  RbTreeNode* const y = x->left;

  x->left = y->right;
  if (y->right != nullptr)
    y->right->parent = x;
  y->parent = x->parent;

  if (x == root)
    root = y;
  else if (x == x->parent->right)
    x->parent->right = y;
  else
    x->parent->left = y;
  y->right = x;
  x->parent = y;
}


void
RbTreeRotateRight(RbTreeNode* const x,
                  RbTreeNode*& root)
{ localRbTreeRotateRight (x, root); }

void
RbTreeInsertAndReBalance(const bool          insert_left,
                         RbTreeNode* x,
                         RbTreeNode* p,
                         RbTreeNode& header) noexcept
{
  RbTreeNode *& root = header.parent;

  // Initialize fields in new node to insert.
  x->parent = p;
  x->left = nullptr;
  x->right = nullptr;
  x->color = red;

  // Insert.
  // Make new node child of parent and maintain root, leftmost and
  // rightmost nodes.
  // N.B. First node is always inserted left.
  if (insert_left)
  {
    p->left = x; // also makes leftmost = x when p == &header

    if (p == &header)
    {
      header.parent = x;
      header.right = x;
    }
    else if (p == header.left)
      header.left = x; // maintain leftmost pointing to min node
  }
  else
  {
    p->right = x;

    if (p == header.right)
      header.right = x; // maintain rightmost pointing to max node
  }
  // ReBalance.
  while (x != root
         && x->parent->color == red)
  {
    RbTreeNode* const xpp = x->parent->parent;

    if (x->parent == xpp->left)
    {
      RbTreeNode* const y = xpp->right;
      if (y && y->color == red)
      {
        x->parent->color = black;
        y->color = black;
        xpp->color = red;
        x = xpp;
      }
      else
      {
        if (x == x->parent->right)
        {
          x = x->parent;
          localRbTreeRotateLeft(x, root);
        }
        x->parent->color = black;
        xpp->color = red;
        localRbTreeRotateRight(xpp, root);
      }
    }
    else
    {
      RbTreeNode* const y = xpp->left;
      if (y && y->color == red)
      {
        x->parent->color = black;
        y->color = black;
        xpp->color = red;
        x = xpp;
      }
      else
      {
        if (x == x->parent->left)
        {
          x = x->parent;
          localRbTreeRotateRight(x, root);
        }
        x->parent->color = black;
        xpp->color = red;
        localRbTreeRotateLeft(xpp, root);
      }
    }
  }
  root->color = black;
}

RbTreeNode*
RbTreeReBalanceForErase(RbTreeNode* const z,
                        RbTreeNode& header) noexcept
{
  RbTreeNode *& root = header.parent;
  RbTreeNode *& leftmost = header.left;
  RbTreeNode *& rightmost = header.right;
  RbTreeNode* y = z;
  RbTreeNode* x = nullptr;
  RbTreeNode* x_parent = nullptr;

  if (y->left == nullptr)     // z has at most one non-null child. y == z.
    x = y->right;     // x might be null.
  else
  if (y->right == nullptr)  // z has exactly one non-null child. y == z.
    x = y->left;    // x is not null.
  else
  {
    // z has two non-null children.  Set y to
    y = y->right;   //   z's successor.  x might be null.
    while (y->left != nullptr)
      y = y->left;
    x = y->right;
  }
  if (y != z)
  {
    // relink y in place of z.  y is z's successor
    z->left->parent = y;
    y->left = z->left;
    if (y != z->right)
    {
      x_parent = y->parent;
      if (x) x->parent = y->parent;
      y->parent->left = x;   // y must be a child of left
      y->right = z->right;
      z->right->parent = y;
    }
    else
      x_parent = y;
    if (root == z)
      root = y;
    else if (z->parent->left == z)
      z->parent->left = y;
    else
      z->parent->right = y;
    y->parent = z->parent;
    swap(y->color, z->color);
    y = z;
    // y now points to node to be actually deleted
  }
  else
  {                        // y == z
    x_parent = y->parent;
    if (x)
      x->parent = y->parent;
    if (root == z)
      root = x;
    else
    if (z->parent->left == z)
      z->parent->left = x;
    else
      z->parent->right = x;
    if (leftmost == z)
    {
      if (z->right == nullptr)        // z->left must be null also
        leftmost = z->parent;
        // makes leftmost == _M_header if z == root
      else
        leftmost = RbTreeNode::minimum(x);
    }
    if (rightmost == z)
    {
      if (z->left == nullptr)         // z->right must be null also
        rightmost = z->parent;
        // makes rightmost == _M_header if z == root
      else                      // x == z->left
        rightmost = RbTreeNode::maximum(x);
    }
  }
  if (y->color != red)
  {
    while (x != root && (x == nullptr || x->color == black))
      if (x == x_parent->left)
      {
        RbTreeNode* w = x_parent->right;
        if (w->color == red)
        {
          w->color = black;
          x_parent->color = red;
          localRbTreeRotateLeft(x_parent, root);
          w = x_parent->right;
        }
        if ((w->left == nullptr ||
             w->left->color == black) &&
            (w->right == nullptr ||
             w->right->color == black))
        {
          w->color = red;
          x = x_parent;
          x_parent = x_parent->parent;
        }
        else
        {
          if (w->right == nullptr
              || w->right->color == black)
          {
            w->left->color = black;
            w->color = red;
            localRbTreeRotateRight(w, root);
            w = x_parent->right;
          }
          w->color = x_parent->color;
          x_parent->color = black;
          if (w->right)
            w->right->color = black;
          localRbTreeRotateLeft(x_parent, root);
          break;
        }
      }
      else
      {
        // same as above, with right <-> left.
        RbTreeNode* w = x_parent->left;
        if (w->color == red)
        {
          w->color = black;
          x_parent->color = red;
          localRbTreeRotateRight(x_parent, root);
          w = x_parent->left;
        }
        if ((w->right == nullptr ||
             w->right->color == black) &&
            (w->left == nullptr ||
             w->left->color == black))
        {
          w->color = red;
          x = x_parent;
          x_parent = x_parent->parent;
        }
        else
        {
          if (w->left == nullptr || w->left->color == black)
          {
            w->right->color = black;
            w->color = red;
            localRbTreeRotateLeft(w, root);
            w = x_parent->left;
          }
          w->color = x_parent->color;
          x_parent->color = black;
          if (w->left)
            w->left->color = black;
          localRbTreeRotateRight(x_parent, root);
          break;
        }
      }
    if (x) x->color = black;
  }
  return y;
}

unsigned int
RbTreeBlackCount(const RbTreeNode* node,
                 const RbTreeNode* root) noexcept
{
  if (node == nullptr)
    return 0;
  unsigned int sum = 0;
  do
  {
    if (node->color == black)
      ++sum;
    if (node == root)
      break;
    node = node->parent;
  }
  while (true);
  return sum;
}


#endif //INC_5_STLRBTREE_H
