/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
// Question : Bob has an array of games, and they are all stored in the system. Now the system takes input a few queries, and the system should result the number of games in the system to which the query is a prefix.


#include <bits/stdc++.h>

using namespace std;

class TrieNode{
    public:
        unordered_map<int,TrieNode*> children;
        bool isEndOfSequence;
        
        TrieNode() {
            isEndOfSequence = false;
        }
};

class Trie {
    private:
        TrieNode* root = new TrieNode();
        int countSequences(TrieNode* node){
            int count = 0;
            if(node->isEndOfSequence)
                count++;
            for(auto it = node->children.begin() ; it != node->children.end();it++){
                count += countSequences(it->second);
            }
            return count;
        }
        
    public:
        void insert(vector<int>& game){
            TrieNode* node = root;
            for(int i =0;i<game.size();i++){
                if(game[i] == -1)
                    break;
                if(node->children.find(game[i]) == node->children.end()){
                    node->children[game[i]] = new TrieNode();
                }
                node = node->children[game[i]];
            }
            node->isEndOfSequence = true;
        }
        
        int countPrefixes(vector<int> query){
            TrieNode* node = root;
            if(query[0] == -1)
                return 0;
            for(int i=0;i<query.size();i++){
                if((node->children.find(query[i]) == node->children.end()) && query[i]!=-1)
                    return 0;
                else if(query[i] == -1)
                    break;
                else
                    node = node->children[query[i]];
            }
            return countSequences(node);
        }
};

vector<int> solve(vector<vector<int>>&games,vector<vector<int>>&queries){
    Trie* t = new Trie();
    for(int i =0 ; i< games.size();i++){
        t->insert(games[i]);
    }
    vector<int>ans;
    for(int i =0;i<queries.size();i++){
        ans.push_back(t->countPrefixes(queries[i]));
    }
    return ans;
}

int main()
{
    int N,M;
    cout<<"enter N and M"<<endl;
    cin>>N>>M;
    vector<vector<int>>games(N,vector<int>(M,0));
    cout<<"enter the arrays"<<endl;
    for(int i =0;i<N;i++){
        for(int j =0; j<M;j++)
            cin>>games[i][j];
    }
    cout<<"enter Q"<<endl;
    int Q;
    cin>>Q;
    cout<<"enter queries"<<endl;
    vector<vector<int>>queries(Q,vector<int>(M,0));
    for(int i=0 ; i< Q;i++){
        for(int j=0; j < M;j++)
            cin>>queries[i][j];
    }
    cout<<"printing the given inputs"<<endl;
    for(int i=0;i < N;i++){
        for(int j=0;j<M;j++){
            cout<<games[i][j];
        }
        cout<<endl;
    }
    for(int i =0;i<Q;i++){
        for(int j =0;j < M;j++){
            cout<<queries[i][j];
        }
        cout<<endl;
    }
    cout<<"inputs printed"<<endl;
    vector<int>ans = solve(games,queries);
    for(int i =0;i<ans.size();i++){
        cout<<ans[i]<<endl;
    }

    return 0;
}
