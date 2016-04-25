#include "render_engine.h"


/******************************************
render_engine.c
Fichier de gestion des structures de données générée lors du parsing.
C'est le coeur du programme.
Il manage les listes de noeuds,de chemins,de relations et également l'initialisation
et les comparaisons de leur attributs.

 ****************************************/

node*
initNode(attributs* attrs, l_tag* tags){
  node* n=malloc (sizeof(node)+sizeof(*tags));
  n->tags=tags;
  n->attrs=attrs;
  n->p=initPoint(attrs->lat,attrs->longi);
  return n;
}

void
printNode(node* node){
  printf("                   **********NODE***********\n");
  if(node !=NULL)
    printAttrs(node->attrs);
  if(node->tags != NULL){
    printTags(node->tags);
  }
  printf("                   *********************\n");
  
}

l_node*
initNodes2(){
  l_node* nodes=malloc(sizeof(l_node));
  if(nodes){
    nodes->cur=NULL;
    nodes->next=NULL;
  }
  return nodes;
}

l_node*
initNodes(node* node){
  l_node* nds=malloc (sizeof(l_node));
  if(nds){
    nds->cur=node;
    nds->next=NULL;
  }
  return nds;
}

way*
initWay(attributs* attr,l_node* nds,l_tag* tags,int area){
  way* way=malloc(sizeof(way)+sizeof(*nds)+sizeof(*tags));
  way->type=identifyWay(tags);
  way->area=area;
  way->attrs=attr;
  way->lnode=nds;
  way->ltag=tags;
  return way;
}

l_way*
initWays2(){
  l_way* ways=malloc(sizeof(l_way));
  if(ways){
    ways->cur=NULL;
    ways->next=NULL;
  }
  return ways;
}

l_way*
initWays(way* way){
  l_way* ways=malloc(sizeof(l_way));
  if(ways){
    ways->cur=way;
    ways->next=NULL;
  }
  return ways;
}

l_relation*
initRelations2(){
  l_relation* res=malloc( sizeof(l_relation) );
  if(res){
    res->cur=NULL;
    res->next=NULL;
  }
  return res;
}

l_relation*
initRelations(relation* r){
  l_relation* res=malloc( sizeof(l_relation) );
  if(res){
    res->cur=r;
    res->next=NULL;
  }
  return res;
}

relation*
initRelation(attributs* attr,l_member* lmember,l_tag* ltag){
  relation* r=malloc( sizeof(relation)+sizeof(*lmember)+sizeof(*ltag) );
  if(r){
    r->attr=attr;
    r->lmember=lmember;
    r->ltag=ltag;    
  }
  return r;
}

l_tag*
initTags(tag* tag){
  l_tag* tags=malloc(sizeof(l_tag));
  if(tags){
    tags->cur=tag;
    tags->next=NULL;
  }
  return tags;
}

l_tag*
initTags2(){
  l_tag* tags=malloc (sizeof(l_tag));
  if(tags){
    tags->cur=NULL;
    tags->next=NULL;
  }
  return tags;
}

l_member*
initMembers2(){
  l_member* ms=malloc( sizeof(l_member) );
  if(ms){
    ms->cur=NULL;
    ms->next=NULL;
  }
  return ms;
}

l_member*
initMembers(member* m){
  l_member* ms=malloc( sizeof(*m) );
  if(ms){
    ms->cur=m;
    ms->next=NULL;
  }
  return ms;
}

l_relation*
addRelation(l_relation* rs,relation* r){
  l_relation* res=initRelations(r);
  res->next=rs;
  return res;
}

l_member*
addMember(l_member* ms,member* m){
  l_member* res=initMembers(m);
  res->next=ms;
  return res;
}

l_tag*
addTag(l_tag* tags,tag* tag){
  l_tag* res=initTags(tag);
  res->next=tags;
  return res;
}

l_node*
addNode(l_node* nodes,node* node){
  l_node* res=initNodes(node);
  res->next=nodes;
  return res;
}

l_way*
addWay(l_way* ways,way* way){
  l_way* res=initWays(way);
  res->next=ways;
  return res;
}

tag*
initTag(char* k,char* v){
  tag* cur=malloc( sizeof(tag) );
  cur->v=v;
  cur->k=k;
  return cur;
}

bound*
initBound(double minlat, double minlon, double maxlat, double maxlon , int width, int height){
  bound* b=malloc( sizeof(bound) );
  b->minlat=minlat;
  b->minlong=minlon;
  b->maxlat=maxlat;
  b->maxlong=maxlon;
  b->width=width;
  b->height=height;
  double tmplon=(double)height;
  double tmplat=(double)width;
  double tmp=(maxlon-minlon);
  double tmp2=(maxlat-minlat);
  b->diflat=tmp2;
  b->diflon=tmp;
  b->ratiolon=tmplon/tmp;
  b->ratiolat=tmplat/tmp2;
  return b;
}

attributs*
initAttributs(long id,double lat,double longi,char* usr,int uid,int vis,int vers,int type){
  attributs* attrs=malloc(sizeof(attributs) );
  attrs->type_attr=type;
  attrs->id=id;
  attrs->lat=lat;
  attrs->longi=longi;
  attrs->usr=usr;
  attrs->uid=uid;
  attrs->vis=vis;
  attrs->vers=vers;
  
  return attrs;
}

member*
initMember(int type, char* role,way* way,node* node ){
  member* memb;
  if(type==0){
    memb=malloc(sizeof(member)+sizeof(*node));
    memb->way=NULL;
    memb->node=node;
    memb->type=type;
    memb->role=role;
  }else{
    if(type==1){
      memb=malloc(sizeof(member)+sizeof(*way) );
      memb->way=way;
      memb->node=malloc(sizeof(node));
      memb->type=type;
      memb->role=role;
    }
  }
  return memb;
}

point*
initPoint(double lat, double lon){
  point* p=malloc( sizeof(point) );
  p->y=(((bnd->maxlat)-lat)/(bnd->diflat))*(bnd->width);
  p->x=(((bnd->maxlong)-lon)/(bnd->diflon))*(bnd->height);
  return p;
}

void
printAttrs (attributs* attrs){
  if(attrs->type_attr==0)
    printf("       Node: %i %ld %.15f %.15f %s %i %i %i\n",attrs->type_attr,attrs->id,attrs->lat,attrs->longi,attrs->usr,attrs->uid,attrs->vis,attrs->vers);
  else
    printf("      Way: %i %ld %s %i %i %i\n",attrs->type_attr,attrs->id,attrs->usr,attrs->uid,attrs->vis,attrs->vers);
}

void
printTag(tag* tag){
  printf(" -k:%s et v:%s \n",tag->k,tag->v);
}

void
printTags(l_tag* tags){
  while(tags->next != NULL){
    printTag(tags->cur);
    tags=tags->next;    
  }
}

void
printWay(way* way){
  printf("                   ****************WAY*****************\n");
  printAttrs(way->attrs);
  if(way->ltag != NULL){
    printTags(way->ltag);
  }
  if(way->lnode !=NULL)
    printNodes(way->lnode);
  printf("            *************************************\n");  
}

void
printNodes(l_node* nodes){
  while(nodes->next != NULL){
    printNode(nodes->cur);
    nodes=nodes->next;    
  }
}

void
printWays(l_way* ways){
  while(ways->next != NULL){
    printWay(ways->cur);
    ways=ways->next;    
  }
}

void
printBound(bound* b){
  printf(" Bound:= minlat=%f minlon=%f maxlat=%f maxlon=%f rlat=%.15f rlon=%.15f \n",b->minlat, b->minlong, b->maxlat ,b->maxlong, b->ratiolat ,b->ratiolon);
}

void
printMembers(l_member* lm){
  while(lm->next !=NULL){
    printMember(lm->cur);
    lm=lm->next;
  }
}

void
printRelations(l_relation* r){
  while(r->next !=NULL){
    printRelation(r->cur);
    r=r->next;
  }
}

void
printRelation(relation* r){
   printf("    [[[[[[[[[[[[[[[[[[[[[[[[[RELATION]]]]]]]]]]]]]]]]]]]\n");
   printAttrs(r->attr);
  if(r->ltag != NULL){
    printTags(r->ltag);
  }
  if(r->lmember !=NULL)
    printMembers(r->lmember);
  printf("    [[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]\n");

}

void
printMember(member * memb){
  if(memb->type==0){
    if(memb->node != NULL)
      printNode(memb->node);
  }else{
    if(memb->type==1){
      if(memb->way != NULL)
	printWay(memb->way);
    }
  }
}

int
identifyWay(l_tag* tags){
  while(tags->next!=NULL){
    return identifyTag(tags->cur);
      tags=tags->next;
  }
  return -1;
}

int
identifyTag(tag* t){
  if(!strcmp(t->k, "building")){
    return identifyBuilding(t->v);
  }
  else if(!strcmp(t->k, "highway")){
    return identifyHigh(t->v);
  }
  else if(!strcmp(t->k, "waterway")){
    return identifyWater(t->v);
  }
  else if(!strcmp(t->k, "natural")){
    return identifyNatural(t->v);
  }
  else if(!strcmp(t->k, "landuse=grass")){
    return 11;
  }
  else if(!strcmp(t->k, "landuse=forest")){
    return 12;
  }
  else if(!strcmp(t->k, "leisure=park")){
    return 13;
  } 
  else{
    return -1;
  }
}

int
identifyBuilding(char* v){
  if(!strcmp(v, "church")){
    return 1;
  }else if(!strcmp(v, "hotel")){
    return 2;
  }else if(!strcmp(v, "school")){
    return 3;
  }else{
    return 1;
  }
}

  
int
identifyHigh(char* v){
  if(!strcmp(v, "motorway")){
    return 4;
  }else if(!strcmp(v, "road")){
    return 5;
  }else if(!strcmp(v, "pedestrian")){
    return 6;
  }else{
    return 4;
  }
}

int
identifyNatural(char* v){
  if(!strcmp(v, "coastline")){
    return 10;
  }else{
    return 10;
  } 
}

int
identifyGreen(char* v){
  if(!strcmp(v, "landuse=grass")){
    return 11;
  }else if(!strcmp(v, "landuse=forest")){
    return 12;
  }else if(!strcmp(v, "leisure=park")){
    return 13;
  }else{
    return 11;
  }
}

int
identifyWater(char* v){
  if(!strcmp(v, "river")){
    return 7;
  }else if(!strcmp(v, "canal")){
    return 8;
  }else{
    return 7;
  } 
}


node*
searchNode(l_node* nds,long id){
  while(nds->next !=NULL){
    if((nds->cur->attrs->id)==id){
      return nds->cur;
    }
    nds=nds->next;
  }
  return NULL;
}

way*
searchWay(l_way* ways,long id){
  while(ways->next !=NULL){
    if((ways->cur->attrs->id)==id){
      return ways->cur;
    }
    ways=ways->next;
  }
  return NULL;
}

void
freeNodes(l_node* n){
  while(n->next !=NULL){
    freeNode(n->cur);
    n=n->next;
  }
}

void
freeNode(node * n){
  if(n !=NULL)
    free(n->attrs);
  if(n->tags !=NULL)
    freeTags(n->tags);
}

void
freeWays(l_way* ways){
  while(ways->next != NULL){
    freeWay(ways->cur);
    ways=ways->next;
  }
}

void
freeWay(way* way){
  if(way!=NULL){
    free(way->attrs);
    free(way->lnode);
  }
  if(way->ltag !=NULL)
    freeTags(way->ltag);
}

void
freeRelations(l_relation* rls){
  while(rls->next != NULL){
    freeRelation(rls->cur);
    rls=rls->next;
  }
}

void
freeRelation(relation* r){
  if(r!=NULL)
    free(r->attr);
  if(r->lmember!=NULL)
    freeMembers(r->lmember);
  if(r->ltag!=NULL)
    freeTags(r->ltag);
}

void
freeMembers(l_member* lm){
  while(lm->next!=NULL){
    free(lm->cur);
    lm=lm->next;
  }
}

void
freeTags(l_tag* tags){
  while(tags->next !=NULL){
    free(tags->cur);
    tags=tags->next;
  }
}
