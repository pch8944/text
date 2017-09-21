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

void centroid();
void update_cv_map(char* str, float value);
void normalize();
void merge_centroid();
string topic_extract(char* line);
void update_mcv_map(string topic, char* str, float value);


struct VectorInfo
{
	std::set<string> child;
	std::map<string, double> vector;
};