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

//�ı����ƶȼ�����
class TextSimilar
{
public:
	typedef std::unordered_map<std::string, double> WordFreq;
	typedef std::unordered_set<std::string> StopWord;
	typedef std::unordered_set<std::string> WordSet;
	typedef std::pair<std::string, double> Pair;
	
	//����
	TextSimilar(const char* dictPath);
	TextSimilar(Config& config);

	//��ȡ�������ƶȽӿ�
	void GetTextSimilar(const char* path1, const char* path2);
private:
	//������
	//��ӡ��Ƶ
	void PrintWordFreq(const WordFreq& wordFreq);
	
	//��ӡͣ�ô�
	void PrintStopWord();


	//��ȡͣ�ô�
	bool GetStopWord(const char* path);

	//��ȡidf
	bool GetIDF(const char* path);

	//��ȡ���´�Ƶ
	bool GetWordFreq(const char* path, WordFreq& wordFreq);

	//��ȡ��Դ�Ƶ
	void GetNomalFreq(WordFreq& wordFreq);

	//��ȡtf-idf
	void GetTfIdf(const WordFreq& normalWordFreq, WordFreq& tfIdf);

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
	WordFreq _idf;						//����idfֵ
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

