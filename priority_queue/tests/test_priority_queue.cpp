#include "priority_queue.h"
#include <gtest/gtest.h>

// struct
template<typename T>
struct greater{
    bool operator()(const T& a, const T& b){
        return a > b;
    }
};

// function
template<typename T>
bool compare_greater(const T& a, const T& b){
    return a > b;
}

// lambda
template<typename T>
auto lambda_greater = [] (const T& a, const T& b) -> bool{
    return a > b;
};

TEST(InitializingTest, ZeroElement){
    gio::priority_queue<int> p_queue{};
    EXPECT_EQ(p_queue.size(), 0);
    EXPECT_EQ(p_queue.empty(), true);
}

TEST(MemberTest, PushElement){
    gio::priority_queue<int> p_queue{};
    for (int num = 9; num >= 0; num --){
        p_queue.push(num);
    }
    EXPECT_EQ(p_queue.size(), 10);
    EXPECT_EQ(p_queue.empty(), false);
    EXPECT_EQ(p_queue.top(), 0);
}

TEST(MemberTest, PopElement){
    gio::priority_queue<int> p_queue{};
    for (int num = 9; num >= 0; num --){
        p_queue.push(num);
    }
    EXPECT_EQ(p_queue.top(), 0);
    p_queue.pop();
    p_queue.pop();
    EXPECT_EQ(p_queue.top(), 2);
    EXPECT_EQ(p_queue.size(), 8);
    EXPECT_EQ(p_queue.empty(), false);
}

TEST(MemberTest, GreaterStructInt){
    gio::priority_queue<int, greater<int>> p_queue{};
    for (int num = 9; num >= 0; num --){
        p_queue.push(num);
    }
    EXPECT_EQ(p_queue.top(), 9);
    p_queue.pop();
    p_queue.pop();
    EXPECT_EQ(p_queue.top(), 7);
    EXPECT_EQ(p_queue.size(), 8);
    EXPECT_EQ(p_queue.empty(), false);
}

TEST(MemberTest, GreaterStructString){
    gio::priority_queue<std::string, greater<std::string>> p_queue{};
    p_queue.push("abc");
    p_queue.push("def");
    p_queue.push("ghikmnl");
    EXPECT_EQ(p_queue.top(), "ghikmnl");
    p_queue.pop();
    EXPECT_EQ(p_queue.top(), "def");
    EXPECT_EQ(p_queue.size(), 2);
}

TEST(MemberTest, GreaterFuncInt){
    /* function pointer */
    bool (*func_ptr)(const int&, const int&) = &compare_greater<int>;
    gio::priority_queue<int, bool(*)(const int&, const int&)> p_queue_ptr{func_ptr};
    for (int num = 9; num >= 0; num --){
        p_queue_ptr.push(num);
    }
    EXPECT_EQ(p_queue_ptr.top(), 9);
    p_queue_ptr.pop();
    p_queue_ptr.pop();
    EXPECT_EQ(p_queue_ptr.top(), 7);
    EXPECT_EQ(p_queue_ptr.size(), 8);
    EXPECT_EQ(p_queue_ptr.empty(), false);

    /* std::function */
    std::function<bool(const int&, const int&)> func = &compare_greater<int>;
    gio::priority_queue<int, std::function<bool(const int&, const int&)>> p_queue{func};
    for (int num = 9; num >= 0; num --){
        p_queue.push(num);
    }
    EXPECT_EQ(p_queue.top(), 9);
    p_queue.pop();
    p_queue.pop();
    EXPECT_EQ(p_queue.top(), 7);
    EXPECT_EQ(p_queue.size(), 8);
    EXPECT_EQ(p_queue.empty(), false);
}

TEST(MemberTest, GreaterFuncString){
    /* function pointer */
    bool (*func_ptr)(const std::string&, const std::string&) = &compare_greater<std::string>;
    gio::priority_queue<std::string, bool(*)(const std::string&, const std::string&)> p_queue_ptr{func_ptr};
    p_queue_ptr.push("abc");
    p_queue_ptr.push("def");
    p_queue_ptr.push("ghikmnl");
    EXPECT_EQ(p_queue_ptr.top(), "ghikmnl");
    p_queue_ptr.pop();
    EXPECT_EQ(p_queue_ptr.top(), "def");
    EXPECT_EQ(p_queue_ptr.size(), 2);

    /* std::function */
    std::function<bool(const std::string&, const std::string&)> func = &compare_greater<std::string>;
    gio::priority_queue<std::string, std::function<bool(const std::string&, const std::string&)>> p_queue{func};
    p_queue.push("abc");
    p_queue.push("def");
    p_queue.push("ghikmnl");
    EXPECT_EQ(p_queue.top(), "ghikmnl");
    p_queue.pop();
    EXPECT_EQ(p_queue.top(), "def");
    EXPECT_EQ(p_queue.size(), 2);
}

TEST(MemberTest, GreaterLambdaInt){
    gio::priority_queue<int, decltype(lambda_greater<int>)> p_queue{lambda_greater<int>};
    for (int num = 9; num >= 0; num --){
        p_queue.push(num);
    }
    EXPECT_EQ(p_queue.top(), 9);
    p_queue.pop();
    p_queue.pop();
    EXPECT_EQ(p_queue.top(), 7);
    EXPECT_EQ(p_queue.size(), 8);
    EXPECT_EQ(p_queue.empty(), false);
}

TEST(MemberTest, GreaterLambdaString){
    gio::priority_queue<std::string, decltype(lambda_greater<std::string>)> p_queue{lambda_greater<std::string>};
    p_queue.push("abc");
    p_queue.push("def");
    p_queue.push("ghikmnl");
    EXPECT_EQ(p_queue.top(), "ghikmnl");
    p_queue.pop();
    EXPECT_EQ(p_queue.top(), "def");
    EXPECT_EQ(p_queue.size(), 2);
}