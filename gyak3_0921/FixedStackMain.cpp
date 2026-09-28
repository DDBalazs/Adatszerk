#include "FixedStack.hpp"
#include "woodpecker.hpp"

TEST("Empty stack", 1){
    FixedStack<int> stack;
    CHECK_EQ(stack.isEmpty(), true);
}

TEST("Adding elements", 1){
    FixedStack<int> stack;
    for(int i = 0; i < 10; i++){
        stack.push(i);
        CHECK_EQ(stack.top(), i);
    }
    CHECK_EQ(stack.isEmpty(), false);
}

TEST("Removing elements", 1){
    FixedStack<int> stack;
    for(int i = 0; i < 10; i++) {
        stack.push(i);
        CHECK_EQ(stack.top(), i);
    }

    for(int i = 9; i >= 0; i--){
        CHECK_EQ(stack.top(), i);
        CHECK_EQ(stack.pop(), i);
    }
    CHECK_EQ(stack.isEmpty(), true);
}

TEST("String stack", 1){
  FixedStack<std::string> stack;
  stack.push("Template");
  stack.push("Exception");
  stack.push("Stack");
  stack.push("Queue");

  CHECK_EQ("Queue", stack.pop());
  CHECK_EQ("Stack", stack.pop());
  CHECK_EQ("Exception", stack.pop());
  CHECK_EQ("Template", stack.pop());
}

TEST("Exceptions", 1){
  FixedStack<int> stack;

  CHECK_EXC(UnderflowException, stack.top());
  CHECK_EXC(UnderflowException, stack.pop());
  CHECK_NOEXC(stack.isEmpty());

  for(int i = 0; i < 10; i++) stack.push(i);

  CHECK_EXC(OverflowException, stack.push(1));
  CHECK_NOEXC(stack.top());
  CHECK_NOEXC(stack.pop());
  CHECK_NOEXC(stack.isEmpty());

  for(int i = 0; i < 9; i++) stack.pop();

  CHECK_EXC(UnderflowException, stack.top());
  CHECK_EXC(UnderflowException, stack.pop());
  CHECK_NOEXC(stack.isEmpty());
}

WOODPECKER_MAIN(1, 1)
