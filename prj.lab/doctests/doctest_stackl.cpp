#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <stackl/stackl.h>


TEST_CASE("StackL - default constructor") {
    StackL stack;
    CHECK(stack.is_empty());
}

TEST_CASE("StackL - is_empty") {
    StackL stack;
    CHECK(stack.is_empty());

    stack.push(1.0f);
    CHECK(!stack.is_empty());

    stack.pop();
    CHECK(stack.is_empty());
}

TEST_CASE("StackL - push/pop/top") {
    StackL stack;
    CHECK_NOTHROW(stack.pop());
    CHECK_THROWS(stack.top());

    stack.push(10.0f);
    stack.push(5.0f);
    stack.push(7.5f);

    CHECK(!stack.is_empty());
    CHECK(doctest::Approx(stack.top()) == 7.5f);
    stack.pop();
    CHECK(doctest::Approx(stack.top()) == 5.0f);
    stack.pop();
    CHECK(doctest::Approx(stack.top()) == 10.0f);
    stack.pop();

    CHECK(stack.is_empty());
    CHECK_NOTHROW(stack.pop());
    CHECK_THROWS(stack.top());

    stack.push(2.0f);
    CHECK(doctest::Approx(stack.top()) == 2.0f);
}

TEST_CASE("StackL - top const") {
    StackL stack;
    stack.push(10.0f);
    stack.push(5.0f);
    stack.push(7.5f);

    const StackL c_stack(stack);
    CHECK(doctest::Approx(stack.top()) == 7.5f);
}

TEST_CASE("StackL - copy constructor") {
    StackL stack;
    stack.push(10.0f);
    stack.push(5.0f);
    stack.push(7.5f);

    StackL stack2(stack);
    CHECK(!stack2.is_empty());
    CHECK(doctest::Approx(stack2.top()) == 7.5f);
    stack2.pop();
    CHECK(doctest::Approx(stack2.top()) == 5.0f);
    stack2.pop();
    CHECK(doctest::Approx(stack2.top()) == 10.0f);
    stack2.pop();

    CHECK(stack2.is_empty());
    CHECK_NOTHROW(stack2.pop());
    CHECK_THROWS(stack2.top());

    stack2.push(2.0f);
    CHECK(doctest::Approx(stack2.top()) == 2.0f);
}

TEST_CASE("StackL - operator=") {
    StackL stack;
    stack.push(10.0f);
    stack.push(5.0f);
    stack.push(7.5f);

    StackL stack2;
    stack2.push(3.0f);

    stack2 = stack;
    CHECK(!stack2.is_empty());
    CHECK(doctest::Approx(stack2.top()) == 7.5f);
    stack2.pop();
    CHECK(doctest::Approx(stack2.top()) == 5.0f);
    stack2.pop();
    CHECK(doctest::Approx(stack2.top()) == 10.0f);
    stack2.pop();

    CHECK(stack2.is_empty());
    CHECK_NOTHROW(stack2.pop());
    CHECK_THROWS(stack2.top());

    stack2.push(2.0f);
    CHECK(doctest::Approx(stack2.top()) == 2.0f);

    stack = stack;
    CHECK(!stack.is_empty());
    CHECK(doctest::Approx(stack.top()) == 7.5f);
    stack.pop();
    CHECK(doctest::Approx(stack.top()) == 5.0f);
    stack.pop();
    CHECK(doctest::Approx(stack.top()) == 10.0f);
    stack.pop();

    CHECK(stack.is_empty());
    CHECK_NOTHROW(stack.pop());
    CHECK_THROWS(stack.top());

    stack.push(2.0f);
    CHECK(doctest::Approx(stack.top()) == 2.0f);
}
