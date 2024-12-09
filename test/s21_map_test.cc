#include "test.h"

TEST(MapTest, GetKey1) {
  s21::Map<std::string, int> map;
  map["bred"] = 30;
  EXPECT_EQ(map.At("bred"), 30);
}

TEST(MapTest, GetKey2) {
  s21::Map<std::string, int> map;
  map["bred"] = 30;
  map["bred"] = 40;
  EXPECT_EQ(map.At("bred"), 40);
}

TEST(MapTest, GetKey3) {
  s21::Map<std::string, int> map;
  map["bred"] = 30;
  EXPECT_EQ(map.At("bred"), 30);
}

TEST(MapTest, InsertAndAt) {
  s21::Map<std::string, int> map;
  auto inserted = map.Insert({"qwe", 1});
  EXPECT_TRUE(inserted.second);
  map.Insert({"asd", 2});
  EXPECT_EQ(map.At("qwe"), 1);
  EXPECT_EQ(map.At("asd"), 2);
}

TEST(MapTest, Contains) {
  s21::Map<std::string, int> map;
  map.Insert({"qwe", 1});
  EXPECT_TRUE(map.Contains("qwe"));
  EXPECT_FALSE(map.Contains("asd"));
}

TEST(MapTest, CopyConstructor1) {
  s21::Map<std::string, int> map1;
  map1.Insert({"qwe", 1});
  map1.Insert({"asd", 2});
  s21::Map<std::string, int> map2 = map1;
  EXPECT_EQ(map2.At({"qwe"}), 1);
  EXPECT_EQ(map2.At({"asd"}), 2);
}

TEST(MapTest, CopyConstructor2) {
  s21::Map<std::string, int> map1;
  map1.Insert({"qwe", 1});
  map1.Insert({"asd", 2});
  s21::Map<std::string, int> map2(map1);
  EXPECT_EQ(map2.At("qwe"), 1);
  EXPECT_EQ(map2.At("asd"), 2);
}

TEST(MapTest, CopyOperator1) {
  s21::Map<std::string, int> map1;
  map1.Insert({"qwe", 1});
  map1.Insert({"asd", 2});
  s21::Map<std::string, int> map2;
  map2 = map1;
  EXPECT_EQ(map2.At("qwe"), 1);
  EXPECT_EQ(map2.At("asd"), 2);
}

TEST(MapTest, MoveConstructor1) {
  s21::Map<std::string, int> map1;
  map1.Insert({"qwe", 1});
  map1.Insert({"asd", 2});
  s21::Map<std::string, int> map2 = std::move(map1);
  EXPECT_EQ(map2.At("qwe"), 1);
  EXPECT_EQ(map2.At("asd"), 2);
  EXPECT_EQ(map1.Size(), 0);
}

TEST(MapTest, MoveConstructor2) {
  s21::Map<std::string, int> map1;
  map1.Insert({"qwe", 1});
  map1.Insert({"asd", 2});
  s21::Map<std::string, int> map2(std::move(map1));
  EXPECT_EQ(map2.At("qwe"), 1);
  EXPECT_EQ(map2.At("asd"), 2);
  EXPECT_EQ(map1.Size(), 0);
}

TEST(MapTest, MoveOperator1) {
  s21::Map<std::string, int> map1;
  map1.Insert({"qwe", 1});
  map1.Insert({"asd", 2});
  s21::Map<std::string, int> map2;
  map2 = std::move(map1);
  EXPECT_EQ(map2.At("qwe"), 1);
  EXPECT_EQ(map2.At("asd"), 2);
}

TEST(MapTest, Clear) {
  s21::Map<std::string, int> map;
  map.Insert({"qwe", 1});
  map.Insert({"asd", 2});
  map.Clear();
  EXPECT_EQ(map.Size(), 0);
  EXPECT_FALSE(map.Contains("qwe"));
}

TEST(MapTest, InsertAndFind) {
  s21::Map<int, std::string> map;
  EXPECT_TRUE(map.Insert({1, "one"}).second);
  EXPECT_TRUE(map.Insert({2, "two"}).second);
  EXPECT_TRUE(map.Insert({3, "three"}).second);
  EXPECT_EQ(map.At(1), "one");
  EXPECT_EQ(map.At(2), "two");
  EXPECT_EQ(map.At(3), "three");
  EXPECT_THROW(map.At(4), std::out_of_range);
}

TEST(MapTest, InsertDuplicateKey) {
  s21::Map<int, std::string> map;
  EXPECT_TRUE(map.Insert({1, "one"}).second);
  EXPECT_FALSE(map.Insert({1, "duplicate"}).second);
  EXPECT_EQ(map.At(1), "one");
}

TEST(MapTest, ResertDuplicateKey) {
  s21::Map<int, std::string> map;
  EXPECT_TRUE(map.Insert({1, "one"}).second);
  map[1] = "duplicate";
  EXPECT_EQ(map.At(1), "duplicate");
}

TEST(MapTest, OperatorSquareBrackets) {
  s21::Map<int, std::string> map;
  map[1] = "one";
  EXPECT_EQ(map[1], "one");
  map[1] = "new_one";
  EXPECT_EQ(map[1], "new_one");
  map[2] = "two";  // Добавление через оператор []
  EXPECT_EQ(map[2], "two");
}

TEST(MapTest, EraseDuplicates) {
  s21::Map<int, std::string> map;
  map.Insert({5, "value5"});
  map.Insert({5, "duplicate1"});
  map.Insert({5, "duplicate2"});

  EXPECT_EQ(map.Erase(5), 1);
  EXPECT_FALSE(map.Contains(5));
  EXPECT_EQ(map.Size(), 0);
}

TEST(MapTest, Erase) {
  s21::Map<int, std::string> map;
  map.Insert({1, "one"});
  map.Insert({2, "two"});
  map.Erase(1);
  EXPECT_FALSE(map.Contains(1));
  EXPECT_EQ(map.Size(), 1);
  EXPECT_THROW(map.At(1), std::out_of_range);
}

TEST(MapTest, EraseExistingKey) {
  s21::Map<int, std::string> map;
  map.Insert({1, "one"});
  map.Insert({2, "two"});
  EXPECT_EQ(map.Size(), 2);
  map.Erase(1);
  EXPECT_FALSE(map.Contains(1));
  EXPECT_EQ(map.Size(), 1);
  EXPECT_EQ(map.At(2), "two");
}

TEST(MapTest, EraseNonExistingKey) {
  s21::Map<int, std::string> map;
  EXPECT_EQ(map.Erase(3), 0);
}

TEST(MapTest, EraseLastKey) {
  s21::Map<int, std::string> map;
  map.Insert({1, "one"});
  EXPECT_EQ(map.Size(), 1);
  map.Erase(1);
  EXPECT_EQ(map.Size(), 0);
  EXPECT_THROW(map.At(1), std::out_of_range);
}

TEST(MapTest, EraseFromEmptyMap) {
  s21::Map<int, std::string> map;
  EXPECT_NO_THROW(map.Erase(1));
  EXPECT_EQ(map.Size(), 0);
}

TEST(MapTest, ConstEraseFromEmptyMap) {
  const s21::Map<int, std::string> map;
  EXPECT_TRUE(map.Empty());
}

// Удаление узла без левого дочернего узла
TEST(MapTest, EraseNodeWithoutLeftChild) {
  s21::Map<int, std::string> map;
  map.Insert({5, "value5"});
  map.Insert({3, "value3"});
  map.Insert({8, "value8"});
  map.Insert({7, "value7"});
  map.Insert({6, "value6"});
  EXPECT_EQ(map.Erase(8), 1);
  EXPECT_EQ(map.Size(), 4);
}

// Удаление узла без правого дочернего узла
TEST(MapTest, EraseNodeWithoutRightChild) {
  s21::Map<int, std::string> map;
  map[5] = "value5";
  map[3] = "value3";
  map[8] = "value8";
  map[7] = "value7";
  map[6] = "value6";
  EXPECT_EQ(map.Erase(3), 1);
  EXPECT_EQ(map.Size(), 4);
}

// Удаление узла с двумя дочерними узлами
TEST(MapTest, EraseNodeWithTwoChildren) {
  s21::Map<int, std::string> map;
  map.Insert({5, "value5"});
  map.Insert({3, "value3"});
  map.Insert({8, "value8"});
  map.Insert({7, "value7"});
  map.Insert({6, "value6"});
  EXPECT_EQ(map.Erase(5), 1);
  EXPECT_EQ(map.Size(), 4);
}

// Удаление несуществующего узла
TEST(MapTest, EraseNonExistentNode) {
  s21::Map<int, std::string> map;
  map.Insert({5, "value5"});
  map.Insert({3, "value3"});
  map.Insert({8, "value8"});
  map.Insert({7, "value7"});
  map.Insert({6, "value6"});
  EXPECT_EQ(map.Erase(100), 0);
  EXPECT_EQ(map.Size(), 5);
}

TEST(MapTest, ConstIteratorTraversal1) {
  s21::Map<int, std::string> map;
  map.Insert({1, "one"});
  map.Insert({2, "two"});
  map.Insert({3, "three"});
  const s21::Map<int, std::string> map1 = map;
  auto it = map1.Begin();
  EXPECT_EQ(it->key, 1);
  ++it;
  EXPECT_EQ(it->key, 2);
  ++it;
  EXPECT_EQ(it->key, 3);
  ++it;
  EXPECT_EQ(it, map1.End());
}

TEST(MapTest, IteratorTraversal1) {
  s21::Map<int, std::string> map;
  map.Insert({1, "one"});
  map.Insert({2, "two"});
  map.Insert({3, "three"});
  auto it = map.Begin();
  EXPECT_EQ(it->key, 1);
  ++it;
  EXPECT_EQ(it->key, 2);
  ++it;
  EXPECT_EQ(it->key, 3);
  ++it;
  EXPECT_EQ(it, map.End());
}

TEST(MapTest, IteratorTraversalWithoutEnd1) {
  s21::Map<int, std::string> map;
  map.Insert({1, "one"});
  map.Insert({2, "two"});
  map.Insert({3, "three"});
  auto it = map.Find(3);
  --it;
  EXPECT_EQ(it->key, 2);
}

TEST(MapTest, IteratorTraversalWithoutEnd2) {
  s21::Map<int, std::string> map;
  map.Insert({3, "one"});
  map.Insert({2, "two"});
  map.Insert({1, "three"});
  auto it = map.Find(3);
  --it;
  EXPECT_EQ(it->key, 2);
}

TEST(MapTest, IteratorTraversalWithoutEnd3) {
  s21::Map<int, std::string> map;
  map.Insert({2, "two"});
  map.Insert({3, "three"});
  map.Insert({1, "one"});
  auto it = map.Find(3);
  --it;
  EXPECT_EQ(it->key, 2);
}

TEST(MapTest, InsertSingleElement) {
  s21::Map<std::string, int> map;
  auto result = map.Insert({"key1", 10});
  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first->value, 10);
}

TEST(MapTest, InsertMoveElement) {
  s21::Map<std::string, int> map;
  std::pair<std::string, int> elem("key1", 20);
  auto result = map.Insert(std::move(elem));
  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first->value, 20);
}

TEST(MapTest, InsertInitializerList) {
  s21::Map<std::string, int> map;
  map.Insert({{"key1", 50}, {"key2", 60}, {"key3", 70}});
  EXPECT_EQ(map.At("key1"), 50);
  EXPECT_EQ(map.At("key2"), 60);
  EXPECT_EQ(map.At("key3"), 70);
}

TEST(MapTest, InsertRange) {
  s21::Map<std::string, int> map;
  std::vector<std::pair<std::string, int>> vec = {{"key1", 80}, {"key2", 90}};
  map.Insert(vec.begin(), vec.end());
  EXPECT_EQ(map.At("key1"), 80);
  EXPECT_EQ(map.At("key2"), 90);
}

TEST(MapTest, InsertManyElements) {
  s21::Map<std::string, int> map;
  map.InsertMany(std::make_pair("key1", 100), std::make_pair("key2", 110));
  EXPECT_EQ(map["key1"], 100);
  EXPECT_EQ(map["key2"], 110);
}

TEST(MapTest, InsertManyUniqueKeys) {
  s21::Map<int, std::string> map;
  auto results = map.InsertMany(std::pair<int, std::string>(1, "one"),
                                std::pair<int, std::string>(2, "two"),
                                std::pair<int, std::string>(3, "three"));
  EXPECT_EQ(results.size(), 3);
}

TEST(MapTest, InsertMany1) {
  s21::Map<int, int> map;

  auto results = map.InsertMany(std::make_pair(1, 10), std::make_pair(2, 20),
                                std::make_pair(3, 30));
  EXPECT_EQ(results.size(), 3);
}

TEST(MapTest, InsertMany2) {
  s21::Map<int, std::string> map;
  auto inserted_elements =
      map.InsertMany(std::make_pair(10, "ten"), std::make_pair(11, "eleven"),
                     std::make_pair(12, "twelve"));
  EXPECT_EQ(inserted_elements.size(), 3);
  EXPECT_TRUE(map.Contains(10));
  EXPECT_TRUE(map.Contains(11));
  EXPECT_TRUE(map.Contains(12));
}

TEST(MapTest, InsertMany3) {
  s21::Map<int, std::string> map;
  auto inserted_elements =
      map.InsertMany(std::make_pair(11, "ten"), std::make_pair(10, "eleven"),
                     std::make_pair(12, "twelve"));
  EXPECT_EQ(inserted_elements.size(), 3);
  EXPECT_TRUE(map.Contains(11));
  EXPECT_TRUE(map.Contains(10));
  EXPECT_TRUE(map.Contains(12));
}

TEST(MapTest, InsertMany4) {
  s21::Map<int, std::string> map;
  auto inserted_elements =
      map.InsertMany(std::make_pair(12, "ten"), std::make_pair(11, "eleven"),
                     std::make_pair(10, "twelve"));
  EXPECT_EQ(inserted_elements.size(), 3);
  EXPECT_TRUE(map.Contains(12));
  EXPECT_TRUE(map.Contains(11));
  EXPECT_TRUE(map.Contains(10));
}

TEST(MapTest, InsertMany6) {
  s21::Map<int, int> map;
  auto results = map.InsertMany(std::make_pair(1, 1), std::make_pair(2, 2),
                                std::make_pair(3, 3));
  EXPECT_EQ(map.Size(), 3);
  for (const auto &result : results) {
    EXPECT_TRUE(result.second);
  }
}

TEST(MapTest, InsertManyMixValuesAndReferences) {
  s21::Map<int, std::string> map;
  int x = 7;
  auto inserted_elements = map.InsertMany(
      std::make_pair(std::ref(x), "seven"), std::make_pair(5, "five"),
      std::make_pair(3.5, "three point five"));

  EXPECT_EQ(inserted_elements.size(), 3);
  EXPECT_TRUE(map.Contains(7));
  EXPECT_TRUE(map.Contains(5));
  EXPECT_TRUE(map.Contains(3.5));
}

TEST(MapTest, InsertManyStrings) {
  s21::Map<int, std::string> map;
  std::string hello = "Hello";
  auto inserted_elements =
      map.InsertMany(std::make_pair(1, hello), std::make_pair(2, "World"),
                     std::make_pair(3, "Test"));

  EXPECT_EQ(inserted_elements.size(), 3);
  EXPECT_TRUE(map.Contains(1));
  EXPECT_TRUE(map.Contains(2));
  EXPECT_TRUE(map.Contains(3));
  EXPECT_EQ(map[1], "Hello");
  EXPECT_EQ(map[2], "World");
  EXPECT_EQ(map[3], "Test");
}

struct Point {
  int x, y;
  std::string to_string() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  }
};

TEST(MapTest, InsertManyComplexObjects) {
  s21::Map<int, Point> map;
  Point p1 = {1, 2}, p2 = {3, 4};
  auto inserted_elements =
      map.InsertMany(std::make_pair(1, p1), std::make_pair(2, p2));

  EXPECT_EQ(inserted_elements.size(), 2);
  EXPECT_TRUE(map.Contains(1));
  EXPECT_TRUE(map.Contains(2));
  EXPECT_EQ(map[1].to_string(), "(1, 2)");
  EXPECT_EQ(map[2].to_string(), "(3, 4)");
}

TEST(MapTest, IteratorDecrementTraversal) {
  s21::Map<int, std::string> map;
  map.Insert({2, "two"});
  map.Insert({1, "one"});
  map.Insert({3, "three"});
  map.Insert({4, "four"});
  map.Insert({5, "five"});
  map.Insert({6, "six"});
  map.Insert({7, "seven"});
  auto it = map.Find(7);
  EXPECT_EQ(it->key, 7);
  --it;
  EXPECT_EQ(it->key, 6);
  --it;
  EXPECT_EQ(it->key, 5);
  --it;
  EXPECT_EQ(it->key, 4);
  --it;
  EXPECT_EQ(it->key, 3);
  --it;
  EXPECT_EQ(it->key, 2);
  --it;
  it = map.Find(1);
  --it;
  EXPECT_TRUE(it->key == 7);
}

TEST(MapTest, IteratorDecrementWhenCurrentIsNull) {
  s21::Map<int, std::string> map;
  map.Insert({1, "one"});
  map.Insert({2, "two"});
  map.Insert({3, "three"});
  s21::Map<int, std::string>::Iterator it(nullptr, &map);
  --it;
  EXPECT_EQ(it->key, 3);
  EXPECT_EQ(it->value, "three");
}

// Тест для вставки одного элемента
TEST(MapTest, InsertSingleElement2) {
  s21::Map<int, std::string> map;

  auto [it, inserted] = map.Insert({1, "one"});
  ASSERT_TRUE(inserted);
  EXPECT_EQ(it->key, 1);
  EXPECT_EQ(it->value, "one");
  auto [it2, inserted2] = map.Insert({1, "uno"});
  ASSERT_FALSE(inserted2);
  EXPECT_EQ(it2->value, "one");
}

// Тест для перемещаемой вставки
TEST(MapTest, InsertMoveElement2) {
  s21::Map<int, std::string> map;
  auto [it, inserted] = map.Insert(std::make_pair(2, "two"));
  ASSERT_TRUE(inserted);
  EXPECT_EQ(it->key, 2);
  EXPECT_EQ(it->value, "two");
}

// Тест для вставки с использованием списка инициализаторов
TEST(MapTest, InsertInitializerList3) {
  s21::Map<int, std::string> map;
  map.Insert({{4, "four"}, {5, "five"}, {6, "six"}});
  EXPECT_TRUE(map.Contains(4));
  EXPECT_TRUE(map.Contains(5));
  EXPECT_TRUE(map.Contains(6));
}

// Тест для вставки диапазона элементов
TEST(MapTest, InsertRange4) {
  s21::Map<int, std::string> map;
  std::vector<std::pair<int, std::string>> elements;
  elements = {{7, "seven"}, {8, "eight"}, {9, "nine"}};
  map.Insert(elements.begin(), elements.end());
  EXPECT_TRUE(map.Contains(7));
  EXPECT_TRUE(map.Contains(8));
  EXPECT_TRUE(map.Contains(9));
}

// Тест для корректности размера дерева после вставок
TEST(MapTest, SizeAfterInserts) {
  s21::Map<int, std::string> map;
  map.Insert({{13, "thirteen"}, {14, "fourteen"}, {15, "fifteen"}});
  EXPECT_EQ(map.Size(), 3);
  map.Erase(14);
  EXPECT_EQ(map.Size(), 2);
}

// Тест для вставки в левое поддерево
TEST(MapTest, InsertLeftSubtree) {
  s21::Map<int, int> map;
  map.Insert({10, 10});
  map.Insert({5, 5});
  EXPECT_EQ(map.Size(), 2);
  auto it = map.Find(5);
  EXPECT_NE(it, map.End());
  EXPECT_EQ(it->key, 5);
  EXPECT_EQ(it->value, 5);
}

// Тест для вставки в правое поддерево
TEST(MapTest, InsertRightSubtree) {
  s21::Map<int, int> map;
  map.Insert({10, 10});
  map.Insert({15, 15});
  EXPECT_EQ(map.Size(), 2);
  auto it = map.Find(15);
  EXPECT_NE(it, map.End());
  EXPECT_EQ(it->key, 15);
  EXPECT_EQ(it->value, 15);
}

// Тест для повторной вставки уже существующего ключа
TEST(MapTest, InsertExistingKey) {
  s21::Map<int, int> map;
  map.Insert({10, 10});
  map.Insert({15, 15});
  auto result = map.Insert({10, 20});

  EXPECT_FALSE(result.second);

  auto it = map.Find(10);
  EXPECT_EQ(it->value, 10);
}

TEST(MapTest, InitializerListConstructor) {
  s21::Map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(map.Size(), 3);
  EXPECT_EQ(map.At(1), "one");
  EXPECT_EQ(map.At(2), "two");
  EXPECT_EQ(map.At(3), "three");
}
