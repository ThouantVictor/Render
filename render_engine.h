#ifndef __RENDER_ENGINE_H__
#define __RENDER_ENGINE_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct attributs attributs;
typedef struct tag tag;
typedef struct l_tag l_tag;
typedef struct node node;
typedef struct l_node l_node;
typedef struct way way;
typedef struct l_way l_way;
typedef struct bound bound;
typedef struct member member;
typedef struct l_member l_member;
typedef struct relation relation;
typedef struct l_relation l_relation;
typedef struct point point;

struct attributs {
  int type_attr;
  long id;
  double lat;
  double longi;
  char* usr;
  int uid;
  int vis;
  int vers; 
};

struct tag {
  char* k;
  char* v;
};

struct l_tag {
  tag* cur;
  l_tag* next;
};

struct node {
  attributs* attrs;
  l_tag* tags;
  point* p;
};

struct l_node {
  node* cur;
  l_node* next;
};
  
struct way {
  int type;
  attributs* attrs;
  int area;
  l_node* lnode;
  l_tag* ltag;
};

struct l_way {
  way* cur;
  l_way* next;
};

struct bound {
  double minlat;
  double minlong;
  double maxlat;
  double maxlong;
  double diflat;
  double diflon;
  double ratiolat;
  double ratiolon;
  int width;
  int height;
};

struct member {
  int type;
  char* role;
  way* way;
  node* node;
};

struct l_member {
  member* cur;
  l_member* next;
};

struct relation {
  attributs* attr;
  l_member* lmember;
  l_tag* ltag;
};

struct l_relation {
  relation* cur;
  l_relation* next;
};

struct point {
  int x;
  int y;
};

bound* bnd;
l_node* nds;
l_way* ways;
l_relation* rls;

node* initNode(attributs* attrs,l_tag* tags);
tag* initTag(char* k,char* v);
way* initWay(attributs* attr,l_node* nds,l_tag* tags,int area);
attributs* initAttributs(long id,double lat,double longi,char* usr,int iud,int vis,int vers,int type);
bound* initBound(double minlat, double minlon, double maxlat, double maxlon, int width ,int height);
member* initMember(int type, char* role, way* way, node* node);
point* initPoint(double lat,double lon);
l_tag* addTag(l_tag* tags,tag* tag);
l_node* addNode(l_node* nodes,node* node);
l_way* addWay(l_way* ways,way* way);
l_member* addMember(l_member* ms,member* m);
l_relation* addRelation(l_relation* rs,relation* r);
relation* initRelation(attributs* attr,l_member* lmember,l_tag* ltag);
void printPoint(point* p);
void printTag(tag* tag);
void printTags(l_tag* tags);
void printAttrs (attributs* attrs);
void printNode(node* node);
void printNodes(l_node* nodes);
void printWay(way* way);
void printWays(l_way* way);
void printBound(bound* b);
void printMember(member* memb);
void printMembers(l_member* lm);
void printRelation(relation* r);
void printRelations(l_relation* r);
l_tag* initTags2();
l_tag* initTags(tag* tag);
l_node* initNodes2();
l_node* initNodes(node* node);
l_way* initWays(way* way);
l_way* initWays2();
l_member* initMenbers(member* m);
l_member* initMembers2();
l_relation* initRelations(relation* r);
l_relation* initRelations2();

int identifyWay(l_tag* tags);
int identifyTag(tag* t);
int identifyBuilding(char* v);
int identifyWater(char* v);
int identifyNatural(char* v);
int identifyHigh(char* v);

node* searchNode(l_node* nds,long id);
way* searchWay(l_way* ways,long id);

void freeTags(l_tag* tags);
void freeNode(node * n);
void freeNodes(l_node* n);
void freeWays(l_way* ways);
void freeWay(way* way);
void freeRelations(l_relation* rls);
void freeRelation(relation* r);
void freeMembers(l_member* lm);
#endif
