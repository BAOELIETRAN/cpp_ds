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
    struct Trie{
        struct Node{
            int id{};
            int children[ALL_CHARS];
            // how many strings end exactly at this Node
            int end{};
            // how many strings have prefix ends exactly at this Node
            int prefix{};
        };

        // an array of nodes -- each id represents each node
        Node all_nodes[MAX_NODES];
        // total number of nodes
        int num_nodes{};

        // constructor
        Trie() : num_nodes{0}{
            // reset the all_nodes array
            for (int i = 0; i < MAX_NODES; i ++){
                all_nodes[i] = Node();
                Node& root = all_nodes[i];
                for (int i = 0; i < ALL_CHARS; i ++){
                    root.children[i] = -1;
                }
                root.end = 0;
                root.prefix = 0;
            }
            // first node is root node 0
            // set root node id to 0
            all_nodes[0].id = num_nodes;
            num_nodes ++;
        }

        // add new node to trie
        void add_node(Node& cur_node, char c){
            Node& new_node = all_nodes[num_nodes];
            new_node.id = num_nodes;
            // 1 string ends exactly at new node
            new_node.end = 1;
            // 1 prefix string ends exactly at new node
            new_node.prefix = 1;
            int neigh_pos = c - 'a';
            cur_node.children[neigh_pos] = new_node.id;
            num_nodes ++;
        }

        // add a new string to the trie
        void add_string(const std::string& new_str){
            int cur_node_id = 0;
            int len = new_str.length();
            int cur_index = 0;
            while (cur_index < len){
                Node& cur_node = all_nodes[cur_node_id];
                char cur_char = new_str[cur_index];
                // next node
                cur_node_id = cur_node.children[cur_char - 'a'];
                // already has this character
                if (cur_node_id != -1){
                    all_nodes[cur_node_id].prefix ++;
                }
                // does not have this character
                else{
                    add_node(cur_node, cur_char);
                }
                cur_index ++;
            }
            // end at cur_node --> raise cur_node.end
            all_nodes[cur_node_id].end ++;
        }

        // check whether the trie contain the str or not
        bool contain(const std::string& str){
            int cur_node_id = 0;
            int len = str.length();
            int cur_index = 0;
            while (cur_index < len){
                Node& cur_node = all_nodes[cur_node_id];
                char cur_char = str[cur_index];
                cur_node_id = cur_node.children[cur_char - 'a'];
                // does not have this character
                if (cur_node_id == -1){
                    return false;
                }
                cur_index ++;
            }  
            return true; 
        }

        // remove a string from the trie
        void remove_string(const std::string& str){
            if (!contain(str)) return;
            
        }
    };
} 


#endif