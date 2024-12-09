#include "../queue/s21_queue.h"
#include "test.h"

TEST(QueueTest, DefaultConstructor) {
  s21::Queue<int> queue;
  EXPECT_TRUE(queue.Empty());
  EXPECT_EQ(queue.Size(), 0);
}

TEST(QueueTest, InitializerListConstructor) {
  s21::Queue<int> queue = {1, 2, 3};
  EXPECT_FALSE(queue.Empty());
  EXPECT_EQ(queue.Size(), 3);
  EXPECT_EQ(queue.Front(), 1);
  EXPECT_EQ(queue.Back(), 3);
}

TEST(QueueTest, CopyConstructor1) {
  s21::Queue<int> original = {1, 2, 3};
  s21::Queue<int> copy(original);
  EXPECT_EQ(copy.Size(), original.Size());
  EXPECT_EQ(copy.Front(), original.Front());
  EXPECT_EQ(copy.Back(), original.Back());
}

TEST(QueueTest, CopyConstructor2) {
  s21::Queue<int> original;
  s21::Queue<int> copy(original);
  EXPECT_EQ(copy.Size(), original.Size());
}

TEST(QueueTest, MoveConstructor) {
  s21::Queue<int> original = {1, 2, 3};
  s21::Queue<int> moved(std::move(original));
  EXPECT_TRUE(original.Empty());
  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(moved.Front(), 1);
  EXPECT_EQ(moved.Back(), 3);
}

TEST(QueueTest, MoveAssignmentOperator) {
  s21::Queue<int> original = {1, 2, 3};
  s21::Queue<int> assigned;
  assigned = std::move(original);
  EXPECT_TRUE(original.Empty());
  EXPECT_EQ(assigned.Size(), 3);
  EXPECT_EQ(assigned.Front(), 1);
  EXPECT_EQ(assigned.Back(), 3);
}

TEST(QueueTest, MoveAssignmentOperator2) {
  s21::Queue<int> original = {1, 2, 3};
  s21::Queue<int> assigned = {1, 2, 3};
  assigned = std::move(original);
  EXPECT_TRUE(original.Empty());
  EXPECT_EQ(assigned.Size(), 3);
  EXPECT_EQ(assigned.Back(), 3);
  EXPECT_EQ(assigned.Front(), 1);
}

TEST(QueueTest, Front) {
  s21::Queue<int> queue = {1, 2, 3};
  EXPECT_EQ(queue.Front(), 1);
  queue.Pop();
  EXPECT_EQ(queue.Front(), 2);
}

TEST(QueueTest, Back) {
  s21::Queue<int> queue = {1, 2, 3};
  EXPECT_EQ(queue.Back(), 3);
  queue.Push(4);
  EXPECT_EQ(queue.Back(), 4);
}

TEST(QueueTest, Empty) {
  s21::Queue<int> queue;
  EXPECT_TRUE(queue.Empty());
  queue.Push(1);
  EXPECT_FALSE(queue.Empty());
}

TEST(QueueTest, Size) {
  s21::Queue<int> queue = {1, 2, 3};
  EXPECT_EQ(queue.Size(), 3);
  queue.Pop();
  EXPECT_EQ(queue.Size(), 2);
}

TEST(QueueTest, Push) {
  s21::Queue<int> queue;
  queue.Push(1);
  EXPECT_EQ(queue.Front(), 1);
  EXPECT_EQ(queue.Back(), 1);
  queue.Push(2);
  EXPECT_EQ(queue.Front(), 1);
  EXPECT_EQ(queue.Back(), 2);
}

TEST(QueueTest, Pop) {
  s21::Queue<int> queue = {1, 2, 3};
  queue.Pop();
  EXPECT_EQ(queue.Front(), 2);
  queue.Pop();
  EXPECT_EQ(queue.Front(), 3);
}

TEST(QueueTest, Swap) {
  s21::Queue<int> queue1 = {1, 2, 3};
  s21::Queue<int> queue2 = {4, 5};
  queue1.Swap(queue2);
  EXPECT_EQ(queue1.Size(), 2);
  EXPECT_EQ(queue1.Front(), 4);
  EXPECT_EQ(queue1.Back(), 5);
  EXPECT_EQ(queue2.Size(), 3);
  EXPECT_EQ(queue2.Front(), 1);
  EXPECT_EQ(queue2.Back(), 3);
}

TEST(QueueTest, InsertManyBack) {
  s21::Queue<int> queue;
  queue.InsertManyBack(1, 2, 3);
  EXPECT_EQ(queue.Size(), 3);
  EXPECT_EQ(queue.Front(), 1);
  EXPECT_EQ(queue.Back(), 3);
}

// TEST(QueueTest, FrontException) {
//     s21::Queue<int> queue;
//     EXPECT_ANY_THROW(queue.Front());
// }

// TEST(QueueTest, BackException) {
//     s21::Queue<int> queue;
//     EXPECT_ANY_THROW(queue.Back());
// }

// TEST(QueueTest, PopException) {
//     s21::Queue<int> queue;
//     EXPECT_THROW(queue.Pop(), std::out_of_range);
// }
