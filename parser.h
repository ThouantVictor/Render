#ifndef __PARSER_H__
#define __PARSER_H__
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <string.h>
#include "render_engine.h"

xmlDocPtr doc;
xmlNodePtr cur;

void parseDoc(char *docname, int width, int height);
node* parseNode(xmlDocPtr doc, xmlNodePtr cur);
way* parseWay (l_node* nds,xmlDocPtr doc, xmlNodePtr cur);
relation* parseRelation(l_way* ways, l_node* nds, xmlDocPtr doc, xmlNodePtr cur);

attributs* wayAttributs(xmlNodePtr cur);
attributs* nodeAttributs(xmlNodePtr cur);
bound* boundAttributs(xmlNodePtr cur, int width, int height);
member* memberAttributs(l_way* ways, l_node* nds, xmlNodePtr cur);

tag* tagAttributs(xmlNodePtr cur);
node* identifyNode(l_node* nds,xmlNodePtr cur);

#endif 
