#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "s_containers.h"
#include "s_containersplus.h"

using namespace std;

template <class T, size_t N>
bool arraycheck(s21::array<T, N> arg1, std::array<T, N> arg2) {
  bool res{true};
  if (arg1.size() != arg2.size())
    res = false;
  else {
    for (size_t i{0}; i < arg1.size() && res; ++i)
      if (arg1[i] != arg2[i]) res = false;
  }
  return res;
}

TEST(list_functions, default_) {
  s21::list<int> a;
  std::list<int> b;
  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.size(), b.size());
}

TEST(list_functions, parameters) {
  s21::list<double> a(7);
  std::list<double> b(7);

  EXPECT_EQ(a.size(), b.size());
}

TEST(list_functions, copy) {
  s21::list<double> a;
  a.push_back(2.2);
  a.push_back(3.6);
  s21::list<double> b(a);

  std::list<double> c;
  c.push_back(2.2);
  c.push_back(3.6);
  std::list<double> d(c);

  EXPECT_EQ(b.front(), d.front());
  EXPECT_EQ(b.back(), d.back());
  EXPECT_EQ(b.size(), d.size());
}

TEST(list_functions, move) {
  s21::list<double> a;
  a.push_back(2.2);
  a.push_back(3.6);
  s21::list<double> b(move(a));

  EXPECT_EQ(a.size(), 0);

  EXPECT_EQ(b.front(), 2.2);
  EXPECT_EQ(b.back(), 3.6);
  EXPECT_EQ(b.size(), 2);
}

TEST(list_functions, list_init) {
  s21::list<double> a{64.4, 73, 1 / 3, 34.23, -02345, -234.54};
  std::list<double> b{64.4, 73, 1 / 3, 34.23, -02345, -234.54};

  EXPECT_EQ(a.size(), b.size());

  auto i = b.begin();
  for (auto j = a.begin(); j != a.end(); ++j)
    EXPECT_TRUE(fabs(*i++ - *j) < 1e-7);
}

TEST(list_functions, operator_equal) {
  s21::list<int> a{1, 2, 3, 4, 5};
  s21::list<int> b{77, 99};
  a = move(b);

  std::list<int> c{1, 2, 3, 4, 5};
  std::list<int> d{77, 99};
  c = move(d);

  EXPECT_EQ(b.empty() + d.empty(), 2);

  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(*a.begin() - *c.begin(), 0);
  EXPECT_EQ(*--a.end() - *--c.end(), 0);
  EXPECT_EQ(a.size() + c.size(), 4);
}

TEST(element_access, both) {
  s21::list<int> a;
  std::list<int> b;
  a.push_back(4);
  a.push_front(2);

  b.push_back(4);
  b.push_front(2);
  EXPECT_EQ(a.front(), b.front());

  a.push_back(9);
  b.push_back(9);
  EXPECT_EQ(a.back(), b.back());
}

TEST(list_iterators, both) {
  s21::list<string> a{"bus", "sus", "aboba"};
  std::list<string> b{"bus", "sus", "aboba"};

  EXPECT_EQ(*a.begin(), *b.begin());
  EXPECT_EQ(*(--a.end()), *(--b.end()));
}

TEST(list_capacity, all) {
  s21::list<string> my{"bus", "sus", "aboba"};
  std::list<string> orig{"bus", "sus", "aboba"};

  EXPECT_EQ(my.empty(), orig.empty());
  EXPECT_EQ(my.size(), orig.size());
  EXPECT_EQ(my.max_size(), orig.max_size());

  s21::list<char> b;
  std::list<char> c;

  EXPECT_EQ(b.empty(), c.empty());
  EXPECT_EQ(b.size(), c.size());
  EXPECT_EQ(b.max_size(), c.max_size());
}

TEST(list_modifiers, clear) {
  s21::list<string> my{"bus", "sus", "aboba"};
  std::list<string> orig{"bus", "sus", "aboba"};
  my.clear();
  orig.clear();
  EXPECT_EQ(my.empty(), orig.empty());
  EXPECT_EQ(my.size(), orig.size());
}

TEST(list_modifiers, insert) {
  s21::list<string> my{"bus", "sus", "aboba"};
  std::list<string> orig{"bus", "sus", "aboba"};

  auto my1 = my.insert(++my.begin(), "boy");
  auto my2 = my.insert(my.end(), "gym");

  auto right1 = orig.insert(++orig.begin(), "boy");
  auto right2 = orig.insert(orig.end(), "gym");

  EXPECT_EQ(*my1, *right1);
  EXPECT_EQ(*my2, *right2);
  EXPECT_EQ(*(++my.begin()), *(++orig.begin()));
  EXPECT_EQ(*(--my.end()), *(--orig.end()));
}

TEST(list_modifiers, erase1) {
  s21::list<string> my{"bus", "boy", "sus", "aboba", "gym"};
  std::list<string> orig{"bus", "boy", "sus", "aboba", "gym"};

  my.erase(--my.end());
  my.erase(++my.begin());

  orig.erase(--orig.end());
  orig.erase(++orig.begin());

  EXPECT_EQ(*(--my.end()), *(--orig.end()));
  EXPECT_EQ(*(++my.begin()), *(++orig.begin()));
}

TEST(list_modifiers, erase2) {
  s21::list<string> my{"bus", "boy"};
  std::list<string> orig{"bus", "boy"};

  my.erase(my.begin());
  orig.erase(orig.begin());

  EXPECT_EQ(my.front(), orig.front());
}

TEST(list_modifiers, erase3) {
  s21::list<string> my{"bus", "boy"};
  EXPECT_THROW(my.erase(my.end()), std::invalid_argument);

  my.clear();
  EXPECT_THROW(my.erase(my.begin()), std::invalid_argument);
}

TEST(list_modifiers, push_back) {
  s21::list<char> a;
  std::list<char> b;

  a.push_back('N');
  b.push_back('N');
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(*(--a.end()), *(--b.end()));

  a.push_back('I');
  b.push_back('I');
  EXPECT_EQ(*(--a.end()), *(--b.end()));
  EXPECT_EQ(a.size(), 2);

  a.push_back('G');
  b.push_back('G');
  EXPECT_EQ(*(--a.end()), *(--b.end()));
  EXPECT_EQ(a.size(), 3);
}

TEST(list_modifiers, push_front) {
  s21::list<char> a;
  std::list<char> b;

  a.push_front('N');
  b.push_front('N');
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(*a.begin(), *b.begin());

  a.push_front('I');
  b.push_front('I');
  EXPECT_EQ(*a.begin(), *b.begin());
  EXPECT_EQ(a.size(), 2);
}

TEST(list_modifiers, pop_front) {
  s21::list<char> a{'x', 'y'};
  std::list<char> b{'z', 'y'};

  a.pop_front();
  b.pop_front();

  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(*a.begin(), *b.begin());
}

TEST(list_modifiers, pop_back) {
  s21::list<char> a{'y', 'x'};
  std::list<char> b{'y', 'z'};

  a.pop_back();
  b.pop_back();

  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(*--a.end(), *--b.end());
}

TEST(list_modifiers, swap) {
  s21::list<int> a{1, 2, 3, 4};
  s21::list<int> b{66, 88, 33, 11, 99, 44};

  std::list<int> c{1, 2, 3, 4};
  std::list<int> d{66, 88, 33, 11, 99, 44};

  a.swap(b);
  c.swap(d);

  auto i = c.begin();
  for (auto j = a.begin(); j != a.end(); ++j) {
    EXPECT_EQ(*i, *j);
    ++i;
  }
  i = d.begin();
  for (auto j = b.begin(); j != b.end(); ++j) {
    EXPECT_EQ(*i, *j);
    ++i;
  }
}

TEST(list_modifiers, splice_1) {
  s21::list<int> a{1, 2, 3, 4};
  s21::list<int> b{66, 88, 33, 11, 99, 44};

  std::list<int> c{1, 2, 3, 4};
  std::list<int> d{66, 88, 33, 11, 99, 44};

  a.splice(a.begin(), b);
  c.splice(c.begin(), d);

  auto i = c.begin();
  for (auto j = a.begin(); j != a.end(); ++j) {
    EXPECT_EQ(*i, *j);
    ++i;
  }
}

TEST(list_modifiers, splice_2) {
  s21::list<int> a{1, 2, 3, 4};
  s21::list<int> b{66, 88, 33, 11, 99, 44};

  std::list<int> c{1, 2, 3, 4};
  std::list<int> d{66, 88, 33, 11, 99, 44};

  a.splice(--a.end(), b);
  c.splice(--c.end(), d);

  //{1, 2, 3, 66, 88, 33, 11, 99, 44, 4};

  auto i = c.begin();
  for (auto j = a.begin(); j != a.end(); ++j) {
    EXPECT_EQ(*i, *j);
    ++i;
  }
  EXPECT_TRUE(b.empty());
}

TEST(list_modifiers, splice_3) {
  s21::list<int> a;
  s21::list<int> b{66, 88, 33, 11, 99, 44};

  std::list<int> c;
  std::list<int> d{66, 88, 33, 11, 99, 44};

  a.splice(a.end(), b);
  c.splice(c.end(), d);

  auto i = c.begin();
  for (auto j = a.begin(); j != a.end(); ++j) {
    EXPECT_EQ(*i, *j);
    ++i;
  }
  EXPECT_TRUE(b.empty());
}

TEST(list_modifiers, reverse_) {
  s21::list<int> b{66, 88, 33, 11, 99, 44};
  std::list<int> d{66, 88, 33, 11, 99, 44};
  // {44,99,11,33,88,66};
  b.reverse();
  d.reverse();

  auto i = d.begin();
  for (auto j = b.begin(); j != b.end(); ++j) {
    EXPECT_EQ(*i++, *j);
  }
}

TEST(list_modifiers, unique) {
  s21::list<int> a{66, 88, 88, 88, 88, 33, 88, 11, 99, 99, 44, 66};
  std::list<int> z{66, 88, 88, 88, 88, 33, 88, 11, 99, 99, 44, 66};

  a.unique();
  z.unique();

  auto i = a.begin();
  for (auto j = z.begin(); j != z.end(); ++j) {
    EXPECT_EQ(*i++, *j);
  }
}

TEST(list_modifiers, sort1) {
  s21::list<string> a{"xyz", "abc", "ok", "ded"};
  std::list<string> z{"xyz", "abc", "ok", "ded"};

  a.sort();
  z.sort();

  auto i = a.begin();
  for (auto j = z.begin(); j != z.end(); ++j) {
    EXPECT_EQ(*i++, *j);
  }
}

TEST(list_modifiers, sort2) {
  s21::list<char> a{'v', 'r', 'a'};
  std::list<char> z{'v', 'r', 'a'};

  a.sort();
  z.sort();

  auto i = a.begin();
  for (auto j = z.begin(); j != z.end(); ++j) {
    EXPECT_EQ(*i++, *j);
  }
}

TEST(list_modifiers, merge1) {
  s21::list<int> a{-6, 7, 190, 6, 11};
  s21::list<int> b{1, 2, -3, -100};

  std::list<int> c{-6, 7, 190, 6, 11};
  std::list<int> d{1, 2, -3, -100};

  a.merge(b);
  c.merge(d);

  auto i = a.begin();
  for (auto j = c.begin(); j != c.end(); ++j) EXPECT_EQ(*i++, *j);
}

TEST(list_modifiers, merge2) {
  s21::list<int> a{-6, -5, -4};
  s21::list<int> b{-3, -2, -1, 0, 1, 2};

  std::list<int> c{-6, -5, -4};
  std::list<int> d{-3, -2, -1, 0, 1, 2};

  a.merge(b);
  c.merge(d);

  auto i = a.begin();
  for (auto j = c.begin(); j != c.end(); ++j) EXPECT_EQ(*i++, *j);
}

TEST(list_modifiers, merge3) {
  s21::list<int> a{-6, 7, 190, 6, 11};
  s21::list<int> b{1, 2, -3, -100};

  std::list<int> c{-6, 7, 190, 6, 11};
  std::list<int> d{1, 2, -3, -100};

  a.sort();
  b.sort();
  c.sort();
  d.sort();

  a.merge(b);
  c.merge(d);

  auto i = a.begin();
  for (auto j = c.begin(); j != c.end(); ++j) EXPECT_EQ(*i++, *j);
}

TEST(list_part3, insert_many1) {
  s21::list<int> a{-6, 7, 190, 6, 11};
  std::list<int> b{-6, 7, 190, 6, 11};

  s21::list<int>::iterator my_result(a.insert_many(a.begin(), 1, 2, -3, -100));
  std::list<int>::iterator actually(b.insert(b.begin(), {1, 2, -3, -100}));

  EXPECT_EQ(*my_result, *actually);
  EXPECT_EQ(a.size(), b.size());

  auto my = a.begin();
  for (auto right = b.begin(); right != b.end(); ++right) {
    EXPECT_EQ(*my++, *right);
  }
}

TEST(list_part3, insert_many2) {
  s21::list<int> a{-6, 7, 190, 6, 11};
  std::list<int> b{-6, 7, 190, 6, 11};

  s21::list<int>::iterator my_result(a.insert_many(a.end(), 1, 2, -3, -100));
  std::list<int>::iterator actually(b.insert(b.end(), {1, 2, -3, -100}));

  EXPECT_EQ(*my_result, *actually);
  EXPECT_EQ(a.size(), b.size());

  auto my = a.begin();
  for (auto right = b.begin(); right != b.end(); ++right) {
    EXPECT_EQ(*my++, *right);
  }
}

TEST(list_part3, insert_many3) {
  s21::list<int> a{-6, 7, 190, 6, 11};
  std::list<int> b{-6, 7, 190, 6, 11};

  s21::list<int>::iterator my_result(
      a.insert_many(++a.begin(), 1, 2, -3, -100));
  std::list<int>::iterator actually(b.insert(++b.begin(), {1, 2, -3, -100}));

  EXPECT_EQ(*my_result, *actually);
  EXPECT_EQ(a.size(), b.size());

  auto my = a.begin();
  for (auto right = b.begin(); right != b.end(); ++right) {
    EXPECT_EQ(*my++, *right);
  }
}

TEST(list_part3, insert_many4) {
  s21::list<int> a;
  std::list<int> b;

  s21::list<int>::iterator my_result(a.insert_many(a.end(), 1, 2, -3, -100));
  std::list<int>::iterator actually(b.insert(b.end(), {1, 2, -3, -100}));

  EXPECT_EQ(*my_result, *actually);
  EXPECT_EQ(a.size(), b.size());

  auto my = a.begin();
  for (auto right = b.begin(); right != b.end(); ++right) {
    EXPECT_EQ(*my++, *right);
  }
}

TEST(list_part3, insert_many_back1) {
  s21::list<int> a{-6, 7, 190, 6, 11};
  std::list<int> b{-6, 7, 190, 6, 11};

  a.insert_many_back(1, 2, -3, -100);
  b.insert(b.end(), {1, 2, -3, -100});

  EXPECT_EQ(a.size(), b.size());

  auto my = a.begin();
  for (auto right = b.begin(); right != b.end(); ++right) {
    EXPECT_EQ(*my++, *right);
  }
}

TEST(list_part3, insert_many_back2) {
  s21::list<int> a;
  std::list<int> b;

  a.insert_many_back(1, 2, -3, -100);
  b.insert(b.end(), {1, 2, -3, -100});

  EXPECT_EQ(a.size(), b.size());

  auto my = a.begin();
  for (auto right = b.begin(); right != b.end(); ++right) {
    EXPECT_EQ(*my++, *right);
  }
}

TEST(list_part3, insert_many_front1) {
  s21::list<int> a{-6, 7, 190, 6, 11};
  std::list<int> b{-6, 7, 190, 6, 11};

  a.insert_many_front(1, 2, -3, -100);
  b.insert(b.begin(), {1, 2, -3, -100});

  EXPECT_EQ(a.size(), b.size());

  auto my = a.begin();
  for (auto right = b.begin(); right != b.end(); ++right) {
    EXPECT_EQ(*my++, *right);
  }
}

TEST(list_part3, insert_many_front2) {
  s21::list<int> a;
  std::list<int> b;

  a.insert_many_front(1, 2, -3, -100);
  b.insert(b.begin(), {1, 2, -3, -100});

  EXPECT_EQ(a.size(), b.size());

  auto my = a.begin();
  for (auto right = b.begin(); right != b.end(); ++right) {
    EXPECT_EQ(*my++, *right);
  }
}

TEST(queue_functions, default_) {
  s21::queue<float> a;
  std::queue<float> b;

  EXPECT_EQ(a.size(), b.size());
}

TEST(queue_functions, copy) {
  s21::queue<string> a;
  a.push("sussy");
  a.push("sus");
  s21::queue<string> b(a);

  std::queue<string> c;
  c.push("sussy");
  c.push("sus");
  std::queue<string> d(c);

  EXPECT_EQ(d.front(), b.front());
  EXPECT_EQ(d.back(), b.back());
  EXPECT_EQ(d.size(), b.size());
}

TEST(queue_functions, move) {
  s21::queue<double> a;
  a.push(2.2);
  a.push(3.6);
  s21::queue<double> b(move(a));

  std::queue<double> c;
  c.push(2.2);
  c.push(3.6);
  std::queue<double> d(move(c));

  EXPECT_EQ(a.size(), c.size());

  EXPECT_EQ(b.front(), d.front());
  EXPECT_EQ(b.back(), d.back());
  EXPECT_EQ(b.size(), d.size());
}

TEST(queue_functions, operator_equal) {
  s21::queue<int> a{1, 2, 3, 4, 5};
  s21::queue<int> b{77, 99};
  a = move(b);

  std::queue<int> right;
  right.push(1);
  right.push(2);
  right.push(3);
  right.push(4);
  right.push(5);
  std::queue<int> d;
  d.push(77);
  d.push(99);
  right = move(d);

  EXPECT_EQ(b.empty() + d.empty(), 2);

  EXPECT_EQ(a.size(), right.size());
  EXPECT_EQ(a.front() - right.front(), 0);
  EXPECT_EQ(a.back() - right.back(), 0);
  EXPECT_EQ(a.size() + right.size(), 4);
}

TEST(queue_access, both) {
  s21::queue<int> a;
  std::queue<int> b;
  a.push(4);
  a.push(2);

  b.push(4);
  b.push(2);
  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.back(), b.back());

  a.push(9);
  b.push(9);
  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.back(), b.back());
}

TEST(queue_capacity, all) {
  s21::queue<string> my{"bus", "sus", "aboba"};
  std::queue<string> right;
  right.push("bus");
  right.push("sus");
  right.push("aboba");

  EXPECT_EQ(my.empty(), right.empty());
  EXPECT_EQ(my.size(), right.size());

  s21::queue<char> b;
  std::queue<char> c;

  EXPECT_EQ(b.empty(), c.empty());
  EXPECT_EQ(b.size(), c.size());
}

TEST(queue_modifiers, push) {
  s21::queue<char> a;
  std::queue<char> b;

  a.push('N');
  b.push('N');
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(a.back(), b.back());

  a.push('I');
  b.push('I');
  EXPECT_EQ(a.back(), b.back());
  EXPECT_EQ(a.size(), 2);
}

TEST(queue_modifiers, pop) {
  s21::queue<char> a{'x', 'y'};
  std::queue<char> b;

  b.push('z');
  b.push('y');

  a.pop();
  b.pop();

  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(a.front(), b.front());
}

TEST(queue_modifiers, swap) {
  s21::queue<int> a{1, 2};
  s21::queue<int> b{66, 88, 33};

  std::queue<int> c;
  c.push(1);
  c.push(2);
  std::queue<int> d;
  d.push(66);
  d.push(88);
  d.push(33);

  a.swap(b);
  c.swap(d);

  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(a.front(), c.front());
  EXPECT_EQ(a.back(), c.back());

  EXPECT_EQ(b.size(), d.size());
  EXPECT_EQ(b.front(), d.front());
  EXPECT_EQ(b.back(), d.back());
}

TEST(queue_part3, insert_many_back1) {
  s21::queue<int> my_q{11};
  std::queue<int> orig;

  orig.push(11);
  orig.push(1);
  orig.push(2);
  orig.push(-3);

  my_q.insert_many_back(1, 2, -3);

  EXPECT_EQ(my_q.size(), orig.size());

  for (size_t i = 0; i < orig.size(); ++i) {
    EXPECT_EQ(my_q.back(), orig.back());
    orig.pop();
    my_q.pop();
  }
}

TEST(queue_part3, insert_many_back2) {
  s21::queue<int> my_q;
  std::queue<int> orig;

  orig.push(1);
  orig.push(2);
  orig.push(-3);

  my_q.insert_many_back(1, 2, -3);

  EXPECT_EQ(my_q.size(), orig.size());

  for (size_t i = 0; i < orig.size(); ++i) {
    EXPECT_EQ(my_q.back(), orig.back());
    orig.pop();
    my_q.pop();
  }
}

TEST(stack_functions, default_) {
  s21::stack<float> a;
  std::stack<float> b;

  EXPECT_EQ(a.size(), b.size());
}

TEST(stack_functions, copy) {
  s21::stack<string> a;
  a.push("sussy");
  a.push("sus");
  s21::stack<string> b(a);

  std::stack<string> c;
  c.push("sussy");
  c.push("sus");
  std::stack<string> d(c);

  EXPECT_EQ(d.top(), b.top());
  EXPECT_EQ(d.size(), b.size());
}

TEST(stack_functions, move) {
  s21::stack<double> a;
  a.push(2.2);
  a.push(3.6);
  s21::stack<double> b(move(a));

  std::stack<double> c;
  c.push(2.2);
  c.push(3.6);
  std::stack<double> d(move(c));

  EXPECT_EQ(a.size(), c.size());

  EXPECT_EQ(b.top(), d.top());
  EXPECT_EQ(b.size(), d.size());
}

TEST(stack_functions, operator_equal) {
  s21::stack<int> a{1, 2, 3, 4, 5};
  s21::stack<int> b{77, 99};
  a = move(b);

  std::stack<int> right;
  right.push(1);
  right.push(2);
  right.push(3);
  right.push(4);
  right.push(5);
  std::stack<int> d;
  d.push(77);
  d.push(99);
  right = move(d);

  EXPECT_EQ(b.empty() + d.empty(), 2);

  EXPECT_EQ(a.size(), right.size());
  EXPECT_EQ(a.top() - right.top(), 0);
  EXPECT_EQ(a.size() + right.size(), 4);
}

TEST(stack_access, both) {
  s21::stack<int> a;
  std::stack<int> b;

  a.push(4);
  a.push(2);
  b.push(4);
  b.push(2);
  EXPECT_EQ(a.top(), b.top());

  a.push(9);
  b.push(9);
  EXPECT_EQ(a.top(), b.top());
}

TEST(stack_capacity, all) {
  s21::stack<string> my{"bus", "sus", "aboba"};
  std::stack<string> right;
  right.push("bus");
  right.push("sus");
  right.push("aboba");

  EXPECT_EQ(my.empty(), right.empty());
  EXPECT_EQ(my.size(), right.size());

  s21::stack<char> b;
  std::stack<char> c;

  EXPECT_EQ(b.empty(), c.empty());
  EXPECT_EQ(b.size(), c.size());
}

TEST(stack_modifiers, push) {
  s21::stack<int> our_stack_int;
  std::stack<int> std_stack_int;

  our_stack_int.push(1);
  std_stack_int.push(1);
  EXPECT_EQ(our_stack_int.size(), std_stack_int.size());
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());

  our_stack_int.push(2);
  std_stack_int.push(2);
  EXPECT_EQ(our_stack_int.size(), std_stack_int.size());
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());

  our_stack_int.push(3);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.size(), std_stack_int.size());
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
}

TEST(stack_modifiers, pop) {
  s21::stack<char> a{'x', 'y', 'z'};
  std::stack<char> b;
  b.push('x');
  b.push('y');
  b.push('z');

  a.pop();
  b.pop();
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.top(), b.top());

  a.pop();
  b.pop();
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.top(), b.top());

  a.pop();
  b.pop();
  EXPECT_EQ(a.size(), b.size());
}

TEST(stack_modifiers, swap) {
  s21::stack<int> a{1, 2};
  s21::stack<int> b{66, 88, 33};

  std::stack<int> c;
  c.push(1);
  c.push(2);
  std::stack<int> d;
  d.push(66);
  d.push(88);
  d.push(33);

  a.swap(b);
  c.swap(d);

  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(a.top(), c.top());

  EXPECT_EQ(b.size(), d.size());
  EXPECT_EQ(b.top(), d.top());
}

TEST(stack_part3, insert_many_front1) {
  s21::stack<int> my_q{11};
  std::stack<int> orig;

  orig.push(11);
  orig.push(1);
  orig.push(2);
  orig.push(-3);

  my_q.insert_many_front(1, 2, -3);

  EXPECT_EQ(my_q.size(), orig.size());

  for (size_t i = 0; i < orig.size(); ++i) {
    EXPECT_EQ(my_q.top(), orig.top());
    orig.pop();
    my_q.pop();
  }
}

TEST(stack_part3, insert_many_front2) {
  s21::stack<int> my_q;
  std::stack<int> orig;

  orig.push(1);
  orig.push(2);
  orig.push(-3);

  my_q.insert_many_front(1, 2, -3);

  EXPECT_EQ(my_q.size(), orig.size());

  for (size_t i = 0; i < orig.size(); ++i) {
    EXPECT_EQ(my_q.top(), orig.top());
    orig.pop();
    my_q.pop();
  }
}

//!! ARRAY

TEST(s_array_test, default_constructor1) {
  s21::array<int, 0> arr;
  std::array<int, 0> ctrl;
  ASSERT_TRUE(arraycheck(arr, ctrl));
}

TEST(s_array_test, default_constructor2) {
  s21::array<int, 0> arr = s21::array<int, 0>();
  ASSERT_EQ(arr.empty(), true);
}

TEST(s_array_test, default_constructor3) {
  s21::array<int, 10> arr = s21::array<int, 10>();
  ASSERT_EQ(arr.empty(), false);
}

TEST(s_array_test, value_constructor1) {
  s21::array<int, 4> arr = s21::array<int, 4>({0, 0, 0, 0});
  ASSERT_EQ(arr.empty(), false);
}

TEST(s_array_test, value_constructor2) {
  s21::array<double, 10> arr{01, 2, 13, 4, 05, 1, 99, 06, 1, 8};
  std::array<double, 10> ctrl{01, 2, 13, 4, 05, 1, 99, 06, 1, 8};
  ASSERT_TRUE(arraycheck(arr, ctrl));
}

TEST(s_array_test, copy_constructor1) {
  s21::array<int, 10> arr{6, 15, 3, 4, 177, 1, 18, 0, 21, 2};
  s21::array<int, 10> arr_copied(arr);
  std::array<int, 10> ctrl{6, 15, 3, 4, 177, 1, 18, 0, 21, 2};
  std::array<int, 10> ctrl_copied(ctrl);
  ASSERT_TRUE(arraycheck(arr, ctrl));
  ASSERT_TRUE(arraycheck(arr_copied, ctrl_copied));
}

TEST(s_array_test, copy_constructor2) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  s21::array<int, 4> arr2 = s21::array<int, 4>(arr);
  ASSERT_EQ(arr2.size(), arr.size());
  ASSERT_EQ(arr2.empty(), false);
}

TEST(s_array_test, move_constructor) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  s21::array<int, 4> arr2 = std::move(arr);
  ASSERT_EQ(arr2.empty(), false);
}

TEST(s_array_test, move_constructor_2) {
  s21::array<int, 10> arr{01, 2, 13, 4, 05, 1, 99, 06, 1, 8};
  s21::array<int, 10> arr_moved(std::move(arr));
  std::array<int, 10> ctrl{01, 2, 13, 4, 05, 1, 99, 06, 1, 8};
  std::array<int, 10> ctrl_moved(std::move(ctrl));
  ASSERT_TRUE(arraycheck(arr, ctrl));
  ASSERT_TRUE(arraycheck(arr_moved, ctrl_moved));
}

TEST(s_array_test, operator_move_constructor1) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr.empty(), false);
}

TEST(s_array_test, operator_move_constructor2) {
  s21::array<int, 10> arr{01, 2, 13, 4, 05, 1, 99, 06, 1, 8};
  s21::array<int, 10> arr_moved;
  arr_moved = std::move(arr);
  std::array<int, 10> ctrl{01, 2, 13, 4, 05, 1, 99, 06, 1, 8};
  std::array<int, 10> ctrl_moved;
  ctrl_moved = std::move(ctrl);
  ASSERT_TRUE(arraycheck(arr, ctrl));
  ASSERT_TRUE(arraycheck(arr_moved, ctrl_moved));
}

TEST(s_array_test, at1) {
  s21::array<int, 4> arr = s21::array<int, 4>();
  arr.fill(3);
  ASSERT_EQ(arr.at(2), 3);
}

TEST(s_array_test, at2) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  EXPECT_ANY_THROW(arr.at(10));
}

TEST(s_array_test, at3) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  EXPECT_ANY_THROW(arr.at(-10));
}

TEST(s_array_test, at4) {
  s21::array<int, 0> arr = s21::array<int, 0>();
  EXPECT_ANY_THROW(arr.at(0));
}

TEST(s_array_test, at5) {
  s21::array<int, 3> arr{0, 1, 2};
  std::array<int, 3> ctrl{0, 1, 2};
  ASSERT_EQ(arr.at(1), ctrl.at(1));
  ASSERT_EQ(arr.at(0), ctrl.at(0));
}

TEST(s_array_test, square_operator1) {
  s21::array<int, 4> arr = s21::array<int, 4>();
  arr.fill(3);
  ASSERT_EQ(arr[2], 3);
}

TEST(s_array_test, square_operator2) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  EXPECT_NO_THROW(arr[10]);
}

TEST(s_array_test, square_operator3) {
  s21::array<int, 10> arr{01, 2, 13, 4, 05, 1, 99, 06, 1, 8};
  std::array<int, 10> ctrl{01, 2, 13, 5, 05, 1, 99, 6, 01, 8};
  ASSERT_EQ(arr[5], ctrl[5]);
  ASSERT_EQ(arr[9], ctrl[9]);
}

TEST(s_array_test, empty1) {
  s21::array<int, 3> arr{1, 2, 3};
  std::array<int, 3> ctrl{1, 2, 3};
  ASSERT_EQ(arr.empty(), ctrl.empty());
}

TEST(s_array_test, empty2) {
  s21::array<int, 0> arr;
  std::array<int, 0> ctrl;
  ASSERT_EQ(arr.empty(), ctrl.empty());

  s21::array<int, 4> arr2 = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr2.empty(), false);
}

TEST(s_array_test, front1) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr.front(), 1);

  s21::array<int, 3> arr2{1, 2, 3};
  std::array<int, 3> ctrl{1, 2, 3};
  ASSERT_EQ(arr2.front(), ctrl.front());

  arr2[0] = 999;
  ctrl[0] = 999;
  ASSERT_EQ(arr2.front(), ctrl.front());
}

TEST(s_array_test, back) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr.back(), 4);
}

TEST(s_array_test, data) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  auto dt = arr.data();
  ASSERT_EQ(dt[0], 1);

  s21::array<int, 1> arr2{6};
  s21::array<int, 1>::iterator iter = arr2.data();
  ASSERT_EQ(*iter, 6);
  ASSERT_EQ(iter, arr2.begin());
}

TEST(s_array_test, begin) {
  s21::array<int, 4> arr = s21::array<int, 4>({01, 02, 03, 04});
  auto dt = arr.begin();
  ASSERT_EQ(*dt, 1);
}

TEST(s_array_test, end) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  auto dt = arr.end();
  ASSERT_EQ(*dt, 4);
}

TEST(s_array_test, begin_end) {
  s21::array<int, 0> arr;
  s21::array<int, 0>::iterator iter = arr.begin();
  ASSERT_EQ(iter, arr.end());
}

TEST(s_array_test, size) {
  s21::array<int, 3> arr{1456, 772, 30};
  std::array<int, 3> ctrl{1, 2, 3};
  ASSERT_EQ(arr.size(), ctrl.size());
}

TEST(s_array_test, max_size) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr.max_size(), 4);
}

TEST(s_array_test, fill) {
  s21::array<int, 9> arr;
  arr.fill(144);
  std::array<int, 9> ctrl;
  ctrl.fill(144);
  ASSERT_TRUE(arraycheck(arr, ctrl));
}

TEST(s_array_test, swap) {
  s21::array<int, 4> arr = s21::array<int, 4>({0, 1, 2, 3});
  s21::array<int, 4> arr2 = s21::array<int, 4>();
  arr2.fill(7);
  arr.swap(arr2);
  ASSERT_EQ(*arr.begin(), 7);
}

TEST(set_test, constr1_unique) {
  s21::set<int> s1 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  std::set<int> s2 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, constr1_unique_string) {
  s21::set<const char*> s1 = {"первый", "двадцать четыре"};
  std::set<const char*> s2 = {"первый", "двадцать четыре"};
  auto it1 = s1.begin();
  EXPECT_EQ(s1.size(), s2.size());
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, constr2_duplicate) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, constr_copy) {
  s21::set<int> s3 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  s21::set<int> s1(s3);
  auto it1 = s1.begin();
  EXPECT_EQ(s1.size(), s2.size());
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, constr_move) {
  s21::set<int> s3 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  s21::set<int> s1(std::move(s3));

  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};

  auto it1(s1.begin());
  auto it2(s2.begin());

  EXPECT_EQ(s1.size(), s2.size());
  while (it1 != s1.end() && it2 != s2.end()) EXPECT_EQ(*it1++, *it2++);
}

TEST(set_test, operator_assaignment_copy) {
  s21::set<int> s3 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  s21::set<int> s1;
  s1 = s3;
  auto it1 = s1.begin();
  EXPECT_EQ(s1.size(), s2.size());
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, operator_assaignment_copy_empty) {
  s21::set<int> s3 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::set<int> s2;
  s21::set<int> s1;
  s3 = s1;
  auto it1 = s3.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, operator_assaignment_copy_self) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  // s21::set<int> s1;
  s1 = s1;
  s2 = s2;
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, operator_assaignment_move) {
  s21::set<int> s3 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  s21::set<int> s1;
  s1 = std::move(s3);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, operator_assaignment_move_self) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  s1 = std::move(s1);
  s2 = std::move(s2);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, begin) {
  s21::set<int> s1 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  auto it1 = s1.begin();
  EXPECT_EQ(*it1, 2);
}

TEST(set_test, empty_false) {
  s21::set<int> s1 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  std::set<int> s2 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, empty_true) {
  s21::set<int> s1;
  std::set<int> s2;
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, size) {
  s21::set<int> s1 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  std::set<int> s2 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, max_size) {
  s21::set<int> s1 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  std::set<int> s2 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  EXPECT_EQ(s1.max_size(), s2.max_size());
}

TEST(set_test, clear) {
  s21::set<int> s1 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  std::set<int> s2;
  s1.clear();
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, insert) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9};
  std::set<int> s2 = {0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  s1.insert(0);
  s1.insert(10);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, swap) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9};
  s21::set<int> s3 = {5, 6, 6};
  std::set<int> s4 = {5, 6, 6};
  s1.swap(s3);
  auto it1 = s1.begin();
  for (auto it4 = s4.begin(); it4 != s4.end(); ++it1, ++it4)
    EXPECT_EQ(*it1, *it4);
  auto it3 = s3.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it3, ++it2)
    EXPECT_EQ(*it3, *it2);
}

TEST(set_test, erase) {
  s21::set<int> s1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s1.erase(s1.begin());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, erase_find_min) {
  s21::set<int> s1 = {24, 5, 1, 15, 3, 8};
  std::set<int> s2 = {24, 5, 1, 15, 3, 8};
  auto fit1 = s1.find(5);
  auto fit2 = s2.find(5);
  s1.erase(fit1);
  s2.erase(fit2);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, merge_unique) {
  s21::set<int> s1 = {1, 2, 3, 4};
  std::set<int> s2 = {1, 2, 3, 4};
  s21::set<int> s3 = {5, 6, 6, 7, 8, 9};
  std::set<int> s4 = {5, 6, 6, 7, 8, 9};
  s1.merge(s3);
  s2.merge(s4);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  auto it3 = s3.begin();
  for (auto it4 = s4.begin(); it4 != s4.end(); ++it3, ++it4)
    EXPECT_EQ(*it3, *it4);
}

TEST(set_test, merge_duplicate) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};
  std::set<int> s2 = {1, 2, 3, 4, 5};
  s21::set<int> s3 = {5, 6, 7, 8, 9};
  std::set<int> s4 = {5, 6, 7, 8, 9};
  s1.merge(s3);
  s2.merge(s4);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  auto it3 = s3.begin();
  for (auto it4 = s4.begin(); it4 != s4.end(); ++it3, ++it4)
    EXPECT_EQ(*it3, *it4);
}

TEST(set_test, find1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(*(s1.find(3)), *(s2.find(3)));
}

TEST(set_test, find2) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  auto it1 = s1.find(2);
  auto it2 = s1.begin();
  it2++;
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, contains) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_FALSE(s1.contains(10));
  ASSERT_TRUE(s1.contains(3));
}

//---------------------------------------------------------
TEST(multiset_test, constr1) {
  s21::multiset<int> s1;
  std::multiset<int> s2;
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, constr1_string) {
  s21::multiset<const char*> s1 = {"первый", "двадцать четыре",
                                   "двадцать четыре"};
  std::multiset<const char*> s2 = {"первый", "двадцать четыре",
                                   "двадцать четыре"};
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, constr2) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, constr_copy) {
  s21::multiset<int> s3 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  s21::multiset<int> s1(s3);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, constr_move) {
  s21::multiset<int> s3 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  s21::multiset<int> s1(std::move(s3));
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, operator_assaignment_copy) {
  s21::multiset<int> s3 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  s21::multiset<int> s1;
  s1 = s3;
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, operator_assaignment_move) {
  s21::multiset<int> s3 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  s21::multiset<int> s1;
  s1 = std::move(s3);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, begin) {
  s21::multiset<int> s1 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  auto it1 = s1.begin();
  EXPECT_EQ(*it1, 2);
}

TEST(multiset_test, empty_false) {
  s21::multiset<int> s1 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  std::multiset<int> s2 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(multiset_test, empty_true) {
  s21::multiset<int> s1;
  std::multiset<int> s2;
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(multiset_test, size) {
  s21::multiset<int> s1 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  std::multiset<int> s2 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(multiset_test, max_size) {
  s21::multiset<int> s1 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  std::multiset<int> s2 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  EXPECT_EQ(s1.max_size(), s2.max_size());
}

TEST(multiset_test, clear) {
  s21::multiset<int> s1 = {24, 5, 6, 2, 7, 33, 8, 9, 10};
  std::multiset<int> s2;
  s1.clear();
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, insert) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9};
  std::multiset<int> s2 = {0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10};
  s1.insert(0);
  s1.insert(10);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, swap) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9};
  s21::multiset<int> s3 = {5, 6, 6};
  std::multiset<int> s4 = {5, 6, 6};
  s1.swap(s3);
  auto it1 = s1.begin();
  for (auto it4 = s4.begin(); it4 != s4.end(); ++it1, ++it4)
    EXPECT_EQ(*it1, *it4);
  auto it3 = s3.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it3, ++it2)
    EXPECT_EQ(*it3, *it2);
}

TEST(multiset_test, erase_unique) {
  s21::multiset<int> s1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s1.erase(s1.begin());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, erase_duplicate) {
  s21::multiset<int> s1 = {0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::multiset<int> s2 = {0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto search1 = s1.find(1);
  s1.erase(search1);
  auto search2 = s2.find(1);
  s2.erase(search2);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, erase_find_min) {
  s21::multiset<int> s1 = {24, 5, 1, 15, 3, 8};
  std::multiset<int> s2 = {24, 5, 1, 15, 3, 8};
  auto fit1 = s1.find(5);
  auto fit2 = s2.find(5);
  s1.erase(fit1);
  s2.erase(fit2);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, merge_unique) {
  s21::multiset<int> s1 = {1, 2, 3, 4};
  std::multiset<int> s2 = {1, 2, 3, 4};
  s21::multiset<int> s3 = {5, 6, 6, 7, 8, 9};
  std::multiset<int> s4 = {5, 6, 6, 7, 8, 9};
  s1.merge(s3);
  s2.merge(s4);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  auto it3 = s3.begin();
  for (auto it4 = s4.begin(); it4 != s4.end(); ++it3, ++it4)
    EXPECT_EQ(*it3, *it4);
}

TEST(multiset_test, merge_duplicate) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5};
  std::multiset<int> s2 = {1, 2, 3, 4, 5};
  s21::multiset<int> s3 = {5, 6, 7, 8, 9};
  std::multiset<int> s4 = {5, 6, 7, 8, 9};
  s1.merge(s3);
  s2.merge(s4);
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  auto it3 = s3.begin();
  for (auto it4 = s4.begin(); it4 != s4.end(); ++it3, ++it4)
    EXPECT_EQ(*it3, *it4);
}

TEST(multiset_test, find1) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(*(s1.find(3)), *(s2.find(3)));
}

TEST(multiset_test, find2) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  auto it1 = s1.find(2);
  auto it2 = s1.begin();
  it2++;
  EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, contains) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_FALSE(s1.contains(10));
  ASSERT_TRUE(s1.contains(3));
}

TEST(multiset_test, count) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 6};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 6};
  auto count1 = s1.count(2);
  auto count2 = s2.count(2);
  EXPECT_EQ(count1, count2);
}

TEST(multiset_test, count_0) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 6};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 6};
  auto count1 = s1.count(11);
  auto count2 = s2.count(11);
  EXPECT_EQ(count1, count2);
}

TEST(multiset_test, equal_range) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 6};
  auto range_first1 = s1.equal_range(6).first;
  auto range_first2 = s1.find(6);
  EXPECT_EQ(range_first1, range_first2);
  auto range_second1 = s1.equal_range(6).second;
  auto range_second2 = s1.find(7);
  EXPECT_EQ(range_second1, range_second2);
}

TEST(multiset_test, equal_range_no_greater_then_key) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 6};
  auto range_first1 = s1.equal_range(6).first;
  auto range_first2 = s1.find(6);
  EXPECT_EQ(range_first1, range_first2);
  auto range_second1 = s1.equal_range(6).second;
  auto range_second2 = s1.end();
  EXPECT_EQ(range_second1, range_second2);
}

TEST(multiset_test, equal_range_no_less_then_key) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 6};
  auto range_first1 = s1.equal_range(0).first;
  auto range_first2 = s1.end();
  EXPECT_EQ(range_first1, range_first2);
  auto range_second1 = s1.equal_range(0).second;
  auto range_second2 = s1.end();
  EXPECT_EQ(range_second1, range_second2);
}

TEST(multiset_test, lower_bound) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 6};
  auto range_first1 = s1.equal_range(6).first;
  auto range_first2 = s1.lower_bound(6);
  EXPECT_EQ(range_first1, range_first2);
}

TEST(multiset_test, lower_bound_no_less) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 6};
  auto range_first1 = s1.end();
  auto range_first2 = s1.lower_bound(0);
  EXPECT_EQ(range_first1, range_first2);
}

TEST(multiset_test, upper_bound) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 6};
  auto range_second1 = s1.equal_range(6).second;
  auto range_second2 = s1.upper_bound(6);
  EXPECT_EQ(range_second1, range_second2);
}

TEST(multiset_test, upper_bound_no_greater) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 6, 7, 8, 6};
  auto range_second1 = s1.end();
  auto range_second2 = s1.upper_bound(11);
  EXPECT_EQ(range_second1, range_second2);
}

TEST(s_vector_test, castop) {
  s21::vector<int> vector{1, 3, 9, 12, 0, 12, 144};
  std::vector<int> vector_2{1, 3, 9, 12, 0, 12, 144};
  int& v1 = vector[4];
  int& v2 = vector_2[4];
  EXPECT_EQ(v1, v2);
  v1 = vector[6];
  v2 = vector_2[6];
  EXPECT_EQ(v1, v2);
  v1 = vector[0];
  v2 = vector_2[0];
  EXPECT_EQ(v1, v2);

  EXPECT_THROW(vector[7], std::exception);
}

TEST(s_vector_test, Front) {
  s21::vector<int> vector{9, 9, 0, 0, 1, 88, 042};
  std::vector<int> vector_2{9, 9, 0, 0, 1, 88, 042};
  EXPECT_EQ(vector.front(), vector_2.front());
}

TEST(s_vector_test, Back) {
  s21::vector<int> vector{1, 2, 3, 4, 5, 6, 7};
  std::vector<int> vector_2{1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(vector.back(), vector_2.back());
}

TEST(s_vector_test, Begin) {
  s21::vector<int> vector{1, 3, 4, 5, 6, 7};
  std::vector<int> vector_2{1, 3, 4, 5, 6, 7};
  s21::vector<int>::iterator v1 = vector.begin();
  std::vector<int>::iterator v2 = vector_2.begin();
  EXPECT_EQ(*v1, *v2);
}

TEST(s_vector_test, End) {
  s21::vector<int> vector{1, 2, 3, 4, 7};
  std::vector<int> vector_2{1, 2, 3, 4, 7};
  s21::vector<int>::iterator v1 = vector.end();
  std::vector<int>::iterator v2 = vector_2.end();
  EXPECT_EQ(*--v1, *--v2);
}

TEST(s_vector_test, iterator1) {
  s21::vector<int> vector{9, 9, 0, 0, 1, 88, 042};
  std::vector<int> vector_2{9, 9, 0, 0, 1, 88, 042};
  s21::vector<int>::iterator v1 = vector.begin();
  std::vector<int>::iterator v2 = vector_2.begin();
  EXPECT_EQ(*++v1, *++v2);
}

TEST(s_vector_test, iterator2) {
  s21::vector<int> vector{9, 9, 0, 0, 1, 88, 042};
  std::vector<int> vector_2{9, 9, 0, 0, 1, 88, 042};
  s21::vector<int>::iterator v1 = vector.end();
  std::vector<int>::iterator v2 = vector_2.end();
  EXPECT_EQ(*--v1, *--v2);
}

TEST(s_vector_test, iterator3) {
  s21::vector<int> vector{9, 9, 0, 0, 1, 88, 042};
  std::vector<int> vector_2{9, 9, 0, 0, 1, 88, 042};
  s21::vector<int>::iterator v1 = vector.begin();
  std::vector<int>::iterator v2 = vector_2.begin();
  EXPECT_TRUE(*v1 == *v2);
}

TEST(s_vector_test, Data) {
  s21::vector<int> vector{9, 9, 0, 0, 1, 88, 042};
  std::vector<int> vector_2{9, 9, 0, 0, 1, 88, 042};
  int* v1 = vector.data();
  int* v2 = vector_2.data();
  EXPECT_EQ(*v1, *v2);
}

TEST(s_vector_test, Empty) {
  s21::vector<int> vector{1, 2, 3, 4, 5, 6, 7};
  std::vector<int> vector_2{1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(vector.empty(), vector.empty());
}

TEST(s_vector_test, Size0) {
  s21::vector<int> vector{1, 2, 3, 4, 5, 6, 7};
  std::vector<int> vector_2{1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(vector.size(), vector.size());
  s21::vector<int> vec1;
  std::vector<int> vec2;
  EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(s_vector_test, max_size1) {
  s21::vector<int> vector{1, 2, 3, 4, 5, 7};
  std::vector<int> vector_2{1, 2, 3, 4, 5, 7};
  EXPECT_EQ(vector.max_size(), vector_2.max_size());
}

TEST(s_vector_test, max_size2) {
  s21::vector<int> test_int;
  std::vector<int> temp0_int;
  EXPECT_EQ(test_int.max_size(), temp0_int.max_size());
  s21::vector<double> test_double;
  std::vector<double> temp0_double;
  EXPECT_EQ(test_double.max_size(), temp0_double.max_size());
}

TEST(s_vector_test, Reserve) {
  s21::vector<int> vector{1, 2, 3, 4, 5, 6, 7};
  std::vector<int> vector_2{1, 2, 3, 4, 5, 6, 7};
  vector.reserve(14);
  vector_2.reserve(14);
  EXPECT_EQ(vector.capacity(), vector_2.capacity());

  EXPECT_THROW(vector.reserve(2), std::exception);
}

TEST(s_vector_test, cap) {
  s21::vector<int> vector{1, 0, 5, 8, 7, 3, 0};
  EXPECT_EQ(vector.capacity(), 8);
}

TEST(s_vector_test, shrink_to_fit) {
  s21::vector<int> vector{1, 2, 13, 4, 16, 7};
  std::vector<int> vector_2{1, 2, 13, 4, 16, 7};
  vector.reserve(14);
  vector_2.reserve(14);
  vector.shrink_to_fit();
  vector_2.shrink_to_fit();
  EXPECT_EQ(vector.capacity(), vector_2.capacity());
}

TEST(s_vector_test, clear) {
  s21::vector<int> vector{0, 2, 3, 4, 5, 6, 7};
  std::vector<int> vector_2{0, 2, 3, 4, 5, 6, 7};
  vector.clear();
  vector_2.clear();
  EXPECT_EQ(vector.capacity(), 8);
  EXPECT_EQ(vector.size(), vector_2.size());
}

TEST(s_vector_test, insert1) {
  s21::vector<int> vector;
  std::vector<int> vector_2;
  vector.push_back(2);
  vector.push_back(12);
  vector.push_back(3);
  vector.push_back(14);
  vector_2.push_back(2);
  vector_2.push_back(12);
  vector_2.push_back(3);
  vector_2.push_back(14);

  s21::vector<int>::iterator v1 = vector.begin();
  std::vector<int>::iterator v2 = vector_2.begin();

  v1 = vector.insert(v1, 1);
  v2 = vector_2.insert(v2, 1);
  EXPECT_EQ(*v1, *v2);
}

TEST(s_vector_test, insert2) {
  s21::vector<int> vector;
  std::vector<int> vector_2;
  vector.push_back(2);
  vector.push_back(23);
  vector.push_back(3);
  vector.push_back(33);
  vector_2.push_back(2);
  vector_2.push_back(23);
  vector_2.push_back(3);
  vector_2.push_back(33);

  s21::vector<int>::iterator v1 = vector.begin();
  std::vector<int>::iterator v2 = vector_2.begin();

  v1 = vector.insert(v1 + 3, 1);
  v2 = vector_2.insert(v2 + 3, 1);
  EXPECT_EQ(*v1, *v2);
}

TEST(s_vector_test, Size) {
  s21::vector<int> vector(99);
  EXPECT_EQ(vector.capacity(), 99);
  EXPECT_THROW(s21::vector<int> vector(-2), std::exception);
}

TEST(s_vector_test, erase1) {
  s21::vector<int> vector;
  std::vector<int> vector_2;
  vector.push_back(2);
  vector.push_back(23);
  vector.push_back(3);
  vector.push_back(33);

  vector_2.push_back(2);
  vector_2.push_back(23);
  vector_2.push_back(3);
  vector_2.push_back(33);

  s21::vector<int>::iterator v1 = vector.begin();
  std::vector<int>::iterator v2 = vector_2.begin();

  vector.erase(v1);
  vector_2.erase(v2);
  EXPECT_EQ(vector[0], vector_2[0]);
}

TEST(s_vector_test, erase2) {
  s21::vector<int> vector;
  std::vector<int> vector_2;
  vector.push_back(2);
  vector.push_back(23);
  vector.push_back(3);
  vector.push_back(33);

  vector_2.push_back(2);
  vector_2.push_back(23);
  vector_2.push_back(3);
  vector_2.push_back(33);

  s21::vector<int>::iterator v = vector.begin();
  std::vector<int>::iterator c = vector_2.begin();

  vector.erase(v + 3);
  vector_2.erase(c + 3);
  EXPECT_EQ(vector[2], vector_2[2]);
}

TEST(s_vector_test, push_back) {
  s21::vector<int> vector;
  std::vector<int> vector2;
  vector.push_back(12);
  vector2.push_back(12);
  vector.push_back(22);
  vector2.push_back(22);
  vector.push_back(1);
  vector2.push_back(1);
  vector.push_back(39);
  vector2.push_back(39);

  for (size_t i{0}; i < vector.size(); ++i) {
    EXPECT_EQ(vector[i], vector2[i]);
  }
}

TEST(s_vector_test, popback) {
  s21::vector<int> vector1;
  std::vector<int> vector2;
  vector1.push_back(1);
  vector2.push_back(1);
  vector1.push_back(10);
  vector2.push_back(10);
  vector1.push_back(2);
  vector2.push_back(2);
  vector1.push_back(15);
  vector2.push_back(15);
  vector1.pop_back();
  vector2.pop_back();
  vector1.pop_back();
  vector2.pop_back();

  for (size_t i{0}; i < vector1.size(); ++i) {
    EXPECT_EQ(vector1[i], vector2[i]);
  }
}

TEST(s_vector_test, move) {
  s21::vector<int> vector1{4, 4, 4};
  s21::vector<int> vector2(std::move(vector1));
  for (size_t i{0}; i < vector2.size(); ++i) {
    EXPECT_EQ(vector2[i], 4);
  }
}

TEST(s_vector_test, move_equal) {
  s21::vector<int> vector1{4, 4, 4};
  s21::vector<int> vector2;
  vector2 = std::move(vector1);
  for (size_t i{0}; i < vector2.size(); ++i) {
    EXPECT_EQ(vector2[i], 4);
  }
}

TEST(s_vector_test, access0) {
  s21::vector<int> test({1, 5, -6, 0, 256, 102});
  std::vector<int> temp0({1, 5, -6, 0, 256, 102});
  EXPECT_EQ(test.back(), temp0.back());
  EXPECT_EQ(test.front(), temp0.front());
  EXPECT_EQ(test.at(3), temp0.at(3));
  EXPECT_EQ(test[3], temp0[3]);
  EXPECT_ANY_THROW(test.at(12597));
  EXPECT_ANY_THROW(test.at(-124));
  int* test_begin = test.begin();
  int* test_end = test.end() - 1;
  int* test_dat = test.data();
  auto temp0_begin = temp0.begin();
  auto temp0_end = temp0.end() - 1;
  auto temp0_dat = temp0.data();
  EXPECT_EQ(*test_begin, *temp0_begin);
  EXPECT_EQ(*test_end, *temp0_end);
  test_dat++;
  temp0_dat++;
  EXPECT_EQ(*test_dat, *temp0_dat);
}

TEST(s_vector_test, Swap) {
  s21::vector<int> vector1{4, 4, 4};
  s21::vector<int> vector2{0, 1, 0};
  std::vector<int> control1{4, 4, 4};
  std::vector<int> control2{0, 1, 0};
  vector1.swap(vector2);
  control1.swap(control2);
  for (size_t i{0}; i < vector1.size(); ++i) {
    EXPECT_EQ(vector1[i], control1[i]);
    EXPECT_EQ(vector2[i], control2[i]);
  }
}

TEST(set_test_part3, insert_many1_in_empty) {
  s21::set<int> a;
  auto v = a.insert_many(4, 5);
  vector<std::pair<s21::set<int>::iterator, bool>> v2;
  v2.push_back(std::make_pair(a.begin(), true));
  v2.push_back(std::make_pair(a.find(5), true));
  auto it2 = v2.begin();
  for (auto it = v.begin(); it != v.end(); ++it, ++it2) EXPECT_EQ(*it, *it2);
  EXPECT_EQ(v.size(), v2.size());
}

TEST(set_test_part3, insert_many2) {
  s21::set<int> a{1};
  auto v = a.insert_many(4, 5);
  vector<std::pair<s21::set<int>::iterator, bool>> v2;
  v2.push_back(std::make_pair(a.find(4), true));
  v2.push_back(std::make_pair(a.find(5), true));
  auto it2 = v2.begin();
  for (auto it = v.begin(); it != v.end(); ++it, ++it2) EXPECT_EQ(*it, *it2);
  EXPECT_EQ(v.size(), v2.size());
}

TEST(set_test_part3, insert_many3_null) {
  s21::set<int> a{1};
  auto v = a.insert_many();
  vector<std::pair<s21::set<int>::iterator, bool>> v2;
  auto it2 = v2.begin();
  for (auto it = v.begin(); it != v.end(); ++it, ++it2) EXPECT_EQ(*it, *it2);
  EXPECT_EQ(v.size(), v2.size());
}

TEST(set_test_part3, insert_many4_duplicate) {
  s21::set<int> a{1};
  auto v = a.insert_many(1, 2);
  vector<std::pair<s21::set<int>::iterator, bool>> v2;
  v2.push_back(std::make_pair(a.end(), false));
  v2.push_back(std::make_pair(a.find(2), true));
  auto it2 = v2.begin();
  for (auto it = v.begin(); it != v.end(); ++it, ++it2) EXPECT_EQ(*it, *it2);
  EXPECT_EQ(v.size(), v2.size());
}

//---------------------------------------------------------

TEST(multiset_test_part3, insert_many1_in_empty) {
  s21::multiset<int> a;
  auto v = a.insert_many(4, 5);
  vector<std::pair<s21::multiset<int>::iterator, bool>> v2;
  v2.push_back(std::make_pair(a.begin(), true));
  v2.push_back(std::make_pair(a.find(5), true));
  auto it2 = v2.begin();
  for (auto it = v.begin(); it != v.end(); ++it, ++it2) EXPECT_EQ(*it, *it2);
  EXPECT_EQ(v.size(), v2.size());
}

TEST(multiset_test_part3, insert_many2) {
  s21::multiset<int> a{1};
  auto v = a.insert_many(4, 5);
  vector<std::pair<s21::multiset<int>::iterator, bool>> v2;
  v2.push_back(std::make_pair(a.find(4), true));
  v2.push_back(std::make_pair(a.find(5), true));
  auto it2 = v2.begin();
  for (auto it = v.begin(); it != v.end(); ++it, ++it2) EXPECT_EQ(*it, *it2);
  EXPECT_EQ(v.size(), v2.size());
}

TEST(multiset_test_part3, insert_many3_null) {
  s21::multiset<int> a{1};
  auto v = a.insert_many();
  vector<std::pair<s21::multiset<int>::iterator, bool>> v2;
  auto it2 = v2.begin();
  for (auto it = v.begin(); it != v.end(); ++it, ++it2) EXPECT_EQ(*it, *it2);
  EXPECT_EQ(v.size(), v2.size());
}

TEST(multiset_test_part3, insert_many4_duplicate) {
  s21::multiset<int> a{1};
  auto v = a.insert_many(1, 2);
  vector<std::pair<s21::multiset<int>::iterator, bool>> v2;
  v2.push_back(std::make_pair(a.lower_bound(1), true));
  v2.push_back(std::make_pair(a.find(2), true));
  auto it2 = v2.begin();
  for (auto it = v.begin(); it != v.end(); ++it, ++it2) EXPECT_EQ(*it, *it2);
  EXPECT_EQ(v.size(), v2.size());
}

TEST(s_vector_test, push_many_back) {
  s21::vector<int> vector;
  std::vector<int> vector_2;
  vector.insert_many_back(0, 4);
  vector.insert_many_back(12);
  vector_2.emplace_back(0);
  vector_2.push_back(4);
  vector_2.push_back(12);

  s21::vector<int>::iterator v1 = vector.begin();
  std::vector<int>::iterator v2 = vector_2.begin();
  EXPECT_EQ(*v1, *v2);
  v1 = vector.end();
  v2 = vector_2.end();
  EXPECT_EQ(*v1, *v2);
}

TEST(s_vector_test, insert_many) {
  s21::vector<int> vec{1, 2, 3};
  s21::vector<int> vec1{1, 2, 3, 4, 5, 6};
  s21::vector<int> vec2{0, 30, 900};
  vec.insert_many(vec.begin() + 2, 1, 2, 3);
  vec1.insert_many(vec1.end(), 1, 2, 3);
  vec2.insert_many(vec2.begin() + 2, 1, 2, 3);
  ASSERT_EQ(vec.size(), 6);
  ASSERT_EQ(vec1.size(), 9);
  ASSERT_EQ(vec2.size(), 6);
  std::vector<int> vector_14{1, 2, 3, 4, 5};
  vector_14.emplace_back(0);
  ASSERT_EQ(vec2.size(), vector_14.size());
  s21::vector<int> vec4{11, 22, 33};
  std::vector<int> vec5{11, 22, 33};
  vec4.insert_many(vec4.begin() + 2, 1, 9);
  vec5.emplace(vec5.begin() + 2, 1);
  vec5.emplace(vec5.begin() + 3, 9);
  ASSERT_EQ(vec4[0], vec5[0]);
  ASSERT_EQ(vec4[3], vec5[3]);
  ASSERT_EQ(vec4[4], vec5[4]);
}

//---MAP_TESTS---
TEST(s_map, construcor) {
  s21::map<int, float> test1 = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  std::map<int, float> test2 = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  auto j = test2.begin();
  for (auto i = test1.begin(); i != test1.end(); ++i, ++j) {
    ASSERT_EQ((*i).first, (*j).first);
    ASSERT_EQ((*i).second, (*j).second);
  }
}

TEST(s_map, map_vector) {
  std::map<int, std::vector<int>> test1 = {
      {{1, {1, 2, 3}}, {6, {1, 2, 3}}, {3, {1, 2, 3}}}};
  s21::map<int, std::vector<int>> test2 = {
      {{1, {1, 2, 3}}, {6, {1, 2, 3}}, {3, {1, 2, 3}}}};
  auto j = test1.begin();
  for (auto i = test2.begin(); i != test2.end(); i++, j++) {
    EXPECT_EQ(i->first, j->first);
    for (int k = 0; k != 3; k++) {
      EXPECT_EQ(i->second[k], j->second[k]);
    }
  }
}

TEST(s_map, copy) {
  s21::map<int, float> test = {{1, 2.2}, {6, 2.2}, {3, 10.2}};
  s21::map<int, float> test1(test);
  auto j = test1.begin();
  for (auto i = test.begin(); i != test.end(); i++, j++) {
    EXPECT_EQ((*i), (*j));
  }
}

TEST(s_map, move) {
  s21::map<int, float> test = {{1, 2.2}, {6, 2.2}, {3, 10.2}};
  std::map<int, float> test_original = {{1, 2.2}, {6, 2.2}, {3, 10.2}};
  s21::map test_move(move(test));
  std::map test_move_original(move(test_original));
  EXPECT_EQ(test.size(), test_original.size());
  EXPECT_EQ(test_move.size(), test_move_original.size());
}

TEST(s_map, operator_move) {
  s21::map<char, char> test1 = {{'q', 'a'}, {'w', 's'}};
  std::map<char, char> test_original1 = {{'q', 'a'}, {'w', 's'}};
  std::map<char, char> test_original2;
  s21::map<char, char> test2;
  test2 = move(test1);
  test_original2 = move(test_original1);
  EXPECT_EQ(test1.size(), test_original1.size());
  EXPECT_EQ(test2.size(), test_original2.size());
}

TEST(s_map, operator_eq) {
  s21::map<int, float> test2 = {{1, 2.2}, {6, 2.2}, {3, 10.2}};
  s21::map<int, float> test1;
  test1 = test2;
  auto j = test1.begin();
  for (auto i = test2.begin(); i != test2.end(); i++, j++) {
    ASSERT_EQ((*i), (*j));
  }
}

TEST(s_map, at) {
  std::map<std::string, int> mymap = {
      {"hi", 1}, {"welcome", 2}, {"thanks", {3}}, {"bye", 4}};
  s21::map<std::string, int> test = {
      {"hi", 1}, {"welcome", 2}, {"thanks", {3}}, {"bye", 4}};
  EXPECT_EQ(mymap.at("bye"), test.at("bye"));
  EXPECT_ANY_THROW(test.at("be"));
}

TEST(s_map, operator) {
  s21::map<int, float> test = {{1, 2.2}, {6, 3.6}, {3, 10.2}};
  std::map<int, float> original = {{1, 2.2}, {6, 3.6}, {3, 10.2}};
  test[7];
  original[7];
  test[8] = 9.08;
  original[8] = 9.08;
  EXPECT_EQ(test[8], original[8]);
  auto j = original.begin();
  for (auto i = test.begin(); i != test.end(); i++, j++) {
    EXPECT_EQ(i->first, j->first);
    EXPECT_EQ(i->second, j->second);
  }
}

TEST(s_map, begin) {
  s21::map<int, float> test = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  std::map<int, float> test_orginal = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  auto start = test.begin();
  auto start_original = test_orginal.begin();
  EXPECT_EQ((*start).first, (*start_original).first);
  EXPECT_EQ((*start).second, (*start_original).second);
}

TEST(s_map, begin_plus_plus) {
  s21::map<int, float> test = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  std::map<int, float> test_orginal = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  auto start = test.begin();
  auto start_original = test_orginal.begin();
  start++;
  start_original++;
  EXPECT_EQ(start->first, start_original->first);
  EXPECT_EQ(start->second, start_original->second);
}

TEST(s_map, size_max_size) {
  s21::map<char, int> test = {{'q', 1}, {'w', 2}, {'e', 3}};
  std::map<char, int> origin = {{'q', 1}, {'w', 2}, {'e', 3}};
  EXPECT_EQ(test.size(), origin.size());
  EXPECT_EQ(test.max_size(), origin.max_size());
}

TEST(s_map, empty) {
  s21::map<int, int> test;
  std::map<int, int> origin;
  EXPECT_EQ(test.empty(), origin.empty());
  test[1] = 4;
  origin[1] = 4;
  test[2] = 3;
  origin[2] = 3;
  EXPECT_EQ(test.empty(), origin.empty());
}

TEST(s_map, clear) {
  s21::map<int, float> test = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  test.clear();
  EXPECT_EQ(test.size(), 0);
}

TEST(s_map, erase) {
  s21::map<int, float> test = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  s21::map<int, float> test1 = {{1, 2.2}, {6, 2.2}};
  auto it = test.begin();
  it++;
  test.erase(it);
  auto j = test1.begin();
  for (auto i = test.begin(); i != test.end(); i++, j++) {
    EXPECT_EQ((*i), (*j));
  }
}

TEST(s_map, swap) {
  s21::map<int, float> test = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  std::map<int, float> test_or = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  s21::map<int, float> test1 = {{1, 'q'}, {2, 'w'}, {4, 'e'}};
  std::map<int, float> test_or1 = {{1, 'q'}, {2, 'w'}, {4, 'e'}};
  test.swap(test1);
  test_or.swap(test_or1);
  auto j = test_or.begin();
  for (auto i = test.begin(); i != test.end(); i++, j++) {
    EXPECT_EQ(i->first, j->first);
    EXPECT_EQ(i->second, j->second);
  }
}

TEST(s_map, merge) {
  s21::map<int, float> test = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  std::map<int, float> test_or = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  s21::map<int, float> test1 = {{1, 'q'}, {2, 'w'}, {4, 'e'}};
  std::map<int, float> test_or1 = {{1, 'q'}, {2, 'w'}, {4, 'e'}};
  test_or.merge(test_or1);
  test.merge(test1);
  auto j = test_or.begin();
  for (auto i = test.begin(); i != test.end(); i++, j++) {
    EXPECT_EQ(i->first, j->first);
    EXPECT_EQ(i->second, j->second);
  }
}

TEST(s_map, contains) {
  s21::map<int, float> test = {{1, 2.2}, {6, 2.2}, {3, 0.2}};
  EXPECT_EQ(test.contains(6), 1);
  EXPECT_EQ(test.contains(2), 0);
}

TEST(s_map, insert) {
  std::map<int, int> test1 = {{{1, 2}, {6, 2}, {3, 0}}};
  s21::map<int, int> test2 = {{{1, 2}, {6, 2}, {3, 0}}};
  std::map<int, int> test3;
  auto it3 = test3.insert({1, 2});
  EXPECT_EQ(1, it3.second);
  auto i = test1.insert({9, 9});
  auto j = test2.insert(9, 9);
  EXPECT_EQ(i.second, j.second);
  auto i1 = test1.insert({1, 9});
  auto j1 = test2.insert(1, 9);
  EXPECT_EQ(i1.second, j1.second);
  auto k = test1.begin();
  for (auto l = test2.begin(); l != test2.end(); l++, k++) {
    EXPECT_EQ(k->first, l->first);
    EXPECT_EQ(k->second, l->second);
  }
}

TEST(s_map, insert_or_assign) {
  std::map<int, int> test1 = {{{1, 2}, {6, 2}, {3, 0}}};
  s21::map<int, int> test2 = {{{1, 2}, {6, 2}, {3, 0}}};
  std::map<int, int> test3;
  auto it3 = test3.insert({1, 2});
  EXPECT_EQ(1, it3.second);
  auto it1 = test1.insert_or_assign(10, 9);
  auto it2 = test2.insert_or_assign(10, 9);
  EXPECT_EQ(it1.first->first, it2.first->first);
  EXPECT_EQ(it1.first->second, it2.first->second);
  EXPECT_EQ(it1.second, it2.second);
  auto jt1 = test1.insert_or_assign(1, 9);
  auto jt2 = test2.insert_or_assign(1, 9);
  EXPECT_EQ(jt1.first->first, jt2.first->first);
  EXPECT_EQ(jt1.first->second, jt2.first->second);
  EXPECT_EQ(jt1.second, jt2.second);
  auto j = test2.begin();
  for (auto i = test1.begin(); i != test1.end(); i++, j++) {
    EXPECT_EQ(i->first, j->first);
    EXPECT_EQ(i->second, j->second);
  }
}

TEST(s_map, insert_many) {
  s21::map<int, int> test1 = {{4, 2}, {3, 4}, {1, 3}};
  s21::map<int, int> test2 = {{1, 3}};
  s21::map<int, int> test3;
  std::vector<std::pair<int, int>> vec2 = {std::pair(1, 3), std::pair(4, 2),
                                           std::pair(3, 4)};
  std::vector<std::pair<s21::map<int, int>::iterator, bool>> vec =
      test2.insert_many(std::pair(1, 6), std::pair(4, 2), std::pair(3, 4));
  test3.insert_many(std::pair(1, 3), std::pair(4, 2), std::pair(3, 4));
  auto it3 = test3.begin();
  auto j = test1.begin();
  for (auto i = test2.begin(); i != test2.end(); ++i, ++j, ++it3) {
    EXPECT_EQ(i->first, j->first);
    EXPECT_EQ(i->second, j->second);
    EXPECT_EQ(it3->first, j->first);
    EXPECT_EQ(it3->second, j->second);
  }
  auto k = vec2.begin();
  for (auto i = vec.begin(); i != vec.end(); ++i, ++k) {
    EXPECT_EQ(i->first->first, k->first);
    EXPECT_EQ(i->first->second, k->second);
  }
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
