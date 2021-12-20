#include <gtest/gtest.h>
extern "C" {
#include "dopf.h"
}

TEST(delivery_solver_test, compares_with_known_solution) {
    int N = 3, K = 5;
    Good goods[N];
    unsigned int ans[3];
    goods[0].l_t = 2;
    goods[0].d_t = 3;
    goods[0].w_t = 1;
    goods[1].l_t = 3;
    goods[1].d_t = 3;
    goods[1].w_t = 2;
    goods[2].l_t = 1;
    goods[2].d_t = 4;
    goods[2].w_t = 3;
    int cheak_test = delivery_solver(goods, N, K, &ans[0]);
    EXPECT_TRUE(cheak_test = 1);
    EXPECT_TRUE(ans[0] = 2);
    EXPECT_TRUE(ans[1] = 3);
    EXPECT_TRUE(ans[2] = 1);
}

TEST(delivery_solver_test, if_not_found_solution) {
    int N = 3, K = 5;
    Good goods[N];
    unsigned int ans[3];
    goods[0].l_t = 1;
    goods[0].d_t = 2;
    goods[0].w_t = 3;
    goods[1].l_t = 1;
    goods[1].d_t = 2;
    goods[1].w_t = 3;
    goods[2].l_t = 1;
    goods[2].d_t = 2;
    goods[2].w_t = 3;
    int cheak_test = delivery_solver(goods, N, K, &ans[0]);
    EXPECT_TRUE(cheak_test = 0);
}



