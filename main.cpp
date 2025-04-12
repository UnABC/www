
//#define DEBUG

#include <bits/stdc++.h>
using namespace std;

class WV{
private:
	string file_content;
	//各種スタック
	vector<long long> st;
	stack<long long> call_st;
	//ヒープ
	map<long long, long long> heap;
	//ラベル
	map<long long, long long> label;
	//現在の位置
	long long pos = 0;
	//ラベルどこ？
	long long searching_label = -1;

	//DEBUGオプション
	bool DEBUG = false;
public:
	WV(bool debug = false) : DEBUG(debug) {}
	bool ReadFile(string filename);
	long long ReadArg();
	long long bin2dec(string bin);
	bool EXEC();
};

//ファイルを読み込み、コメントを削除する
bool WV::ReadFile(string filename) {
	ifstream inputFile(filename);
	if (!inputFile) {
		cerr << "Error opening file: " << filename << endl;
		return false;
	}
	string line;
	//コメント削除
	while (getline(inputFile, line)) {
		for (char c : line) {
			if ((c == 'w')||(c == 'W')||(c == 'v')||(c == 'V'))file_content += c;
		}
	}
	inputFile.close();
	if (DEBUG)cout << file_content << endl;
	return true;
}

//引数を読み込み、十進数に変換する
long long WV::ReadArg() {
	string bin;
	//引数終了位置まで読み込む
	for (pos += 2;file_content[pos] != 'V';pos++){
		switch (file_content[pos]){
		case 'w':
			bin += "0";
			break;
		case 'v':
			bin += "1";
			break;
		default:
			cerr << "Error: Invalid character in binary string(position:" << pos << ")" << endl;
			return -1;
		}
	}
	pos++;
	if (DEBUG)cout << "DEBUG;bin: " << bin << ",pushed: " << bin2dec(bin) << endl;
	return bin2dec(bin);
}

long long WV::bin2dec(string bin) {
	long long dec = 0;
	for (char c : bin) dec = (dec << 1) | (c - '0');
	return dec;
}

#define is_searching_label if (searching_label != -1)return true;

bool WV::EXEC() {
	if (pos >= file_content.size()){
		//EOF
		if (searching_label != -1){
			cerr << "Error: Label not found" << endl;
			return false;
		}
		if (DEBUG)cout << "DEBUG;EOF" << endl;
		return false; // EOF
	}
	char IMP = file_content[pos++];
	if (DEBUG)cout << "DEBUG;pos: " << pos << ", IMP: " << IMP << ",order:" << file_content.substr(pos, 2) << endl;
	if (IMP == 'W') {
		//スタック操作
		if (file_content.substr(pos, 2) == "WW"){
			//スタックに値をpush
			if (long long arg = ReadArg(); arg == -1){
				return false;
			}else{
				is_searching_label
				st.push_back(arg);
			}
		}else if (file_content.substr(pos, 2) == "Ww"){
			//(引数)番目のスタックを複製し一番上に積む
			if (long long arg = ReadArg(); arg == -1){
				return false;
			}else{
				is_searching_label
				if (arg >= st.size()){
					cerr << "Error: Stack index out of range(position:" << pos << ")" << endl;
					return false;
				}
				st.push_back(st.at(arg));
			}
		}else if (file_content.substr(pos, 2) == "Wv"){
			pos += 2;
			is_searching_label
			//一番上のスタックを複製し一番上に積む
			if (st.empty()){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			st.push_back(st.back());
		}else if (file_content.substr(pos, 2) == "WV"){
			pos += 2;
			is_searching_label
			//スタックを交換
			if (st.size() < 2){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			swap(st[st.size()-1], st[st.size()-2]);
		}else if (file_content.substr(pos, 2) == "Vv"){
			pos += 2;
			is_searching_label
			//スタックを破棄
			if (st.empty()){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			st.pop_back();
		}else if (file_content.substr(pos, 2) == "VV"){
			//(引数)個のスタックを破棄
			if (long long arg = ReadArg(); arg == -1){
				return false;
			}else{
				is_searching_label
				if (arg > st.size()){
					cerr << "Error: Stack index out of range(position:" << pos << ")" << endl;
					return false;
				}
				st.erase(st.end()-arg, st.end());
			}
		}else if (file_content.substr(pos, 2) == "Ww"){
			pos += 2;
			is_searching_label
			//スタックをランダムに並び替える
			if (st.empty()){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			random_device seed_gen;
			mt19937 engine(seed_gen());
			shuffle(st.begin(), st.end(),engine);
		}
	} else if (IMP == 'w') {
		//四則演算およびラベル操作
		if (file_content.substr(pos, 2) == "ww"){
			pos += 2;
			is_searching_label
			//スタックの一番上の値を加算
			if (st.size() < 2){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			long long a = st.back(); st.pop_back();
			long long b = st.back(); st.pop_back();
			st.push_back(a + b);
		}else if (file_content.substr(pos, 2) == "wv"){
			pos += 2;
			is_searching_label
			//スタックの一番上の値を減算
			if (st.size() < 2){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			long long a = st.back(); st.pop_back();
			long long b = st.back(); st.pop_back();
			st.push_back(b - a);
		}else if (file_content.substr(pos, 2) == "vv"){
			pos += 2;
			is_searching_label
			//スタックの一番上の値を乗算
			if (st.size() < 2){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			long long a = st.back(); st.pop_back();
			long long b = st.back(); st.pop_back();
			st.push_back(a * b);
		}else if (file_content.substr(pos, 2) == "vw"){
			pos += 2;
			is_searching_label
			//スタックの一番上の値を除算
			if (st.size() < 2){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			long long a = st.back(); st.pop_back();
			long long b = st.back(); st.pop_back();
			if (a == 0){
				cerr << "Error: Division by zero(position:" << pos << ")" << endl;
				return false;
			}
			st.push_back(b / a);
		}else if (file_content.substr(pos, 2) == "vW"){
			pos += 2;
			is_searching_label
			//スタックの一番上の値を剰余
			if (st.size() < 2){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			long long a = st.back(); st.pop_back();
			long long b = st.back(); st.pop_back();
			if (a == 0){
				cerr << "Error: Division by zero(position:" << pos << ")" << endl;
				return false;
			}
			st.push_back(b % a);
		//ここからラベル操作
		}else if (file_content.substr(pos, 2) == "Vw"){
			//ラベルを設定
			if (long long arg = ReadArg(); arg == -1){
				return false;
			}else{
				label[arg] = pos;
				//ラベルが見つかった場合、現在の位置を更新
				if (searching_label == arg)searching_label = -1;
			}
		}else if (file_content.substr(pos, 2) == "Ww"){
			//ラベルを参照
			if (long long arg = ReadArg(); arg == -1){
				return false;
			}else{
				is_searching_label
				if (!label.count(arg)){
					searching_label = arg;
				}else{
					pos = label[arg];
				}
				if (DEBUG)cout << "DEBUG;goto * " << arg << ",pos: " << pos << endl;
			}
		}else if (file_content.substr(pos, 2) == "Wv"){
			//スタックが0ならラベルを参照
			if (st.empty() && (searching_label == -1)){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			if (long long arg = ReadArg(); arg == -1){
				return false;
			}else{
				is_searching_label
				if (long long a = st.back();a == 0){
					if (!label.count(arg)){
						searching_label = arg;
					}else{
						pos = label[arg];
					}
					if (DEBUG)cout << "DEBUG;goto * " << arg << ",pos: " << pos << endl;
				}
			}
			st.pop_back();
		}else if (file_content.substr(pos, 2) == "WV"){
			//スタックが負ならラベルを参照
			if (st.empty() && (searching_label == -1)){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
				if (long long arg = ReadArg(); arg == -1){
					return false;
				}else{
					is_searching_label
					if (long long a = st.back();a < 0){
						if (!label.count(arg)){
							searching_label = arg;
						}else{
							pos = label[arg];
						}
						if (DEBUG)cout << "DEBUG;goto * " << arg << ",pos: " << pos << endl;
					}
				}
			st.pop_back();
		}else if (file_content.substr(pos, 2) == "Vv"){
			//現在の位置をコールスタックに積んで指定したラベルに移動
			if (long long arg = ReadArg(); arg == -1){
				return false;
			}else{
				is_searching_label
				call_st.push(pos);
				if (!label.count(arg)){
					searching_label = arg;
				}else{
					pos = label[arg];
				}
				if (DEBUG)cout << "DEBUG;goto * " << arg << ",pos: " << pos << endl;
			}
		}else if (file_content.substr(pos, 2) == "vV"){
			is_searching_label
			//コールスタックから戻る
			if (call_st.empty()){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			pos = call_st.top(); call_st.pop();
		}
	} else if (IMP == 'v') {
		//ヒープおよび入出力操作
		if (file_content.substr(pos, 2) == "Vv"){
			pos += 2;
			is_searching_label
			//ヒープに値を格納
			if (st.size() < 2){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			long long address = st.back(); st.pop_back();
			long long value = st.back(); st.pop_back();
			heap[address] = value;
			if (DEBUG)cout << "DEBUG;heap[" << address << "] = " << value << endl;
		}else if (file_content.substr(pos, 2) == "VV"){
			pos += 2;
			is_searching_label
			//ヒープから値を取得
			if (st.empty()){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			long long address = st.back(); st.pop_back();
			if (!heap.count(address)){
				cerr << "Error: Address(" << address << ") not found in heap(position:" << pos << ")" << endl;
				return false;
			}
			st.push_back(heap[address]);
		}else if (file_content.substr(pos, 2) == "vv"){
			pos += 2;
			is_searching_label
			//一番上のスタックの値=文字コードに対応する文字を出力
			if (st.empty()){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			long long value = st.back(); st.pop_back();
			if (DEBUG)cout << "DEBUG;value: " << value << endl;
			cout << static_cast<char>(value);
		}else if (file_content.substr(pos, 2) == "vw"){
			pos += 2;
			is_searching_label
			//一番上のスタックの値を出力
			if (st.empty()){
				cerr << "Error: Stack is empty(position:" << pos << ")" << endl;
				return false;
			}
			cout << st.back();st.pop_back();
		}else if (file_content.substr(pos, 2) == "wv"){
			pos += 2;
			is_searching_label
			//一文字を読み取りその文字コードをスタックに積む
			char c;
			scanf("%c", &c);
			st.push_back(static_cast<long long>(c));
		}else if (file_content.substr(pos, 2) == "ww"){
			pos += 2;
			is_searching_label
			//一行を読み取りその数字をスタックに積む
			long long num;
			cin >> num;
			st.push_back(num);
		}
	} else if (IMP == 'V') {
		is_searching_label
		//終了処理
		if (file_content.substr(pos, 1) == "V"){
			if (DEBUG)cout << "DEBUG;END" << endl;
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	bool DEBUG = false;
	if ((argc == 3)&&(argv[2] == string("-d"))){
		DEBUG = true;
	}else if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <input_file> [-d]" << endl;
		return 1;
	}
	WV wv(DEBUG);
	//ファイル読み込み+コメント削除
	wv.ReadFile(argv[1]);
	//ファイル内容を実行する
	while (wv.EXEC());
	return 0;
}

