#include "file.h"


void readclient() {

	char buf[1024];
	char id[20] = "", pw[15] = "", name[10] = "";
	char idCheck[10]="", reserve[10]="";
	int buflen;
	int clientNum = 1, cnt = 0; //회원 수(할당 시 쓰임)
	FILE *fp;

	fopen_s(&fp, "client.txt", "r+");


	member = (MEMBER**)calloc(clientNum, sizeof(MEMBER*));
	member[0] = (MEMBER*)calloc(1, sizeof(MEMBER)); //무조건 회원변수에 값 할당

	while (1) {



		if (fgets(buf, sizeof(buf), fp) == NULL) break;  //파일의 내용을 한줄 씩 읽어온다

		//printf("%s", buf);

		char *context = NULL;
		char *ptr = strtok_s(buf, " ", &context);

		strcpy_s(id, 20, ptr);
		printf("%s\n", id);
		//id[strlen(id) + 1] = '\0';
		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(pw, 15, ptr);

		printf("%s\n", pw);
		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(name, 10, ptr);

		//printf("%s\n",name);
		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(idCheck, 10, ptr);
		//printf("%c\n", b);
		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(reserve,10, ptr);
		//printf("%c\n", b);    //한줄씩 파일에서 가져와 buf에 저장하고 " "를 기준으로 단어별로 자른다.


		if (cnt>0) {  //처음을 제외하고 파일을 한줄씩 읽을때마다 추가로 멤버변수를 할당해준다.
			member = (MEMBER**)realloc(member, (clientNum+1) * sizeof(MEMBER*));
			member[clientNum] = (MEMBER*)calloc(1, sizeof(MEMBER));
			clientNum++;
		}



		wsprintf(member[cnt]->id,id);
		wsprintf(member[cnt]->pw, pw);
		wsprintf(member[cnt]->name, name);

		if (strcmp(idCheck, "true") == 0) {
			lstrcpy(member[cnt]->clientCheck , "true");}
		else {
			lstrcpy(member[cnt]->clientCheck , "false");
		}
		
		if (strcmp(reserve, "true") == 0) {
			lstrcpy(member[cnt]->reservaiton,"true");
		}
		else {
			lstrcpy(member[cnt]->reservaiton , "false");
		}

		cnt++;
	}

	memberNum = cnt; //회원 수 카운트
	
	//printf("사람수 %d", memberNum);
	fclose(fp);
}

void readawait() {

	char buf[1024];
	char id[20] = "", pw[15] = "", name[10] = "";
	int buflen;
	int num=1,cnt = 0; //회원 수(할당 시 쓰임)
	int i;
	bool check=false;
	FILE *fp;

	fopen_s(&fp, "signup.txt", "r+");


	awaiter = (MEMBER**)calloc(1, sizeof(MEMBER*));
	awaiter[0] = (MEMBER*)calloc(1, sizeof(MEMBER)); //무조건 회원변수에 값 할당

	while (1) {



		if (fgets(buf, sizeof(buf), fp) == NULL) break;  //파일의 내용을 한줄 씩 읽어온다

														// printf("%s\n", buf);
		char *context = NULL;
		char *ptr = strtok_s(buf, " ", &context);

		strcpy_s(id, 20, ptr);
		//printf("%s\n", id);
		//id[strlen(id) + 1] = '\0';
		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(pw, 15, ptr);

		//printf("%s\n", pw);
		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(name, 10, ptr);


		if (cnt>0) {  //처음을 제외하고 파일을 한줄씩 읽을때마다 추가로 멤버변수를 할당해준다.
			awaiter = (MEMBER**)realloc(awaiter, (num + 1) * sizeof(MEMBER*));
			awaiter[num] = (MEMBER*)calloc(1, sizeof(MEMBER));
			num++;
		}

		printf("성공 \n");
		wsprintf(awaiter[cnt]->id, id);
		wsprintf(awaiter[cnt]->pw, pw);
		wsprintf(awaiter[cnt]->name, name);
	    	
		cnt++;
		printf("%s %s %s %s %s\n", awaiter[cnt-1]->id, awaiter[cnt - 1]->pw, awaiter[cnt - 1]->name, awaiter[cnt - 1]->clientCheck, awaiter[cnt - 1]->reservaiton);
		
	}
	
	awaitNum = cnt;				 //printf("사람수 %d", memberNum);
	fclose(fp);
}


void writeWait(TCHAR *id, TCHAR *pw, TCHAR*name) {

	FILE *fp,*frp;
	char ch;
	fopen_s(&frp, "signup.txt", "r");
	ch = fgetc(frp);
	fclose(frp);

	fopen_s(&fp, "signup.txt", "a+");

	if (ch != EOF) {
		fprintf(fp,"\n");
		fprintf(fp, "%s %s %s %s", id, pw, name,"exit");
		printf("aaa");
	}

	else
	fprintf(fp, "%s %s %s %s", id, pw, name,"exit");

	fclose(fp);

}

void writeRequestDelete() {

	FILE *fp;
	int i;

	fopen_s(&fp, "signup.txt", "w+");
	

	for (i = 1; i < awaitNum-1; i++) {
	
		fprintf(fp, "%s %s %s %s\n", awaiter[i]->id, awaiter[i]->pw, awaiter[i]->name,"exit");
   
	}


	fprintf(fp, "%s %s %s %s", awaiter[i]->id, awaiter[i]->pw, awaiter[i]->name, "exit");

	fclose(fp);
}

void writeMember() {

	FILE *fp, *frp;
	char ch;
	int i;

	fopen_s(&fp, "client.txt", "w");

	
	for (i = 0; i < memberNum-1; i++) {
	

		fprintf(fp, "%s %s %s %s %s\n", member[i]->id, member[i]->pw, member[i]->name,member[i]->clientCheck,member[i]->reservaiton);
	}

	fprintf(fp, "%s %s %s %s %s", member[i]->id, member[i]->pw, member[i]->name, member[i]->clientCheck, member[i]->reservaiton);

	fclose(fp);

}


void readBook() {

	char buf[1024];
	char name[50] , author[50] , publisher[50] ,publishDay[15],reserveId[20],rent[10],ISBN[9],version[2];
	int buflen;
	int bookNum = 1, cnt = 0; //도서 수(할당 시 쓰임)
	FILE *fp;

	fopen_s(&fp, "book.txt", "r+");


	book = (BOOK**)calloc(bookNum, sizeof(BOOK*));
	book[0] = (BOOK*)calloc(1, sizeof(BOOK)); //무조건 회원변수에 값 할당

	while (1) {

		if (fgets(buf, sizeof(buf), fp) == NULL) break;  //파일의 내용을 한줄 씩 읽어온다

														 //printf("%s", buf);
		char *context = NULL;
		char *ptr = strtok_s(buf, " ", &context);

		strcpy_s(name, 50, ptr);
		printf("%s ", name);  //도서명
	
		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(author, 50, ptr);
		printf("%s ", author); //저자

		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(publisher, 50, ptr);
        printf("%s ",publisher); //출판사
		
		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(publishDay, 15, ptr);
		printf("%s",publishDay); //출판일
		
		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(reserveId, 20, ptr);
		printf("%s ", reserveId); //예약자 아이디
		
		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(rent, 10, ptr);
		printf("%s ", rent);  //대여가능 여부

		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(ISBN, 9, ptr); 
		printf("%s ", ISBN);  //ISBN코드

		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(version, 2, ptr);
		printf("%s\n", version);  //버젼

		//한줄씩 파일에서 가져와 buf에 저장하고 " "를 기준으로 단어별로 자른다.


		if (cnt>0) {  //처음을 제외하고 파일을 한줄씩 읽을때마다 추가로 멤버변수를 할당해준다.
			book = (BOOK**)realloc(book, (bookNum + 1) * sizeof(BOOK*));
			book[bookNum] = (BOOK*)calloc(1, sizeof(BOOK));
			bookNum++;
		}

		
		wsprintf(book[cnt]->bookName, name);
		wsprintf(book[cnt]->Author, author);
		wsprintf(book[cnt]->publisher, publisher);
		wsprintf(book[cnt]->publishDay, publishDay);
        
		if (strcmp(reserveId, "null") == 0) {
			wsprintf(book[cnt]->reserveId, "없음");
		}else {
			wsprintf(book[cnt]->reserveId, reserveId);
		}

		if (strcmp(rent, "true") == 0) {
			book[cnt]->rent = true;
		}else
			book[cnt]->rent = false;
		
		wsprintf(book[cnt]->ISBN, ISBN);
		
		book[cnt]->version=atoi(version);

		
		cnt++;
	}


	bookNumber = cnt; //회원 수 카운트
	fclose(fp);

}