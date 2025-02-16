#define CATCH_CONFIG_FAST_COMPILE
#include "catch_amalgamated.hpp"
#include "../avlTree.h"

#include <sstream>
#include <string>
using namespace std;

avlTree<int> make_easy_test_tree() { // order of insertion requires AVL no balancing
    avlTree<int> tree;
    for(int i : { 6, 3, 9, 2, 4, 7, 10, 1, 5, 8 })
        tree.insert(i);
    return tree;
}

TEST_CASE( "Insert", "[avlTree]") {

    SECTION( "Insert into empty tree" ) {
        avlTree<int> tree;
        tree.insert(42);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE( oss.str() == "42\n" );
    }

    SECTION( "Insert smaller to the left" ) {
        avlTree<int> tree;
        tree.insert(3);
        tree.insert(2);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE( oss.str()  == "3\n"
                                    "|_ 2\n"
                                    "|_ .\n" );
    }

    SECTION( "Insert larger to the right" ) {
        avlTree<int> tree;
        tree.insert(3);
        tree.insert(4);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE( oss.str()  == "3\n"
                                    "|_ .\n"
                                    "|_ 4\n" );
    }

    SECTION( "Insert twice has no effect" ) {
        avlTree<int> tree;
        tree.insert(3);
        tree.insert(4);
        tree.insert(4);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE( oss.str()  == "3\n"
                                    "|_ .\n"
                                    "|_ 4\n" );
    }

    SECTION( "Easy tree") {
        avlTree<int> tree = make_easy_test_tree();

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE( oss.str()  == "6\n"
                                    "|_ 3\n"
                                    "|  |_ 2\n"
                                    "|  |  |_ 1\n"
                                    "|  |  |_ .\n"
                                    "|  |_ 4\n"
                                    "|     |_ .\n"
                                    "|     |_ 5\n"
                                    "|_ 9\n"
                                    "   |_ 7\n"
                                    "   |  |_ .\n"
                                    "   |  |_ 8\n"
                                    "   |_ 10\n");
    }

    SECTION("Inserting with rebalancing") {
        ostringstream oss;
        avlTree<int> tree;
        tree.insert(3);
        tree.insert(1);
        tree.insert(12);

        oss << tree;
        REQUIRE(oss.str() == "3(1(.,.),12(.,.))");
        oss.str("");
        tree.insert(8);

        oss << tree;
        REQUIRE(oss.str() == "3(1(.,.),12(8(.,.),.))");
    }
}

TEST_CASE("Constructor", "[avlTree]") {
    SECTION("Empty tree") {
        avlTree<int> tree;
        REQUIRE(tree.height() == 0);
    }
}

TEST_CASE("Copy constructor", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> firstTree;
        avlTree<int> secondTree(firstTree);

        REQUIRE(secondTree.height() == 0);
    }

    SECTION("Copy easy test tree") {
        avlTree<int> firstTree = make_easy_test_tree();
        avlTree<int> secondTree(firstTree);

        ostringstream oss;
        oss << secondTree;
        REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }
}

TEST_CASE("Display_indented", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == ".\n");
    }

    SECTION("Easy test tree") {
        avlTree<int> tree = make_easy_test_tree();

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "6\n"
                             "|_ 3\n"
                             "|  |_ 2\n"
                             "|  |  |_ 1\n"
                             "|  |  |_ .\n"
                             "|  |_ 4\n"
                             "|     |_ .\n"
                             "|     |_ 5\n"
                             "|_ 9\n"
                             "   |_ 7\n"
                             "   |  |_ .\n"
                             "   |  |_ 8\n"
                             "   |_ 10\n");
    }
}

TEST_CASE("Operator<<", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;
        ostringstream oss;
        oss << tree;
        REQUIRE( oss.str() == ".");
    }

    SECTION("Easy test tree") {
        avlTree<int> tree = make_easy_test_tree();

        ostringstream oss;
        oss << tree;
        REQUIRE( oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))" );
    }
}

TEST_CASE("Contains", "[avlTree]") {

    SECTION("Not found in empty tree") {
        avlTree<int> tree;
        CHECK_FALSE(tree.contains(0));
        CHECK_FALSE(tree.contains(42));
    }

    SECTION("Contained in tree") {
        avlTree<int> tree = make_easy_test_tree();
        CHECK(tree.contains(7));
        CHECK(tree.contains(10));
    }

    SECTION("Not contained in tree") {
        avlTree<int> tree = make_easy_test_tree();
        CHECK_FALSE(tree.contains(42));
        CHECK_FALSE(tree.contains(14));
    }
}

TEST_CASE("Min", "[avlTree]") {

    SECTION("Throws if empty") {
        avlTree<int> tree;
        REQUIRE_THROWS_MATCHES(tree.min(), std::invalid_argument,
                               Catch::Matchers::Message("Empty tree"));
    }

    SECTION("Returns min value") {
        avlTree<int> tree = make_easy_test_tree();
        REQUIRE(tree.min() == 1);
    }
}

TEST_CASE("Max", "[avlTree]") {

    SECTION("Throws if empty") {
        avlTree<int> tree;
        REQUIRE_THROWS_MATCHES(tree.max(), std::invalid_argument,
                               Catch::Matchers::Message("Empty tree"));
    }

    SECTION("Returns max value") {
        avlTree<int> tree = make_easy_test_tree();
        REQUIRE(tree.max() == 10);
    }
}

TEST_CASE( "Destructor", "[avlTree]") {
    SECTION( "Destruction of an empty tree" ) {
        avlTree<int> tree;
        tree.~avlTree();
        REQUIRE(tree.height() == 0);
    }

    SECTION( "Destruction of a full tree" ) {
        avlTree<int> tree;
        for (int i : {6, 2, 3, 4, 8, 7, 1, 5}){
            tree.insert(i);
        }
        tree.~avlTree();
        REQUIRE(tree.height() == 0);
    }
}

TEST_CASE("Operator=", "[avlTree]") {

    SECTION("Assign empty tree onto empty tree") {
        avlTree<int> firstTree;
        avlTree<int> secondTree;
        secondTree = firstTree;
        REQUIRE(secondTree.height() == 0);
    }

    SECTION("Assign tree onto empty tree") {
        avlTree<int> firstTree = make_easy_test_tree();
        avlTree<int> secondTree;

        secondTree = firstTree;

        ostringstream oss;
        oss << secondTree;
        REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }

    SECTION("Assign tree onto existing tree") {
        avlTree<int> firstTree = make_easy_test_tree();
        avlTree<int> secondTree;
        for (int i : {1, 21, 20, 9, 19, 13}){
            secondTree.insert(i);
        }

        secondTree = firstTree;

        ostringstream oss;
        oss << secondTree;
        REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }
}

TEST_CASE( "Operator>>", "[avlTree]") {
    SECTION( "Empty tree" ) {
        avlTree<int> tree;
        ostringstream oss;
        oss << tree;
        REQUIRE( oss.str() == "." );
    }

    SECTION("Tree with values") {
        avlTree<int> tree;

        stringstream in("3(2(1(.,.),.),5(4(.,.),6(.,12(9(8(.,.),.),.))))");
        in >> tree;

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "3(2(1(.,.),.),5(4(.,.),6(.,12(9(8(.,.),.),.))))");
        REQUIRE(tree.height() == 6);
    }

    SECTION("Test tree with different order") {
        avlTree<int> tree;

        stringstream ss("3(4(1(.,2(.,.)),5(.,6(.,.))),7(.,8(.,.)))");
        ss >> tree;

        ostringstream oss;
        oss << tree;
        REQUIRE( oss.str() == "3(4(1(.,2(.,.)),5(.,6(.,.))),7(.,8(.,.)))" );
        REQUIRE( tree.height() == 4 );
    }

    SECTION("Test tree with different order and spaces") {
        avlTree<int> tree;

        stringstream ss("  3 ( 4 ( 1 ( . , 2 ( . , . ) ) , 5 ( . , 6 ( . , . ) ) ) , 7 ( . , 8 ( . , . ) ) ) ");
        ss >> tree;

        ostringstream oss;
        oss << tree;
        REQUIRE( oss.str() == "3(4(1(.,2(.,.)),5(.,6(.,.))),7(.,8(.,.)))" );
        REQUIRE( tree.height() == 4 );
    }

    SECTION("Test with missing right parenthesis") {
        avlTree<int> tree;

        stringstream ss("4(1(.,2(.,.)),5(.,6(.,.)),7(.,8(.,.))");
        REQUIRE_THROWS_MATCHES(ss >> tree, std::invalid_argument,
                               Catch::Matchers::Message("Expected ')' after right node"));
    }

    SECTION("Test with missing left parenthesis") {
        avlTree<int> tree;

        stringstream in("3 2(1(.,.),.),5(4(.,.),6(.,12(9(8(.,.),.),.))))");
        REQUIRE_THROWS_MATCHES(in >> tree, std::invalid_argument,
                               Catch::Matchers::Message("Expected '(' after parent node"));
    }

    SECTION("Test with missing node separation") {
        avlTree<int> tree;

        stringstream ss("3(2(1(.,.),.),5(4(..),6(.,12(9(8(.,.),.),.))))");
        REQUIRE_THROWS_MATCHES(ss >> tree, std::invalid_argument,
                               Catch::Matchers::Message("Expected ',' after left node"));
    }

    SECTION("Test with unknown character") {
        avlTree<int> tree;

        stringstream ss("3(2(1(.,.),.),5(4(.,?),6(.,12(9(8(.,.),.),.))))");
        REQUIRE_THROWS_MATCHES(ss >> tree, std::invalid_argument,
                               Catch::Matchers::Message("Expected '.' or digit"));
    }
}

TEST_CASE("Erase", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;
        tree.erase(8);
        REQUIRE(tree.height() == 0);
    }

    SECTION("Erase root") {
        avlTree<int> tree;
        tree.insert(8);
        tree.erase(8);
        REQUIRE(tree.height() == 0);
    }

    SECTION("Erase one value") {
        avlTree<int> tree = make_easy_test_tree();
        tree.erase(10);

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),8(7(.,.),9(.,.)))");
    }

    SECTION("Erase all values") {
        avlTree<int> tree = make_easy_test_tree();
        for (int i : {3, 2, 4, 1, 5, 6, 9, 7, 8, 10})
            tree.erase(i);
        REQUIRE(tree.height() == 0);
    }

    SECTION("Erase rebalancing") {
        avlTree<int> tree = {3, 1, 12, 2, 10, 13, 7, 11};
        tree.erase(2);

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "10(3(1(.,.),7(.,.)),12(11(.,.),13(.,.)))");
    }
}

TEST_CASE("EraseMin", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;
        REQUIRE_THROWS_MATCHES(tree.eraseMin(), std::invalid_argument,
                               Catch::Matchers::Message("Empty tree"));
    }

    SECTION("Erases min value") {
        avlTree<int> tree = make_easy_test_tree();
        tree.eraseMin();

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "6(3(2(.,.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }

    SECTION("Erase min value with rebalancing") {
        avlTree<int> tree = {3, 1, 12, 2, 10, 13, 7, 11};
        tree.eraseMin();

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "10(3(2(.,.),7(.,.)),12(11(.,.),13(.,.)))");
    }
}

TEST_CASE("EraseMax", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;
        REQUIRE_THROWS_MATCHES(tree.eraseMax(), std::invalid_argument,
                               Catch::Matchers::Message("Empty tree"));
    }

    SECTION("Erases max value") {
        avlTree<int> tree = make_easy_test_tree();
        tree.eraseMax();

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),8(7(.,.),9(.,.)))");
    }

    SECTION("Erase max value with rebalancing") {
        avlTree<int> tree = {3, 1, 12, 2, 10, 13, 7, 11};
        tree.eraseMax();

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "3(1(.,2(.,.)),10(7(.,.),12(11(.,.),.)))");
    }
}