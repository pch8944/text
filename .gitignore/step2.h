#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string.h>
#include<map>
#include<string>
#include<fstream>
#include<math.h>

using namespace std;

void cal_idf();
void cal_tf();
void get_text(char* str);
void remove_ptm(char* str);
void update_doc_map(char* str);
void update_idf_map();
void call_idf_index();
void update_doc_map2(char* str);
