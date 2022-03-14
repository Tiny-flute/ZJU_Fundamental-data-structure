#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;
class File{
public:
    vector<vector<string>> blocks;
    unordered_map<string, int> hash_files;  //string for title name, int for number of blocks accordingly
    unordered_map<string, vector<int>> inverted_file;
    void stem_words(string name, File * pobj);
    void create_index(string file_name, File * pin);
    void output(vector<string> order, File *pin);

private:
    double distance(File * in, string doc1, string doc2);
    int frequency(File  * in, string doc, string word);
    int find_position(string block_name, unordered_map<string, int> table);
};
int main() {
    int number_block = 0;
    string temp;
    File documents;
    int i, j = 0;
    cin>> number_block;
    for(i = 0; i < number_block; i++)
    {
        getchar();
        vector<string> words;
        string title_name;
        getline(cin, title_name);
        transform(title_name.begin(),title_name.end(),title_name.begin(),::tolower);
        documents.hash_files.emplace(title_name, i);
        cin>> temp;
        for(transform(temp.begin(),temp.end(),temp.begin(),::tolower);;j++)
        {
            if(temp == "#")
                break;
            else
                words.emplace_back(temp);
            cin>> temp;
            transform(temp.begin(),temp.end(),temp.begin(),::tolower);  //upper case to lower case
        }
        documents.blocks.insert(documents.blocks.begin() + i, words);
        documents.stem_words(title_name, &documents);
        documents.create_index(title_name, &documents);
    }

    int number_inqury;
    cin>>number_inqury;
    number_inqury *= 2;
    vector<string> inquries;
    for(int i = 0; i < number_inqury; i++)
    {
        cin>>temp;
        transform(temp.begin(),temp.end(),temp.begin(),::tolower);
        inquries.push_back(temp);
    }

    documents.output(inquries, &documents);

    return 0;
}
double File::distance(File *pin, string doc1, string doc2)
{
    unordered_map<string, int> words_list;  //bookkeeping for existed words
    auto in = *pin;
    double product = 0;
    double product1, product2;
    product1 = product2 = 0;
    int a = in.blocks[find_position(doc1, in.hash_files)].size();
    int b = in.blocks[find_position(doc2, in.hash_files)].size();
    int i;
    auto file1 = in.blocks[find_position(doc1, in.hash_files)];
    auto file2 = in.blocks[find_position(doc2, in.hash_files)];  //store list
    for(i = 0; i < a; i++)
    {
        double f1, f2;
        if(i == 0)
        {
            words_list.emplace(file1[i], i);
            f1 = frequency(&in, doc1, file1[i]);
            f2 = frequency(&in, doc2, file1[i]);
            product1 += f1 * f1;
            product2 += f2 * f2;
            product += f1 * f2;
            continue;
        }
        if(words_list.end() == words_list.find(file1[i]))  //not find
        {
            words_list.emplace(file1[i], i);
            f1 = frequency(&in, doc1, file1[i]);
            f2 = frequency(&in, doc2, file1[i]);
            product1 += f1 * f1;
            product2 += f2 * f2;
            product += f1 * f2;
        }
    }

    for(i = 0; i < b; i++)
    {
        if(words_list.end() == words_list.find(file2[i]))  //not exist
        {
            double f2 = frequency(&in, doc2, file2[i]);
            product2 += f2 * f2;
        }
        else continue;
    }

    return acos((product)/sqrt((fabs(product1) * fabs(product2))));
}
int File::find_position(string block_name, unordered_map<string, int> table)
{
    auto temp = table.find(block_name);
    if(temp == table.end())
    {
        printf("[Error]: ");
    }
    return temp->second;
}
void File::stem_words(string name, File * pobj)
{
    int number = find_position(name, File::hash_files);
    int i = 0;
    auto current_document = (*pobj).blocks[number];
    string temp;
    int end = current_document.size();
    for(;i < end; i++)
    {
        temp = current_document[i];  //for single word
        int size_word = temp.size();
        if(size_word <= 2)
            continue;
        if(temp[size_word - 1] == 's')  //last word
        {
            if(temp[size_word - 2] == 'e')  //es condition
            {
                if(temp[size_word - 3] == 'i')  //ies condition
                {
                    temp.replace(size_word - 3, size_word - 1, "y");
                }
                else
                    temp.erase(size_word - 2);  //es
            }
        }
        else if(temp[size_word - 1] == 'g' && temp[size_word - 2] == 'n' && temp[size_word - 3] == 'i')  //ing condition
            temp.erase(size_word - 3);
        else if(temp[size_word - 1] == 'd' || temp[size_word - 2] == 'e')  //ed condition
            temp.erase(size_word - 2);
        current_document[i] = temp;
    }
    (*pobj).blocks[number] = current_document;
}
void File::create_index(string file_name, File *in)
{
    int number_file = find_position(file_name, in->hash_files);
    auto p2index = &(in->inverted_file);  //index needs to be updated
    auto current_file = in->blocks[number_file];
    int size_file = current_file.size();
    int i;
    for(i = 0; i < size_file; i++)
    {
        auto temp = (*p2index).find(current_file[i]);
        if(temp == (*p2index).end())  //do not find
        {
            vector<int> location;
            location.push_back(number_file);
            (*p2index).emplace(current_file[i], location);
        }
        else
        {
            auto location = temp->second;
            location.push_back(number_file);   //update location
            temp->second = location;
        }
    }
}
int File::frequency(File *pin, string doc, string word)
{
    auto in = *pin;
    auto inverted_index = in.inverted_file;
    auto times_vec = inverted_index.find(word)->second;  //frequency information
    int size_vec = times_vec.size();
    int i;
    int number_file = find_position(doc, in.hash_files);
    int count = 0;
    for(i = 0; i < size_vec; i++)
    {
        if(number_file == times_vec[i])
            count++;
    }
    return count;
}
void File::output(vector <string> order,File *pin)
{
    auto in = *pin;
    int size_list = order.size() / 2;
    int i;
    for(i = 0; i < size_list; i++)
    {
        double result = distance(&in, order[2 * i], order[2 * i + 1]);

        cout.precision(3);
        cout<<"Case "<<i+1<<": "<<result;
        if(i < size_list - 1)
            cout<<endl;
    }
}