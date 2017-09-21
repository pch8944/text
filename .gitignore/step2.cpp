#include"step2.h"

std::map<string, int> idf;
std::map<string, int> doc;
std::map<string, double> idf_index;

void cal_idf() {
	FILE *fp_r;
	errno_t err;
	char line[10000];
	char* word;
	int process = 1;
	double value;

	char description[16] = "<d:Description>";

	err = fopen_s(&fp_r, "clean_data.xml", "r");
	idf.clear();
	doc.clear();
	idf["!total!"] = 0;

	while (!feof(fp_r)) {
		fgets(line, sizeof(line), fp_r);
		if (strstr(line, description) != NULL) {
			get_text(line);
			remove_ptm(line);
			word = strtok(line, " ");
			while (word != NULL) {
				update_doc_map(word);
				word = strtok(NULL, " ");
			}
			update_idf_map();
			idf["!total!"]++;
		}
		if (process % 1000 == 0)
			printf("line: %d\n", process);
		process++;
	}

	fclose(fp_r);

	ofstream fp_w("idf.dat");
	for (auto it = idf.begin(); it != idf.end(); it++) {
		value = log10((double)idf["!total!"] / (double)it->second);
		fp_w << it->first << " " << value << " ";
	}
	fp_w.close();
	idf.clear();

	printf("idf file complete\n");

	return;
}

void cal_tf() {
	FILE *fp_r;
	errno_t err;
	char line[10000];
	char* word;
	int process = 1;
	double value;

	char description[16] = "<d:Description>";

	err = fopen_s(&fp_r, "clean_data.xml", "r");
	ofstream fp_w("tf_idf.xml");

	call_idf_index();

	while (!feof(fp_r)) {
		fgets(line, sizeof(line), fp_r);
		if (strstr(line, description) != NULL) {
			doc.clear();
			doc["!total!"] = 0;
			get_text(line);
			remove_ptm(line);
			word = strtok(line, " ");
			while (word != NULL) {
				update_doc_map2(word);
				word = strtok(NULL, " ");
			}
			auto it = doc.begin();
			it++;
			for (; it != doc.end(); it++) {
				value = ((double)it->second / (double)doc["!total!"])*idf_index[it->first];
//				cout << it->first << ":" << idf_index[it->first] << endl;
				fp_w << it->first << " " << value << " ";
			}
			fp_w << "\n";
		}
		else {
			fp_w << line ;
		}
		if (process % 1000 == 0)
			printf("line: %d\n", process);
		process++;
	}

	fclose(fp_r);

	fp_w.close();
	idf_index.clear();

	printf("tf-idf file complete\n");

	return;
}

void get_text(char *str) {

	char description[16] = "<d:Description>";
	char description_end[17] = "</d:Description>";

	strcpy(str, strstr(str, description) + 15);
	*strstr(str, description_end) = '\0';

	return;
}

void remove_ptm(char *str) {
	_strlwr(str);
	for (; *str != '\0'; str++) {
		if (*str == ',' || *str == '.' || *str == '\'' || *str == '-' || *str == '*' || *str == '[' || *str == ']' || *str == '(' || *str == ')' || *str == ']' || *str == '!' || *str == '\"' || *str == '\\' || *str == '_' || *str == '`' || *str == '¡°' || *str == '¡±' || *str == '¡®' || *str == '¡¯' || *str == '¡¸' || *str == '¡¹') {
			strcpy(str, str + 1);
			str--;
		}
	}
}

void update_doc_map(char *str) {
	string word = str;
	doc[word] = 1;

	return;
}

void update_idf_map() {
	for (auto it = doc.begin(); it != doc.end(); it++) {
		if (idf[it->first] == 0)
			idf[it->first] = 1;
		else
			idf[it->first]++;
	}

	doc.clear();

	return;
}

void call_idf_index() {
	FILE *fp_r;
	errno_t err;
	char word[100];
	string key;
	float value;

	printf("call idf file...\n");

	idf_index.clear();

	err = fopen_s(&fp_r, "idf.dat", "r");
	while (!feof(fp_r)) {
		fscanf(fp_r, "%s %f ", &word, &value);
		key = word;
		idf_index[key] = value;
	}

	printf("idf index complete!\n");

	return;
}

void update_doc_map2(char *str) {
	string word = str;
	doc["!total!"]++;
	if (doc[str] == 0)
		doc[word] = 1;
	else
		doc[word]++;

	return;
}