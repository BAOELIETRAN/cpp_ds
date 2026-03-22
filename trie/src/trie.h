#ifndef OBITO_TRIE_H
#define OBITO_TRIE_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>

#define MAX_NODES 1000
#define ALL_CHARS 26

namespace obito{
    // everything is public
    // in a trie, each node represents for a prefix
    struct List_Trie{
        struct Node{
            int id{};
            int children[ALL_CHARS]{};
            // number of strings end exactly at this node
            int end{};
            // number of strings have prefix represented by this node
            int prefix{};

            Node() : id{0}, end{0}, prefix{0}{
                // re-assign value of children
                for (int i = 0; i < ALL_CHARS; i ++){
                    children[i] = -1;
                }
            } 
        };

        // an array of nodes -- each id represents each node
        Node all_nodes[MAX_NODES];
        // total number of nodes
        int num_nodes{};

        // constructor
        List_Trie() : num_nodes{1}{
            all_nodes[0].id = 0;
        }

        // creata a new node
        int create_node(){
            if (num_nodes >= MAX_NODES){
                throw std::runtime_error("Trie is full");
            }
            all_nodes[num_nodes] = Node();
            all_nodes[num_nodes].id = num_nodes;
            int new_node_id = num_nodes;
            num_nodes ++;
            return new_node_id;
        }

        // add a new string to the trie
        void add_string(const std::string& new_str){
            int cur_node_id = 0;
            for (char c : new_str){
                int next_node_id = all_nodes[cur_node_id].children[c - 'a'];
                // the char does not exist
                if (next_node_id == -1){
                    // create a new node
                    next_node_id = create_node();
                    // add it as a child of the current node
                    all_nodes[cur_node_id].children[c - 'a'] = next_node_id;
                }
                all_nodes[next_node_id].prefix ++;
                cur_node_id = next_node_id;
            }
            // if we add an empty string
            if (cur_node_id == 0) all_nodes[cur_node_id].prefix ++;
            // a new string ends at cur_node_id --> raise end
            all_nodes[cur_node_id].end ++;
        }

        // check whether the trie contain the string "word" or not
        bool contain_word(const std::string& word) const{
            int cur_node_id = 0;
            for (char c : word){
                int next_node_id = all_nodes[cur_node_id].children[c - 'a'];
                if (next_node_id == -1){
                    return false;
                }
                cur_node_id = next_node_id;
            }
            if (all_nodes[cur_node_id].end == 0) return false;
            return true;
        }

        // check whether the trie contain the prefix "prefix" or not
        bool contain_prefix(const std::string& prefix) const{
            int cur_node_id = 0;
            for (char c : prefix){
                int next_node_id = all_nodes[cur_node_id].children[c - 'a'];
                if (next_node_id == -1){
                    return false;
                }
                cur_node_id = next_node_id;
            }
            return true;
        }

        // remove the string "str" from the trie
        void remove_string(const std::string& str){
            if (!contain_word(str)) return;
            int path_nodes[MAX_NODES];
            int path_chars[MAX_NODES];
            int cur_node_id = 0;
            int depth = 0;
            for (char c : str){
                path_nodes[depth] = cur_node_id;
                path_chars[depth] = c - 'a';
                int next_node_id = all_nodes[cur_node_id].children[c - 'a'];
                all_nodes[next_node_id].prefix --;
                cur_node_id = next_node_id;
                depth ++;
            }
            // if str is an empty string
            if (cur_node_id == 0) all_nodes[cur_node_id].prefix --;
            all_nodes[cur_node_id].end --;
            // clean up
            for (int i = depth - 1; i >= 0; i --){
                int parent_node_id = path_nodes[i];
                int cur_char = path_chars[i];
                int child_node_id = all_nodes[parent_node_id].children[cur_char];
                // current node is not needed anymore --> reset child node's id to -1
                if (all_nodes[child_node_id].prefix == 0 && all_nodes[child_node_id].end == 0){
                    all_nodes[parent_node_id].children[cur_char] = -1;
                }
                // the rest nodes are needed
                else{
                    break;
                }
            }

        }
    };
} 


#endif