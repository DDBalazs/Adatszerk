#include "AvlTree.hpp"
#include "woodpecker.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <set>

std::random_device rd;
std::mt19937 gen(rd()); // pseudo random szam generator
std::uniform_int_distribution<int> dist(0, std::numeric_limits<int>::max());

TEST("Empty Tree", 1) {
  AvlTree<int> tree;
  CHECK_EQ(tree.isEmpty(), true);
  CHECK_EQ(tree.size(), 0uz);
}

TEST("Basic insertion", 1) {
  AvlTree<int> tree;
  CHECK_EQ(tree.isEmpty(), true);
  CHECK_EQ(tree.size(), 0uz);

  tree.insert(2);
  CHECK_EQ(tree.isEmpty(), false);
  CHECK_EQ(tree.size(), 1uz);
  CHECK_EQ(tree.find(2), true);
  CHECK_NOEXC(tree.validate());
  tree.insert(3);
  CHECK_EQ(tree.isEmpty(), false);
  CHECK_EQ(tree.size(), 2uz);
  CHECK_EQ(tree.find(3), true);
  CHECK_NOEXC(tree.validate());
  tree.insert(5);
  CHECK_EQ(tree.isEmpty(), false);
  CHECK_EQ(tree.size(), 3uz);
  CHECK_EQ(tree.find(5), true);
  CHECK_NOEXC(tree.validate());
}

TEST("Removal", 1) {
  AvlTree<int> tree;
  CHECK_EQ(tree.isEmpty(), true);
  CHECK_EQ(tree.size(), 0uz);
  tree.insert(2);
  CHECK_EQ(tree.isEmpty(), false);
  CHECK_EQ(tree.size(), 1uz);
  CHECK_EQ(tree.find(2), true);
  CHECK_NOEXC(tree.validate());
  tree.insert(3);
  CHECK_EQ(tree.isEmpty(), false);
  CHECK_EQ(tree.size(), 2uz);
  CHECK_EQ(tree.find(3), true);
  CHECK_NOEXC(tree.validate());

  tree.remove(2);
  CHECK_EQ(tree.isEmpty(), false);
  CHECK_EQ(tree.size(), 1uz);
  CHECK_NOEXC(tree.validate());
  CHECK_EQ(tree.find(2), false);
  CHECK_EQ(tree.find(3), true);

  tree.remove(3);
  CHECK_EQ(tree.isEmpty(), true);
  CHECK_EQ(tree.size(), 0uz);
  CHECK_NOEXC(tree.validate());
  CHECK_EQ(tree.find(2), false);
  CHECK_EQ(tree.find(3), false);
}

TEST("Copy constructor test", 1) {
  AvlTree<int> avlTree;
  for (int i = 0; i < 10; ++i) {
    avlTree.insert(dist(gen));
  }

  AvlTree avlTree2(avlTree);
  CHECK_NOEXC(avlTree2.validate());

  std::ostringstream originalPreorder, copyPreorder;
  avlTree.preorder(originalPreorder);
  avlTree2.preorder(copyPreorder);
  CHECK_EQ(originalPreorder.str(), copyPreorder.str());
}

/**
  *      Futtatunk egy tesztet, amely 1000 véletlen számot szúr be az AVL
  *      fánkba. Minden egyes beszúrás után ellenõrizzük, hogy az
  *      adatszerkezet érvényes AVL fa-e.
  *
  *      Hogy kizárjuk annak lehetõségét, hogy véletlenül csúcsokat drótozunk
  *      ki a fából, amikor nem is akarunk törölni, ugyanezeket a számokat
  *      beszúrjuk egy std::set-be is, majd ellenõrizzük, hogy a két
  *      adatszerkezet ugyanannyi elemet tartalmaz.
  *
  *      Végül az std::set-bõl az elemeket kimásoljuk egy std::vector-ba,
  *      amit megkeverünk, hogy véletlenszerû sorrendben tudjuk törölni az
  *      összes elemet a fából. Ezzel ellenõrizzük, hogy a törlés jól
  *      mûködik-e, és a végén megnézzük, hogy tényleg üres lett-e az AVL
  *      fánk.
  */

TEST("Small test with 1000 elements", 1) {
  std::set<int> treeSet;
  AvlTree<int> avlTree;

  for (int i = 0; i < 1000; i++) {
    int x = dist(gen);
    treeSet.insert(x);
    avlTree.insert(x);
    CHECK_NOEXC(avlTree.validate());
  }

  CHECK_EQ(avlTree.size(), treeSet.size());

  std::vector removeArray(treeSet.begin(), treeSet.end());
  std::ranges::shuffle(removeArray, gen);

  for (const auto &val : removeArray) {
    avlTree.remove(val);
    CHECK_NOEXC(avlTree.validate());
  }

  CHECK_EQ(avlTree.size(), 0uz);
}

/**
  *      Most egymillió véletlen számot szúrunk be az AVL fába, és
  *      párhuzamosan egy std::set-be. Csak a végén ellenõrizzük, hogy
  *      érvényes-e az AVL fa és egyezik-e a két adatszerkezet mérete.
  *
  *      Ezután megnézzük, hogy minden std::set-beli elem megtalálható-e az
  *      AVL fában, majd sorban kitöröljuk õket, és ellenõrizzük, hogy üres
  *      lett-e a fa.
  *
  *      Ennek a tesztnek néhány másodperc alatt le kell futnia. Ha fél
  *      percnél tovább tart, akkor olyan hiba lehet a kódban, ami elrontja
  *      az aszimptotikus futási idõt.
  */

TEST("Large test with 1,000,000 elements", 1) {
  std::set<int> treeSet;
  AvlTree<int> avlTree;

  for (int i = 0; i < 1000000; i++) {
    int x = dist(gen);
    treeSet.insert(x);
    avlTree.insert(x);
  }

  CHECK_NOEXC(avlTree.validate());
  CHECK_EQ(avlTree.size(), treeSet.size());

  for (const auto &val : treeSet) {
    CHECK_EQ(avlTree.find(val), true);
  }

  for (const auto &val : treeSet) {
    avlTree.remove(val);
  }

  CHECK_NOEXC(avlTree.validate());
  CHECK_EQ(avlTree.size(), 0uz);
}


WOODPECKER_MAIN(-1,-1)
