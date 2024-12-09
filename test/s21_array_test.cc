#include <array>

#include "test.h"

TEST(ArrayTest, initListContructor) {
  s21::Array<int, 10> orig{1, 2, 3, 4, 5};
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(orig[i], i + 1);
  }
}

TEST(ArrayTest, copyContructor) {
  s21::Array<int, 10> orig{1, 2, 3, 4, 5};
  s21::Array<int, 10> out(orig);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(orig[i], out[i]);
  }
}

TEST(ArrayTest, moveContructor) {
  s21::Array<int, 10> orig{1, 2, 3, 4, 5};
  s21::Array<int, 10> out = std::move(orig);
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(orig[i], i + 1);
  }
}

TEST(ArrayTest, asignMove) {
  s21::Array<int, 10> arr1{1, 2, 3, 4, 5};
  s21::Array<int, 10> arr2;
  arr2 = std::move(arr1);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(arr1.At(i), arr2.At(i));
  }
}

TEST(ArrayTest, asignCopy) {
  s21::Array<int, 10> arr1{1, 2, 3, 4, 5};
  s21::Array<int, 10> arr2;
  arr2 = arr1;
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(arr1.At(i), arr2.At(i));
  }
}

TEST(ArrayTest, atPosition) {
  s21::Array<int, 10> my = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> orig = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(my.At(i), orig.at(i));
  }
}

TEST(ArrayTest, atPositionError) {
  s21::Array<int, 10> my = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (size_t i = 10; i < 12; ++i) {
    EXPECT_THROW(my.At(i), std::out_of_range);
  }
}

TEST(ArrayTest, indexPosition) {
  s21::Array<int, 10> my = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> orig = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(my[i], orig[i]);
  }
}

TEST(ArrayTest, front) {
  s21::Array<int, 10> my = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> orig = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(my.Front(), orig.front());
}

TEST(ArrayTest, back) {
  s21::Array<int, 10> my = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> orig = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(my.Back(), orig.back());
}

TEST(ArrayTest, empty) {
  s21::Array<int, 0> my = {};
  std::array<int, 0> orig = {};
  EXPECT_EQ(my.Empty(), orig.empty());
}

TEST(ArrayTest, notEmpty) {
  s21::Array<int, 1> my = {1};
  std::array<int, 1> orig = {1};
  EXPECT_EQ(my.Empty(), orig.empty());
}

TEST(ArrayTest, emptyNotEqual) {
  s21::Array<int, 0> my = {};
  std::array<int, 1> orig = {1};
  EXPECT_NE(my.Empty(), orig.empty());
}

TEST(ArrayTest, size) {
  s21::Array<int, 10> my;
  std::array<int, 10> orig;

  EXPECT_EQ(my.Size(), orig.size());
  EXPECT_EQ(my.MaxSize(), orig.max_size());
}

TEST(ArrayTest, data) {
  s21::Array<int, 10> my = {1, 2, 3, 4, 5};
  std::array<int, 10> orig = {1, 2, 3, 4, 5};

  s21::Array<int, 10>::iterator my_iter = my.Data();
  std::array<int, 10>::iterator orig_iter = orig.data();
  EXPECT_EQ(*my_iter, *orig_iter);
}

TEST(ArrayTest, begin) {
  s21::Array<int, 10> my = {1, 2, 3, 4, 5};
  s21::Array<int, 10>::iterator iter = my.Begin();
  EXPECT_EQ(*iter, 1);
}

TEST(ArrayTest, end) {
  s21::Array<int, 5> my = {1, 2, 3, 4, 5};
  s21::Array<int, 5>::iterator iter = my.End();
  --iter;
  EXPECT_EQ(*iter, 5);
}

TEST(ArrayTest, constData) {
  const s21::Array<int, 10> my = {1, 2, 3, 4, 5};
  const std::array<int, 10> orig = {1, 2, 3, 4, 5};

  const s21::Array<int, 10>::constIterator my_iter = my.Data();
  const std::array<int, 10>::const_iterator orig_iter = orig.data();
  EXPECT_EQ(*my_iter, *orig_iter);
}

TEST(ArrayTest, constBegin) {
  const s21::Array<int, 10> my = {1, 2, 3, 4, 5};
  const std::array<int, 10> orig = {1, 2, 3, 4, 5};

  const s21::Array<int, 10>::constIterator my_iter = my.Begin();
  const std::array<int, 10>::const_iterator orig_iter = orig.begin();
  EXPECT_EQ(*my_iter, *orig_iter);
}

TEST(ArrayTest, constEnd) {
  const s21::Array<int, 5> my = {1, 2, 3, 4, 5};
  const std::array<int, 5> orig = {1, 2, 3, 4, 5};

  s21::Array<int, 10>::constIterator my_iter = my.End();
  std::array<int, 10>::const_iterator orig_iter = orig.end();

  --my_iter;
  --orig_iter;
  EXPECT_EQ(*my_iter, *orig_iter);
}

TEST(ArrayTest, swap) {
  s21::Array<int, 10> a1 = {0, 1, 2, 3, 4};
  s21::Array<int, 10> a2 = {100, 200, 300, 400, 500};
  a1.Swap(a2);

  for (int i = 0, j = 100; i < 5; ++i, j += 100) {
    EXPECT_EQ(a1[i], j);
    EXPECT_EQ(a2[i], i);
  }
}

TEST(ArrayTest, fill) {
  s21::Array<int, 10> my = {21, 21, 21, 21};
  std::array<int, 10> orig = {42, 42, 42, 42, 42};

  my.Fill(100);
  orig.fill(100);

  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(my[i], orig[i]);
  }
}
