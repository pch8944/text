#include"step3.h"

std::map<string, double> cv;
std::map<string, VectorInfo> mcvector;

std::map<string, double> mcalgorithm(string root);

void centroid() {
	FILE *fp_r;
	errno_t err;
	char line[1000000];
	char* word;
	char* value_string;
	int process = 1;
	float value;
	int no = 0;

	char topic[12] = "<Topic r:id";

	err = fopen_s(&fp_r, "tf_idf.xml", "r");
	ofstream fp_w("centorid_tf_idf.xml");


	while (!feof(fp_r)) {
		fgets(line, sizeof(line), fp_r);
		if (strstr(line, topic) != NULL) {
			if (cv.empty() == false) {
				for (auto it = cv.begin(); it != cv.end(); it++) {
					fp_w << it->first << " " << (it->second / no) << " ";
				}
				fp_w << "\n";
			}

			cv.clear();
			no = 0;
			fp_w << line;

		}
		else {
			word = strtok(line, " ");
			while (word != NULL && strcmp(word, "\n") != 0) {
				value_string = strtok(NULL, " ");
				value = atof(value_string);
				update_cv_map(word, value);
				word = strtok(NULL, " ");
			}
			no++;
		}

		if (process % 1000 == 0)
			printf("line: %d\n", process);
		process++;
	}

	if (cv.empty() == false) {
		for (auto it = cv.begin(); it != cv.end(); it++) {
			fp_w << it->first << " " << (it->second / (no - 1)) << " ";
		}
		fp_w << "\n";
	}
	cv.clear();
	no = 0;

	fclose(fp_r);

	fp_w.close();

	printf("centroid tf-idf file complete\n");

	return;
}

void update_cv_map(char* str, float value) {
	string word = str;
	if (cv[word] == 0)
		cv[word] = value;
	else
		cv[word] = cv[word] + value;


	return;
}

void normalize() {
	FILE *fp_r;
	errno_t err;
	char line[1000000];
	char* word;
	char* value_string;
	int process = 1;
	float value;
	double no = 0;

	char topic[12] = "<Topic r:id";

	err = fopen_s(&fp_r, "centorid_tf_idf.xml", "r");
	ofstream fp_w("normalized_centroid.xml");


	while (!feof(fp_r)) {
		fgets(line, sizeof(line), fp_r);
		if (strstr(line, topic) != NULL) {
			if (cv.empty() == false) {
				for (auto it = cv.begin(); it != cv.end(); it++) {
					no += pow(it->second, 2.0);
				}
				no = sqrt(no);
				for (auto it = cv.begin(); it != cv.end(); it++) {
					fp_w << it->first << " " << (it->second / no) << " ";
				}
				fp_w << "\n";
			}

			cv.clear();
			no = 0;
			fp_w << line;

		}
		else {
			word = strtok(line, " ");
			while (word != NULL && strcmp(word, "\n") != 0) {
				value_string = strtok(NULL, " ");
				value = atof(value_string);
				update_cv_map(word, value);
				word = strtok(NULL, " ");
			}
		}

		if (process % 1000 == 0)
			printf("line: %d\n", process);
		process++;
	}

	if (cv.empty() == false) {
		for (auto it = cv.begin(); it != cv.end(); it++) {
			no += pow(it->second, 2.0);
		}
		no = sqrt(no);
		for (auto it = cv.begin(); it != cv.end(); it++) {
			fp_w << it->first << " " << (it->second / (no)) << " ";
		}
		fp_w << "\n";
	}
	cv.clear();
	no = 0;

	fclose(fp_r);

	fp_w.close();

	printf("centroid tf-idf file complete\n");

	return;
}

void merge_centroid() {
	FILE *fp_r;
	errno_t err;
	char line[1000000];
	string c_topic;
	char* word;
	char* value_string;
	float value;

	mcvector.clear();
	char topic[12] = "<Topic r:id";

	err = fopen_s(&fp_r, "normalized_centroid.xml", "r");

	while (!feof(fp_r)) {
		fgets(line, sizeof(line), fp_r);
		if (strstr(line, topic) != NULL) {
			c_topic = topic_extract(line);
		}
		else {
			word = strtok(line, " ");
			while (word != NULL && strcmp(word, "\n") != 0) {
				value_string = strtok(NULL, " ");
				value = atof(value_string);
				update_mcv_map(c_topic, word, value);
				word = strtok(NULL, " ");
			}
		}
	}

	fclose(fp_r);
	// end of read file part
	printf("complete: read file\n");
	for (auto it = mcvector["Top"].child.begin(); it != mcvector["Top"].child.end(); it++) {
			cout << "\n" << *it << endl;
	}

//	mcalgorithm("Adult");
	mcalgorithm("Top/Shopping");
	mcalgorithm("Top/Society");
	mcalgorithm("Top/Sports");
	//	mcalgorithm("Kids_and_Teens");
//	mcalgorithm("Top/Health/Conditions_and_Diseases");

/*
	for (auto it = mcvector.begin(); it != mcvector.end(); it++) {
		cout << "topic: " << it->first << endl;
		for (auto at = it->second.vector.begin(); at != it->second.vector.end(); at++) {
			cout << at->first << " " << at->second << " ";
		}
		cout << " " << endl;
	}
	*/
	// calculate using dfs -> write file via orginal file's sequence
	
	err = fopen_s(&fp_r, "normalized_centroid.xml", "r");
	ofstream fp_w("merge_centroid.xml");
	string print_line;

	while (!feof(fp_r)) {
		fgets(line, sizeof(line), fp_r);
		if (strstr(line, topic) != NULL) {
			print_line = line;
			c_topic = topic_extract(line);
			if (mcvector[c_topic].child.size() != 0 && mcvector[c_topic].vector.size() != 0) {
//				fp_w << mcvector[c_topic].vector.size() << "\n";
				fp_w << print_line;
				for (auto it = mcvector[c_topic].vector.begin(); it != mcvector[c_topic].vector.end(); it++) {
					fp_w << it->first << " " << it->second << " ";
				}
				fp_w << "\n";
			}
		}
	}

	fclose(fp_r);
	fp_w.close();

	return;
}

string topic_extract(char* line) {
	string topic;
	string parents;
	char topic_begin[14] = "<Topic r:id=\"";
	char topic_end[3] = "\">";
	char *pch;

	strcpy(line, strstr(line, topic_begin) + 13);
	*strstr(line, topic_end) = '\0';
	topic = line;
	if ((pch = strrchr(line, '/')) != NULL) {
		*pch = '\0';
		parents = line;
		mcvector[parents].child.insert(topic);
	}

	return topic;
}

void update_mcv_map(string topic, char* str, float value) {
	string word = str;
	if (mcvector[topic].vector[word] == 0)
		mcvector[topic].vector[word] = value;
	else
		mcvector[topic].vector[word] = mcvector[topic].vector[word] + value;

	return;
}

std::map<string, double> mcalgorithm(string root) {
	std::map<string, double> vector;
	int child_num;

	cout << root << endl;
	for (auto it = mcvector[root].vector.begin(); it != mcvector[root].vector.end(); it++) {
		vector[it->first] = it->second;
	}

	if (mcvector[root].child.empty()) {
		return vector;
	}
	else {

		for (auto it = mcvector[root].child.begin(); it != mcvector[root].child.end(); it++) {
			std::map<string, double> cvector = mcalgorithm(*it);
//			cout << "\n" << *it << endl;
			for (auto it2 = cvector.begin(); it2 != cvector.end(); it2++) {
//				cout << it2->first << " " << it2->second << " ";
				if (vector[it2->first] == 0) {
					vector[it2->first] = it2->second;
				}
				else {
					vector[it2->first] = vector[it2->first] + it2->second;
				}
			}
		}
		child_num = mcvector[root].child.size();
		for (auto it = vector.begin(); it != vector.end(); it++) {
			mcvector[root].vector[it->first] = it->second / child_num;
		}

		return mcvector[root].vector;
	}


}