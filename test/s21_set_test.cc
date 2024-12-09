#include "test.h"

TEST(SetTest, InsertAndContains1) {
  s21::Set<int> set = {1, 2, 2};
  EXPECT_TRUE(set.Contains(1));
  EXPECT_TRUE(set.Contains(2));
  EXPECT_FALSE(set.Contains(3));
}

TEST(SetTest, InsertAndContains2) {
  s21::Set<int> set;
  set.Insert(1);
  set.Insert(2);
  EXPECT_TRUE(set.Contains(1));
  EXPECT_TRUE(set.Contains(2));
  EXPECT_FALSE(set.Contains(3));
}

TEST(SetTest, InsertAndIgnore1) {
  s21::Set<int> set;
  set.Insert(1);
  set.Insert(2);
  auto a = set.Insert(2);
  EXPECT_TRUE(set.Contains(1));
  EXPECT_TRUE(set.Contains(2));
  EXPECT_FALSE(a.second);
}

TEST(SetTest, Clear) {
  s21::Set<int> set;
  set.Insert(1);
  set.Insert(2);
  set.Clear();
  EXPECT_EQ(set.Size(), 0);
  EXPECT_FALSE(set.Contains(1));
}

TEST(SetTest, CopyConstructor1) {
  s21::Set<int> set1;
  set1.Insert(1);
  set1.Insert(2);
  s21::Set<int> set2 = set1;
  EXPECT_TRUE(set2.Contains(1));
  EXPECT_TRUE(set2.Contains(2));
}

TEST(SetTest, CopyConstructor2) {
  s21::Set<int> set1;
  set1.Insert(1);
  set1.Insert(2);
  s21::Set<int> set2(set1);
  EXPECT_TRUE(set2.Contains(1));
  EXPECT_TRUE(set2.Contains(2));
}

TEST(SetTest, MoveConstructor1) {
  s21::Set<int> set1;
  set1.Insert(1);
  set1.Insert(2);
  s21::Set<int> set2 = std::move(set1);
  EXPECT_TRUE(set2.Contains(1));
  EXPECT_TRUE(set2.Contains(2));
  EXPECT_EQ(set1.Size(), 0);
}

TEST(SetTest, MoveConstructor2) {
  s21::Set<int> set1;
  set1.Insert(1);
  set1.Insert(2);
  s21::Set<int> set2(std::move(set1));
  EXPECT_TRUE(set2.Contains(1));
  EXPECT_TRUE(set2.Contains(2));
  EXPECT_EQ(set1.Size(), 0);
}

TEST(SetTest, InsertAndContains) {
  s21::Set<int> set;
  EXPECT_TRUE(set.Insert(1).second);
  EXPECT_TRUE(set.Insert(2).second);
  EXPECT_TRUE(set.Insert(3).second);

  EXPECT_TRUE(set.Contains(1));
  EXPECT_TRUE(set.Contains(2));
  EXPECT_TRUE(set.Contains(3));
  EXPECT_FALSE(set.Contains(4));
}

TEST(SetTest, InsertDuplicate) {
  s21::Set<int> set;
  EXPECT_TRUE(set.Insert(1).second);
  EXPECT_FALSE(set.Insert(1).second);  // Дублирование элемента
  EXPECT_TRUE(set.Contains(1));
}

TEST(SetTest, Erase) {
  s21::Set<int> set;
  set.Insert(1);
  set.Insert(2);
  set.Insert(3);

  set.Erase(2);
  EXPECT_FALSE(set.Contains(2));
  EXPECT_EQ(set.Size(), 2);

  set.Erase(3);
  EXPECT_FALSE(set.Contains(3));
  EXPECT_EQ(set.Size(), 1);
}

TEST(SetTest, IteratorTraversal) {
  s21::Set<int> set;
  set.Insert(1);
  set.Insert(2);
  set.Insert(3);

  auto it = set.Begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, set.End());
}

TEST(SetTest, IteratorTraversalAndEqSTD1) {
  std::set<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);

  s21::Set<int> ma;
  ma.Insert(1);
  ma.Insert(2);
  ma.Insert(3);

  auto it = ma.Begin();
  auto iter = set.begin();

  while (iter != set.end() && it != ma.End()) {
    EXPECT_EQ(*it, *iter);
    ++it;
    ++iter;
  }
}

TEST(SetTest, IteratorTraversalAndEqSTD2) {
  std::set<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);

  s21::Set<int> ma;
  ma.Insert(1);
  ma.Insert(2);
  ma.Insert(3);
  const s21::Set<int> a = ma;
  auto it = a.Begin();
  auto iter = set.begin();

  while (iter != set.end() && it != a.End()) {
    EXPECT_EQ(*it, *iter);
    ++it;
    ++iter;
  }
}

TEST(SetTest, EmptyAndClear) {
  s21::Set<int> set;
  EXPECT_TRUE(set.Empty());
  set.Insert(1);
  EXPECT_FALSE(set.Empty());

  set.Clear();
  EXPECT_TRUE(set.Empty());
  EXPECT_EQ(set.Size(), 0);
}

TEST(SetTest, FindIndexTest) {
  s21::Set<int> myset;
  myset.Insert(10);
  myset.Insert(20);
  myset.Insert(30);

  s21::Set<int>::Iterator it = myset.Find(20);
  ASSERT_TRUE(it != myset.End());
  myset.Erase(*it);

  it = myset.Find(20);
  ASSERT_TRUE(it == myset.End());
}

TEST(SetTest, ConstructorInsertMany1) {
  std::set<int> s{1, 2, 3, 4, 5};
  s21::Set<int> f{1, 2, 3, 4, 5};

  auto std_it = s.begin();
  auto s21_it = f.Begin();

  while (std_it != s.end() && s21_it != f.End()) {
    EXPECT_EQ(*std_it, *s21_it);
    ++std_it;
    ++s21_it;
  }
}

TEST(SetTest, ConstructorInsertMany2) {
  std::set<int> s{2, 1, 3, 4, 5};
  s21::Set<int> f{2, 1, 3, 4, 5};

  auto std_it = s.begin();
  auto s21_it = f.Begin();

  while (std_it != s.end() && s21_it != f.End()) {
    EXPECT_EQ(*std_it, *s21_it);
    ++std_it;
    ++s21_it;
  }
}

TEST(SetTest, InsertMany1) {
  std::set<int> s;
  s.insert({1, 2, 3, 4, 5});

  s21::Set<int> f;
  f.Insert({1, 2, 3, 4, 5});

  auto std_it = s.begin();
  auto s21_it = f.Begin();

  while (std_it != s.end() && s21_it != f.End()) {
    EXPECT_EQ(*std_it, *s21_it);
    ++std_it;
    ++s21_it;
  }
}

TEST(SetTest, InsertMany2) {
  std::set<int> s;
  s.insert({2, 1, 3, 4, 5});

  s21::Set<int> f;
  f.Insert({2, 1, 3, 4, 5});

  auto std_it = s.begin();
  auto s21_it = f.Begin();

  while (std_it != s.end() && s21_it != f.End()) {
    EXPECT_EQ(*std_it, *s21_it);
    ++std_it;
    ++s21_it;
  }
}

TEST(SetTest, InitializerListConstructor) {
  s21::Set<int> set = {5, 10, 15};
  EXPECT_EQ(set.Size(), 3);
  EXPECT_TRUE(set.Contains(5));
  EXPECT_TRUE(set.Contains(10));
  EXPECT_TRUE(set.Contains(15));
}

TEST(SetTest, InsertRange) {
  s21::Set<int> set;
  std::vector<int> values = {10, 20, 30};
  set.Insert(values.begin(), values.end());
  EXPECT_EQ(set.Size(), 3);
  EXPECT_TRUE(set.Contains(10));
  EXPECT_TRUE(set.Contains(20));
  EXPECT_TRUE(set.Contains(30));
  set.Insert(values.begin(), values.end());
  EXPECT_EQ(set.Size(), 3);
  std::vector<int> new_values = {40, 50};
  set.Insert(new_values.begin(), new_values.end());
  EXPECT_EQ(set.Size(), 5);
  EXPECT_TRUE(set.Contains(40));
  EXPECT_TRUE(set.Contains(50));
}

TEST(SetTest, InsertMany) {
  s21::Set<int> set;
  auto results = set.InsertMany(10, 20, 30);
  EXPECT_EQ(set.Size(), 3);
  EXPECT_TRUE(set.Contains(10));
  EXPECT_TRUE(set.Contains(20));
  EXPECT_TRUE(set.Contains(30));
  EXPECT_EQ(results.size(), 3);
  results = set.InsertMany(10, 20, 30);
  EXPECT_EQ(set.Size(), 3);
}

TEST(SetTest, InsertRangeWithNewElements) {
  s21::Set<int> set;
  std::vector<int> values = {1, 2, 3, 4};
  set.Insert(values.begin(), values.end());
  EXPECT_EQ(set.Size(), 4);
  std::vector<int> more_values = {5, 6};
  set.Insert(more_values.begin(), more_values.end());
  EXPECT_EQ(set.Size(), 6);
}
