#include "../list/s21_list.h"
#include "test.h"

TEST(ListTest, DefaultConstructor) {
  s21::List<int> list;
  EXPECT_TRUE(list.Empty());
  EXPECT_EQ(list.Size(), 0);
}

TEST(ListTest, SizeConstructor) {
  s21::List<int> list(5);
  EXPECT_FALSE(list.Empty());
  EXPECT_EQ(list.Size(), 5);
}

TEST(ListTest, InitializerListConstructor) {
  s21::List<int> list = {1, 2, 3};
  EXPECT_FALSE(list.Empty());
  EXPECT_EQ(list.Size(), 3);
  EXPECT_EQ(list.Front(), 1);
  EXPECT_EQ(list.Back(), 3);
}

TEST(ListTest, CopyConstructor1) {
  s21::List<int> original = {1, 2, 3};
  s21::List<int> copy(original);
  EXPECT_EQ(copy.Size(), original.Size());
  EXPECT_EQ(copy.Front(), original.Front());
  EXPECT_EQ(copy.Back(), original.Back());
}

TEST(ListTest, CopyConstructor2) {
  s21::List<int> original;
  s21::List<int> copy(original);
  EXPECT_EQ(copy.Size(), original.Size());
}

TEST(ListTest, MoveConstructor) {
  s21::List<int> original = {1, 2, 3};
  s21::List<int> moved(std::move(original));
  EXPECT_TRUE(original.Empty());
  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(moved.Front(), 1);
  EXPECT_EQ(moved.Back(), 3);
}

TEST(ListTest, MoveAssignmentOperator1) {
  s21::List<int> original = {1, 2, 3};
  s21::List<int> assigned;
  assigned = std::move(original);
  EXPECT_TRUE(original.Empty());
  EXPECT_EQ(assigned.Size(), 3);
  EXPECT_EQ(assigned.Front(), 1);
  EXPECT_EQ(assigned.Back(), 3);
}

TEST(ListTest, MoveAssignmentOperator2) {
  s21::List<int> original = {1, 2, 3};
  s21::List<int> assigned = {1, 2, 3};
  assigned = std::move(original);
  EXPECT_TRUE(original.Empty());
  EXPECT_EQ(assigned.Size(), 3);
  EXPECT_EQ(assigned.Front(), 1);
  EXPECT_EQ(assigned.Back(), 3);
}

TEST(ListTest, EqualityOperator1) {
  s21::List<int> list1 = {1, 2, 3};
  s21::List<int> list2 = {1, 2, 3};
  s21::List<int> list3 = {1, 2, 4};
  EXPECT_TRUE(list1 == list2);
  EXPECT_FALSE(list1 == list3);
}

TEST(ListTest, EqualityOperator2) {
  s21::List<int> list1 = {1, 2, 3};
  s21::List<int> list2 = {1, 2, 3, 4};
  EXPECT_FALSE(list1 == list2);
}

TEST(ListTest, Front) {
  s21::List<int> list = {1, 2, 3};
  EXPECT_EQ(list.Front(), 1);
}

TEST(ListTest, Back) {
  s21::List<int> list = {1, 2, 3};
  EXPECT_EQ(list.Back(), 3);
}

TEST(ListTest, Empty) {
  s21::List<int> list;
  EXPECT_TRUE(list.Empty());
  list.PushBack(1);
  EXPECT_FALSE(list.Empty());
}

TEST(ListTest, Size) {
  s21::List<int> list = {1, 2, 3};
  EXPECT_EQ(list.Size(), 3);
  list.PopBack();
  EXPECT_EQ(list.Size(), 2);
}

TEST(ListTest, MaxSize) {
  s21::List<int> list;
  EXPECT_EQ(list.MaxSize(), std::numeric_limits<std::size_t>::max());
}

TEST(ListTest, Clear) {
  s21::List<int> list = {1, 2, 3};
  list.Clear();
  EXPECT_TRUE(list.Empty());
  EXPECT_EQ(list.Size(), 0);
}

TEST(ListTest, PushBack) {
  s21::List<int> list;
  list.PushBack(1);
  EXPECT_EQ(list.Back(), 1);
  list.PushBack(2);
  EXPECT_EQ(list.Back(), 2);
}

TEST(ListTest, PushFront) {
  s21::List<int> list;
  list.PushFront(1);
  EXPECT_EQ(list.Front(), 1);
  list.PushFront(2);
  EXPECT_EQ(list.Front(), 2);
}

TEST(ListTest, PopBack) {
  s21::List<int> list = {1, 2, 3};
  list.PopBack();
  EXPECT_EQ(list.Back(), 2);
  list.PopBack();
  EXPECT_EQ(list.Back(), 1);
}

TEST(ListTest, PopFront) {
  s21::List<int> list = {1, 2, 3};
  list.PopFront();
  EXPECT_EQ(list.Front(), 2);
  list.PopFront();
  EXPECT_EQ(list.Front(), 3);
}

TEST(ListTest, Swap) {
  s21::List<int> list1 = {1, 2, 3};
  s21::List<int> list2 = {4, 5};
  list1.Swap(list2);
  EXPECT_EQ(list1.Size(), 2);
  EXPECT_EQ(list1.Front(), 4);
  EXPECT_EQ(list1.Back(), 5);
  EXPECT_EQ(list2.Size(), 3);
  EXPECT_EQ(list2.Front(), 1);
  EXPECT_EQ(list2.Back(), 3);
}

TEST(ListTest, Reverse) {
  s21::List<int> list = {1, 2, 3};
  list.Reverse();
  EXPECT_EQ(list.Front(), 3);
  EXPECT_EQ(list.Back(), 1);
}

TEST(ListTest, ReverseSingleElementList) {
  s21::List<int> list = {1};
  list.Reverse();
  EXPECT_EQ(list.Size(), 1);
  EXPECT_EQ(list.Front(), 1);
  EXPECT_EQ(list.Back(), 1);
}

TEST(ListTest, BeginEnd) {
  s21::List<int> list = {1, 2, 3};
  auto it = list.Begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, list.End());
}

TEST(ListTest, CBeginCEnd) {
  const s21::List<int> list = {1, 2, 3};
  auto it = list.Cbegin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, list.Cend());
}

TEST(ListTest, Sort) {
  s21::List<int> list = {3, 1, 2};
  list.Sort();
  EXPECT_EQ(list.Front(), 1);
  EXPECT_EQ(list.Back(), 3);
}

TEST(ListTest, Unique) {
  s21::List<int> list = {1, 1, 2, 2, 3, 3};
  list.Unique();
  EXPECT_EQ(list.Size(), 3);
  EXPECT_EQ(list.Front(), 1);
  EXPECT_EQ(list.Back(), 3);
}

TEST(ListTest, Insert) {
  s21::List<int> list = {1, 2, 3};
  auto it = list.Begin();
  ++it;
  list.Insert(it, 4);
  EXPECT_EQ(list.Size(), 4);
  EXPECT_EQ(list.Front(), 1);
  EXPECT_EQ(list.Back(), 3);
  it = list.Begin();
  ++it;
  EXPECT_EQ(*it, 4);
}

TEST(ListTest, Erase) {
  s21::List<int> list = {1, 2, 3};
  auto it = list.Begin();
  ++it;
  list.Erase(it);
  EXPECT_EQ(list.Size(), 2);
  EXPECT_EQ(list.Front(), 1);
  EXPECT_EQ(list.Back(), 3);
}

// TEST(ListTest, EraseTail) {
//   s21::List<int> list1 = {1};
//   auto it1 = list1.End();
//   --it1;
//   list1.erase(it1);
//   EXPECT_EQ(list1.Empty(), 1);

//   std::list<int> list2 = {1};
//   auto it2 = list2.End();
//   --it2;
//   list2.erase(it2);
//   EXPECT_EQ(list2.Empty(), 1);
// }

// TEST(ListTest, ItOperatorMinus) {
//   s21::List<int> list1 = {1, 2, 3};
//   auto it1 = list1.End();
//   --it1;
//   EXPECT_EQ(*it1, 3);

//   std::list<int> list2 = {1, 2, 3};
//   auto it2 = list2.End();
//   --it2;
//   EXPECT_EQ(*it2, 3);
// }

TEST(ListTest, IteratorDecrement) {
  s21::List<int> list = {1, 2, 3};
  auto it = list.Begin();
  ++it;
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(ListTest, IteratorEndDecrement) {
  s21::List<int> list = {1, 2, 3};
  auto it = list.End();
  EXPECT_THROW(--it, std::out_of_range);
}

TEST(ListTest, IteratorEndIncrement) {
  s21::List<int> list = {1, 2, 3};
  auto it = list.End();
  EXPECT_THROW(++it, std::out_of_range);
}

TEST(ListTest, Merge) {
  s21::List<int> list1 = {1, 3, 5};
  s21::List<int> list2 = {2, 4, 6};
  list1.Merge(list2);
  EXPECT_EQ(list1.Size(), 6);
  EXPECT_EQ(list1.Front(), 1);
  EXPECT_EQ(list1.Back(), 6);
}

TEST(ListTest, Splice) {
  s21::List<int> list1 = {1, 2, 3};
  s21::List<int> list2 = {4, 5, 6};
  auto it = list1.Begin();
  ++it;
  list1.Splice(it, list2);
  EXPECT_EQ(list1.Size(), 6);
  EXPECT_EQ(list1.Front(), 1);
  EXPECT_EQ(list1.Back(), 3);
  it = list1.Begin();
  ++it;
  EXPECT_EQ(*it, 4);
}

TEST(ListTest, InsertMany) {
  s21::List<int> list = {1, 2, 3};
  auto it = list.Begin();
  ++it;
  list.InsertMany(it, 4, 5);
  EXPECT_EQ(list.Size(), 5);
  EXPECT_EQ(list.Front(), 1);
  EXPECT_EQ(list.Back(), 3);
  it = list.Begin();
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
}

TEST(ListTest, InsertManyBack) {
  s21::List<int> list = {1, 2, 3};
  list.InsertManyBack(4, 5);
  EXPECT_EQ(list.Size(), 5);
  EXPECT_EQ(list.Front(), 1);
  EXPECT_EQ(list.Back(), 5);
}

TEST(ListTest, InsertManyFront) {
  s21::List<int> list = {1, 2, 3};
  list.InsertManyFront(4, 5);
  EXPECT_EQ(list.Size(), 5);
  EXPECT_EQ(list.Front(), 5);
  EXPECT_EQ(list.Back(), 3);
}

TEST(ListTest, FrontException) {
  s21::List<int> list;
  EXPECT_THROW(list.Front(), std::out_of_range);
}

TEST(ListTest, BackException) {
  s21::List<int> list;
  EXPECT_THROW(list.Back(), std::out_of_range);
}

TEST(ListTest, PopBackException) {
  s21::List<int> list;
  EXPECT_THROW(list.PopBack(), std::out_of_range);
}

TEST(ListTest, PopFrontException) {
  s21::List<int> list;
  EXPECT_THROW(list.PopFront(), std::out_of_range);
}

TEST(ListTest, EraseException) {
  s21::List<int> list;
  EXPECT_THROW(list.Erase(list.Begin()), std::out_of_range);
}

TEST(ListTest, OperatorDereference) {
  s21::List<int> list = {1, 2, 3};
  auto it = list.Begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_THROW(*it, std::out_of_range);
}
