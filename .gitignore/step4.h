#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string.h>
#include<map>
#include<set>
#include<string>
#include<fstream>
#include<math.h>

using namespace std;

void classifier();
string topic_extract2(char* line);
void update_t_map(string topic, char* str, float value);
void cal_tf2();
void call_idf_index2();
void remove_ptm2(char *str);
void update_doc_map3(char *str);

struct Vector {
	std::map<string, double> vector;
};