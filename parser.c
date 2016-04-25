#include "parser.h"

/*****************************************************
parser.c
Parse le document xml et crée les structures de données
necessaire au bon fonctionnement de l'application.
Tel que: 
       - nds : la liste des noeuds 
       -ways : la liste des chemins
       -rls  : la liste des relations 
 ********************************************/

attributs*
nodeAttributs(xmlNodePtr cur){
  long id=-1;
  double lat=-1;
  double longi=-1;
  char* usr="";
  int vis=-1;
  int vers=-1;
  int uid=-1;
  
  for(xmlAttrPtr attr = cur->properties; NULL != attr; attr = attr->next)
    {
      if(!strcmp((char *)(attr->name), "id")){
	id=atol((char *)(attr->children->content));
      }
      if(!strcmp((char *)(attr->name), "lat")){
	lat=strtod((char *)(attr->children->content),NULL);	
      }
      if(!strcmp((char *)(attr->name), "lon")){
	longi=strtod((char *)(attr->children->content),NULL);	
      }
      if(!strcmp((char *)(attr->name), "user")){
	usr=(char *)(attr->children->content);
      }
      if(!strcmp((char *)(attr->name), "visible")){
	if(!strcmp((char *)(attr->children->content), "true"))vis=1;
	else{
	  if (!strcmp((char *)(attr->children->content), "false"))vis=0;
	}
      }
      if(!strcmp((char *)(attr->name), "uid")){
	uid=atoi((char *)(attr->children->content));
      }
      if(!strcmp((char *)(attr->name), "version")){
	vers=atoi((char *)(attr->children->content));
      }
    }
  return initAttributs(id,lat,longi,usr,uid,vis,vers,0);
}

tag*
tagAttributs(xmlNodePtr cur) {
  
  char* k;
  char* v;
  for(xmlAttrPtr attr = cur->properties; NULL != attr; attr = attr->next)
    {
      if(!strcmp((char*)(attr->name), "k")){
        k=(char*)(attr->children->content);
      }
      if(!strcmp((char*)(attr->name), "v")){
	v=(char*)(attr->children->content);
      }
    }
  
  return initTag(k,v);
}

node*
identifyNode(l_node* nds,xmlNodePtr cur){
  long id=-1;
  for(xmlAttrPtr attr = cur->properties; NULL != attr; attr = attr->next)
    {
      if(!strcmp((char*)(attr->name), "ref")){
        id=atol((char*)(attr->children->content));
	return searchNode(nds,id);
      }
    }
  return NULL;
}

attributs*
wayAttributs(xmlNodePtr cur){
  long id=-1;
  char* usr="";
  int vis=-1;
  int vers=-1;
  int uid=-1;
  
  for(xmlAttrPtr attr = cur->properties; NULL != attr; attr = attr->next)
    {
      if(!strcmp((char *)(attr->name), "id")){
	id=atol((char *)(attr->children->content));
      }
      if(!strcmp((char *)(attr->name), "user")){
	usr=(char *)(attr->children->content);
    }
      if(!strcmp((char *)(attr->name), "visible")){
	if(!strcmp((char *)(attr->children->content), "true"))vis=1;
	else{
	  if (!strcmp((char *)(attr->children->content), "false"))vis=0;
	}
      }
      if(!strcmp((char *)(attr->name), "uid")){
	uid=atoi((char *)(attr->children->content));
      }
      if(!strcmp((char *)(attr->name), "version")){
	vers=atoi((char *)(attr->children->content));
      }
    }
  return initAttributs(id,-1,-1,usr,uid,vis,vers,1);
}

bound*
boundAttributs(xmlNodePtr cur, int width, int height){
  double minlat=-1;
  double minlon=-1;
  double maxlat=-1;
  double maxlon=-1;
  for(xmlAttrPtr attr = cur->properties; NULL != attr; attr = attr->next)
    {
      if(!strcmp((char *)(attr->name), "minlat")){
	minlat=strtod((char *)(attr->children->content),NULL);	
      }
      if(!strcmp((char *)(attr->name), "minlon")){
	minlon=strtod((char *)(attr->children->content),NULL);	
      }
      if(!strcmp((char *)(attr->name), "maxlat")){
	maxlat=strtod((char *)(attr->children->content),NULL);	
      }
      if(!strcmp((char *)(attr->name), "maxlon")){
	maxlon=strtod((char *)(attr->children->content),NULL);
      }
    }
  return initBound(minlat,minlon,maxlat,maxlon,width,height);
}

member*
memberAttributs(l_way* ways, l_node* nds, xmlNodePtr cur){
  int type=-1;
  long id=-1;
  char * role="";
  for(xmlAttrPtr attr = cur->properties; NULL != attr; attr = attr->next)
    {
      if(!strcmp((char *)(attr->name), "type")){
	if(!strcmp((char *)(attr->children->content), "node"))	
	  type=0;
	if(!strcmp((char *)(attr->children->content), "way"))	
	  type=1;
      }     
      if(!strcmp((char *)(attr->name), "ref")){
	id=atol((char *)(attr->children->content));	
      }
      if(!strcmp((char *)(attr->name), "role")){
	role=(char *)(attr->children->content);	
      }
    }
  if(type==1)
    return initMember(type,role,searchWay(ways,id),NULL);
  if(type==0)
    return initMember(type,role,NULL,searchNode(nds,id));
  return initMember(type,role,NULL,NULL);
}

relation *
parseRelation(l_way* ways, l_node* nds, xmlDocPtr doc, xmlNodePtr cur){
  attributs* at=wayAttributs(cur);
  cur = cur->xmlChildrenNode;
  l_tag* res_tags=initTags2();
  l_member* res_memb=initMembers2();
  while (cur != NULL) {
    if ((!xmlStrcmp(cur->name, (const xmlChar *)"tag"))) 
      res_tags=addTag(res_tags,tagAttributs(cur));
    if ((!xmlStrcmp(cur->name, (const xmlChar *)"member"))) {
      res_memb=addMember(res_memb,memberAttributs(ways,nds,cur));
    }
    cur = cur->next;
  }
  return initRelation(at,res_memb,res_tags);	
}

node*
parseNode (xmlDocPtr doc, xmlNodePtr cur) {
  attributs* at=nodeAttributs(cur);
  cur = cur->xmlChildrenNode;
  if(cur == NULL){
    return initNode(at,NULL);
  }else{
    l_tag* res=initTags2();
    while (cur != NULL) {
      if ((!xmlStrcmp(cur->name, (const xmlChar *)"tag"))) {
	res=addTag(res,tagAttributs(cur));
      }
      cur = cur->next;
    }
    return initNode(at,res);	
  }
}

way*
parseWay (l_node* nds,xmlDocPtr doc, xmlNodePtr cur) {
  attributs* at=wayAttributs(cur);
  int fstnode=1;
  node* headnode;
  cur = cur->xmlChildrenNode;
  if(cur == NULL){
    return initWay(at,NULL,NULL,0);
  }else{
    l_tag* res_tags=initTags2();
    l_node* res_nodes=initNodes2();
    while (cur != NULL) {
      if ((!xmlStrcmp(cur->name, (const xmlChar *)"tag"))) 
	res_tags=addTag(res_tags,tagAttributs(cur));
      if ((!xmlStrcmp(cur->name, (const xmlChar *)"nd"))) {
	if(fstnode){
	  headnode=identifyNode(nds,cur);
	  res_nodes=addNode(res_nodes,headnode);
	  fstnode=0;
	}
	else
	  res_nodes=addNode(res_nodes,identifyNode(nds,cur));
      }
      cur = cur->next;
    }
    if(headnode->attrs->id==res_nodes->cur->attrs->id)
      return initWay(at,res_nodes,res_tags,1);
    return initWay(at,res_nodes,res_tags,0);
  }
}

void
parseDoc(char *docname, int width, int height) {
  
	nds=initNodes2();
	ways=initWays2();
	rls=initRelations2();
	
	doc = xmlParseFile(docname);
	
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}
	
	cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "osm")) {
	  fprintf(stderr,"document of the wrong type, root node != osm");
	  xmlFreeDoc(doc);
	  return;
	}
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
	  
	  if ((!xmlStrcmp(cur->name, (const xmlChar *)"bounds"))){
	    bnd=boundAttributs(cur,width,height);	    
	  }
	  
	  if((!xmlStrcmp(cur->name, (const xmlChar *)"way"))){
	    ways=addWay(ways,parseWay(nds, doc, cur));
	  }
	  
	  if ((!xmlStrcmp(cur->name, (const xmlChar *)"node"))){
	    nds=addNode(nds,parseNode (doc, cur));
	  }
	  if ((!xmlStrcmp(cur->name, (const xmlChar *)"relation"))){
	    rls=addRelation(rls,parseRelation(ways,nds,doc,cur));
	  }
	  cur = cur->next;
	}
	//printf("              _________Parsing_____Finit__________\n");
	return;
}

