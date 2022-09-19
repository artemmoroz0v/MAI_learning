#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <sstream>
namespace TrieAhoKorasik {
    struct TrieNode {
        long long value;
        std:: map<long long, TrieNode*> nodes;
        TrieNode* dad;
        std:: vector<int> positions;
        TrieNode* link_of_failure;
        TrieNode* link_of_exit; 
        bool end_of_pattern;
        TrieNode (long long val) {
            value = val;
            dad = nullptr;
            link_of_failure = nullptr;
            link_of_exit = nullptr;
            end_of_pattern = false;
        }
        TrieNode* CheckLink (long long& value) {
            std:: map<long long, TrieNode*>:: iterator iterator = nodes.find(value);
            if (iterator == nodes.end()) {
                return nullptr;
            }
            return iterator->second;
        }
        ~TrieNode() {
            for (std:: map<long long, TrieNode*>:: iterator iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
                delete(iterator->second);
            }
        }
    };
    struct Trie {
		TrieNode* root;
		int amount_of_patterns;
		Trie (int patterns_amount) {
			root = new TrieNode (0);
			amount_of_patterns = patterns_amount;
		}
		void InsertPattern (std:: vector<long long>& pattern, int& position) {
			TrieNode* current = root;
			TrieNode* next;
			for (std:: vector<long long>:: iterator iterator = pattern.begin(); iterator != pattern.end(); ++iterator) {
				next = current->CheckLink(*iterator);
				if (next == nullptr) {
					next = new TrieNode(*iterator);
					current->nodes.insert({*iterator, next});
					next->dad = current;
				}
				current = next;
			}
			current->end_of_pattern = true;
			current->positions.push_back(position);
		}
		void SetLinks() {
			std:: queue<TrieNode*> elements;
			elements.push(root);
			TrieNode* current;
			while (!elements.empty()) {
				current = elements.front();
				elements.pop();
				for (std:: map<long long, TrieNode*>:: iterator iterator = current->nodes.begin(); iterator != current->nodes.end(); ++iterator) {
					elements.push(iterator->second);
				}
				if (current == root) {
					continue;
				}
				TrieNode* parent = current->dad->link_of_failure;
				while (parent != nullptr && parent->CheckLink(current->value) == nullptr) {
					parent = parent->link_of_failure;
				}
				if (parent == nullptr) {
					current->link_of_failure = root;
				}
				else {
					current->link_of_failure = parent->CheckLink(current->value);
				}
				if (current->link_of_failure->end_of_pattern) {
					current->link_of_exit = current->link_of_failure;
				}
				else if (current->link_of_failure->link_of_exit != nullptr){
					current->link_of_exit = current->link_of_failure->link_of_exit;
				}
			}
		}
		void Search (std:: vector<std:: pair<long long, std:: pair<int, int>>>& text, std:: vector<std:: pair<int, int>>& inclusions) {
			int occurances[text.size()] = {};
			TrieNode * current = root;
			for (int i = 0; i < text.size(); ++i) {
				while (current->link_of_failure != nullptr && current->CheckLink(text[i].first) == nullptr) {
					current = current->link_of_failure;
				}
				if (current->CheckLink(text[i].first) != nullptr) {
					current = current->CheckLink(text[i].first);
				}
				if (current->end_of_pattern) {
					for (std:: vector<int>:: iterator iterator = current->positions.begin(); iterator != current->positions.end(); ++iterator) {
						if (i - *iterator >= 0) {
							++occurances[i - *iterator];
						}
					}
				}
				if (current->link_of_exit != nullptr) {
					TrieNode* node = current->link_of_exit;
					while (node != nullptr) {
						for (std:: vector<int>:: iterator iterator = node->positions.begin(); iterator != node->positions.end(); ++iterator) {
							if (i - *iterator >= 0) {
								++occurances[i - *iterator];
							}
						}
						node = node->link_of_exit;
					}
				}
			}
			for (int i = 0; i < text.size(); ++i) {
				if (occurances[i] == amount_of_patterns) {
					inclusions.push_back(text[i].second);
				}
			}
		}
		~Trie() {
			delete root;
		}
	};
}
namespace TextPatternOperations {
    void PatternProcessing (std:: vector<std:: pair<int, std:: vector<long long>>>& patterns) { 
        std:: string input, data;
		std:: vector<long long> inputed_pattern;
        int position_in_input = 0;
        std:: getline(std:: cin, input);
        std:: stringstream string_pattern(input);
		bool number = false;
        while (string_pattern >> data) {
            if (data == "?" && number) {
                patterns.push_back({position_in_input - 1, inputed_pattern});
                inputed_pattern.clear();
				number = false;
            }
            else if (data != "?") {
                inputed_pattern.push_back(std:: stoll(data));
				number = true;
            }
            ++position_in_input;
        }
        if (position_in_input > 0) {
            patterns.push_back({position_in_input - 1, inputed_pattern});
        }
    }
    void TextProcessing (std:: vector<std:: pair<long long, std:: pair<int, int>>>& text) {
        int number_of_line = 1;
        int number_of_word;
        long long number;
        std:: string input;
        while (std:: getline(std:: cin, input)) {
            std:: stringstream string_pattern(input);
            number_of_word = 1;
            while (string_pattern >> number) {
                text.push_back({number, {number_of_line, number_of_word}});
                ++number_of_word;
            }
            ++number_of_line;
        }
    }
}
int main() {
	std:: ios:: sync_with_stdio(false);
    std:: cin.tie(0);
    std:: cout.tie(0);
    std:: vector<std:: pair<int, std::vector<long long>>> patterns;
    std:: vector<std:: pair<long long, std:: pair<int, int>>> text;
    std:: vector<std:: pair<int, int>> positions;
    TextPatternOperations:: PatternProcessing(patterns);
    TrieAhoKorasik:: Trie* AhoKorasik = new TrieAhoKorasik:: Trie(patterns.size());
	for (std:: vector<std:: pair<int, std:: vector<long long>>>:: iterator iterator = patterns.begin(); iterator != patterns.end(); ++iterator) {
		AhoKorasik->InsertPattern(iterator->second, iterator->first);
	}
	AhoKorasik->SetLinks();
    TextPatternOperations:: TextProcessing(text);
    AhoKorasik->Search(text, positions);
    for (std:: vector<std:: pair<int, int>>:: iterator it = positions.begin(); it != positions.end(); ++it) {
        std:: cout << it->first << ", " << it->second << "\n";
    }
    delete AhoKorasik;
    return 0;
}
