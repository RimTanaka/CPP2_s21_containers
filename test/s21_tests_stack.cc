#include "../stack/s21_stack.h"
#include "test.h"

TEST(StackTest, DefaultConstructor) {
  s21::Stack<int> stack;
  EXPECT_TRUE(stack.Empty());
  EXPECT_EQ(stack.Size(), 0);
}

TEST(StackTest, InitializerListConstructor) {
  s21::Stack<int> stack = {1, 2, 3};
  EXPECT_FALSE(stack.Empty());
  EXPECT_EQ(stack.Size(), 3);
  EXPECT_EQ(stack.Top(), 3);
}

TEST(StackTest, CopyConstructor1) {
  s21::Stack<int> original = {1, 2, 3};
  s21::Stack<int> copy(original);
  EXPECT_EQ(copy.Size(), original.Size());
  EXPECT_EQ(copy.Top(), original.Top());
}

TEST(StackTest, CopyConstructor2) {
  s21::Stack<int> original;
  s21::Stack<int> copy(original);
  EXPECT_EQ(copy.Size(), original.Size());
}

TEST(StackTest, MoveConstructor) {
  s21::Stack<int> original = {1, 2, 3};
  s21::Stack<int> moved(std::move(original));
  EXPECT_TRUE(original.Empty());
  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(moved.Top(), 3);
}

TEST(StackTest, MoveAssignmentOperator1) {
  s21::Stack<int> original = {1, 2, 3};
  s21::Stack<int> assigned;
  assigned = std::move(original);
  EXPECT_TRUE(original.Empty());
  EXPECT_EQ(assigned.Size(), 3);
  EXPECT_EQ(assigned.Top(), 3);
}

TEST(StackTest, MoveAssignmentOperator2) {
  s21::Stack<int> original = {1, 2, 3};
  s21::Stack<int> assigned = {1, 2, 3};
  assigned = std::move(original);
  EXPECT_TRUE(original.Empty());
  EXPECT_EQ(assigned.Size(), 3);
  EXPECT_EQ(assigned.Top(), 3);
}

TEST(StackTest, Top) {
  s21::Stack<int> stack = {1, 2, 3};
  EXPECT_EQ(stack.Top(), 3);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 2);
}

TEST(StackTest, Empty) {
  s21::Stack<int> stack;
  EXPECT_TRUE(stack.Empty());
  stack.Push(1);
  EXPECT_FALSE(stack.Empty());
}

TEST(StackTest, Size) {
  s21::Stack<int> stack = {1, 2, 3};
  EXPECT_EQ(stack.Size(), 3);
  stack.Pop();
  EXPECT_EQ(stack.Size(), 2);
}

TEST(StackTest, Push) {
  s21::Stack<int> stack;
  stack.Push(1);
  EXPECT_EQ(stack.Top(), 1);
  stack.Push(2);
  EXPECT_EQ(stack.Top(), 2);
}

TEST(StackTest, Pop) {
  s21::Stack<int> stack = {1, 2, 3};
  stack.Pop();
  EXPECT_EQ(stack.Top(), 2);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 1);
}

TEST(StackTest, Swap) {
  s21::Stack<int> stack1 = {1, 2, 3};
  s21::Stack<int> stack2 = {4, 5};
  stack1.Swap(stack2);
  EXPECT_EQ(stack1.Size(), 2);
  EXPECT_EQ(stack1.Top(), 5);
  EXPECT_EQ(stack2.Size(), 3);
  EXPECT_EQ(stack2.Top(), 3);
}

TEST(StackTest, InsertManyBack) {
  s21::Stack<int> stack;
  stack.InsertManyBack(1, 2, 3);
  EXPECT_EQ(stack.Size(), 3);
  EXPECT_EQ(stack.Top(), 3);
}

// TEST(StackTest, TopException) {
//     s21::Stack<int> stack;
//     EXPECT_THROW(stack.Top(), std::out_of_range);
// }

// TEST(StackTest, PopException) {
//     s21::Stack<int> stack;
//     EXPECT_THROW(stack.Pop(), std::out_of_range);
// }
