#include <iostream>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
const char END_OF_FILE = '!';
const char left_way = '0';
const char right_way = '1';
std:: string FILE_NAME;
using namespace std;
//<offset, size, next> - code
struct Node {
    int offset;
    int size;
    char next;
    Node (int offset, int size, char next) {
        this->offset = offset;
        this->size = size;
        this->next = next;
    }
};
void LZ77Encode (std:: vector<char>& text, std:: vector<Node*>& encoded) {
    int global_position = 0;
    while (global_position < text.size()) {
        Node* result = new Node(0, 0, text[global_position]);
        for (int i = 0; i < global_position; ++i) {
            int local_position = global_position;
            int local_size = 0;
            for (int j = i; text[local_position] == text[j] && local_position < text.size(); ++j) { //смещаемся по тексту и ищем самый большой size
                ++local_size;
                ++local_position;
            }
            if (local_size >= result->size && local_size != 0) {
                result->size = local_size;
                result->offset = global_position - i;
                if (local_position >= text.size()) { //если превысили или на конце текста
                    result->next = END_OF_FILE;
                }
                else {
                    result->next = text[local_position]; //кладем следующий символ, если все ок
                }
            }
        }
        encoded.emplace_back(result);
        global_position += result->size + 1; // смещаем наш итератор на следующую ячейку после последнего обработанного символа
    }
}
void LZ77EncodeWithFile(std:: string& file, bool c, bool l) { //WORKS
    std:: ifstream f(file);
    std:: vector<Node*> encoded;
    std:: vector<char> word = std:: vector<char>(std:: istreambuf_iterator<char>(f), std:: istreambuf_iterator<char>());
    f.close();
    LZ77Encode(word, encoded);
    if (l) { //works
        std:: cout << "Result of LZ77 encoding algorithm for file " << file << "\n";
        std:: cout << "Size of original word: " << word.size() * 8 << " bytes\n"; //1byte = 8bits
        std:: cout << "Size of compressed text: " << encoded.size() * 8 << " bytes\n";
    }
    if (!c) { //works
        std:: string name = file + ".LZ77";
        std:: ofstream f(name);
        for (int i = 0; i < encoded.size(); ++i) {
            f << encoded[i]->offset << " " << encoded[i]->size << " " << encoded[i]->next << "\n";
        }
        f.close();
    }
    else { //works
        for (int i = 0; i < encoded.size(); ++i) {
            std:: cout << encoded[i]->offset << " " << encoded[i]->size << " " << encoded[i]->next << "\n";
        }
    }
}
void LZ77Decode (std:: string& text, std:: vector<Node*>& code) {
    int global_position = 0;
    for (int i = 0; i < code.size(); ++i) {
        if (code[i]->size > 0) { //если есть что брать
            global_position = text.size() - code[i]->offset; //смещаемся на длину строки - смещение
            for (int j = 0; j < code[i]->size; ++j) {
                text.push_back(text[global_position + j]); //прибавляем в текст пока j < размера того, что берем
            }
        }
        if (code[i]->next == END_OF_FILE) { //если пустой, выходим
            break;
        }
        else {
            text.push_back(code[i]->next); //добавляем следующий символ в текст, если не пустой символ
        }
    }
}
void LZ77DecodeWithFile(std:: string& file, bool c, bool l) { //WORKS
    std:: ifstream f(file);
    std:: vector<Node*> code;
    int offset, size;
    char next;
    while (f >> offset >> size >> next) {
        Node* inputed = new Node(offset, size, next);
        code.emplace_back(inputed);
    }
    f.close();
    std:: string text;
    LZ77Decode(text, code);
    std:: string original_filename = file.substr(0, file.size() - 5); //test.txt
    if (l) {
        std:: cout << "Result of LZ77 decoding algorithm for file " << original_filename << "\n";
        std:: cout << "Size of original word: " << text.size() * 8 << " bytes\n";
        std:: cout << "Size of compressed text: " << code.size() * 8 << " bytes\n";
    }
    if (!c) {
        std:: ofstream f("decoded" + original_filename);
        f << text;
        f.close();
    }
    else {
        std:: cout << text << "\n";
    }
}

//HUFFMAN PART
struct HuffmanNode {
    HuffmanNode *left;
    HuffmanNode *right;
    char symbol;
    int frequency;
    HuffmanNode (HuffmanNode* left, HuffmanNode* right, char symbol, int frequency) {
        this->left = left;
        this->right = right;
        this->symbol = symbol;
        this->frequency = frequency;
    }
    ~HuffmanNode() {}
};
//char to binary string
std:: string MakeBinaryString (const char& symbol){
    char str[9] = {0};
    for (int i = 8; i--; ) {
        str[7 - i] = !!(symbol & (1 << i)) + '0';
    }
    std:: string binarystring = str;
    return binarystring;
}
// binary string to char
char MakeCharFromBinaryString(const std:: string& word) {
    char res = 0;
    int temp = 1;
    for (int i = 7 ; i >= 0; --i) {
        if (word.at(i) == '1') {
            res += temp;
        }
        temp = temp * 2;
    }
    return res;
}
void MakeFrequencyArray(std:: vector<int>& frequency_array, const std:: vector<char>& word) { //массив частот для каждого символа works
    for (int i = 0; i < word.size(); ++i) { //заполняем частоты
        int current_char = (int)word[i];
        ++frequency_array[current_char];
    }
}
struct {
    bool operator() (HuffmanNode *first, HuffmanNode *second) const { return first->frequency > second->frequency; }
} customLess;
void FillNodes(std:: vector<HuffmanNode*>& nodes, std:: vector<int>& frequency_array) { //WORKS
    for (int i = 0; i < frequency_array.size(); ++i) {
        if (frequency_array[i]) {
            //create new node
            char node_symbol = (char)i;
            HuffmanNode* node = new HuffmanNode(nullptr, nullptr, node_symbol, frequency_array[i]);
            nodes.emplace_back(node);
        }
    }
}
HuffmanNode* MakeHuffmanTree(std:: vector<HuffmanNode*>& nodes) {
    std:: sort(nodes.begin(), nodes.end(), customLess);
    while (nodes.size() != 1) {
        std:: sort(nodes.begin(), nodes.end(), customLess);
        HuffmanNode* first = nodes.back();
        nodes.pop_back();
        HuffmanNode* second = nodes.back();
        nodes.pop_back();
        int merged_frequnecy = first->frequency + second->frequency;
        HuffmanNode* merged_node = new HuffmanNode(first, second, '\0', merged_frequnecy);
        nodes.emplace_back(merged_node);
    }
    HuffmanNode* result = nodes.back();
    return result;
}
void MakeBinaryCode (HuffmanNode* node, std:: string code, std:: map<char, std:: string>& codes) {
    if (node == nullptr) {
        return;
    }
    if (!node->left && !node->right) {
        if (code.empty()) {
            code = "0";
        }
        codes[node->symbol] = code;
    }
    MakeBinaryCode(node->left, code + left_way, codes);
    MakeBinaryCode(node->right, code + right_way, codes);
}
void HuffmanEncodeWithFile(std:: string &name, bool c, bool l) {
    std:: ifstream file(name);
    std:: vector<char> word = std:: vector<char>(std:: istreambuf_iterator<char>(file), std:: istreambuf_iterator<char>());
    int word_size = word.size();
    file.close();
    std:: vector<int> frequency_array(256, 0); //массив частот на 256 символов по умолчанию 0
    std:: vector<HuffmanNode*> nodes; //массив с нодами
    MakeFrequencyArray(frequency_array, word); //заполняем массив частот
    FillNodes(nodes, frequency_array); //формируем ноды для каждой встречающейся буквы
    HuffmanNode* tree = MakeHuffmanTree(nodes); //получаем дерево хафмана
    std:: map<char, std:: string> codes;
    std:: string begin = "";
    MakeBinaryCode(tree, begin, codes); //обход дерева чтобы получить бинарный код каждого чара
    std:: string vocabulary_name = name + ".HuffmanVocabulary";
    std:: ofstream f;
    f.open(vocabulary_name);
    f << word_size << "\n";
    for (std:: map<char, std:: string>::iterator it = codes.begin(); it != codes.end(); ++it) {
        f << it->first << " " << it->second << "\n";
    }
    f.close();
    std:: string result = "";
    std:: string result_name = name + ".Huffman";
    std:: ofstream Huffman;
    Huffman.open(result_name, std:: ios:: out | std:: ios:: binary | std:: ios:: app);
    for (int i = 0; i < word.size(); ++i) {
        result += codes[word[i]]; //итоговая строка из 0 и 1 на последней итерации
        while (result.size() >= 8) {
            std:: string to_code = result.substr(0, 8); //считываем по восьмеркам в чар
            result.erase(0, 8);
            char coded = MakeCharFromBinaryString(to_code); //создаем чар и пишем в бинарник
            if (!c) {
                Huffman.write(reinterpret_cast<char*>(&coded), sizeof(coded));
            }
            else {
                std:: cout << coded;
            }
        }
    }
    if (result.size()) {
        result += "0000000";
        std:: string to_code = result.substr(0, 8);
        char coded = MakeCharFromBinaryString(to_code);
        if (!c) {
            Huffman.write(reinterpret_cast<char*>(&coded), sizeof(coded));
        }
        else {
            std:: cout << coded << "\n";
        }
    }
    Huffman.close();
    if (l) {
        std:: ifstream output(result_name, std:: ios:: binary | std:: ios:: ate);
        int output_size = output.tellg();
        output.close();
        std:: cout << "Result of Huffman encoding algorithm for file " << name << "\n";
        std:: cout << "Size of original word: " << word.size() * 8 << " bytes\n";
        std:: cout << "Size of compressed text: " << output_size * 8 << " bytes\n";
    }
}
void HuffmanDecompressWitFile(std:: string &name, bool c, bool l) {
    int word_size;
    std:: string str;
    char ch;
    std:: ifstream vocabulary_read;
    vocabulary_read.open(name + "Vocabulary");
    vocabulary_read >> word_size;
    std:: map<std:: string, char> codes;
    while (vocabulary_read >> ch >> str) {
        codes[str] = ch;
    }
    std:: ifstream read_huffman;
    read_huffman.open(name, std:: ios:: binary | std:: ios:: in);
    int decoded_size = 0;
    int start_iter;
    char current_byte;
    int finish_iter;
    std:: string coded_string = "";
    std:: ofstream res;
    res.open("decoded" + name, std:: ios:: binary | std:: ios:: out);
    while (read_huffman.read(reinterpret_cast<char*>(&current_byte), sizeof(current_byte)) && decoded_size < word_size) {
        coded_string += MakeBinaryString(current_byte);
        start_iter = 0;
        finish_iter = 1;
        while (start_iter + finish_iter <= coded_string.size() && decoded_size < word_size) {
            std:: string potential_code = coded_string.substr(start_iter, finish_iter);
            std:: map<std:: string, char>::iterator iter = codes.find(potential_code);
            if (iter != codes.end()) {
                coded_string.erase(0, start_iter + finish_iter); //удаляем совпадение
                ++decoded_size;
                char symbol = iter->second;
                if (!c) {
                    res.write(reinterpret_cast<char*>(&symbol), sizeof(symbol));
                }
                else {
                    std:: cout << symbol;
                }
                finish_iter = 1;
            }
            else {
                ++finish_iter;
            }
        }
    }
    if (l) {
        std:: ifstream output(name, std:: ios:: binary | std:: ios:: ate);
        int output_size = output.tellg();
        std:: cout << "Result of Huffman decoding algorithm for file " << name << "\n";
        std:: cout << "Size of compressed text: " << output_size * 8 << " bytes\n";
        std:: cout << "Size of original word: " << word_size * 8 << " bytes\n";
    }
}
void Help() {
    std:: cout << "Hello!" << "\n";
    std:: cout << "Here is instruction for flags: " << "\n";
    std:: cout << "\t" << "-9 for LZ77 coding" << "\n";
    std:: cout << "\t" << "-1 for Huffman coding" << "\n";
    std:: cout << "\t" << "-l for information about compressed/decompressed and original sizes" << "\n";
    std:: cout << "\t" << "-c for output in standart thread instead of input in file" << "\n";
    std:: cout << "\t" << "-d for decoding" << "\n";
    std:: cout << "\t" << "-k for information" << "\n";
}
void RunWithFlags(std:: string& file, bool lz77, bool huffman, bool c, bool d, bool l) {
    if (lz77) {
        if (d) { //разархивировать при помощи LZ77 {
            LZ77DecodeWithFile(file, c, l);
        }
        else { //заархивировать при помощи LZ77
            LZ77EncodeWithFile(file, c, l);
        }
    }
    else if (huffman) {
        if (d) { //разархивировать при помощи хаффмана
            HuffmanDecompressWitFile(file, c, l);
        }
        else { //заархивировать при помощи хаффмана
            HuffmanEncodeWithFile(file, c, l);
        }
    }
}
int main (int args, char** argv) {
    //инициализируем булевские значения ложью по умолчанию
    bool lz77 = false; //-9 - сжатие при помощи алгоритма LZ-77
    bool huffman = false; //-1 - сжатие припомощи алгоритма Хаффмана
    bool l = false; //информация о сжатом и разжатом размерах
    bool c = false; //false - вывод в файл, true - в окно ввода
    bool d = false; //разархивация
    bool k = false; //информация
    for (int i = 1; i < args; ++i) { //с единички чтобы запуск программы не был как файл для сжатия
        std:: string current = argv[i]; //чтобы не было ошибок сравнения char с const char*
        if (current == "-9") {
            lz77 = true;
        }
        else if (current == "-1") {
            huffman = true;
        }
        else if (current == "-l") {
            l = true;
        }
        else if (current == "-c") {
            c = true;
        }
        else if (current == "-d") {
            d = true;
        }
        else if (current == "-k") {
            k = true;
        }
        else {
            FILE_NAME = current;
        }
    }
    if (lz77 == false && huffman == false) { //если флагов на сжатие на было введено, по умолчанию кодируем через лз77
        lz77 = true;
    }
    else if (lz77 == true && huffman == true) { //если оба введены
        std:: cout << "You should enter only one key: -1 for huffman coding or -9 for LZ77 coding!" << "\n"; 
        exit(EXIT_FAILURE);
    }
    else if (lz77 == false && huffman == false && l == false && c == false && d == false && k == false) { //если ничего не введено
        std:: cout << "You should enter one more flag. You've entered nothing. Here is info: " << "\n";
        Help();
        exit(EXIT_FAILURE);
    }
    else if (k) { //информация
        lz77 = false;
        huffman = false;
        l = false;
        c = false;
        d = false;
        Help();
    }
    else {
        RunWithFlags(FILE_NAME, lz77, huffman, c, d, l);
    }
    return 0;
}