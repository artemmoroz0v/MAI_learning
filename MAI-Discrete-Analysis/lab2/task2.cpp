#include <iostream>
#include <bitset>
#include <string>
#include <fstream>
const short int AMOUNT_OF_BITS_FOR_ONE_SYMBOL = 8;
const short int SHEAR_LIMIT = 7; //предел сдвига
const short int DEFAULT_INDEX_VALUE = -100;
const char FILE_SENTINEL = '$';
namespace StringBitFunctions {
    void ToLower (std:: string &key) {
        for (short int i = 0; i < key.size(); ++i) {
            key[i] = std:: tolower(key[i]);
        }
    }
    bool GetIndexBit (std:: string& string, short int index) { // index / 8 - номер символа, index % 8 - номер бита внутри одного символа
        if (index / AMOUNT_OF_BITS_FOR_ONE_SYMBOL >= string.size()) { //номер бита / 8 = номер символа
            return 0;
        }
        return (string[index / AMOUNT_OF_BITS_FOR_ONE_SYMBOL] & ((1u << SHEAR_LIMIT) >> (index % AMOUNT_OF_BITS_FOR_ONE_SYMBOL))); //1u == 00000001
    }
    short int FirstDifferentBit (std:: string& first_string, std:: string& second_string) {
        for (int i = 0; i < std:: max(first_string.size(), second_string.size()) * AMOUNT_OF_BITS_FOR_ONE_SYMBOL; ++i) {
            if (GetIndexBit(first_string, i) != GetIndexBit(second_string, i)) {
                return i;
            }
        }
        return -1;
    }
}
namespace PatriciaTrie {
    struct PNode {
        std:: string key;
        unsigned long long value;
        short int index;
        PNode* left;
        PNode* right;
        PNode() {
            key = " ";
            value = 0;
            index = DEFAULT_INDEX_VALUE;
            left = right = nullptr;
        }
        ~PNode() {
            right = left = nullptr;
        }
    };
    struct Patricia {
        PNode *header;
        Patricia () {
            header = nullptr;
        }
        bool IsTreeEmpty () {
            if (header == nullptr) {
                return true;
            }
            return false;
        }
        void Search (std:: string &key) {
            if (IsTreeEmpty()) {
                std:: cout << "NoSuchWord" << "\n";
                return;
            }
            if (header->key == key) {
                std:: cout << "OK: " << header->value << "\n";
                return;
            }
            PNode* previous_node = header;
            PNode* current_node = header->left;
            while (current_node->index > previous_node->index) { //когда current_node->index <= previous_node->index, то просто выходим из while, так как мы перешли по обратной ссылке и получили невозрастающую последовательность(Макаров)
                previous_node = current_node;
                if (StringBitFunctions:: GetIndexBit(key, current_node->index)) {
                    current_node = current_node->right;
                }
                else {
                    current_node = current_node->left;
                }
            }
            if (current_node->key == key) {
                std:: cout << "OK: " << current_node->value << "\n";
                return;
            }
            else {
                std:: cout << "NoSuchWord" << "\n";
                return;
            }
            return;
        }
        bool Insert (std:: string &key, const unsigned long long &value) {
            //Step 1: if there is no header in trie, we must insert first element in header.
            if (IsTreeEmpty()) {
                PNode* root = new PNode;
                root->key = key;
                root->value = value;
                root->left = root;
                root->index = 0;
                root->right = nullptr; //у хедера нет правой ссылки (Макаров)
                header = root; //обратная ссылка на самого себя по алгоритму
                return true;
            }
            //Step 2: If we have a header, we must search an element which we want to insert
            else {
                PNode* previous_node = header;
                PNode* current_node = header->left; //если при добавлении есть один хедер, то header->left = header!
                while (current_node->index > previous_node->index) { //сначала ищем элемент при вставке 
                    previous_node = current_node;
                    if (StringBitFunctions:: GetIndexBit(key, current_node->index)) {
                        current_node = current_node->right;
                    }
                    else {
                        current_node = current_node->left;
                    }
                }
                if (current_node->key == key) {
                    return false;
                }//если найденный элемент не равен тому который хотим вставить то начинаем вставлять
                //Step 3: We have almost alike node in our trie. So we have to know the first different bit between trie's node and our node.
                PNode* node = new PNode;
                node->key = key;
                node->value = value;
                node->index = StringBitFunctions:: FirstDifferentBit(current_node->key, key);
                previous_node = header;
                current_node = header->left;
                while (current_node->index > previous_node->index && current_node->index < node->index) { //спускаемся в дереве постоянно увеличивая биты! поэтому currentnindex < nodeindex (Макаров)
                    previous_node = current_node;
                    if (StringBitFunctions:: GetIndexBit(key, current_node->index)) {
                        current_node = current_node->right;
                    }
                    else {
                        current_node = current_node->left;
                    }
                }
                if (StringBitFunctions:: GetIndexBit(key, node->index)) {
                    node->left = current_node;
                    node->right = node;
                }
                else {
                    node->left = node;
                    node->right = current_node;
                }
                if (previous_node->right == current_node) { //если мы пришли к текущей ноде по правой ссылке предыдущей ноды, то перезаписываем правую ссылку на новую ноду
                    previous_node->right = node;
                }
                else {
                    previous_node->left = node; //если мы пришли к текущей ноде по леввой ссылке предыдущей ноды, то перезаписывае левую ссылку на новую ноду
                }
            }
            return true;
        }
        void Erase (std:: string &key) {
            if (IsTreeEmpty()) { //проверка на пустоту
                std:: cout << "NoSuchWord" << "\n";
                return;
            }
            //0 случай - хедер указывает на себя (Макаров)
            if (header->left == header) {
                if (header->key == key) {
                    delete header;
                    header = nullptr;
                    std:: cout << "OK" << "\n";
                    return;
                }
                else {
                    std:: cout << "NoSuchWord" << "\n";
                    return;
                }
            }
            //если элемент не в хедере, то банально ищем его в дереве:
            PNode* owner_delete_node = header;
            PNode* delete_node = header->left;
            PNode* parent_owner_delete_node;
            while (delete_node->index > owner_delete_node->index) {
                parent_owner_delete_node = owner_delete_node;
                owner_delete_node = delete_node;
                if (StringBitFunctions:: GetIndexBit(key, delete_node->index)) {
                    delete_node = delete_node->right;
                }
                else {
                    delete_node = delete_node->left;
                }
            }
            if (!(delete_node->key == key)) {
                std:: cout << "NoSuchWord" << "\n";
                return;
            }
            //If delete node is leaf
            if (owner_delete_node == delete_node) { //если перешли по обратной ссылке и нода листовая
                if (parent_owner_delete_node->right == delete_node) {
                    if (delete_node->right == delete_node) {
                        parent_owner_delete_node->right = delete_node->left;
                    }
                    else {
                        parent_owner_delete_node->right = delete_node->right;
                    }
                }
                else {
                    if (delete_node->right == delete_node) {
                        parent_owner_delete_node->left = delete_node->left;
                    }
                    else {
                        parent_owner_delete_node->left = delete_node->right;
                    }
                }
                delete delete_node;
                delete_node = nullptr;
                std:: cout << "OK" << "\n";
                return;
            }
            //последний кейс, когда удаляемая нода не является листом
            //после поиска делаем следующее:
            PNode* p = delete_node;
            PNode* q = owner_delete_node;
            PNode* parent_of_q = parent_owner_delete_node;
            PNode* r;
            delete_node = header->left;
            r = header;
            while (delete_node->index > r->index) {
                r = delete_node;
                if (StringBitFunctions:: GetIndexBit(q->key, delete_node->index)) {
                    delete_node = delete_node->right;
                }
                else {
                    delete_node = delete_node->left;
                }
            }
            bool ComingFromRight = StringBitFunctions:: GetIndexBit(r->key, q->index); //1 - r находится справа в дереве по отношению к q проверяем ключ r-ки по q-тому индексу (пример из лекции)
            if (r->right == q) {
                r->right = p;
            }
            else {
                r->left = p;
            }
            if (parent_of_q->right == q) {
                if (ComingFromRight) {
                    parent_of_q->right = q->right;
                }
                else {
                    parent_of_q->right = q->left;
                }
            }
            else {
                if (ComingFromRight) {
                    parent_of_q->left = q->right;
                }
                else {
                    parent_of_q->left = q->left;
                }
            }
            p->key = q->key; //меняем только ключ и значение в старой ноде (Макаров)
            p->value = q->value;
            delete q;
            q = nullptr;
            std:: cout << "OK" << "\n";
            return;
        }
        void ClearNode (PNode* node) { //recursive clear
            if (node->left->index > node->index) {
                ClearNode (node->left);
            }
            if (node->right->index > node->index) {
                ClearNode (node->right);
            }
            delete node;
            node = nullptr;
        }
        void Clear() {
            if (!header) {
                return;
            }
            if (header != header->left) {
                ClearNode(header->left);
            }
            delete header;
            header = nullptr;
        }
        void SaveToFile (PNode* current_node, std:: ofstream& f) {
            if (!current_node) {
                std:: cout << "OK" << "\n";
                return;
            }
            short int current_index = current_node->index;
            short int key_size = current_node->key.size();
            f.write((char*)(&key_size), sizeof(short int));
            f.write(current_node->key.c_str(), sizeof(char) * current_node->key.size());
            f.write((char*)(&current_index), sizeof(short int));
            f.write((char*)(&current_node->value), sizeof(unsigned long long));
            if (current_node->left != nullptr && current_node->left->index > current_index) {
                SaveToFile(current_node->left, f);
            }
            if (current_node->right != nullptr && current_node->right->index > current_index) {
                SaveToFile(current_node->right, f);
            }
            if (current_node->index == 0) {
                std:: cout << "OK" << "\n";
            }
        }
        void LoadFromFile (std:: ifstream& f) {
            short int key_size;
            PatriciaTrie:: Patricia trie;
            while (f.read((char*)&key_size, sizeof(key_size))) {
                std:: string tree_key;
                tree_key.resize(key_size);
                unsigned long long tree_value;
                short int tree_index;
                f.read((char*)tree_key.data(), key_size);
                f.read((char*)&tree_index, sizeof(tree_index));
                f.read((char*)&tree_value, sizeof(tree_value));
                trie.Insert(tree_key, tree_value);
            }
            std:: swap(*this, trie);
            return;
        }
        ~Patricia() {
            Clear();
        }
    };
}
int main () {
    std:: ios:: sync_with_stdio(false);
    std:: cin.tie(0);
    std:: cout.tie(0);
    PatriciaTrie:: Patricia* patricia = new PatriciaTrie:: Patricia;
    std:: string command;
    std:: string key;
    unsigned long long value;
    while (std:: cin >> command) {
        if (command == "+") {
            std:: cin >> key >> value;
            StringBitFunctions:: ToLower(key);
            if (patricia->Insert(key, value)) {
                std:: cout << "OK" << "\n";
            }
            else {
                std:: cout << "Exist" << "\n";
            }
        }
        else if (command == "-") {
            std:: cin >> key;
            StringBitFunctions:: ToLower(key);
            patricia->Erase(key);
        }
        else if (command == "!") {
            std:: string save_or_load;
            std:: cin >> save_or_load;
            if (save_or_load == "Save") {
                std:: cin >> key;
                std:: ofstream f(key, std:: ios:: binary);
                patricia->SaveToFile(patricia->header, f);
                f.close();
            }
            else {
                std:: cin >> key;
                std:: ifstream f(key, std:: ios:: binary);
                patricia->Clear();
                patricia->LoadFromFile(f);
                f.close();
                std:: cout << "OK" << "\n";
            }
        }
        else {
            StringBitFunctions:: ToLower(command);
            patricia->Search(command);
        }
    }
    delete patricia;
    return 0;
}