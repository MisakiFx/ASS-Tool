#include "TextSimilar.h"
#include <Windows.h>



//const char* const DICT_PATH = "../dict/jieba.dict.utf8";
//const char* const HMM_PATH = "../dict/hmm_model.utf8";
//const char* const USER_DICT_PATH = "../dict/user.dict.utf8";
//const char* const IDF_PATH = "../dict/idf.utf8";
//const char* const STOP_WORD_PATH = "../dict/stop_words.utf8";

TextSimilar::TextSimilar(const char * dictPath)
	:DICT_PATH(dictPath)
	, _jieba(DICT_PATH + "/jieba.dict.utf8"
		, DICT_PATH + "/hmm_model.utf8"
		, DICT_PATH + "/user.dict.utf8"
		, DICT_PATH + "/idf.utf8"
		, DICT_PATH + "/stop_words.utf8")
	, _max(20)
{
	//加载停用词
	std::string path = DICT_PATH + "/stop_words.utf8";
	if (GetStopWord(path.c_str()) == false)
	{
		cerr << "object init failed" << endl;
		exit(-1);
	}
	path = DICT_PATH + "/idf.utf8";
	if (GetIDF(path.c_str()) == false)
	{
		cerr << "object init failed" << endl;
		exit(-1);
	}
}
TextSimilar::TextSimilar(Config & config)
	: _jieba(config._dictPath
		, config._hmmModelPath
		, config._userDictPath
		, config._idfPath
		, config._stopWordPath)
	, _max(config._maxWordNum)
{
	//std::string path = DICT_PATH + "/stop_words.utf8";
	if (GetStopWord(config._stopWordPath.c_str()) == false)
	{
		cerr << "object init failed" << endl;
		exit(-1);
	}
	//path = DICT_PATH + "/idf.utf8";
	if (GetIDF(config._idfPath.c_str()) == false)
	{
		cerr << "object init failed" << endl;
		exit(-1);
	}
}
void TextSimilar::PrintWordFreq(const WordFreq& wordFreq)
{
	for (const auto& e : wordFreq)
	{
		cout << UTF8ToGBK(e.first) << ": " << e.second << endl;
	}
}
void TextSimilar::PrintStopWord()
{
	for (const auto& e : _stopWord)
	{
		cout << UTF8ToGBK(e) << " ";
	}
	cout << endl;
}
void TextSimilar::GetTextSimilar(const char * path1, const char * path2)
{
	TextSimilar::WordFreq wf, tfIdf;
	if (GetWordFreq(path1, wf) == false)
	{
		exit(-1);
	}
	GetNomalFreq(wf);
	GetTfIdf(wf, tfIdf);
	
	//排序
	std::vector<TextSimilar::Pair> sorted, tfIdfSorted;
	SortByFreq(wf, sorted);
	/*cout << "tf: " << endl;
	for (const auto& e : sorted)
	{
		cout << UTF8ToGBK(e.first) << ": " << e.second << " ";
	}
	cout << endl;*/
	SortByFreq(tfIdf, tfIdfSorted);
	/*cout << "tf-edf: " << endl;
	for (const auto& e : tfIdfSorted)
	{
		cout << UTF8ToGBK(e.first) << ": " << e.second << " ";
	}
	cout << endl;*/
	TextSimilar::WordFreq wf2, tfIdf2;
	if (GetWordFreq(path2, wf2) == false)
	{
		exit(-1);
	}
	GetNomalFreq(wf2);
	GetTfIdf(wf2, tfIdf2);
	
	//排序
	std::vector<TextSimilar::Pair> sorted2, tfIdfSorted2;
	SortByFreq(wf2, sorted2);
	/*cout << "tf: " << endl;
	for (const auto& e : sorted2)
	{
		cout << UTF8ToGBK(e.first) << ": " << e.second << " ";
	}
	cout << endl;*/
	SortByFreq(tfIdf2, tfIdfSorted2);
	/*cout << "tf-edf: " << endl;
	for (const auto& e : tfIdfSorted2)
	{
		cout << UTF8ToGBK(e.first) << ": " << e.second << " ";
	}
	cout << endl;*/

	//获取编码
	TextSimilar::WordSet wordCode, wordTfIdfCode;
	GetWordCode(sorted, wordCode);
	GetWordCode(sorted2, wordCode);
	GetWordCode(tfIdfSorted, wordTfIdfCode);
	GetWordCode(tfIdfSorted2, wordTfIdfCode);
	
	//获取词频向量
	std::vector<double> vec1, vec2;
	std::vector<double> tfIdfVec1, tfIdfVec2;
	GetVector(wordCode, wf, vec1);
	GetVector(wordCode, wf2, vec2);
	GetVector(wordTfIdfCode, tfIdf, tfIdfVec1);
	GetVector(wordTfIdfCode, tfIdf2, tfIdfVec2);

	//计算余弦相似度
	cout << "tf: " << GetCos(vec1, vec2) << endl;
	cout << "tf-idf: " << GetCos(tfIdfVec1, tfIdfVec2) << endl;
	//return GetCos(vec1, vec2);
}
bool TextSimilar::GetStopWord(const char* path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		cerr << "stop word file open error" << endl;
		return false;
	}
	std::string temp;
	while (!file.eof())
	{
		std::getline(file, temp);
		_stopWord.insert(temp);
	}
	file.close();
	return true;
}
bool TextSimilar::GetIDF(const char * path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		cerr << "open IDF file error" << endl;
		return false;
	}
	std::pair<std::string, double> input;
	while (!file.eof())
	{
		file >> input.first >> input.second;
		_idf.insert(input);
	}
	//cout << "idf size:" << _idf.size() << endl;
	return true;
}
bool TextSimilar::GetWordFreq(const char * path, WordFreq & wordFreq)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		cerr << "path: [" << path << "] file open error" << endl;
		return false;
	}
	std::string line;
	std::vector<std::string> words;
	//读取每一行进行分词
	while (!file.eof())
	{
		words.clear();
		std::getline(file, line);
		line = GBKToUTF8(line);
		_jieba.Cut(line, words, true);
		for (const auto& e : words)
		{
			//去停用词
			if (_stopWord.find(e) != _stopWord.end())
			{
				continue;
			}

			wordFreq[e]++;
		}
	}
	file.close();
}

void TextSimilar::GetNomalFreq(WordFreq & wordFreq)
{
	//int sz = wordFreq.size();
	int sz = 0;
	for (const auto& e : wordFreq)
	{
		sz += e.second;
	}
	for (auto& wf : wordFreq)
	{
		wf.second /= sz;
	}
}

void TextSimilar::GetTfIdf(const WordFreq & normalWordFreq, WordFreq & tfIdf)
{
	for (const auto& e : normalWordFreq)
	{
		tfIdf.insert(std::make_pair(e.first, e.second * _idf[e.first]));
	}
}

std::string TextSimilar::GBKToUTF8(const std::string & gbk)
{
	//只有UTF16才有到各种编码格式的映射，所以要先转UTF16作为桥梁
	//GBK -> UTF16
	int utf16Bytes = MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, nullptr, 0);
	//宽字符字符串
	wchar_t* utf16Buffer = new wchar_t[utf16Bytes];
	MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, utf16Buffer, utf16Bytes);

	//UTF16 -> UTF8
	int utf8Bytes = WideCharToMultiByte(CP_UTF8, 0, utf16Buffer, -1, nullptr, 0, nullptr, nullptr);
	char* utf8Buffer = new char[utf8Bytes];
	WideCharToMultiByte(CP_UTF8, 0, utf16Buffer, -1, utf8Buffer, utf8Bytes, nullptr, nullptr);

	std::string outString(utf8Buffer);
	delete[] utf16Buffer;
	delete[] utf8Buffer;
	return outString;
	return std::string();
}

std::string TextSimilar::UTF8ToGBK(const std::string & utf8)
{
	//只有UTF16才有到各种编码格式的映射，所以要先转UTF16作为桥梁
	//UTF8 -> UTF16
	int utf16Bytes = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
	//宽字符字符串
	wchar_t* utf16Buffer = new wchar_t[utf16Bytes];
	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, utf16Buffer, utf16Bytes);

	//UTF16 -> GBK
	int gbkBytes = WideCharToMultiByte(CP_ACP, 0, utf16Buffer, -1, nullptr, 0, nullptr, nullptr);
	char* gbkBuffer = new char[gbkBytes];
	WideCharToMultiByte(CP_ACP, 0, utf16Buffer, -1, gbkBuffer, gbkBytes, nullptr, nullptr);

	std::string outString(gbkBuffer);
	delete[] utf16Buffer;
	delete[] gbkBuffer;
	return outString;
	return std::string();
}

void TextSimilar::SortByFreq(const WordFreq & wordFreq, std::vector<Pair>& sorted)
{
	sorted.clear();
	for (const auto& e : wordFreq)
	{
		sorted.push_back(e);
	}
	std::sort(sorted.begin(), sorted.end(), Compare());
}

void TextSimilar::GetWordCode(std::vector<Pair>& sorted, WordSet & wordCode)
{
	int len = sorted.size();
	int sz = len < _max ? len : _max;
	for (int i = 0; i < sz; i++)
	{
		wordCode.insert(sorted[i].first);
	}
}

void TextSimilar::GetVector(const WordSet & wordCode, const WordFreq & wordFreq, std::vector<double>& vec)
{
	vec.clear();
	int sz = wordCode.size();
	vec.reserve(sz);
	for (const auto& e : wordCode)
	{
		TextSimilar::WordFreq::const_iterator it = wordFreq.find(e);
		if (it != wordFreq.end())
		{
			vec.push_back(it->second);
		}
		else
		{
			vec.push_back(0);
		}
	}
}

double TextSimilar::GetCos(const std::vector<double>& vec1, const std::vector<double>& vec2)
{
	if (vec1.size() != vec2.size())
	{
		cerr << "unknown error" << endl;
		return 0;
	}
	double product = 0.0;
	double modal1 = 0.0, modal2 = 0.0;
	for (int i = 0; i < vec1.size(); i++)
	{
		product += vec1[i] * vec2[i];
	}
	for (int i = 0; i < vec1.size(); i++)
	{
		modal1 += pow(vec1[i], 2);
	}
	modal1 = sqrt(modal1);
	for (int i = 0; i < vec2.size(); i++)
	{
		modal2 += pow(vec2[i], 2);
	}
	modal2 = sqrt(modal2);
	return product / (modal1 * modal2);
}
