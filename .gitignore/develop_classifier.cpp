#include"step1.h"
#include"step2.h"
#include"step3.h"
#include"step4.h"

void run();
void display();

void main()
{
	run();
	return;
}

void run() {
	int key = 0;

	do {
		display();
		scanf_s("%d", &key, sizeof(key));

		switch (key)
		{
		case 1: delete_cat(); break;
		case 2: delete_cat2(); break;
		case 3: extract_data(); break;
		case 4: cal_idf(); break;
		case 5: cal_tf(); break;
		case 6: centroid(); break;
		case 7: normalize(); break;
		case 8: merge_centroid(); break;
		case 9: classifier(); break;
		case 10: break;
		default: printf("Wrong number!\n"); break;
		}
		printf("\n");
	} while (key != 10);

	return;
}

void display() {

	printf("===========develop classifier===========\n");
	printf("1. Exclude Regional and World Category\n");
	printf("2. Exclude International Category\n");
	printf("3. Extract Clean Data from ODP\n");
	printf("4. Calculate idf\n");
	printf("5. Calculate tf\n");
	printf("6. Compute Centroid Vector\n");
	printf("7. Normalize Centroid Vector\n");
	printf("8. Compute Merge Centroid Vector\n");
	printf("9. Target File Analyse\n");
	printf("10. EXIT\n");
	printf("========================================\n");
	printf("select number: ");

	return;
}