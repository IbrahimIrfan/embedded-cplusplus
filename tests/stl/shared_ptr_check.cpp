#include "gtest/gtest.h"

#include "stl/SharedPtr.h"

using namespace wlp;

static int __destructs;

struct Integer {
    int v;

    Integer() : v(0) {}

    Integer(int i) : v(i) {}

    ~Integer() { ++__destructs; }
};

typedef SharedPtr<Integer> shared_ptr;
typedef WeakPtr<Integer> weak_ptr;

TEST(shared_ptr_test, test_multiple_shared_delete) {
    __destructs = 0;
    shared_ptr p1 = shared_ptr(malloc<Integer>(6));
    ASSERT_EQ(6, (*p1).v);
    ASSERT_EQ(1, p1.use_count());
    ASSERT_TRUE(p1.unique());
    shared_ptr p2 = p1;
    ASSERT_EQ(2, p1.use_count());
    ASSERT_EQ(2, p2.use_count());
    ASSERT_EQ(6, p2->v);
    ASSERT_FALSE(p2.unique());
    ASSERT_EQ(p1->v, p2->v);
    shared_ptr p3 = shared_ptr(malloc<Integer>(10));
    ASSERT_EQ(10, p3->v);
    ASSERT_EQ(1, p3.use_count());
    p2.swap(p3);
    ASSERT_EQ(10, p2->v);
    ASSERT_EQ(1, p2.use_count());
    ASSERT_EQ(2, p3.use_count());
    ASSERT_EQ(6, p3->v);
    p2 = p3;
    ASSERT_EQ(3, p3.use_count());
    ASSERT_EQ(3, p2.use_count());
    ASSERT_EQ(3, p1.use_count());
    ASSERT_EQ(6, p2->v);
    ASSERT_FALSE(p1.owner_before(p2));
    ASSERT_FALSE(p2.owner_before(p1));
    ASSERT_FALSE(p3.owner_before(p2));
    p1.reset(malloc<Integer>(15));
    ASSERT_EQ(2, p2.use_count());
    ASSERT_EQ(2, p3.use_count());
    ASSERT_EQ(1, p1.use_count());
    ASSERT_EQ(15, p1->v);
    ASSERT_EQ(6, p2->v);
    ASSERT_EQ(6, p3->v);
    p3.reset();
    ASSERT_EQ(1, p2.use_count());
    ASSERT_TRUE(p2.unique());
    p2.reset();
    p1.reset();
    ASSERT_EQ(3, __destructs);
}

TEST(shared_ptr_test, test_destruction_out_of_scope) {
    __destructs = 0;
    shared_ptr p1 = shared_ptr(malloc<Integer>(1));
    ASSERT_EQ(1, p1.use_count());
    {
        shared_ptr p2(p1);
        ASSERT_EQ(2, p2.use_count());
        ASSERT_EQ(2, p1.use_count());
        ASSERT_EQ(1, p2->v);
    }
    ASSERT_EQ(0, __destructs);
    ASSERT_EQ(1, p1.use_count());
}

TEST(shared_ptr_test, test_weak_ptr) {
    __destructs = 0;
    shared_ptr sp1 = shared_ptr(malloc<Integer>(1));
    shared_ptr sp2(sp1);
    shared_ptr sp3(sp2);
    ASSERT_EQ(3, sp1.use_count());
    weak_ptr wp1 = sp1.weak();
    weak_ptr wp2 = wp1;
    weak_ptr wp3 = sp3.weak();
    weak_ptr wps[] = {wp1, wp2, wp3};
    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(3, wps[i].use_count());
        {
            shared_ptr sp = wps[i].lock();
            ASSERT_EQ(4, sp.use_count());
            ASSERT_EQ(4, wps[i].use_count());
            ASSERT_EQ(1, sp->v);
        }
        ASSERT_EQ(3, wps[i].use_count());
        ASSERT_EQ(0, __destructs);
    }
    shared_ptr sp4 = wp3.lock();
    ASSERT_EQ(4, sp3.use_count());
    ASSERT_EQ(4, sp4.use_count());
    ASSERT_EQ(4, sp1.use_count());
    sp4.reset();
    ASSERT_EQ(3, wp2.use_count());
    ASSERT_EQ(3, sp1.use_count());
    sp3.reset();
    sp2.reset();
    ASSERT_EQ(0, __destructs);
    ASSERT_FALSE(wp1.expired());
    sp1.reset();
    ASSERT_EQ(1, __destructs);
    ASSERT_TRUE(wp1.expired());
    ASSERT_TRUE(wp2.expired());
    ASSERT_TRUE(wp3.expired());
}
