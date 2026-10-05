#include <iostream>
#include "woodpecker.hpp"
#include "multiList.hpp"

TEST("Empy list") {
    MultiList<int> list;
    CHECK_EQ(list.getSize(), 0);
    CHECK_EQ(list.contains(42), false);
    CHECK_EQ(list.erase(42), false);
}

TEST("Single element") {
    MultiList<int> list;

    CHECK_EQ(list.insert(42), true); 
    CHECK_EQ(list.insert(42), false); //Inserting again should fail

    CHECK_EQ(list.getSize(), 1);
    CHECK_EQ(list.contains(42), true);
    CHECK_EQ(list.contains(43), false);

    CHECK_EQ(list.erase(43), false);
    CHECK_EQ(list.erase(42), true);
    CHECK_EQ(list.erase(42), false);

    //List is empty again
    CHECK_EQ(list.getSize(), 0);
    CHECK_EQ(list.contains(42), false);
    CHECK_EQ(list.erase(42), false);
}

TEST("Tricky insertion/erasure") {
    MultiList<int> list;

    CHECK_EQ(list.insert(3), true);
    CHECK_EQ(list.insert(1), true); //Inserting before existing Node
    CHECK_EQ(list.insert(2), true); //Inserting between Nodes
    CHECK_EQ(list.insert(4), true); //Inserting last Node

    //Re-insertions should fail
    CHECK_EQ(list.insert(1), false);
    CHECK_EQ(list.insert(2), false);
    CHECK_EQ(list.insert(3), false);
    CHECK_EQ(list.insert(4), false);

    CHECK_EQ(list.contains(1), true);
    CHECK_EQ(list.contains(2), true);
    CHECK_EQ(list.contains(3), true);
    CHECK_EQ(list.contains(4), true);

    CHECK_EQ(list.getSize(), 4);

    CHECK_EQ(list.erase(4), true);
    CHECK_EQ(list.erase(2), true);
    CHECK_EQ(list.erase(1), true);
    CHECK_EQ(list.erase(3), true);

    CHECK_EQ(list.erase(1), false);
    CHECK_EQ(list.erase(2), false);
    CHECK_EQ(list.erase(3), false);
    CHECK_EQ(list.erase(4), false);

    CHECK_EQ(list.contains(1), false);
    CHECK_EQ(list.contains(2), false);
    CHECK_EQ(list.contains(3), false);
    CHECK_EQ(list.contains(4), false);

    CHECK_EQ(list.getSize(), 0);
}

WOODPECKER_TEST_MAIN()