#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>
#include <cstring>
#include <ctime>
#include "database.h"

const char *DATABASE_NAME = 	"PCA.db";

const char *SQL_CREATE_USER = 	"CREATE TABLE IF NOT EXISTS USER("
							  	"USERNAME	TEXT		NOT NULL,"
							  	"PASSWORD	CHAR(50)	NOT NULL,"
								"EMAIL		TEXT		NOT NULL,"
								"NICKNAME	TEXT,"
								"COURSES	TEXT);";

const char *SQL_CREATE_COURSE = 	"CREATE TABLE IF NOT EXISTS COURSE("
							   		"COURSENAME		TEXT	NOT NULL,"
							   		"RATING			TEXT"
							   		"DESCRIPTION	TEXT	NOT NULL,"
									"TAGS			TEXT,"
							   		"COMMENT		TEXT,"
									"PRETEST		TEXT);";

const char *SQL_INSERT_USER = 	"INSERT INTO USER (USERNAME, PASSWORD, EMAIL, NICKNAME) "
							  	"VALUES ('%s', '%s', '%s', '%s');";

const char *SQL_CHECK_USER = 	"SELECT USERNAME from USER where USERNAME like '%s';";

const char *SQL_CHECK_PASSWORD = 	"SELECT USERNAME from USER where "
								 	"USERNAME like '%s' and PASSWORD like '%s';";

const char *SQL_UPDATE_PASSWORD = "UPDATE USER SET PASSWORD = '%s' WHERE USERNAME = '%s';";

const char *SQL_UPDATE_EMAIL = "UPDATE USER SET EMAIL = '%s' WHERE USERNAME = '%s';";

const char *SQL_UPDATE_NICKNAME = "UPDATE USER SET NICKNAME = '%s' WHERE USERNAME = '%s';";

const char *SQL_UPDATE_COURSE = "UPDATE USER SET COURSE = '%s' WHERE USERNAME = '%s';";

const char *SQL_UPDATE_RATING = "UPDATE COURSE SET RATING = '%s' WHERE COURSENAME = '%s';";

const char *SQL_UPDATE_TAGS = "UPDATE COURSE SET TAGS = '%s' WHERE COURSENAME = '%s';";

const char *SQL_UPDATE_COMMENT = "UPDATE COURSE SET COMMENT = '%s' WHERE COURSENAME = '%s';";

const char *SQL_GET_USER = "SELECT * FROM USER;";

const char *SQL_GET_COURSE = "SELECT * FROM COURSE;";

sqlite3 *db;
char *zErrMsg = 0;
int rc;
sqlite3_stmt *statement;
const char *pzTest;
int res = 0;
int userCount;//if cbuser is called


int Databases::initDatabases() {
	rc = sqlite3_open(DATABASE_NAME, &db);
	/* Open database */
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return 0;
	}
	else {
      	fprintf(stdout, "Opened database successfully\n");
	}

	rc = sqlite3_exec(db, SQL_CREATE_USER, NULL, 0, &zErrMsg);
	rc += sqlite3_exec(db, SQL_CREATE_COURSE, NULL, 0, &zErrMsg);

	/* Execute SQL statement */
	if (rc != (SQLITE_OK * 3)){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}
	
	return 1;
}

int Databases::addUser(char* userName, char* password, char* email) {
	//if user already exists, return -2
    if (ifUserExist(userName))
		return -2;
	
	char insertBuffer[300];
	sprintf(insertBuffer, SQL_INSERT_USER, userName, password, email, userName);
	rc = sqlite3_exec(db, insertBuffer, NULL, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
   		fprintf(stderr, "SQL error: %s\n", zErrMsg);
      	sqlite3_free(zErrMsg);
      	return -1;
   	}

   	return 0;
}

int cbIfUserExist(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	userCount++;
	for(i = 0; i < argc; i++){
		fprintf(stderr, "%d %s = %s\n",argc, azColName[i], argv[i] ? argv[i] : "NULL");
	}

	return 0;
}

int Databases::ifUserExist(char* userName) {
	char checkBuffer[300];	
	sprintf(checkBuffer, SQL_CHECK_USER, userName);
	userCount = 0;
	rc = sqlite3_exec(db, checkBuffer, cbIfUserExist, 0, &zErrMsg);

	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}
	
	return userCount;
}

int Databases::passwordCheck(char* userName, char* passWord){
	char checkBuffer[300];
	sprintf(checkBuffer, SQL_CHECK_PASSWORD, userName, passWord);
	userCount = 0;
	rc = sqlite3_exec(db, checkBuffer, cbIfUserExist, 0, &zErrMsg);
	
	if(rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}
	
	return userCount;
}
//xuhao
int Databases::changeNickname(char* userName, char* nickname) {
<<<<<<< HEAD
	
=======
	char checkBuffer[300];
	sprintf(checkBufer, SQL_UPDATE_NICKNAME, userName, nickName);
	rc = sqlite3_exec()
>>>>>>> 709b60f4aa64f84dd828442de141afe0d49080d6
	return 0;
}
//xuhao
int Databases::changeEmail(char* userName, char* email) {
	
	return 0;
}
//xu
int Databases::changeCourse(char* userName, char* course) {
	return 0;
}
//wang
int Databases::changePassword(char* userName, char* password) {
	return 0;
}
//liu
char* Databases::getUser(char* userName) {
	return NULL;
}
//liu
char* Databases::getCourselist(char* tags) {
	return NULL;
}
//liu
char* Databases::getCourse(char* course) {
	return NULL;
}
//xu
int Databases::updateRating(char* course, char* rating) {
	return 0;
}
//qi
int Databases::updateTags(char* course, char* tags) {
	return 0;
}
//niu
int Databases::updateComment(char* course, char* comment) {
	return 0;
}







