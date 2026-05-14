#include <gtest/gtest.h>
#include "Vector.h"
#include <string>
#include <list>
#include <sstream>

// ─────────────────────────────────────────────────────────────────────────────
// Helper: tracks constructor/destructor calls to catch memory errors
// ─────────────────────────────────────────────────────────────────────────────
struct Tracked {
    static int live;
    int value;
    explicit Tracked(int v = 0) : value(v) { ++live; }
    Tracked(const Tracked& o)   : value(o.value) { ++live; }
    Tracked(Tracked&& o) noexcept : value(o.value) { ++live; o.value = -1; }
    Tracked& operator=(Tracked&& o) noexcept { value = o.value; o.value = -1; return *this; }
    Tracked& operator=(const Tracked& o) { value = o.value; return *this; }
    ~Tracked() { --live; }
    bool operator==(const Tracked& o) const { return value == o.value; }
    auto operator<=>(const Tracked& o) const { return value <=> o.value; }
};
int Tracked::live = 0;

struct TrackedFixture : ::testing::Test {
    void SetUp()    override { Tracked::live = 0; }
    void TearDown() override { EXPECT_EQ(Tracked::live, 0) << "memory leak or double-destroy"; }
};

// ─────────────────────────────────────────────────────────────────────────────
// Construction
// ─────────────────────────────────────────────────────────────────────────────
TEST(Construction, DefaultConstructor) {
    Vector<int> v;
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
    EXPECT_TRUE(v.empty());
}

TEST(Construction, SizeValue) {
    Vector<int> v(5, 42);
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < 5; ++i) EXPECT_EQ(v[i], 42);
}

TEST(Construction, SizeDefault) {
    Vector<int> v(4);
    EXPECT_EQ(v.size(), 4u);
    for (size_t i = 0; i < 4; ++i) EXPECT_EQ(v[i], 0);
}

TEST(Construction, InitializerList) {
    Vector<int> v{1, 2, 3, 4, 5};
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < 5; ++i) EXPECT_EQ(v[i], static_cast<int>(i) + 1);
}

TEST(Construction, IteratorRange) {
    std::list<int> src{10, 20, 30};
    Vector<int> v(src.begin(), src.end());
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 10); EXPECT_EQ(v[1], 20); EXPECT_EQ(v[2], 30);
}

TEST(Construction, CopyConstructor) {
    Vector<int> a{1, 2, 3};
    Vector<int> b(a);
    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(b[0], 1); EXPECT_EQ(b[2], 3);
    // deep copy — modifying b must not affect a
    b[0] = 99;
    EXPECT_EQ(a[0], 1);
}

TEST(Construction, MoveConstructor) {
    Vector<int> a{1, 2, 3};
    int* original_data = a.data();
    Vector<int> b(std::move(a));
    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(b.data(), original_data);  // pointer was stolen
    EXPECT_TRUE(a.empty());
}

TEST(Construction, EmptyInitializerList) {
    Vector<int> v{};
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(TrackedFixture, DestructorCalledOnConstruction) {
    { Vector<Tracked> v(3, Tracked{7}); EXPECT_EQ(Tracked::live, 3); }
    EXPECT_EQ(Tracked::live, 0);
}

// ─────────────────────────────────────────────────────────────────────────────
// Assignment
// ─────────────────────────────────────────────────────────────────────────────
TEST(Assignment, CopyAssignment) {
    Vector<int> a{1, 2, 3};
    Vector<int> b{9, 9};
    b = a;
    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(b[0], 1); EXPECT_EQ(b[2], 3);
    b[0] = 99;
    EXPECT_EQ(a[0], 1);  // deep copy
}

TEST(Assignment, SelfCopyAssignment) {
    Vector<int> v{1, 2, 3};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-assign-overloaded"
    v = v;
#pragma GCC diagnostic pop
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
}

TEST(Assignment, MoveAssignment) {
    Vector<int> a{1, 2, 3};
    int* ptr = a.data();
    Vector<int> b;
    b = std::move(a);
    EXPECT_EQ(b.data(), ptr);
    EXPECT_TRUE(a.empty());
}

TEST(Assignment, SelfMoveAssignment) {
    Vector<int> v{1, 2, 3};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-move"
    v = std::move(v);
#pragma GCC diagnostic pop
    // just must not crash or corrupt
}

TEST(Assignment, InitializerListAssignment) {
    Vector<int> v{9, 9, 9};
    v = {1, 2, 3, 4};
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[3], 4);
}

TEST(Assignment, AssignCountValue) {
    Vector<int> v{1, 2, 3};
    v.assign(5, 7);
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < 5; ++i) EXPECT_EQ(v[i], 7);
}

TEST(Assignment, AssignIteratorRange) {
    std::list<int> src{4, 5, 6};
    Vector<int> v{1, 2, 3};
    v.assign(src.begin(), src.end());
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 4);
}

TEST(Assignment, AssignInitializerList) {
    Vector<int> v;
    v.assign({10, 20, 30});
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[1], 20);
}

// ─────────────────────────────────────────────────────────────────────────────
// Element access
// ─────────────────────────────────────────────────────────────────────────────
TEST(ElementAccess, OperatorBracket) {
    Vector<int> v{10, 20, 30};
    EXPECT_EQ(v[0], 10);
    v[1] = 99;
    EXPECT_EQ(v[1], 99);
}

TEST(ElementAccess, OperatorBracketConst) {
    const Vector<int> v{10, 20, 30};
    EXPECT_EQ(v[2], 30);
}

TEST(ElementAccess, AtInRange) {
    Vector<int> v{1, 2, 3};
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(2), 3);
}

TEST(ElementAccess, AtOutOfRange) {
    Vector<int> v{1, 2, 3};
    EXPECT_THROW(v.at(3),  std::out_of_range);
    EXPECT_THROW(v.at(99), std::out_of_range);
}

TEST(ElementAccess, AtOutOfRangeConst) {
    const Vector<int> v{1, 2};
    EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(ElementAccess, FrontBack) {
    Vector<int> v{10, 20, 30};
    EXPECT_EQ(v.front(), 10);
    EXPECT_EQ(v.back(),  30);
    v.front() = 1; v.back() = 3;
    EXPECT_EQ(v[0], 1); EXPECT_EQ(v[2], 3);
}

TEST(ElementAccess, Data) {
    Vector<int> v{1, 2, 3};
    int* p = v.data();
    EXPECT_EQ(p[0], 1);
    p[0] = 99;
    EXPECT_EQ(v[0], 99);
}

// ─────────────────────────────────────────────────────────────────────────────
// Iterators
// ─────────────────────────────────────────────────────────────────────────────
TEST(Iterators, BeginEnd) {
    Vector<int> v{1, 2, 3};
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) sum += *it;
    EXPECT_EQ(sum, 6);
}

TEST(Iterators, RangeFor) {
    Vector<int> v{1, 2, 3, 4};
    int sum = 0;
    for (int x : v) sum += x;
    EXPECT_EQ(sum, 10);
}

TEST(Iterators, ConstIterators) {
    const Vector<int> v{1, 2, 3};
    int sum = 0;
    for (auto it = v.cbegin(); it != v.cend(); ++it) sum += *it;
    EXPECT_EQ(sum, 6);
}

TEST(Iterators, ReverseIterators) {
    Vector<int> v{1, 2, 3};
    std::vector<int> rev(v.rbegin(), v.rend());
    EXPECT_EQ(rev[0], 3);
    EXPECT_EQ(rev[2], 1);
}

TEST(Iterators, EmptyBeginEqualsEnd) {
    Vector<int> v;
    EXPECT_EQ(v.begin(), v.end());
    EXPECT_EQ(v.cbegin(), v.cend());
}

// ─────────────────────────────────────────────────────────────────────────────
// Capacity
// ─────────────────────────────────────────────────────────────────────────────
TEST(Capacity, Empty) {
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    v.push_back(1);
    EXPECT_FALSE(v.empty());
}

TEST(Capacity, Size) {
    Vector<int> v;
    EXPECT_EQ(v.size(), 0u);
    v.push_back(1); v.push_back(2);
    EXPECT_EQ(v.size(), 2u);
}

TEST(Capacity, Reserve) {
    Vector<int> v;
    v.reserve(100);
    EXPECT_GE(v.capacity(), 100u);
    EXPECT_EQ(v.size(), 0u);
}

TEST(Capacity, ReserveDoesNotShrink) {
    Vector<int> v;
    v.reserve(100);
    size_t cap = v.capacity();
    v.reserve(10);
    EXPECT_EQ(v.capacity(), cap);
}

TEST(Capacity, ShrinkToFit) {
    Vector<int> v;
    v.reserve(1000);
    for (int i = 0; i < 5; ++i) v.push_back(i);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), v.size());
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < 5; ++i) EXPECT_EQ(v[i], static_cast<int>(i));
}

TEST(Capacity, CapacityGrowsOnPushBack) {
    Vector<int> v;
    size_t prev = 0;
    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
        EXPECT_GE(v.capacity(), v.size());
        EXPECT_GE(v.capacity(), prev);
        prev = v.capacity();
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Modifiers — push/pop/emplace
// ─────────────────────────────────────────────────────────────────────────────
TEST(Modifiers, PushBackLvalue) {
    Vector<int> v;
    int x = 42;
    v.push_back(x);
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v[0], 42);
}

TEST(Modifiers, PushBackRvalue) {
    Vector<std::string> v;
    std::string s = "hello";
    v.push_back(std::move(s));
    EXPECT_EQ(v[0], "hello");
}

TEST(Modifiers, PushBackMany) {
    Vector<int> v;
    for (int i = 0; i < 1000; ++i) v.push_back(i);
    EXPECT_EQ(v.size(), 1000u);
    for (size_t i = 0; i < 1000; ++i) EXPECT_EQ(v[i], static_cast<int>(i));
}

TEST(Modifiers, PopBack) {
    Vector<int> v{1, 2, 3};
    v.pop_back();
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v.back(), 2);
}

TEST(Modifiers, PopBackToEmpty) {
    Vector<int> v{1};
    v.pop_back();
    EXPECT_TRUE(v.empty());
}

TEST(Modifiers, PopBackOnEmpty) {
    Vector<int> v;
    EXPECT_NO_THROW(v.pop_back());  // Vector guards against this
}

TEST(Modifiers, EmplaceBack) {
    Vector<std::pair<int,int>> v;
    v.emplace_back(1, 2);
    v.emplace_back(3, 4);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0].first,  1); EXPECT_EQ(v[0].second, 2);
    EXPECT_EQ(v[1].first,  3); EXPECT_EQ(v[1].second, 4);
}

TEST(Modifiers, EmplaceBackReturnsRef) {
    Vector<int> v;
    int& r = v.emplace_back(42);
    EXPECT_EQ(r, 42);
    r = 99;
    EXPECT_EQ(v[0], 99);
}

TEST_F(TrackedFixture, PushBackDestroyCount) {
    {
        Vector<Tracked> v;
        for (int i = 0; i < 10; ++i) v.push_back(Tracked{i});
        EXPECT_EQ(Tracked::live, 10);
    }
    EXPECT_EQ(Tracked::live, 0);
}

// ─────────────────────────────────────────────────────────────────────────────
// Modifiers — clear / resize
// ─────────────────────────────────────────────────────────────────────────────
TEST(Modifiers, Clear) {
    Vector<int> v{1, 2, 3};
    size_t cap = v.capacity();
    v.clear();
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), cap);  // capacity preserved
}

TEST_F(TrackedFixture, ClearDestroys) {
    Vector<Tracked> v;
    for (int i = 0; i < 5; ++i) v.emplace_back(i);
    EXPECT_EQ(Tracked::live, 5);
    v.clear();
    EXPECT_EQ(Tracked::live, 0);
}

TEST(Modifiers, ResizeGrow) {
    Vector<int> v{1, 2, 3};
    v.resize(6, 99);
    EXPECT_EQ(v.size(), 6u);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 99); EXPECT_EQ(v[5], 99);
}

TEST(Modifiers, ResizeShrink) {
    Vector<int> v{1, 2, 3, 4, 5};
    v.resize(2);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], 1); EXPECT_EQ(v[1], 2);
}

TEST(Modifiers, ResizeSame) {
    Vector<int> v{1, 2, 3};
    v.resize(3);
    EXPECT_EQ(v.size(), 3u);
}

// ─────────────────────────────────────────────────────────────────────────────
// Modifiers — insert
// ─────────────────────────────────────────────────────────────────────────────
TEST(Insert, SingleValueAtBegin) {
    Vector<int> v{2, 3, 4};
    auto it = v.insert(v.begin(), 1);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(v[0], 1); EXPECT_EQ(v[1], 2);
}

TEST(Insert, SingleValueAtEnd) {
    Vector<int> v{1, 2, 3};
    auto it = v.insert(v.end(), 4);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(*it, 4);
    EXPECT_EQ(v.back(), 4);
}

TEST(Insert, SingleValueInMiddle) {
    Vector<int> v{1, 3, 4};
    v.insert(v.begin() + 1, 2);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[1], 2); EXPECT_EQ(v[2], 3);
}

TEST(Insert, RvalueInsert) {
    Vector<std::string> v{"a", "c"};
    std::string s = "b";
    v.insert(v.begin() + 1, std::move(s));
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[1], "b");
}

TEST(Insert, NCopiesToMiddle) {
    Vector<int> v{1, 4, 5};
    v.insert(v.begin() + 1, 2, 99);
    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[1], 99); EXPECT_EQ(v[2], 99);
    EXPECT_EQ(v[3], 4);
}

TEST(Insert, NCopiesZero) {
    Vector<int> v{1, 2, 3};
    v.insert(v.begin() + 1, 0, 99);
    EXPECT_EQ(v.size(), 3u);
}

TEST(Insert, IteratorRange) {
    Vector<int> v{1, 4, 5};
    std::list<int> src{2, 3};
    v.insert(v.begin() + 1, src.begin(), src.end());
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < 5; ++i) EXPECT_EQ(v[i], static_cast<int>(i) + 1);
}

TEST(Insert, InitializerList) {
    Vector<int> v{1, 5};
    v.insert(v.begin() + 1, {2, 3, 4});
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < 5; ++i) EXPECT_EQ(v[i], static_cast<int>(i) + 1);
}

TEST(Insert, IntoEmpty) {
    Vector<int> v;
    v.insert(v.begin(), 42);
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v[0], 42);
}

// ─────────────────────────────────────────────────────────────────────────────
// Modifiers — erase
// ─────────────────────────────────────────────────────────────────────────────
TEST(Erase, SingleElement) {
    Vector<int> v{1, 2, 3, 4};
    auto it = v.erase(v.begin() + 1);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(v[0], 1); EXPECT_EQ(v[1], 3); EXPECT_EQ(v[2], 4);
}

TEST(Erase, LastElement) {
    Vector<int> v{1, 2, 3};
    auto it = v.erase(v.end() - 1);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(it, v.end());
}

TEST(Erase, Range) {
    Vector<int> v{1, 2, 3, 4, 5};
    auto it = v.erase(v.begin() + 1, v.begin() + 4);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(*it, 5);
    EXPECT_EQ(v[0], 1); EXPECT_EQ(v[1], 5);
}

TEST(Erase, EmptyRange) {
    Vector<int> v{1, 2, 3};
    auto it = v.erase(v.begin() + 1, v.begin() + 1);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(*it, 2);
}

TEST(Erase, AllElements) {
    Vector<int> v{1, 2, 3};
    v.erase(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST_F(TrackedFixture, EraseDestroys) {
    Vector<Tracked> v;
    for (int i = 0; i < 4; ++i) v.emplace_back(i);
    EXPECT_EQ(Tracked::live, 4);
    v.erase(v.begin() + 1);
    EXPECT_EQ(Tracked::live, 3);
}

// ─────────────────────────────────────────────────────────────────────────────
// Modifiers — emplace
// ─────────────────────────────────────────────────────────────────────────────
TEST(Emplace, EmplaceAtBegin) {
    Vector<std::pair<int,int>> v{{2,2},{3,3}};
    v.emplace(v.begin(), 1, 1);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0].first, 1);
}

TEST(Emplace, EmplaceInMiddle) {
    Vector<int> v{1, 2, 4, 5};
    auto it = v.emplace(v.begin() + 2, 3);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < 5; ++i) EXPECT_EQ(v[i], static_cast<int>(i) + 1);
}

// ─────────────────────────────────────────────────────────────────────────────
// Swap
// ─────────────────────────────────────────────────────────────────────────────
TEST(Swap, MemberSwap) {
    Vector<int> a{1, 2, 3};
    Vector<int> b{4, 5};
    a.swap(b);
    EXPECT_EQ(a.size(), 2u); EXPECT_EQ(a[0], 4);
    EXPECT_EQ(b.size(), 3u); EXPECT_EQ(b[0], 1);
}

TEST(Swap, NonMemberSwap) {
    Vector<int> a{1, 2, 3};
    Vector<int> b{4, 5};
    swap(a, b);
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 3u);
}

TEST(Swap, SwapWithEmpty) {
    Vector<int> a{1, 2, 3};
    Vector<int> b;
    a.swap(b);
    EXPECT_TRUE(a.empty());
    EXPECT_EQ(b.size(), 3u);
}

// ─────────────────────────────────────────────────────────────────────────────
// Comparison operators
// ─────────────────────────────────────────────────────────────────────────────
TEST(Comparison, Equal) {
    Vector<int> a{1, 2, 3}, b{1, 2, 3};
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(Comparison, NotEqual) {
    Vector<int> a{1, 2, 3}, b{1, 2, 4};
    EXPECT_TRUE(a != b);
}

TEST(Comparison, DifferentSizes) {
    Vector<int> a{1, 2}, b{1, 2, 3};
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}

TEST(Comparison, LessThan) {
    Vector<int> a{1, 2, 3}, b{1, 2, 4};
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(Comparison, LexicographicOrder) {
    Vector<int> a{1, 2}, b{1, 2, 0};
    EXPECT_TRUE(a < b);   // shorter is less when prefix matches
}

TEST(Comparison, Spaceship) {
    Vector<int> a{1, 2, 3}, b{1, 2, 3}, c{1, 2, 4};
    EXPECT_EQ(a <=> b, std::strong_ordering::equal);
    EXPECT_EQ(a <=> c, std::strong_ordering::less);
    EXPECT_EQ(c <=> a, std::strong_ordering::greater);
}

// ─────────────────────────────────────────────────────────────────────────────
// Non-member erase / erase_if
// ─────────────────────────────────────────────────────────────────────────────
TEST(NonMemberErase, EraseByValue) {
    Vector<int> v{1, 2, 2, 3, 2, 4};
    auto n = erase(v, 2);
    EXPECT_EQ(n, 3u);
    EXPECT_EQ(v.size(), 3u);
    Vector<int> expected{1, 3, 4};
    EXPECT_EQ(v, expected);
}

TEST(NonMemberErase, EraseNotPresent) {
    Vector<int> v{1, 2, 3};
    auto n = erase(v, 99);
    EXPECT_EQ(n, 0u);
    EXPECT_EQ(v.size(), 3u);
}

TEST(NonMemberErase, EraseIf) {
    Vector<int> v{1, 2, 3, 4, 5, 6};
    auto n = erase_if(v, [](int x){ return x % 2 == 0; });
    EXPECT_EQ(n, 3u);
    Vector<int> expected{1, 3, 5};
    EXPECT_EQ(v, expected);
}

TEST(NonMemberErase, EraseIfNone) {
    Vector<int> v{1, 3, 5};
    auto n = erase_if(v, [](int x){ return x % 2 == 0; });
    EXPECT_EQ(n, 0u);
    EXPECT_EQ(v.size(), 3u);
}

// ─────────────────────────────────────────────────────────────────────────────
// String (non-trivial type)
// ─────────────────────────────────────────────────────────────────────────────
TEST(StringType, PushBackAndAccess) {
    Vector<std::string> v;
    v.push_back("hello");
    v.push_back("world");
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], "hello");
    EXPECT_EQ(v[1], "world");
}

TEST(StringType, CopyConstructor) {
    Vector<std::string> a{"one", "two", "three"};
    Vector<std::string> b(a);
    EXPECT_EQ(b.size(), 3u);
    b[0] = "modified";
    EXPECT_EQ(a[0], "one");  // deep copy
}

TEST(StringType, MoveIntoVector) {
    Vector<std::string> v;
    for (size_t i = 0; i < 20; ++i)
        v.push_back("string_" + std::to_string(i));
    EXPECT_EQ(v.size(), 20u);
    for (size_t i = 0; i < 20; ++i)
        EXPECT_EQ(v[i], "string_" + std::to_string(i));  // i is size_t here
}

// ─────────────────────────────────────────────────────────────────────────────
// Implicit conversions
// ─────────────────────────────────────────────────────────────────────────────
TEST(Conversions, ToStdVector) {
    Vector<int> v{1, 2, 3};
    std::vector<int> sv = v;
    EXPECT_EQ(sv.size(), 3u);
    EXPECT_EQ(sv[0], 1); EXPECT_EQ(sv[2], 3);
}

TEST(Conversions, ToSpan) {
    Vector<int> v{1, 2, 3};
    std::span<int> s = v;
    EXPECT_EQ(s.size(), 3u);
    EXPECT_EQ(s[0], 1);
}

TEST(Conversions, ToConstSpan) {
    const Vector<int> v{1, 2, 3};
    std::span<const int> s = v;
    EXPECT_EQ(s.size(), 3u);
}

// ─────────────────────────────────────────────────────────────────────────────
// Growth and memory
// ─────────────────────────────────────────────────────────────────────────────
TEST(Growth, CapacityNeverSmallerThanSize) {
    Vector<int> v;
    for (int i = 0; i < 500; ++i) {
        v.push_back(i);
        EXPECT_GE(v.capacity(), v.size());
    }
}

TEST(Growth, ContentsPreservedAcrossReallocation) {
    Vector<int> v;
    v.reserve(1);  // force small initial capacity
    for (int i = 0; i < 200; ++i) v.push_back(i);
    for (size_t i = 0; i < 200; ++i) EXPECT_EQ(v[i], static_cast<int>(i));
}

TEST_F(TrackedFixture, NoLeakAfterReallocation) {
    Vector<Tracked> v;
    for (int i = 0; i < 50; ++i) v.emplace_back(i);
    EXPECT_EQ(Tracked::live, 50);
    // destructor runs here, TearDown checks live==0
}

// ─────────────────────────────────────────────────────────────────────────────
// C++23 range methods
// ─────────────────────────────────────────────────────────────────────────────
TEST(RangeMethods, AssignRange) {
    std::list<int> src{7, 8, 9};
    Vector<int> v{1, 2, 3};
    v.assign_range(src);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 7);
}

TEST(RangeMethods, AppendRange) {
    Vector<int> v{1, 2};
    std::list<int> src{3, 4, 5};
    v.append_range(src);
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < 5; ++i) EXPECT_EQ(v[i], static_cast<int>(i) + 1);
}

TEST(RangeMethods, InsertRange) {
    Vector<int> v{1, 5};
    std::list<int> src{2, 3, 4};
    v.insert_range(v.begin() + 1, src);
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < 5; ++i) EXPECT_EQ(v[i], static_cast<int>(i) + 1);
}