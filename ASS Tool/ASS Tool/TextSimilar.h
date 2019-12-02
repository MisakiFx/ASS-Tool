#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cppjieba/Jieba.hpp>
#include <algorithm>
#include "config.h"

using std::cin;
using std::cerr;
using std::cout;
using std::endl;

//文本相似度检索类
class TextSimilar
{
public:
	typedef std::unordered_map<std::string, double> WordFreq;
	typedef std::unordered_set<std::string> StopWord;
	typedef std::unordered_set<std::string> WordSet;
	typedef std::pair<std::string, double> Pair;
	
	//构造
	TextSimilar(const char* dictPath);
	TextSimilar(Config& config);

	//获取文章相似度接口
	void GetTextSimilar(const char* path1, const char* path2);
private:
	//调试用
	//打印词频
	void PrintWordFreq(const WordFreq& wordFreq);
	
	//打印停用词
	void PrintStopWord();


	//获取停用词
	bool GetStopWord(const char* path);

	//获取idf
	bool GetIDF(const char* path);

	//获取文章词频
	bool GetWordFreq(const char* path, WordFreq& wordFreq);

	//获取相对词频
	void GetNomalFreq(WordFreq& wordFreq);

	//获取tf-idf
	void GetTfIdf(const WordFreq& normalWordFreq, WordFreq& tfIdf);

	//GBK码转UTF8码
	std::string GBKToUTF8(const std::string& gbk);

	//UTF8转GBK码
	std::string UTF8ToGBK(const std::string& utf8);

	//根据词频排序
	void SortByFreq(const WordFreq& wordFreq, std::vector<Pair>& sorted);

	//获取词频编码
	void GetWordCode(std::vector<Pair>& sorted, WordSet& wordCode);

	//构建词频向量
	void GetVector(const WordSet& wordCode, const WordFreq& wordFreq, std::vector<double>& vec);

	//计算向量余弦相似度
	double GetCos(const std::vector<double>& vec1, const std::vector<double>& vec2);
private:
	std::string DICT_PATH;				//词典的位置
	cppjieba::Jieba _jieba;				//分词对象
	StopWord _stopWord;					//停用词表
	int _max;							//最大选取词频向量长度
	WordFreq _idf;						//单词idf值
};

struct Compare
{
	bool operator()(const TextSimilar::Pair& pair1, const TextSimilar::Pair& pair2)
	{
		if (pair1.second > pair2.second)
		{
			return true;
		}
		return false;
	}
};

