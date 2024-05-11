#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "huffman_tree_node.h"
#include "huffman_tree.h"
#include "huffman_archiver.h"
#include <vector>
#include <fstream>
#include <memory>

typedef huffman_archiver::huffman_tree_node htn;
typedef huffman_archiver::huffman_tree ht;
typedef huffman_archiver::huffman_archiver ha;
typedef std::shared_ptr<huffman_archiver::huffman_tree_node> shtn;
typedef std::shared_ptr<huffman_archiver::huffman_tree> sht;

#define mshtn std::make_shared<htn>
#define msht std::make_shared<ht>

TEST_CASE("SMOKE huffman_tree_node creation test 1")
{
    shtn node = mshtn(5, true, 'A');

    CHECK(node->get_byte() == 'A');
    CHECK(node->is_leaf() == true);
    CHECK(node->get_freq() == 5);
    CHECK(node->get_left() == nullptr);
    CHECK(node->get_right() == nullptr);
}

TEST_CASE("SMOKE huffman_tree_node creation test 2")
{
    shtn left = mshtn(1, true, 'A');
    shtn right = mshtn(2, true, 'B');
    shtn parent = mshtn(5, false, 'C', left, right);

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
}

TEST_CASE("huffman_tree_node::get_byte test")
{
    shtn node = mshtn(5, true, 'T');
    CHECK(node->get_byte() == 'T');
}

TEST_CASE("huffman_tree_node::get_freq test")
{
    shtn node = mshtn(545, true, 'T');
    CHECK(node->get_freq() == 545);
}

TEST_CASE("huffman_tree_node::is_leaf test")
{
    shtn node1 = mshtn(545, true, 'T');
    CHECK(node1->is_leaf() == true);
    shtn node2 = mshtn(545, false, 'T');
    CHECK(node2->is_leaf() == false);
}

TEST_CASE("huffman_tree_node::get_left test")
{
    shtn left = mshtn(1, true, 'A');
    shtn right = mshtn(2, true, 'B');
    shtn parent = mshtn(3, false, 'C', left, right);
    CHECK(parent->get_left() == left);
    CHECK(parent->get_right() == right);
}

TEST_CASE("SMOKE huffman_tree creation test")
{
    sht tree = msht(mshtn(5, true, 'A'), 1);
    CHECK(tree->get_size() == 1);
    CHECK(tree->get_byte_of_cur().first == true);
    CHECK(tree->get_byte_of_cur().second == 'A');
    tree->go_left();
    CHECK(tree->get_byte_of_cur().first == false);
    tree->reset_cur();
    CHECK(tree->get_byte_of_cur().first == true);
    CHECK(tree->get_byte_of_cur().second == 'A');
}

TEST_CASE("huffman_tree::get_size (default constructor) test")
{
    shtn left = mshtn(1, true, 'A');
    shtn right = mshtn(2, true, 'B');
    shtn parent = mshtn(3, false, 'C', left, right);
    sht tree = msht(parent, 3);
    CHECK(tree->get_size() == 3);
}

TEST_CASE("huffman_tree::get_size (using huffman_tree:build_tree) test")
{
    std::map<uint8_t, std::size_t> freqs =
        {
            {'a', 7},
            {'b', 2},
            {'c', 3},
            {'d', 8},
            {'e', 1}};
    sht tree = huffman_archiver::huffman_tree::build_tree(freqs);
    CHECK(tree->get_size() == 2 * freqs.size() - 1);
}

TEST_CASE("huffman_tree::get_byte_of_cur and huffman_tree::reset_cur test 1")
{
    std::map<uint8_t, std::size_t> freqs =
        {
            {'a', 7},
            {'b', 2},
            {'c', 3},
            {'d', 8},
            {'e', 1},
            {'f', 18}};
    sht tree = huffman_archiver::huffman_tree::build_tree(freqs);
    CHECK(tree->get_byte_of_cur().first == false);
    tree->go_left();
    CHECK(tree->get_byte_of_cur().second == 'f');
    tree->go_left();
    tree->reset_cur();
    CHECK(tree->get_byte_of_cur().first == false);
    tree->go_right();
    tree->go_right();
    tree->go_right();
    tree->go_right();
    tree->go_right();
    tree->go_right();
    tree->go_right();
    tree->go_right();
    CHECK(tree->get_byte_of_cur().first == false);
}

TEST_CASE("huffman_tree::get_codes test")
{
    shtn left1 = mshtn(1, true, 'A');
    shtn right1 = mshtn(2, true, 'B');
    shtn parent1 = mshtn(3, false, 'C', left1, right1);
    shtn right2 = mshtn(100, true, 'j');
    shtn left2 = mshtn(3, true, 'e');
    shtn parent2 = mshtn(3, false, 'C', left2, right2);
    shtn parent3 = mshtn(800, false, 'C', parent1, parent2);
    sht tree = msht(parent3, 7);
    std::unordered_map<uint8_t, std::string> codes = tree->get_codes();
    CHECK(codes['A'] == "00");
    CHECK(codes['B'] == "01");
    CHECK(codes['j'] == "11");
    CHECK(codes['e'] == "10");
}

TEST_CASE("huffman_tree::build_tree test")
{
    std::map<uint8_t, std::size_t> freqs =
        {
            {'a', 2},
            {'b', 2},
            {'c', 1},
            {'d', 1}};
    sht tree = huffman_archiver::huffman_tree::build_tree(freqs);
    std::unordered_map<uint8_t, std::string> codes = tree->get_codes();
    CHECK(codes['a'] == "11");
    CHECK(codes['b'] == "10");
    CHECK(codes['c'] == "00");
    CHECK(codes['d'] == "01");
}

TEST_CASE("huffman_archiver::get_bytes test 1")
{
    std::string text = "hello,world";
    ha ha(text);
    CHECK(ha.get_bytes() == text);
}

TEST_CASE("huffman_archiver::get_bytes test 2")
{
    std::string text = "";
    ha ha(text);
    CHECK(ha.get_bytes() == text);
}

TEST_CASE("huffman_archiver::get_bytes test 3")
{
    std::string text = "!";
    ha ha(text);
    CHECK(ha.get_bytes() == text);
}

TEST_CASE("huffman_archiver::archive test 1")
{
    std::string text = "aabc";
    ha ha(text);
    ha.archive();
    CHECK(ha.get_bytes().at(0) == 52);
}

TEST_CASE("huffman_archiver::archive test 2")
{
    std::string text = "aabcdb";
    ha ha(text);
    ha.archive();
    CHECK(ha.get_bytes().at(0) == 31);
    CHECK(ha.get_bytes().at(1) == 6);
}

TEST_CASE("huffman_archiver::get_amount_of_additional_bytes test")
{
    std::string text = "aabcdb";
    ha ha(text);
    ha.archive();
    CHECK(ha.get_amount_of_additional_bytes() == 46);
}

TEST_CASE("huffman_archiver::get_amount_of_bytes test 1")
{
    std::string text = "dhshdaoeohdhldhjsh";
    ha ha(text);
    ha.archive();
    CHECK(ha.get_amount_of_bytes() <= text.size());
}

TEST_CASE("huffman_archiver::get_amount_of_bytes test 2")
{
    std::string text = "aabcdb";
    ha ha(text);
    CHECK(ha.get_amount_of_bytes() == text.size());
}

TEST_CASE("huffman_archiver::archiver BIG test 1")
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

TEST_CASE("huffman_archiver::archiver BIG test 2")
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

TEST_CASE("huffman_archiver::unarchive test 1")
{
    std::string text = "Born in 1987, Kilian has been training for Everest his whole life. And that really does mean his whole life, as he grew up 2,000 metres above sea level in the Pyrenees in the ski resort of Lles de Cerdanya in Catalonia, north-eastern Spain. While other children his age were learning to walk, Kilian was on skis. At one and a half years old he did a five-hour hike with his mother, entirely under his own steam. He left his peers even further behind when he climbed his first mountain and competed in his first cross-country ski race at age three. By age seven, he had scaled a 4,000er and, at ten, he did a 42-day crossing of the Pyrenees.";
    huffman_archiver::huffman_archiver ha(text);
    ha.archive();
    ha.unarchive();
    CHECK(ha.get_bytes() == text);
    CHECK(ha.get_amount_of_bytes() == text.size());
}

TEST_CASE("huffman_archiver::operator<< and huffman_archiver::operator>> test 1")
{
    std::string text = "When you picture mountain climbers scaling Mount Everest, what probably comes to mind are teams of climbers with Sherpa guides leading them to the summit, equipped with oxygen masks, supplies and tents. And in most cases you'd be right, as 97 per cent of climbers use oxygen to ascend to Everest's summit at 8,850 metres above sea level. The thin air at high altitudes makes most people breathless at 3,500 metres, and the vast majority of climbers use oxygen past 7,000 metres. A typical climbing group will have 8–15 people in it, with an almost equal number of guides, and they'll spend weeks to get to the top after reaching Base Camp.";
    ha ha(text);
    ha.archive();

    std::ofstream file1("samples/test_operator<<.txt");
    file1 << ha;
    file1.close();

    std::ifstream file2("samples/test_operator<<.txt");
    file2 >> ha;
    file2.close();
    ha.unarchive();

    CHECK(ha.get_bytes() == text);
}

TEST_CASE("huffman_archiver::operator<< and huffman_archiver::operator>> test 2")
{
    std::string text = "Привет привет привет привет привет привет!";
    ha ha(text);
    ha.archive();

    std::ofstream file1("samples/test_operator<<.txt");
    file1 << ha;
    file1.close();

    std::ifstream file2("samples/test_operator<<.txt");
    file2 >> ha;
    file2.close();
    ha.unarchive();

    CHECK(ha.get_bytes() == text);
}

TEST_CASE("huffman_archiver::archive empty test")
{
    std::string text = "";
    ha ha(text);
    ha.archive();
    ha.unarchive();
    CHECK(ha.get_bytes() == text);
}

TEST_CASE("huffman_archiver::unarchive empty test")
{
    ha ha;
    std::ifstream file("samples/empty.txt");
    file >> ha;
    ha.unarchive();
    file.close();
    CHECK(ha.get_bytes() == "");
}

TEST_CASE("huffman_archiver::archive and huffman_archiver::unarchive test 1")
{
    std::string text = "hello,world\n";
    ha ha(text);
    ha.archive();
    CHECK(ha.get_amount_of_bytes() <= text.size());
    ha.unarchive();
    CHECK(ha.get_amount_of_bytes() == text.size());
    CHECK(ha.get_bytes() == text);
}

TEST_CASE("huffman_archiver::archive and huffman_archiver::unarchive test 2")
{
    std::string text = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
    ha ha(text);
    ha.archive();
    CHECK(ha.get_amount_of_bytes() <= text.size());
    ha.unarchive();
    CHECK(ha.get_bytes() == text);
}

TEST_CASE("huffman_archiver::archive and huffman_archiver::unarchive one symbol test")
{
    std::string text = "!";
    ha ha(text);
    ha.archive();
    CHECK(ha.get_amount_of_bytes() <= text.size());
    ha.unarchive();
    CHECK(ha.get_amount_of_bytes() == text.size());
    CHECK(ha.get_bytes() == text);
}

TEST_CASE("huffman_archiver::archive and huffman_archiver::unarchive all bytes test")
{
    std::ifstream in("samples/all_bytes_test.txt");
    if (!in.good())
        std::cout << "File not found for test \"archive unarchive all bytes test\"" << std::endl;
    else
    {
        std::string text;
        while (true)
        {
            char byte;
            in.read(&byte, sizeof(byte));
            if (in.eof() || in.fail())
                break;
            text.push_back(byte);
        }
        ha ha(text);
        ha.archive();
        CHECK(ha.get_amount_of_bytes() <= text.size());
        ha.unarchive();
        CHECK(ha.get_amount_of_bytes() == text.size());
        CHECK(ha.get_bytes() == text);
    }
    in.close();
}

TEST_CASE("huffman_archiver::archive and huffman_archiver::unarchive all symbols test")
{
    std::string text = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя!@#$%-^&*()_+~\"№;%:?=[]{}|/,.'<>";
    ha ha(text);
    ha.archive();
    CHECK(ha.get_amount_of_bytes() <= text.size());
    ha.unarchive();
    CHECK(ha.get_amount_of_bytes() == text.size());
    CHECK(ha.get_bytes() == text);
}

TEST_CASE("huffman_archiver::archive and huffman_archiver::unarchive all equal symbols using huffman_archiver::operator<< and huffman_archiver::operator>> test")
{
    std::ifstream in("samples/all_equal_test.txt");
    std::string text;
    getline(in, text);
    ha ha(text);
    ha.archive();
    ha.unarchive();
    CHECK(ha.get_bytes() == text);
}