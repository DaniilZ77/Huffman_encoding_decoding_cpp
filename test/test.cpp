#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "huffman_tree_node.h"
#include "huffman_tree.h"
#include "huffman_archiver.h"
#include <vector>
#include <fstream>

typedef huffman_archiver::huffman_tree_node htn;
typedef huffman_archiver::huffman_tree ht;
typedef huffman_archiver::huffman_archiver ha;

TEST_CASE("simple huffman tree node creation")
{
    htn *node = new htn(5, true, 'A');

    CHECK(node->get_byte() == 'A');
    CHECK(node->is_leaf() == true);
    CHECK(node->get_freq() == 5);
    CHECK(node->get_left() == nullptr);
    CHECK(node->get_right() == nullptr);

    delete node;
}

TEST_CASE("more comples huffman tree node creation")
{
    htn *left = new htn(1, true, 'A');
    htn *right = new htn(2, true, 'B');
    htn *parent = new htn(5, false, 'C', left, right);

    CHECK(parent->get_freq() == 5);
    CHECK(parent->is_leaf() == false);
    CHECK(parent->get_left() == left);
    CHECK(parent->get_right() == right);
    CHECK(parent->get_left()->get_freq() == 1);
    CHECK(parent->get_right()->get_freq() == 2);
    CHECK(parent->get_left()->get_byte() == 'A');
    CHECK(parent->get_right()->get_byte() == 'B');
    CHECK(parent->get_left()->is_leaf() == true);
    CHECK(parent->get_right()->is_leaf() == true);

    delete left;
    delete right;
    delete parent;
}

TEST_CASE("simple creation of huffman tree")
{
    ht *tree = new ht(new htn(5, true, 'A'), 1);
    CHECK(tree->get_size() == 1);
    delete tree;
}

TEST_CASE("huffman tree building test")
{
    std::vector<uint8_t> test_data = {'a', 'a', 'b', 'c'};
    ht *tree = ht::build_tree(test_data);

    CHECK(tree->get_size() == 5);
    CHECK(tree->get_head()->get_freq() == 4);
    CHECK(tree->get_head()->get_right()->get_freq() == 2);
    CHECK(tree->get_head()->get_left()->get_freq() == 2);
    CHECK(tree->get_head()->get_right()->get_left()->get_freq() == 1);
    CHECK(tree->get_head()->get_right()->get_right()->get_freq() == 1);
    CHECK(tree->get_head()->get_left()->get_byte() == 'a');
    CHECK(tree->get_head()->get_left()->is_leaf() == true);
    CHECK(tree->get_head()->get_right()->get_left()->get_byte() == 'c');
    CHECK(tree->get_head()->get_right()->get_right()->get_byte() == 'b');
    CHECK(tree->get_head()->get_right()->get_left()->is_leaf() == true);
    CHECK(tree->get_head()->get_right()->get_right()->is_leaf() == true);

    delete tree;
}

TEST_CASE("test constructor and methods of huffman archiver")
{
    ha ha("hello,world");
    CHECK(ha.get_bytes() == "hello,world");
}

TEST_CASE("archive test 1 of huffman_archive class")
{
    ha ha("aabc");
    ha.archive();
    CHECK(ha.get_bytes().at(0) == 28);
}

TEST_CASE("archive test 2 of huffman_archive class")
{
    ha ha("aabcdb");
    ha.archive();
    CHECK(ha.get_bytes().at(0) == 181);
    CHECK(ha.get_bytes().at(1) == 12);
}

TEST_CASE("big archive test 1")
{
    std::ifstream file("samples/big_test_archive.txt");
    std::string text;
    file >> text;
    ha ha(text);
    std::size_t bytes_in_original = ha.get_bytes().size();
    file.close();
    ha.archive();
    std::size_t bytes_in_archived = ha.get_bytes().size();
    CHECK(ha.get_bytes().size() * 1.0 / bytes_in_original <= 0.6);
}

TEST_CASE("big archive test 2")
{
    std::ifstream file("samples/big_test_archive_book.txt");
    std::string text;
    file >> text;
    ha ha(text);
    std::size_t bytes_in_original = ha.get_bytes().size();
    file.close();
    ha.archive();
    std::size_t bytes_in_archived = ha.get_bytes().size();
    CHECK(ha.get_bytes().size() * 1.0 / bytes_in_original <= 0.6);
}

TEST_CASE("unarchive test of huffman_archiver class")
{
    huffman_archiver::huffman_archiver ha("Born in 1987, Kilian has been training for Everest his whole life. And that really does mean his whole life, as he grew up 2,000 metres above sea level in the Pyrenees in the ski resort of Lles de Cerdanya in Catalonia, north-eastern Spain. While other children his age were learning to walk, Kilian was on skis. At one and a half years old he did a five-hour hike with his mother, entirely under his own steam. He left his peers even further behind when he climbed his first mountain and competed in his first cross-country ski race at age three. By age seven, he had scaled a 4,000er and, at ten, he did a 42-day crossing of the Pyrenees.");
    ha.archive();
    ha.unarchive();
    CHECK(ha.get_bytes() == "Born in 1987, Kilian has been training for Everest his whole life. And that really does mean his whole life, as he grew up 2,000 metres above sea level in the Pyrenees in the ski resort of Lles de Cerdanya in Catalonia, north-eastern Spain. While other children his age were learning to walk, Kilian was on skis. At one and a half years old he did a five-hour hike with his mother, entirely under his own steam. He left his peers even further behind when he climbed his first mountain and competed in his first cross-country ski race at age three. By age seven, he had scaled a 4,000er and, at ten, he did a 42-day crossing of the Pyrenees.");
}

TEST_CASE("operator<< and operator>> smoke test of huffman_archive class")
{
    ha ha("When you picture mountain climbers scaling Mount Everest, what probably comes to mind are teams of climbers with Sherpa guides leading them to the summit, equipped with oxygen masks, supplies and tents. And in most cases you'd be right, as 97 per cent of climbers use oxygen to ascend to Everest's summit at 8,850 metres above sea level. The thin air at high altitudes makes most people breathless at 3,500 metres, and the vast majority of climbers use oxygen past 7,000 metres. A typical climbing group will have 8–15 people in it, with an almost equal number of guides, and they'll spend weeks to get to the top after reaching Base Camp.");
    ha.archive();

    std::ofstream file1("samples/test_operator<<.txt");
    file1 << ha;
    file1.close();

    std::ifstream file2("samples/test_operator<<.txt");
    file2 >> ha;
    file2.close();
    ha.unarchive();

    CHECK(ha.get_bytes() == "When you picture mountain climbers scaling Mount Everest, what probably comes to mind are teams of climbers with Sherpa guides leading them to the summit, equipped with oxygen masks, supplies and tents. And in most cases you'd be right, as 97 per cent of climbers use oxygen to ascend to Everest's summit at 8,850 metres above sea level. The thin air at high altitudes makes most people breathless at 3,500 metres, and the vast majority of climbers use oxygen past 7,000 metres. A typical climbing group will have 8–15 people in it, with an almost equal number of guides, and they'll spend weeks to get to the top after reaching Base Camp.");
}

TEST_CASE("operator<< and operator>> smoke test of huffman_archive class")
{
    ha ha("Привет привет привет привет привет привет!");
    ha.archive();

    std::ofstream file1("samples/test_operator<<.txt");
    file1 << ha;
    file1.close();

    std::ifstream file2("samples/test_operator<<.txt");
    file2 >> ha;
    file2.close();
    ha.unarchive();

    CHECK(ha.get_bytes() == "Привет привет привет привет привет привет!");
}