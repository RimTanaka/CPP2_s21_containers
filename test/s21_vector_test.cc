#include <type_traits>
#include <vector>

#include "test.h"

template <typename T>
class VectorTest : public ::testing::Test {
 public:
  s21::Vector<T> my;
  std::vector<T> orig;
};

using stdNumberTypes = ::testing::Types<char, short, int, long>;

TYPED_TEST_SUITE(VectorTest, stdNumberTypes);

TEST(VectorTest, initWithSize) {
  s21::Vector<int> my(5);
  std::vector<int> orig(5);

  EXPECT_EQ(my.Size(), orig.size());
}

TEST(VectorTest, initWithoutSize) {
  s21::Vector<int> my(0);
  std::vector<int> orig(0);

  EXPECT_EQ(my.Size(), orig.size());
}

TEST(VectorTest, asignCopy) {
  s21::Vector<int> vector1 = {1, 2, 3, 4, 5};
  s21::Vector<int> vector2;

  vector2 = vector1;
  for (size_t i = 0; i < vector1.Size(); ++i) {
    EXPECT_EQ(vector1.At(i), vector2.At(i));
  }
}

TEST(VectorTest, asignMove) {
  s21::Vector<int> vector1 = {1, 2, 3, 4, 5};
  s21::Vector<int> vector2;

  vector2 = std::move(vector1);
  for (size_t i = 0; i < vector1.Size(); ++i) {
    EXPECT_EQ(vector1.At(i), i + 1);
  }
}

TEST(VectorTest, swap) {
  s21::Vector<int> vector1 = {1, 2, 3, 4, 5};
  s21::Vector<int> vector2;

  vector2.Swap(vector1);

  for (size_t i = 0; i < vector2.Size(); ++i) {
    EXPECT_EQ(vector2.At(i), i + 1);
  }

  EXPECT_EQ(vector1.Size(), 0);
  EXPECT_EQ(vector1.Capacity(), 0);
}

TEST(VectorTest, reserve) {
  s21::Vector<int> my;
  std::vector<int> orig;

  my.Reserve(50);
  orig.reserve(50);

  EXPECT_EQ(my.Capacity(), orig.capacity());
  EXPECT_EQ(my.Size(), orig.size());
}

TEST(VectorTest, reserveUndersizing) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};
  size_t size = my.Size();
  my.Reserve(1);

  EXPECT_EQ(size, my.Capacity());
}

TEST(VectorTest, reserveWithMove) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};
  std::vector<int> orig = {1, 2, 3, 4, 5};

  my.Reserve(1000);
  orig.reserve(1000);
  EXPECT_EQ(my.Capacity(), 1000);
  EXPECT_EQ(orig.capacity(), 1000);
}

TYPED_TEST(VectorTest, isEmptyTest) {
  EXPECT_EQ(this->my.Empty(), this->orig.empty());
}

TYPED_TEST(VectorTest, pushBackAndSize) {
  this->my.PushBack(TypeParam{});
  this->orig.push_back(TypeParam{});
  EXPECT_EQ(this->my.Size(), this->orig.size());
}

TYPED_TEST(VectorTest, maxSizeTest) {
  EXPECT_EQ(this->my.MaxSize(), this->orig.max_size());
}

TYPED_TEST(VectorTest, defaultConstructor) {
  EXPECT_EQ(this->my.Empty(), this->orig.empty());
  EXPECT_EQ(this->my.Size(), this->orig.size());
}

TYPED_TEST(VectorTest, initConstructor) {
  s21::Vector<TypeParam> my = {TypeParam(1), TypeParam(2), TypeParam(3)};
  std::vector<TypeParam> orig = {TypeParam(1), TypeParam(2), TypeParam(3)};

  EXPECT_EQ(my.Size(), orig.size());
  EXPECT_EQ(my.Empty(), orig.empty());

  for (size_t i = 0; i < orig.size(); ++i) {
    EXPECT_EQ(my.At(i), orig.at(i));
  }
}

TYPED_TEST(VectorTest, copyConstructor) {
  s21::Vector<TypeParam> my = {TypeParam(1), TypeParam(2), TypeParam(3)};
  s21::Vector<TypeParam> my1 = my;

  std::vector<TypeParam> orig = {TypeParam(1), TypeParam(2), TypeParam(3)};
  std::vector<TypeParam> orig1 = orig;

  EXPECT_EQ(my.Size(), orig.size());
  EXPECT_EQ(my.Empty(), orig.empty());

  for (size_t i = 0; i < my.Size(); ++i) {
    EXPECT_EQ(my[i], my1[i]);
    EXPECT_EQ(orig[i], orig1[i]);
  }

  EXPECT_EQ(my.Capacity(), my1.Capacity());
  my[0] = TypeParam(21);

  EXPECT_NE(my[0], my1[0]);

  EXPECT_NE(&my[0], &my1[0]);
}

TYPED_TEST(VectorTest, moveContructor) {
  s21::Vector<TypeParam> orig = {TypeParam(1), TypeParam(2), TypeParam(3)};
  size_t orig_size = orig.Size();
  size_t orig_capacity = orig.Capacity();

  s21::Vector<TypeParam> moved(std::move(orig));

  EXPECT_EQ(moved.Size(), orig_size);
  EXPECT_EQ(moved.Capacity(), orig_capacity);

  for (size_t i = 0; i < orig_size; ++i) {
    EXPECT_EQ(moved[i], TypeParam(i + 1));
  }
  EXPECT_EQ(orig.Size(), 0);
  EXPECT_EQ(orig.Capacity(), 0);

  if (orig_size > 0) {
    EXPECT_NE(&moved[0], &orig[0]);
  }
}

TYPED_TEST(VectorTest, atExceptOutOfRange) {
  s21::Vector<TypeParam> my = {TypeParam(1), TypeParam(2), TypeParam(3)};
  std::vector<TypeParam> orig = {TypeParam(1), TypeParam(2), TypeParam(3)};

  EXPECT_EQ(my.Size(), orig.size());
  EXPECT_EQ(my.Empty(), my.Empty());

  for (int i = 3; i < 5; ++i) {
    EXPECT_THROW(my.At(i), std::out_of_range);
  }
}

TYPED_TEST(VectorTest, pushBack) {
  for (TypeParam i = 0; i < 126; ++i) {
    this->my.PushBack(i);
    this->orig.push_back(i);
    EXPECT_EQ(this->my.At(i), this->orig.at(i));
  }
}

TYPED_TEST(VectorTest, popBack) {
  for (int i = 0; i < 126; ++i) {
    this->my.PopBack();
    this->orig.pop_back();

    EXPECT_EQ(this->my.Size(), this->orig.size());
  }
}

TEST(VectorTest, begin) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};
  std::vector<int> orig = {1, 2, 3, 4, 5};

  EXPECT_EQ(*my.Begin(), *orig.begin());
}

TEST(VectorTest, beginConst) {
  const s21::Vector<int> my = {1, 2, 3, 4, 5};
  const std::vector<int> orig = {1, 2, 3, 4, 5};

  EXPECT_EQ(*my.Begin(), *orig.begin());
}

TEST(VectorTest, end) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};
  std::vector<int> orig = {1, 2, 3, 4, 5};
  s21::Vector<int>::iterator myIter = my.End();
  std::vector<int>::iterator origIter = orig.end();

  --myIter;
  --myIter;
  --origIter;
  --origIter;
  EXPECT_EQ(*myIter, *origIter);
}

TEST(VectorTest, endConst) {
  const s21::Vector<int> my = {1, 2, 3, 4, 5};
  const std::vector<int> orig = {1, 2, 3, 4, 5};
  s21::Vector<int>::constIterator myIter = my.End();
  std::vector<int>::const_iterator origIter = orig.end();

  --myIter;
  --myIter;
  --origIter;
  --origIter;
  EXPECT_EQ(*myIter, *origIter);
}

TEST(VectorTest, data) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};
  std::vector<int> orig = {1, 2, 3, 4, 5};
  auto myIter = my.Data();
  auto origIter = orig.data();

  EXPECT_EQ(*myIter, *origIter);
}

TEST(VectorTest, constData) {
  const s21::Vector<int> my = {1, 2, 3, 4, 5};
  const std::vector<int> orig = {1, 2, 3, 4, 5};
  auto myIter = my.Data();
  auto origIter = orig.data();

  EXPECT_EQ(*myIter, *origIter);
}

TEST(VectorTest, front) {
  const s21::Vector<int> my = {1, 2, 3, 4, 5};
  const std::vector<int> orig = {1, 2, 3, 4, 5};
  auto myRef = my.Front();
  auto origRef = orig.front();

  EXPECT_EQ(myRef, origRef);
}

TEST(VectorTest, back) {
  const s21::Vector<int> my = {1, 2, 3, 4, 5};
  const std::vector<int> orig = {1, 2, 3, 4, 5};
  auto myRef = my.Back();
  auto origRef = orig.back();
  EXPECT_EQ(myRef, origRef);
}

TEST(VectorTest, clear) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};
  std::vector<int> orig = {1, 2, 3, 4, 5};
  my.Clear();
  orig.clear();

  EXPECT_EQ(my.Size(), orig.size());
}

TEST(VectorTest, shrinkToFit) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};
  std::vector<int> orig = {1, 2, 3, 4, 5};

  my.Reserve(100);
  orig.reserve(100);

  EXPECT_EQ(my.Capacity(), orig.capacity());

  my.ShrinkToFit();
  orig.shrink_to_fit();

  EXPECT_EQ(my.Capacity(), orig.capacity());
}

TEST(VectorTest, insert) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};
  std::vector<int> orig = {1, 2, 3, 4, 5};

  auto myIter = my.Begin();
  auto origIter = orig.begin();
  ++myIter;
  ++origIter;
  auto newMyIter = my.Insert(myIter, 300);
  auto newOrigIter = orig.insert(origIter, 300);

  EXPECT_EQ(my.Size(), orig.size());
  EXPECT_EQ(*newMyIter, *newOrigIter);
}

TEST(VectorTest, insertMany) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};

  auto myIter = my.Begin();

  ++myIter;

  auto newIter = my.InsertMany(myIter, s21::Vector<int>{100, 200, 300});

  EXPECT_EQ(my.Size(), 8);
  EXPECT_EQ(my.Capacity(), 8);
  EXPECT_EQ(*newIter, 2);
}

TEST(VectorTest, insertManyBack) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};
  std::vector<int> orig = {1, 2, 3, 4, 5};

  orig.insert(orig.end(), {100, 200, 300});
  my.InsertManyBack(100, 200, 300);

  EXPECT_EQ(orig.size(), my.Size());
  for (size_t i = 0; i < my.Size(); ++i) {
    EXPECT_EQ(orig.at(i), my.At(i));
  }
}

TEST(VectorTest, reserveError) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};
  std::vector<int> orig = {1, 2, 3, 4, 5};

  EXPECT_THROW(my.Reserve(my.MaxSize() + 1), std::length_error);
  EXPECT_THROW(orig.reserve(orig.max_size() + 1), std::length_error);
}

TEST(VectorTest, erase) {
  s21::Vector<int> my = {1, 2, 3, 4, 5};
  std::vector<int> orig = {1, 2, 3, 4, 5};

  auto myIter = my.Begin();
  auto origIter = orig.begin();

  ++myIter;
  ++myIter;

  ++origIter;
  ++origIter;

  my.Erase(myIter);
  orig.erase(origIter);

  EXPECT_EQ(my.Size(), orig.size());
  for (size_t i = 0; i < my.Size(); ++i) {
    EXPECT_EQ(my.At(i), orig.at(i));
  }
}