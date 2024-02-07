#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <queuea/queuea.h>


TEST_CASE("QueueA - default constructor") {
    QueueA queue;
    CHECK(queue.is_empty());
}

TEST_CASE("QueueA - is_empty") {
    QueueA queue;
    CHECK(queue.is_empty());

    queue.push(1.0f);
    CHECK(!queue.is_empty());

    queue.pop();
    CHECK(queue.is_empty());
}

TEST_CASE("QueueA - push/pop/top") {
    QueueA queue;
    CHECK_NOTHROW(queue.pop());
    CHECK_THROWS(queue.top());

    queue.push(10.0f);
    queue.push(5.0f);
    queue.push(7.5f);

    CHECK(!queue.is_empty());
    CHECK(doctest::Approx(queue.top()) == 10.0f);
    queue.pop();
    CHECK(doctest::Approx(queue.top()) == 5.0f);
    queue.pop();
    CHECK(doctest::Approx(queue.top()) == 7.5f);
    queue.pop();

    CHECK(queue.is_empty());
    CHECK_NOTHROW(queue.pop());
    CHECK_THROWS(queue.top());

    queue.push(2.0f);
    CHECK(doctest::Approx(queue.top()) == 2.0f);
}

TEST_CASE("QueueA - top const") {
    QueueA queue;
    queue.push(10.0f);
    queue.push(5.0f);
    queue.push(7.5f);

    const QueueA c_queue(queue);
    CHECK(doctest::Approx(queue.top()) == 10.0f);
}

TEST_CASE("QueueA - copy constructor") {
    QueueA queue;
    queue.push(10.0f);
    queue.push(5.0f);
    queue.push(7.5f);

    QueueA queue2(queue);
    CHECK(!queue2.is_empty());
    CHECK(doctest::Approx(queue2.top()) == 10.0f);
    queue2.pop();
    CHECK(doctest::Approx(queue2.top()) == 5.0f);
    queue2.pop();
    CHECK(doctest::Approx(queue2.top()) == 7.5f);
    queue2.pop();

    CHECK(queue2.is_empty());
    CHECK_NOTHROW(queue2.pop());
    CHECK_THROWS(queue2.top());

    queue2.push(2.0f);
    CHECK(doctest::Approx(queue2.top()) == 2.0f);
}

TEST_CASE("QueueA - operator=") {
    QueueA queue;
    queue.push(10.0f);
    queue.push(5.0f);
    queue.push(7.5f);

    QueueA queue2;
    queue2.push(3.0f);

    queue2 = queue;
    CHECK(!queue2.is_empty());
    CHECK(doctest::Approx(queue2.top()) == 10.0f);
    queue2.pop();
    CHECK(doctest::Approx(queue2.top()) == 5.0f);
    queue2.pop();
    CHECK(doctest::Approx(queue2.top()) == 7.5f);
    queue2.pop();

    CHECK(queue2.is_empty());
    CHECK_NOTHROW(queue2.pop());
    CHECK_THROWS(queue2.top());

    queue2.push(2.0f);
    CHECK(doctest::Approx(queue2.top()) == 2.0f);

    queue = queue;
    CHECK(!queue.is_empty());
    CHECK(doctest::Approx(queue.top()) == 10.0f);
    queue.pop();
    CHECK(doctest::Approx(queue.top()) == 5.0f);
    queue.pop();
    CHECK(doctest::Approx(queue.top()) == 7.5f);
    queue.pop();

    CHECK(queue.is_empty());
    CHECK_NOTHROW(queue.pop());
    CHECK_THROWS(queue.top());

    queue.push(2.0f);
    CHECK(doctest::Approx(queue.top()) == 2.0f);
}
