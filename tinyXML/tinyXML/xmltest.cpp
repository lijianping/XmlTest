#include "tinyxml/tinyxml.h"
#include <iostream>
#include <string>
using namespace std;
void dump_to_stdout(const char *file_name) {
	TiXmlDocument doc(file_name);
	bool is_load_ok = doc.LoadFile();
	if (is_load_ok) {
		cout <<endl;
		cout <<file_name <<":" <<endl;
		dump_to_stdout((const char *)&doc);
	} else {
		cout <<"Failed to load file\"%s\"" <<file_name <<endl;
	}
}
const char* getIndent(unsigned int numIndents) {
	static const char *pINDENT="                      +";
	static const unsigned int LENGTH=strlen(pINDENT);
	unsigned int n = numIndents * 2;
	if (n > LENGTH) {
		n = LENGTH;
	}
	return &pINDENT[LENGTH - n];
}

/*
 * The function will get all attributes of an element, print the name and 
 * string value, and if the value can be converted to an integer or double,
 * print that value too.
 * @ return value:
 *		The return is the number of attributes for the element. If there is
 *      no attribute the return value is zero.
 */
int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent) {
	if (!pElement) {
		return 0;
	}
	TiXmlAttribute* pAttrib = pElement->FirstAttribute();
	int i = 0;
	int ival;
	double dval;
	const char* pIndent = getIndent(indent);
	cout <<endl;
	while (pAttrib) {
		cout <<pIndent <<pAttrib->Name() <<": value[" 
			<<pAttrib->Value() <<"]" <<endl;
		if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) {
			cout <<"int = " <<ival <<endl;
		}
		if (pAttrib->QueryDoubleValue(&dval) == TIXML_SUCCESS) {
			cout <<"double = " <<dval <<endl;
		}
		i++;
		pAttrib = pAttrib->Next();   /* Get the next attribute */
	}
	return i;
}
int main() {
	TiXmlDocument document("example2.xml");
	bool is_load_ok = document.LoadFile();
	if (is_load_ok) {
		cout <<"Start getting file content." <<endl;
		TiXmlNode* parent = &document;
		TiXmlNode* child = parent->FirstChild();
		TiXmlText* text;
		for (child = parent->FirstChild(); child != 0; child = child->NextSibling()) {
			int type = child->Type();
			cout <<"type: " <<type <<endl;
			if (TiXmlNode::TINYXML_TEXT == type) {
				text = child->ToText();
				const char *te = text->Value();
				cout <<text->Value() <<endl;
			}
			if (TiXmlNode::TINYXML_ELEMENT == type) {
				TiXmlElement* element = child->ToElement();
				cout <<"element value: " <<element->Value();
			}
		}
	}
	return 0;
}