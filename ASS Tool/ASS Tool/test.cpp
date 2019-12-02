//#include "cppjieba/Jieba.hpp"
//#include <Windows.h>
//
//using namespace std;
//
//const char* const DICT_PATH = "../dict/jieba.dict.utf8";
//const char* const HMM_PATH = "../dict/hmm_model.utf8";
//const char* const USER_DICT_PATH = "../dict/user.dict.utf8";
//const char* const IDF_PATH = "../dict/idf.utf8";
//const char* const STOP_WORD_PATH = "../dict/stop_words.utf8";
//
////��GBK����תUTF8����
//string GBKToUTF8(const string& gbk)
//{
//	//ֻ��UTF16���е����ֱ����ʽ��ӳ�䣬����Ҫ��תUTF16��Ϊ����
//	//GBK -> UTF16
//	int utf16Bytes = MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, nullptr, 0);
//	//���ַ��ַ���
//	wchar_t* utf16Buffer = new wchar_t[utf16Bytes];
//	MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, utf16Buffer, utf16Bytes);
//	
//	//UTF16 -> UTF8
//	int utf8Bytes = WideCharToMultiByte(CP_UTF8, 0, utf16Buffer, -1, nullptr, 0, nullptr, nullptr);
//	char* utf8Buffer = new char[utf8Bytes];
//	WideCharToMultiByte(CP_UTF8, 0, utf16Buffer, -1, utf8Buffer, utf8Bytes, nullptr, nullptr);
//	
//	string outString(utf8Buffer);
//	delete[] utf16Buffer;
//	delete[] utf8Buffer;
//	return outString;	
//}
//
//string UTF8ToGBK(const string& utf8)
//{
//	//ֻ��UTF16���е����ֱ����ʽ��ӳ�䣬����Ҫ��תUTF16��Ϊ����
//	//UTF8 -> UTF16
//	int utf16Bytes = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
//	//���ַ��ַ���
//	wchar_t* utf16Buffer = new wchar_t[utf16Bytes];
//	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, utf16Buffer, utf16Bytes);
//
//	//UTF16 -> GBK
//	int gbkBytes = WideCharToMultiByte(CP_ACP, 0, utf16Buffer, -1, nullptr, 0, nullptr, nullptr);
//	char* gbkBuffer = new char[gbkBytes];
//	WideCharToMultiByte(CP_ACP, 0, utf16Buffer, -1, gbkBuffer, gbkBytes, nullptr, nullptr);
//
//	string outString(gbkBuffer);
//	delete[] utf16Buffer;
//	delete[] gbkBuffer;
//	return outString;
//}
//
//int main(int argc, char** argv) {
//	cppjieba::Jieba jieba(DICT_PATH,
//		HMM_PATH,
//		USER_DICT_PATH,
//		IDF_PATH,
//		STOP_WORD_PATH);
//	vector<string> words;
//	//vector<cppjieba::Word> jiebawords;
//	string s;
//	string result;
//
//	s = "�����������׺��д���";
//	cout << s << endl;
//	string utf8 = GBKToUTF8(s);
//	cout << "[demo] Cut With HMM" << endl;
//	jieba.Cut(utf8, words, true);
//	//cout << limonp::Join(words.begin(), words.end(), "/") << endl;
//	for (auto e : words)
//	{
//		cout << UTF8ToGBK(e) << " ";
//	}
//	/*cout << "[demo] Cut Without HMM " << endl;
//	jieba.Cut(utf8, words, false);
//	cout << limonp::Join(words.begin(), words.end(), "/") << endl;*/
//
//	/*
//	s = "�����������廪��ѧ";
//	cout << s << endl;
//	cout << "[demo] CutAll" << endl;
//	jieba.CutAll(s, words);
//	cout << limonp::Join(words.begin(), words.end(), "/") << endl;
//
//	s = "С��˶ʿ��ҵ���й���ѧԺ�������������ձ�������ѧ����";
//	cout << s << endl;
//	cout << "[demo] CutForSearch" << endl;
//	jieba.CutForSearch(s, words);
//	cout << limonp::Join(words.begin(), words.end(), "/") << endl;
//
//	cout << "[demo] Insert User Word" << endl;
//	jieba.Cut("��ĬŮ��", words);
//	cout << limonp::Join(words.begin(), words.end(), "/") << endl;
//	jieba.InsertUserWord("��ĬŮ��");
//	jieba.Cut("��ĬŮ��", words);
//	cout << limonp::Join(words.begin(), words.end(), "/") << endl;
//
//	cout << "[demo] CutForSearch Word With Offset" << endl;
//	jieba.CutForSearch(s, jiebawords, true);
//	cout << jiebawords << endl;
//
//	cout << "[demo] Lookup Tag for Single Token" << endl;
//	const int DemoTokenMaxLen = 32;
//	char DemoTokens[][DemoTokenMaxLen] = { "������", "CEO", "123", "��" };
//	vector<pair<string, string> > LookupTagres(sizeof(DemoTokens) / DemoTokenMaxLen);
//	vector<pair<string, string> >::iterator it;
//	for (it = LookupTagres.begin(); it != LookupTagres.end(); it++) {
//		it->first = DemoTokens[it - LookupTagres.begin()];
//		it->second = jieba.LookupTag(it->first);
//	}
//	cout << LookupTagres << endl;
//
//	cout << "[demo] Tagging" << endl;
//	vector<pair<string, string> > tagres;
//	s = "����������ѧԺ�ַ�������רҵ�ġ����ö�ã��Ҿͻ���ְ��н������CEO�����������۷塣";
//	jieba.Tag(s, tagres);
//	cout << s << endl;
//	cout << tagres << endl;
//
//	cout << "[demo] Keyword Extraction" << endl;
//	const size_t topk = 5;
//	vector<cppjieba::KeywordExtractor::Word> keywordres;
//	jieba.extractor.Extract(s, keywordres, topk);
//	cout << s << endl;
//	cout << keywordres << endl;
//	return EXIT_SUCCESS;
//	*/
//}
#include "TextSimilar.h"

//void testWordFreq()
//{
//	TextSimilar textSimilar("../dict");
//	//textSimilar.PrintStopWord();
//	TextSimilar::WordFreq wf;
//	textSimilar.GetWordFreq("../../test.txt", wf);
//	textSimilar.GetNomalFreq(wf);
//	//textSimilar.PrintWordFreq(wf);
//	//����
//	std::vector<TextSimilar::Pair> sorted;
//	textSimilar.SortByFreq(wf, sorted);
//	cout << "-------------------------------------------------------" << endl;
//	for (const auto& e : sorted)
//	{
//		cout << textSimilar.UTF8ToGBK(e.first) << ": " << e.second << " ";
//	}
//	cout << endl;
//
//
//	TextSimilar::WordFreq wf2;
//	textSimilar.GetWordFreq("../../test2.txt", wf2);
//	textSimilar.GetNomalFreq(wf2);
//	cout << "text2_______________________________________________________" << endl;
//	//textSimilar.PrintWordFreq(wf2);
//	//����
//	std::vector<TextSimilar::Pair> sorted2;
//	textSimilar.SortByFreq(wf2, sorted2);
//	cout << "-------------------------------------------------------" << endl;
//	for (const auto& e : sorted2)
//	{
//		cout << textSimilar.UTF8ToGBK(e.first) << ": " << e.second << " ";
//	}
//	cout << endl;
//
//	//��ȡ����
//	TextSimilar::WordSet wordCode;
//	textSimilar.GetWordCode(sorted, wordCode);
//	textSimilar.GetWordCode(sorted2, wordCode);
//	cout << "����: " << endl;
//	for (const auto& e : wordCode)
//	{
//		cout << textSimilar.UTF8ToGBK(e) << " ";
//	}
//	cout << endl;
//
//	std::vector<double> vec1, vec2;
//	textSimilar.GetVector(wordCode, wf, vec1);
//	for (const auto& e : vec1)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//	textSimilar.GetVector(wordCode, wf2, vec2);
//	for (const auto& e : vec2)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	cout << textSimilar.GetCos(vec1, vec2) << endl;
//}
//int main()
//{
//	//testWordFreq();
//	TextSimilar textSimilar("../dict");
//	cout << (textSimilar.GetTextSimilar("../../test.txt", "../../test2.txt")) << endl;
//	system("pause");
//}

