#include"DataStructure/Tire.h"

int main() {
    Trie trie;
    trie.insert("apple");
    trie.printLayerOrder();
    cout<<trie.search("apple")<<endl;
    cout<<trie.search("app")<<endl;
    cout<<trie.startsWith("app")<<endl;
    trie.insert("app");
    trie.printLayerOrder();
    cout<<trie.search("app")<<endl;

    return 0;
}