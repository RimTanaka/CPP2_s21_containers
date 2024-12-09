#include "test.h"

TEST(MultiSetTest, InsertAndContains1) {
  s21::MultiSet<int> set = {1, 2, 2};
  EXPECT_TRUE(set.Contains(1));
  EXPECT_TRUE(set.Contains(2));
  EXPECT_FALSE(set.Contains(3));
}

// Наличие копий
TEST(MultiSetTest, InsertAndCount) {
  s21::MultiSet<int> mulSet;
  mulSet.Insert(10);
  mulSet.Insert(20);
  mulSet.Insert(20);
  mulSet.Insert(30);
  EXPECT_EQ(mulSet.Count(10), 1);
  EXPECT_EQ(mulSet.Count(20), 2);
  EXPECT_EQ(mulSet.Count(30), 1);
}

// Наличие в левом поддереве
TEST(MultiSetTest, InsertLeftChildTest) {
  s21::MultiSet<int> mulSet;
  mulSet.Insert(10);
  mulSet.Insert(5);
  EXPECT_EQ(mulSet.Count(5), 1);
  EXPECT_EQ(mulSet.Count(10), 1);
}

// Наличие в правом поддереве
TEST(MultiSetTest, InsertRightChildTest) {
  s21::MultiSet<int> mulSet;
  mulSet.Insert(5);
  mulSet.Insert(10);
  EXPECT_EQ(mulSet.Count(5), 1);
  EXPECT_EQ(mulSet.Count(10), 1);
}

TEST(MultiSetTest, InsertManyInt) {
  s21::MultiSet<int> set;
  auto results = set.InsertMany(10, 20, 30, 20);
  EXPECT_EQ(set.Size(), 4);
  results = set.InsertMany(10, 20, 30, 20);
  EXPECT_EQ(set.Size(), 8);
}

TEST(MultiSetTest, InsertManyChar) {
  s21::MultiSet<char> set;
  auto results = set.InsertMany('a', 'b', 'c');
  EXPECT_EQ(set.Size(), 3);
  results = set.InsertMany('a', 'b', 'c');
  EXPECT_EQ(set.Size(), 6);
}

// Удаление элементов
TEST(MultiSetTest, EraseElements) {
  s21::MultiSet<int> mulSet;
  mulSet.Insert(20);
  mulSet.Insert(20);
  mulSet.Insert(30);
  int erased_count = mulSet.Erase(20);
  EXPECT_EQ(erased_count, 2);
  EXPECT_EQ(mulSet.Count(20), 0);
  EXPECT_EQ(mulSet.Count(30), 1);
}

// Копирование множества
TEST(MultiSetTest, CopyOperator1) {
  s21::MultiSet<int> mulSet1;
  mulSet1.Insert(10);
  mulSet1.Insert(20);
  mulSet1.Insert(20);
  s21::MultiSet<int> mulSet2;
  mulSet2 = mulSet1;
  EXPECT_EQ(mulSet2.Count(10), 1);
  EXPECT_EQ(mulSet2.Count(20), 2);
}

// Копирование множества
TEST(MultiSetTest, CopyOperator2) {
  s21::MultiSet<int> mulSet1;
  mulSet1.Insert(10);
  mulSet1.Insert(20);
  mulSet1.Insert(20);
  s21::MultiSet<int> mulSet2(mulSet1);
  EXPECT_EQ(mulSet2.Count(10), 1);
  EXPECT_EQ(mulSet2.Count(20), 2);
}

// Перемещение множества
TEST(MultiSetTest, MoveAssignmentOperator1) {
  s21::MultiSet<int> mulSet1;
  mulSet1.Insert(10);
  mulSet1.Insert(20);
  s21::MultiSet<int> mulSet2 = std::move(mulSet1);
  EXPECT_EQ(mulSet2.Count(10), 1);
  EXPECT_EQ(mulSet2.Count(20), 1);
  EXPECT_EQ(mulSet1.Count(10), 0);
  EXPECT_EQ(mulSet1.Count(20), 0);
}

// Перемещение множества
TEST(MultiSetTest, MoveAssignmentOperator2) {
  s21::MultiSet<int> mulSet1;
  mulSet1.Insert(10);
  mulSet1.Insert(20);
  s21::MultiSet<int> mulSet2;
  mulSet2 = std::move(mulSet1);
  EXPECT_EQ(mulSet2.Count(10), 1);
  EXPECT_EQ(mulSet2.Count(20), 1);
  EXPECT_EQ(mulSet1.Count(10), 0);
  EXPECT_EQ(mulSet1.Count(20), 0);
}

// Поиск элемента
TEST(MultiSetTest, FindElement) {
  s21::MultiSet<int> mulSet;
  mulSet.Insert(10);
  mulSet.Insert(20);
  mulSet.Insert(30);
  auto it = mulSet.Find(20);
  EXPECT_EQ(*it, 20);
  it = mulSet.Find(40);
  EXPECT_EQ(it, mulSet.End());
}

// Тест на пустоту
TEST(MultiSetTest, IsEmpty) {
  s21::MultiSet<int> mulSet;
  EXPECT_TRUE(mulSet.Empty());
  mulSet.Insert(10);
  EXPECT_FALSE(mulSet.Empty());
}

TEST(MultiSetTest, ContainsTest) {
  s21::MultiSet<int> mulSet;
  mulSet.Insert(10);
  mulSet.Insert(20);
  mulSet.Insert(5);
  EXPECT_TRUE(mulSet.Contains(10));
  EXPECT_TRUE(mulSet.Contains(20));
  EXPECT_TRUE(mulSet.Contains(5));
  EXPECT_FALSE(mulSet.Contains(15));
}

TEST(MultiSetTest, InsertElementToLeft) {
  s21::MultiSet<int> ms;
  ms.Insert(10);
  ms.Insert(5);
  EXPECT_EQ(ms.Count(5), 1);
  EXPECT_EQ(ms.Count(10), 1);
}

TEST(MultiSetTest, InsertToLeftSubtree) {
  s21::MultiSet<int> ms;
  ms.Insert(10);
  ms.Insert(5);
  ms.Insert(3);
  EXPECT_EQ(ms.Count(5), 1);
  EXPECT_EQ(ms.Count(3), 1);
}

TEST(MultiSetTest, InsertRange) {
  s21::MultiSet<int> ms;
  std::vector<int> values = {10, 20, 30};
  ms.Insert(values.begin(), values.end());
  EXPECT_EQ(ms.Count(10), 1);
  EXPECT_EQ(ms.Count(20), 1);
  EXPECT_EQ(ms.Count(30), 1);
}

TEST(MultiSetTest, InsertInitializerList) {
  s21::MultiSet<int> ms;
  ms.Insert({10, 20, 30});
  EXPECT_EQ(ms.Count(10), 1);
  EXPECT_EQ(ms.Count(20), 1);
  EXPECT_EQ(ms.Count(30), 1);
}

// Тест для вставки в левое поддерево
TEST(MultiSetTest, InsertLeftSubtree1) {
  s21::MultiSet<int> ms;
  ms.Insert({10, 10});
  ms.Insert({5, 5});
  auto it = ms.Find(5);
  EXPECT_NE(it, ms.End());
  EXPECT_EQ(it->key, 5);
  EXPECT_EQ(it->value, 5);
}

TEST(MultiSetTest, InsertLeftSubtree2) {
  s21::MultiSet<int> ms;
  ms.Insert({10});
  ms.Insert({5});
}

// Тест для вставки в правое поддерево
TEST(MultiSetTest, InsertRightSubtree) {
  s21::MultiSet<int> ms;
  ms.Insert({10, 10});
  ms.Insert({15, 15});
  auto it = ms.Find(15);
  EXPECT_NE(it, ms.End());
  EXPECT_EQ(it->key, 15);
  EXPECT_EQ(it->value, 15);
}

// Тест для повторной вставки уже существующего ключа
TEST(MultiSetTest, InsertExistingKey) {
  s21::MultiSet<int> multiSet;
  multiSet.Insert(10);
  multiSet.Insert(15);
  auto result = multiSet.Insert(10);
  EXPECT_TRUE(result.second);
}

TEST(MultiSetTest, InitializerListConstructor) {
  s21::MultiSet<int> multiSet = {10, 20, 30};
  EXPECT_EQ(multiSet.Size(), 3);
  EXPECT_EQ(multiSet.Count(10), 1);
  EXPECT_EQ(multiSet.Count(20), 1);
  EXPECT_EQ(multiSet.Count(30), 1);
}
