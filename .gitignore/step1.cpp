#include"step1.h"

void delete_cat() {
	FILE *fp_r, *fp_w;
	errno_t err;
	char line[10000];

	char skip_topic1[26] = "<Topic r:id=\"Top/Regional";
	char skip_topic2[26] = "<Topic r:id=\"Top/World";
	char topic[12] = "<Topic r:id";
	char description[16] = "<d:Description>";

	err = fopen_s(&fp_r, "content.rdf.u8", "r");
	err = fopen_s(&fp_w, "content-rw.rdf.u8", "w");

	int skip = 0;

	while (!feof(fp_r)) {
		fgets(line, sizeof(line), fp_r);
		if (strstr(line, skip_topic1) != NULL) {
			printf("skip topic: %s", line);
			skip = 1;
		}
		else if (strstr(line, skip_topic2) != NULL) {
			printf("skip topic: %s", line);
			skip = 1;
		}
		else if (strstr(line, topic) != NULL) {
			skip = 0;
			printf("topic: %s", line);
			fprintf(fp_w, "%s", line);
		}
		else if ((strstr(line, description) != NULL) && (skip != 1))
			fprintf(fp_w, "%s", line);
	}

	fclose(fp_r);
	fclose(fp_w);

	delete_cat3();

	return;
}

void delete_cat3() {
	FILE *fp_r, *fp_w;
	errno_t err;
	char line[10000];

	char skip_topic1[28] = "<Topic r:id=\"Adult/Regional";
	char skip_topic2[26] = "<Topic r:id=\"Adult/World";
	char topic[12] = "<Topic r:id";
	char description[16] = "<d:Description>";

	err = fopen_s(&fp_r, "ad-content.rdf.u8", "r");
	err = fopen_s(&fp_w, "ad-content-rw.rdf.u8", "w");

	int skip = 0;

	while (!feof(fp_r)) {
		fgets(line, sizeof(line), fp_r);
		if (strstr(line, skip_topic1) != NULL) {
			printf("skip topic: %s", line);
			skip = 1;
		}
		else if (strstr(line, skip_topic2) != NULL) {
			printf("skip topic: %s", line);
			skip = 1;
		}
		else if (strstr(line, topic) != NULL) {
			skip = 0;
			printf("topic: %s", line);
			fprintf(fp_w, "%s", line);
		}
		else if ((strstr(line, description) != NULL) && (skip != 1))
			fprintf(fp_w, "%s", line);
	}

	fclose(fp_r);
	fclose(fp_w);

	return;
}

void delete_cat2() {
	FILE *fp_r, *fp_w;
	errno_t err;
	char line[10000];

	char skip_topic[42] = "<Topic r:id=\"Kids_and_Teens/International";
	char topic[12] = "<Topic r:id";
	char description[16] = "<d:Description>";

	err = fopen_s(&fp_r, "kt-content.rdf.u8", "r");
	err = fopen_s(&fp_w, "kt-content-i.rdf.u8", "w");

	int skip = 0;

	while (!feof(fp_r)) {
		fgets(line, sizeof(line), fp_r);
		if (strstr(line, skip_topic) != NULL) {
			printf("skip topic: %s", line);
			skip = 1;
		}
		else if (strstr(line, topic) != NULL) {
			skip = 0;
			printf("topic: %s", line);
			fprintf(fp_w, "%s", line);
		}
		else if ((strstr(line, description) != NULL) && (skip != 1))
			fprintf(fp_w, "%s", line);
	}

	fclose(fp_r);
	fclose(fp_w);

	return;
}

void extract_data() {
	clean_write("ad-content-rw.rdf.u8");
	clean_write("content-rw.rdf.u8");
	clean_write("kt-content-i.rdf.u8");

	return;
}

void clean_write(char* dir) {
	FILE *fp_r, *fp_w;
	errno_t err;
	char line[10000];

	char topic[12] = "<Topic r:id";
	char description[16] = "<d:Description>";

	err = fopen_s(&fp_r, dir, "r");
	err = fopen_s(&fp_w, "clean_data.xml", "a");

	while (!feof(fp_r)) {
		fgets(line, sizeof(line), fp_r);
		if (strstr(line, topic) != NULL) {
			printf("topic: %s", line);
			fprintf(fp_w, "%s", line);
		}
		else if (strstr(line, description) != NULL)
			fprintf(fp_w, "%s", line);
	}

	fclose(fp_r);
	fclose(fp_w);

	printf("%s complete\n", dir);

	return;
}