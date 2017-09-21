#include"step4.h"

std::map<string, double> target;
std::map<string, Vector> tvector;
std::map<string, double> idf_index2;

void classifier() {
	FILE *fp_r;
	errno_t err;
	char line[1000000];
	string c_topic;
	char* word;
	char* value_string;
	float value;

	tvector.clear();
	char topic[12] = "<Topic r:id";

	err = fopen_s(&fp_r, "merge_centroid_ghn.xml", "r");

	while (!feof(fp_r)) {
		fgets(line, sizeof(line), fp_r);
		if (strstr(line, topic) != NULL) {
			c_topic = topic_extract2(line);
		}
		else {
			word = strtok(line, " ");
			while (word != NULL && strcmp(word, "\n") != 0) {
				value_string = strtok(NULL, " ");
				value = atof(value_string);
				update_t_map(c_topic, word, value);
				word = strtok(NULL, " ");
			}
		}
	}

	fclose(fp_r);
	// end of read file part
	printf("complete: read file\n");

	char description[16] = "<d:Description>";

	err = fopen_s(&fp_r, "target.txt", "r");

	call_idf_index2();

	fgets(line, sizeof(line), fp_r);
	target.clear();
	target["!total!"] = 0;
	remove_ptm2(line);
	word = strtok(line, " ");
	while (word != NULL) {
		update_doc_map3(word);
		word = strtok(NULL, " ");
	}
	auto it = target.begin();
	it++;
	for (; it != target.end(); it++) {
		target[it->first] = ((double)it->second / (double)target["!total!"])*idf_index2[it->first];
	}

	fclose(fp_r);

	idf_index2.clear();

	printf("target file read complete\n");
	target.erase("!total!");

	// target normalize

	double no = 0;

	for (auto it = target.begin(); it != target.end(); it++) {
		no += pow(it->second, 2.0);
	}
	no = sqrt(no);
	for (auto it = target.begin(); it != target.end(); it++) {
		target[it->first] = it->second / no;
	}

	// cosine similarity
	string result;
	float max_sim = 0;

	float sim;

	for (auto it = tvector.begin(); it != tvector.end(); it++) {
		sim = 0;
		for (auto it2 = target.begin(); it2 != target.end(); it2++) {
			sim += it2->second * it->second.vector[it2->first];
		}
		if (sim >= max_sim) {
			max_sim = sim;
			result = it->first;
		}
	}

	cout << "result: " << result << " = " << max_sim << endl;

	return;
}

string topic_extract2(char* line) {
	string topic;
	char topic_begin[14] = "<Topic r:id=\"";
	char topic_end[3] = "\">";

	strcpy(line, strstr(line, topic_begin) + 13);
	*strstr(line, topic_end) = '\0';
	topic = line;

	return topic;
}

void update_t_map(string topic, char* str, float value) {
	string word = str;
	if (tvector[topic].vector[word] == 0)
		tvector[topic].vector[word] = value;
	else
		tvector[topic].vector[word] = tvector[topic].vector[word] + value;

	return;
}

void cal_tf2() {
	FILE *fp_r;
	errno_t err;
	char line2[100000];
	char* word;
	double value;

	char description[16] = "<d:Description>";

	err = fopen_s(&fp_r, "target.txt", "r");

	call_idf_index2();

	fgets(line2, sizeof(line2), fp_r);
	target.clear();
	target["!total!"] = 0;
	remove_ptm2(line2);
	word = strtok(line2, " ");
	while (word != NULL) {
		update_doc_map3(word);
		word = strtok(NULL, " ");
	}
	auto it = target.begin();
	it++;
	for (; it != target.end(); it++) {
		target[it->first] = ((double)it->second / (double)target["!total!"])*idf_index2[it->first];
	}

	fclose(fp_r);

	idf_index2.clear();

	printf("target file read complete\n");

	return;
}

void call_idf_index2() {
	FILE *fp_r;
	errno_t err;
	char word[100];
	string key;
	float value;

	printf("call idf file...\n");

	idf_index2.clear();

	err = fopen_s(&fp_r, "idf.dat", "r");
	while (!feof(fp_r)) {
		fscanf(fp_r, "%s %f ", &word, &value);
		key = word;
		idf_index2[key] = value;
	}

	printf("idf index complete!\n");

	return;
}

void remove_ptm2(char *str) {
	_strlwr(str);
	for (; *str != '\0'; str++) {
		if (*str == ',' || *str == '.' || *str == '\'' || *str == '-' || *str == '*' || *str == '[' || *str == ']' || *str == '(' || *str == ')' || *str == ']' || *str == '!' || *str == '\"' || *str == '\\' || *str == '_' || *str == '`' || *str == '¡°' || *str == '¡±' || *str == '¡®' || *str == '¡¯' || *str == '¡¸' || *str == '¡¹') {
			strcpy(str, str + 1);
			str--;
		}
	}
}

void update_doc_map3(char *str) {
	string word = str;
	target["!total!"]++;
	if (target[str] == 0)
		target[word] = 1;
	else
		target[word]++;

	return;
}