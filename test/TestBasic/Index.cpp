#include <Basic/Index.hpp>
#include <gtest/gtest.h>

NameSpace_Math_Begin

template struct IndexD<2>;
template struct IndexD<3>;

TEST(Index, Common)
{
	Scale sc({ 2, 3 });

    EXPECT_EQ(sc.ind2sub({0, 1}), 2);
    EXPECT_EQ(sc.ind2sub({1, 1}), 3);
    EXPECT_EQ(sc.ind2sub({1, 2}), 5);

    EXPECT_EQ(sc.sub2ind(5), Index({1, 2}));

	Scale sc2({ 2, 3, 5 });

    EXPECT_EQ(sc2.ind2sub({0, 1, 1}), 8);
    EXPECT_EQ(sc2.ind2sub({1, 2, 4}), 29);      

    EXPECT_EQ(sc2.sub2ind(29), Index({1, 2, 4}));

    EXPECT_TRUE(sc < sc2);
    EXPECT_TRUE(sc.innerThan(sc2));
    EXPECT_TRUE(sc2.outerThan(sc));

    Scale sc3({3, 4});
    EXPECT_TRUE(sc < sc3);
    EXPECT_TRUE(sc3 > sc);
    EXPECT_TRUE(sc.innerThan(sc3));
    EXPECT_TRUE(sc3.outerThan(sc));

    Scale sc4({3, 2});
    EXPECT_FALSE(sc < sc4);
    EXPECT_FALSE(sc4 > sc);
    EXPECT_FALSE(sc.innerThan(sc4));
    EXPECT_FALSE(sc4.outerThan(sc));
}

NameSpace_Math_End