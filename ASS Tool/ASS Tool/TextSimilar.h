#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cppjieba/Jieba.hpp>
#include <algorithm>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;

//�ı����ƶȼ�����
class TextSimilar
{
public:
	typedef std::unordered_map<std::string, int> WordFreq;
	typedef std::unordered_set<std::string> StopWord;
	typedef std::unordered_set<std::string> WordSet;
	typedef std::pair<std::string, int> Pair;
	
	//��ȡ�������ƶȽӿ�
	TextSimilar(const char* dictPath);

	void PrintWordFreq(const WordFreq& wordFreq);

	void PrintStopWord();
//private:
	//��ȡͣ�ô�
	void getStopWord(const std::string& path);

	//��ȡ���´�Ƶ
	void getWordFreq(const char* path, WordFreq& wordFreq);

	//GBK��תUTF8��
	std::string GBKToUTF8(const std::string& gbk);

	//UTF8תGBK��
	std::string UTF8ToGBK(const std::string& utf8);

	//���ݴ�Ƶ����
	void SortByFreq(const WordFreq& wordFreq, std::vector<Pair>& sorted);

	//��ȡ��Ƶ����
	void GetWordCode(std::vector<Pair>& sorted, WordSet& wordCode);

	//������Ƶ����
	void GetVector(const WordSet& wordCode, const WordFreq& wordFreq, std::vector<double>& vec);

	//���������������ƶ�
	double GetCos(const std::vector<double>& vec1, const std::vector<double>& vec2);
private:
	std::string DICT_PATH;				//�ʵ��λ��
	cppjieba::Jieba _jieba;				//�ִʶ���
	StopWord _stopWord;					//ͣ�ôʱ�
	int _max;							//���ѡȡ��Ƶ��������
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

